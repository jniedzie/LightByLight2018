//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/showerShape.root";

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
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params["maxEvents"]) break;
    
    auto event = events->GetEvent(iEvent);
    
    for(auto photon : event->GetPhotonSCs()){
//      if(photon->GetEt() < config.params["minEt"]) continue;

      if(fabs(photon->GetEta()) < maxEtaEB ){
        hists.at("showerShapeBarrel"+datasetName)->Fill(photon->GetEtaWidth());
        hists.at("etaBarrel"+datasetName)->Fill(fabs(photon->GetEta()));
        
        if(photon->GetEtaWidth() < 0.001){
          hists.at("etaLowWidthBarrel"+datasetName)->Fill(fabs(photon->GetEta()));
          hists.at("etLowWidthBarrel"+datasetName)->Fill(photon->GetEt());
        }
      }
      else if(fabs(photon->GetEta()) < maxEtaEE){
        hists.at("showerShapeEndcap"+datasetName)->Fill(photon->GetEtaWidth());
        hists.at("etaEndcap"+datasetName)->Fill(fabs(photon->GetEta()));
        
        if(photon->GetEtaWidth() < 0.001){
          hists.at("etaLowWidthEndcap"+datasetName)->Fill(fabs(photon->GetEta()));
          hists.at("etLowWidthEndcap"+datasetName)->Fill(photon->GetEt());
        }
      }
      if(fabs(photon->GetEta()) > minEtaEE && fabs(photon->GetEta()) < 2.3){
        hists.at("showerShapeEndcap2p3"+datasetName)->Fill(photon->GetEtaWidth());
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
