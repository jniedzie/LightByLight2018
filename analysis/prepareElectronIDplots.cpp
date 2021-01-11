//  prepareElectronIDplots.cpp
//
//  Created by Jeremi Niedziela on 09/08/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"

bool requirePassingOtherCuts = false;

vector<EDataset> datasetsToSkip = {
  kMCcep,
  kMClbl,
//  kMCqedSL
};

vector<tuple<string, int, double, double>> histParams = {
  // title                     nBins min   max
  {"nMissingHits"             , 10    , 0   , 10  },
  
  {"HoverE_Barrel"            , 1000  , 0   , 2.5 },
  {"HoverE_Endcap"            , 1000  , 0   , 2.5 },
  
  {"chargedIsoBarrel"         , 2500  , 0   , 15  },
  {"photonIsoBarrel"          , 2500  , 0   , 15  },
  {"neutralIsoBarrel"         , 2500  , 0   , 15  },
  {"chargedIsoEndcap"         , 2500  , 0   , 15  },
  {"photonIsoEndcap"          , 2500  , 0   , 15  },
  {"neutralIsoEndcap"         , 2500  , 0   , 15  },
  {"relIsoWithEA_Barrel"      , 240   , 0   , 120 },
  {"relIsoWithEA_Endcap"      , 240   , 0   , 120 },
  
  {"dEtaSeedBarrel"           , 1000  , 0   , 1   },
  {"dEtaSeedEndcap"           , 1000  , 0   , 1   },
};

vector<tuple<string, int, double, double, int, double, double>> histParams2D = {
  // title         nBinsX minX   maxX   nBinsY minY  maxY
//  {"HoverEmapNum" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
//  {"HoverEmapDen" , 314 , -3.14 , 3.14 , 460 , -2.3 , 2.3 },
};

/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters:\n";
    Log(0)<<"./eleIDVariables configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }
  
  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
}


void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    const map<string, TH2D*> &hists2D,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    // Triggers
//    if(!event->HasSingleEG3Trigger()) continue;
    
    // Fill histograms for electron ID cuts
    for(auto electron : event->GetPhysObjects(EPhysObjType::kElectron)){
      double eta = fabs(electron->GetEtaSC());
      
      // Check basic cuts:
      if(electron->GetPt() < config.params("electronMinPt")) continue;
      if(eta > config.params("electronMaxEta")) continue;
      if(physObjectProcessor.IsInCrack(*electron)) continue;
      if(physObjectProcessor.IsInHEM(*electron)) continue;
      
      hists.at("nMissingHits"+datasetName)->Fill(electron->GetNmissingHits());
      
      if(electron->GetNmissingHits() > config.params("electronMaxNmissingHits")) continue;
      
      string subdet = "";
      if((eta < maxEtaEB)) subdet = "Barrel";
      else if((eta < maxEtaEE)) subdet = "Endcap";
      
      bool passesHoverE     = electron->GetHoverE()     < config.params("electronMaxHoverE_"+subdet);
      bool passesDetaSeed   = electron->GetDetaSeed()   < config.params("electronMaxDetaSeed"+subdet);
      bool passesIsolation  = electron->GetChargedIso() < config.params("electronMaxChargedIso"+subdet) &&
                              electron->GetPhotonIso()  < config.params("electronMaxPhotonIso"+subdet)  &&
                              electron->GetNeutralIso() < config.params("electronMaxNeutralIso"+subdet);
      
      hists.at("chargedIso"+subdet+datasetName)->Fill(electron->GetChargedIso());
      hists.at("photonIso"+subdet+datasetName)->Fill(electron->GetPhotonIso());
      hists.at("neutralIso"+subdet+datasetName)->Fill(electron->GetNeutralIso());
      hists.at("relIsoWithEA_"+subdet+datasetName)->Fill(electron->GetRelIsoWithEA());
      hists.at("dEtaSeed"+subdet+datasetName)->Fill(fabs(electron->GetDetaSeed()));
      hists.at("HoverE_"+subdet+datasetName)->Fill(electron->GetHoverE());
      
      if(passesHoverE && passesDetaSeed){
        hists.at("chargedIso"+subdet+datasetName+"_withCuts")->Fill(electron->GetChargedIso());
        hists.at("photonIso"+subdet+datasetName+"_withCuts")->Fill(electron->GetPhotonIso());
        hists.at("neutralIso"+subdet+datasetName+"_withCuts")->Fill(electron->GetNeutralIso());
      }
      if(passesHoverE && passesDetaSeed && passesIsolation){
        hists.at("relIsoWithEA_"+subdet+datasetName+"_withCuts")->Fill(electron->GetRelIsoWithEA());
      }
      if(passesHoverE && passesIsolation){
        hists.at("dEtaSeed"+subdet+datasetName+"_withCuts")->Fill(fabs(electron->GetDetaSeed()));
      }
      if(passesDetaSeed && passesIsolation){
        hists.at("HoverE_"+subdet+datasetName+"_withCuts")->Fill(electron->GetHoverE());
      }
    }
  }
}


/// Application starting point
int main(int argc, char* argv[])
{
  string configPath, inputPath, outputPath, sampleName;
  ReadInputArguments(argc, argv, configPath, inputPath, outputPath, sampleName);

  config = ConfigManager(configPath);
  EDataset dataset = datasetForName.at(sampleName);
 
  TH1D *hist = new TH1D("hist","",9,1,10);
 
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
   
  map<string, TH1D*> hists;
  map<string, TH2D*> hists2D;
  
  string name = datasetName.at(dataset);
  
  for(auto params : histParams){
    string title = get<0>(params)+name;
    hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
    title += "_withCuts";
    hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
  }
  for(auto params : histParams2D){
    string title = get<0>(params)+name;
    hists2D[title] = new TH2D(title.c_str(), title.c_str(),
			      get<1>(params), get<2>(params), get<3>(params),
			      get<4>(params), get<5>(params), get<6>(params));
  }
  
  Log(0)<<"Creating "<<name<<" plots\n";
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  fillHistograms(events, hists, hists2D, name);
  
  outFile->cd();
  for(auto hist : hists)    hist.second->Write();
  for(auto hist : hists2D)  hist.second->Write();
  
  
  outFile->Close();
}

