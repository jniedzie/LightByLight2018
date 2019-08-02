//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/photonID.root";

vector<tuple<string, int, double, double>> histParams = {
// title                     nBins min   max
  {"showerShapeBarrel"      , 100 , 0   , 0.1 },
  {"showerShapeEndcap"      , 100 , 0   , 0.1 },
  {"showerShapeEndcap2p3"   , 100 , 0   , 0.1 },
  {"etaLowWidthBarrel"      , 100 , 0   , 2.0 },
  {"etaBarrel"              , 100 , 0   , 2.0 },
  {"etLowWidthBarrel"       , 100 , 0   , 10  },
  {"etaLowWidthEndcap"      , 100 , 1.0 , 3.2 },
  {"etaEndcap"              , 100 , 1.0 , 3.2 },
  {"etLowWidthEndcap"       , 100 , 0   , 10  },
  {"HoverE"                 , 300 , 0   , 0.6 },
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    // Check that event passes cuts
    
    // Trigger
    if(!event->HasDoubleEG2Trigger()) continue;
    
    // Charged exclusivity
    if(event->HasChargedTracks()) continue;
    
    // Neutral exclusivity
    if(event->HasAdditionalTowers()) continue;
    
    // Fill histograms for N-1 photon ID cuts
    for(auto photon : event->GetPhotons()){
      double eta = fabs(photon->GetEta());
      
      // Check basic cuts:
      if(photon->GetEt() < config.params("photonMinEt")) continue;
      if(eta > config.params("photonMaxEta")) continue;
      if(eta > config.params("ecalCrackMin") &&
         eta < config.params("ecalCrackMax"))   continue;
      
      // Fill in shower shape histograms
      if(photon->GetHoverE() < config.params("photonMaxHoverE")){
        
        if(eta < maxEtaEB ){
          hists.at("showerShapeBarrel"+datasetName)->Fill(photon->GetEtaWidth());
          hists.at("etaBarrel"+datasetName)->Fill(eta);
          
          if(photon->GetEtaWidth() < 0.001){
            hists.at("etaLowWidthBarrel"+datasetName)->Fill(eta);
            hists.at("etLowWidthBarrel"+datasetName)->Fill(photon->GetEt());
          }
        }
        else if(eta < maxEtaEE){
          hists.at("showerShapeEndcap"+datasetName)->Fill(photon->GetEtaWidth());
          hists.at("etaEndcap"+datasetName)->Fill(eta);
          
          if(photon->GetEtaWidth() < 0.001){
            hists.at("etaLowWidthEndcap"+datasetName)->Fill(eta);
            hists.at("etLowWidthEndcap"+datasetName)->Fill(photon->GetEt());
          }
        }
        if(eta > minEtaEE && eta < 2.3){
          hists.at("showerShapeEndcap2p3"+datasetName)->Fill(photon->GetEtaWidth());
        }
      }
      
      // Fill in H/E plots
      if((eta < maxEtaEB &&
          photon->GetEtaWidth()  < config.params("photonMaxEtaWidthBarrel")) ||
         (eta > minEtaEE && eta < maxEtaEE &&
          photon->GetEtaWidth()  < config.params("photonMaxEtaWidthEndcap"))){
      
           hists.at("HoverE"+datasetName)->Fill(photon->GetHoverE());
      }
    }
  }
}

int main()
{
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
 
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(EDataset dataset : datasets){
    string name = datasetName.at(dataset);
    
    for(auto &[histName, nBins, min, max] : histParams){
      string title = histName+name;
      hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
    }
    
    cout<<"Creating "<<name<<" plots"<<endl;
    
    unique_ptr<EventProcessor> events(new EventProcessor(dataset));
    fillHistograms(events, hists, name);
    
    outFile->cd();
    for(auto &[name, hist] : hists) hist->Write();
  }

  outFile->Close();
}
