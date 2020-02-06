//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/photonID_test.root";

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
  
  {"HoverEbarrel"           , 300 , 0   , 0.6 },
  {"HoverEendcap"           , 300 , 0   , 0.6 },
  {"etaHighHoverE"          , 320 , 0   , 3.2 },
  {"etaLowHoverE"           , 320 , 0   , 3.2 },
};

vector<tuple<string, int, double, double, int, double, double>> histParams2D = {
  // title         nBinsX minX   maxX   nBinsY minY  maxY
  {"HoverEmapNum" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
  {"HoverEmapDen" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    const map<string, TH2D*> &hists2D,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    // Check that event passes cuts
    
    // Triggers and exclusivity
//    if(!event->HasDoubleEG2Trigger()) continue;
//    if(event->HasChargedTracks()) continue;
//    if(event->HasAdditionalTowers()) continue;
    
    // Fill histograms for N-1 photon ID cuts
    for(auto photon : event->GetPhotons()){
      double eta = fabs(photon->GetEta());
      
      // Check basic cuts:
      if(photon->GetEt() < config.params("photonMinEt")) continue;
      if(eta > config.params("ecalCrackMin") &&
         eta < config.params("ecalCrackMax"))   continue;
      
      // Check for HEM issue
      if(photon->GetEta() < -minEtaEE &&
         photon->GetPhi() > config.params("ecalHEMmin") &&
         photon->GetPhi() < config.params("ecalHEMmax")) continue;
      
      // Fill in shower shape histograms
      if((eta < maxEtaEB) && (photon->GetHoverE() < config.params("photonMaxHoverEbarrel"))){
        hists.at("showerShapeBarrel"+datasetName)->Fill(photon->GetEtaWidth());
        hists.at("etaBarrel"+datasetName)->Fill(eta);
        
        if(photon->GetEtaWidth() < 0.001){
          hists.at("etaLowWidthBarrel"+datasetName)->Fill(eta);
          hists.at("etLowWidthBarrel"+datasetName)->Fill(photon->GetEt());
        }
      }
      else if((eta < maxEtaEE) && (photon->GetHoverE() < config.params("photonMaxHoverEendcap"))){
        hists.at("showerShapeEndcap"+datasetName)->Fill(photon->GetEtaWidth());
        hists.at("etaEndcap"+datasetName)->Fill(eta);
        
        if(photon->GetEtaWidth() < 0.001){
          hists.at("etaLowWidthEndcap"+datasetName)->Fill(eta);
          hists.at("etLowWidthEndcap"+datasetName)->Fill(photon->GetEt());
        }
        if(eta < 2.3) hists.at("showerShapeEndcap2p3"+datasetName)->Fill(photon->GetEtaWidth());
      }
      
      // for other distributions, check already that |η| < 2.3
      if(eta > config.params("photonMaxEta")) continue;
      
      // Fill in H/E plots
      if((eta < maxEtaEB) && (photon->GetEtaWidth()  < config.params("photonMaxEtaWidthBarrel"))){
        hists.at("HoverEbarrel"+datasetName)->Fill(photon->GetHoverE());
        
        if(photon->GetHoverE() > 0.15) hists.at("etaHighHoverE"+datasetName)->Fill(eta);
        else                           hists.at("etaLowHoverE"+datasetName)->Fill(eta);
        
        hists2D.at("HoverEmapNum"+datasetName)->Fill(photon->GetPhi(), photon->GetEta(), photon->GetHoverE());
        hists2D.at("HoverEmapDen"+datasetName)->Fill(photon->GetPhi(), photon->GetEta());
      }
      else if((eta < maxEtaEE) && (photon->GetEtaWidth()  < config.params("photonMaxEtaWidthEndcap"))){
        hists.at("HoverEendcap"+datasetName)->Fill(photon->GetHoverE());
        
        if(photon->GetHoverE() > 0.15) hists.at("etaHighHoverE"+datasetName)->Fill(eta);
        else                           hists.at("etaLowHoverE"+datasetName)->Fill(eta);
        
        hists2D.at("HoverEmapNum"+datasetName)->Fill(photon->GetPhi(), photon->GetEta(), photon->GetHoverE());
        hists2D.at("HoverEmapDen"+datasetName)->Fill(photon->GetPhi(), photon->GetEta());
      }
    }
  }
}

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 8){
    cout<<"This app requires 0 or 7 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPathData inputPathLbL inputPathQED_SC inputPathQED_SL inputPathCEP outputPath"<<endl;
    exit(0);
  }
  
  map<EDataset, string> inputPaths;
  
  if(argc == 8){
    configPath           = argv[1];
    inputPaths[kData]    = argv[2];
    inputPaths[kMClbl]   = argv[3];
    inputPaths[kMCqedSC] = argv[4];
    inputPaths[kMCqedSL] = argv[5];
    inputPaths[kMCcep]   = argv[6];
    outputPath           = argv[7];
  }
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  map<string, TH2D*> hists2D;
 
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(EDataset dataset : datasets){
    string name = datasetName.at(dataset);
    
    for(auto params : histParams){
      string title = get<0>(params)+name;
      hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
    }
    for(auto params : histParams2D){
      string title = get<0>(params)+name;
      hists2D[title] = new TH2D(title.c_str(), title.c_str(),
                                get<1>(params), get<2>(params), get<3>(params),
                                get<4>(params), get<5>(params), get<6>(params));
    }
    
    cout<<"Creating "<<name<<" plots"<<endl;
    auto events = make_unique<EventProcessor>(argc == 8 ? inputPaths[dataset] : inFileNames.at(dataset));
    fillHistograms(events, hists, hists2D, name);
    
    outFile->cd();
    for(auto hist : hists)    hist.second->Write();
    for(auto hist : hists2D)  hist.second->Write();
  }

  outFile->Close();
}
