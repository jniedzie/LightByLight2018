//  prepareElectronIDplots.cpp
//
//  Created by Jeremi Niedziela on 09/08/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/electronID_test.root";

vector<EDataset> datasetsToSkip = { kMCcep, kMClbl };

vector<tuple<string, int, double, double>> histParams = {
  // title                     nBins min   max
  {"nMissingHits"           , 10    , 0   , 10  },
  
  {"HoverEbarrel"           , 500   , 0   , 2.5 },
  {"HoverEendcap"           , 500   , 0   , 2.5 },
  
  {"relIsoWithEAbarrel"     , 240   , 0   , 120 },
  {"relIsoWithEAendcap"     , 240   , 0   , 120 },
  
  {"dEtaSeedbarrel"         , 4000  , 0   , 4   },
  {"dEtaSeedendcap"         , 4000  , 0   , 4   },
};

vector<tuple<string, int, double, double, int, double, double>> histParams2D = {
  // title         nBinsX minX   maxX   nBinsY minY  maxY
//  {"HoverEmapNum" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
//  {"HoverEmapDen" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
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
    
    // Triggers
//    if(!event->HasSingleEG3Trigger()) continue;
    
    // Fill histograms for electron ID cuts
    for(auto electron : event->GetElectrons()){
      double eta = fabs(electron->GetEtaSC());
      
      // Check basic cuts:
      if(electron->GetPt() < config.params("electronMinPt")) continue;
      if(eta > config.params("ecalCrackMin") &&
         eta < config.params("ecalCrackMax"))   continue;
      if(eta > config.params("electronMaxEta")) continue;
      
      // Check for HEM issue
      if(electron->GetEtaSC() < -minEtaEE &&
         electron->GetPhiSC() > config.params("ecalHEMmin") &&
         electron->GetPhiSC() < config.params("ecalHEMmax")) continue;
      
      
      hists.at("nMissingHits"+datasetName)->Fill(electron->GetNmissingHits());
      
      if(electron->GetNmissingHits() > config.params("electronMaxNmissingHits")) continue;
      
      if((eta < maxEtaEB)){
        
        bool passesHoverE   = electron->GetHoverE() <= config.params("electronMaxHoverEbarrel");
        bool passesRelIso   = electron->GetRelIsoWithEA() <= 0.112+0.506/electron->GetPt();
        bool passesDetaSeed = electron->GetDetaSeed() <= config.params("electronMaxDetaSeedBarrel");
        
        if(passesHoverE && passesDetaSeed) hists.at("relIsoWithEAbarrel"+datasetName)->Fill(electron->GetRelIsoWithEA());
        
        if(passesHoverE && passesRelIso)
          hists.at("dEtaSeedbarrel"+datasetName)->Fill(fabs(electron->GetDetaSeed()));
        
        if(passesRelIso && passesDetaSeed)
          hists.at("HoverEbarrel"+datasetName)->Fill(electron->GetHoverE());
      }
      else if((eta < maxEtaEE)){
        
        bool passesHoverE   = electron->GetHoverE() <= config.params("electronMaxHoverEendcap");
        bool passesRelIso   = electron->GetRelIsoWithEA() <= 0.108+0.963/electron->GetPt();
        bool passesDetaSeed = electron->GetDetaSeed() <= config.params("electronMaxDetaSeedEndcap");
        
        if(passesHoverE && passesDetaSeed)
          hists.at("relIsoWithEAendcap"+datasetName)->Fill(electron->GetRelIsoWithEA());
        
        if(passesHoverE && passesRelIso)
          hists.at("dEtaSeedendcap"+datasetName)->Fill(fabs(electron->GetDetaSeed()));
        
        if(passesRelIso && passesDetaSeed)
          hists.at("HoverEendcap"+datasetName)->Fill(electron->GetHoverE());
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
    if(find(datasetsToSkip.begin(), datasetsToSkip.end(), dataset) != datasetsToSkip.end()) continue;
    
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
    
    unique_ptr<EventProcessor> events;
    if(argc == 8){
      events = unique_ptr<EventProcessor>(new EventProcessor(inputPaths[dataset]));
    }
    else{
      events = unique_ptr<EventProcessor>(new EventProcessor(dataset));
    }
    
    fillHistograms(events, hists, hists2D, name);
    
    outFile->cd();
    for(auto hist : hists)    hist.second->Write();
    for(auto hist : hists2D)  hist.second->Write();
  }
  
  outFile->Close();
}

