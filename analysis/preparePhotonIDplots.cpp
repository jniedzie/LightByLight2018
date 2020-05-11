//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/photonID_test.root";

vector<EDataset> datasetsToAnalyze = {
  kData_LbLsignal,
  kMCqedSC,
  kMClbl,
  kMCcep
  
//  kData,
//  kMClbl,
//  kMCqedSC,
//  kMCqedSL,
//  kMCcep,
};

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
  
  {"swissCrossBarrel"       , 1000, 0.0 , 1.0 },
  {"swissCrossEndcap"       , 1000, 0.0 , 1.0 },
  
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

double getSwisscross(shared_ptr<PhysObject> photon)
{
  double E4 = photon->GetEnergyCrystalTop() +
  photon->GetEnergyCrystalBottom() +
  photon->GetEnergyCrystalLeft() +
  photon->GetEnergyCrystalRight();
  
  double swissCross = E4/photon->GetEnergyCrystalMax();
  
  if(E4 < 0){
    Log(1)<<"WARNING -- swiss cross cannot be calculated. The event will pass this selection automatically!!\n";
    swissCross = 999999;
  }
  
  return swissCross;
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
    
    // Check that event passes cuts
    
    // Triggers and exclusivity
    //    if(!event->HasDoubleEG2Trigger()) continue;
    //    if(event->HasChargedTracks()) continue;
    //    if(event->HasAdditionalTowers()) continue;
    
    // Fill histograms for N-1 photon ID cuts
    for(auto photon : event->GetPhysObjects(kPhoton)){
      double eta = fabs(photon->GetEta());
      
      // Check basic cuts:
      if(photon->GetEt() < config.params("photonMinEt")) continue;
      if(eta > config.params("ecalCrackMin") &&
         eta < config.params("ecalCrackMax"))   continue;
      
      // Check for HEM issue
      if(photon->GetEta() < -minEtaEE &&
         photon->GetPhi() > config.params("ecalHEMmin") &&
         photon->GetPhi() < config.params("ecalHEMmax")) continue;
      
      double swissCross = getSwisscross(photon);
      double hOverE     = photon->GetHoverE();
      double etaWidth   = photon->GetEtaWidth();
      
      bool passesSwissCross   = swissCross > config.params("photonMinSwissCross");
      
      string suffixUpper, suffixLower;
      
      if(eta < maxEtaEB){
        suffixUpper = "Barrel";
        suffixLower = "barrel";
      }
      else if(eta < maxEtaEE){
        suffixUpper = "Endcap";
        suffixLower = "endcap";
      }
      
      bool passesHoverE       = hOverE     < config.params("photonMaxHoverE"+suffixLower);
      bool passesSigmaEtaEta  = etaWidth   > config.params("photonMaxEtaWidth"+suffixUpper);
      
      if(passesSwissCross && passesHoverE){
        hists.at("showerShape"+suffixUpper+datasetName)->Fill(etaWidth);
      }
      if(passesSwissCross && passesSigmaEtaEta){
        hists.at("HoverE"+suffixLower+datasetName)->Fill(hOverE);
        hists2D.at("HoverEmapNum"+datasetName)->Fill(photon->GetPhi(), photon->GetEta(), hOverE);
        hists2D.at("HoverEmapDen"+datasetName)->Fill(photon->GetPhi(), photon->GetEta());
      }
      
      if(passesHoverE && passesSigmaEtaEta){
        hists.at("swissCross"+suffixUpper+datasetName)->Fill(swissCross);
      }
      
      if(passesSwissCross && passesHoverE && passesSigmaEtaEta){
        hists.at("eta"+suffixUpper+datasetName)->Fill(eta);
        
        if(etaWidth < 0.001){
          hists.at("etaLowWidth"+suffixUpper+datasetName)->Fill(eta);
          hists.at("etLowWidth"+suffixUpper+datasetName)->Fill(photon->GetEt());
        }
      }
    }
  }
}

map<string, TH1D*> init1Dhists(string name)
{
  map<string, TH1D*> hists;
  for(auto params : histParams){
    string title = get<0>(params)+name;
    hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
  }
  return hists;
}

map<string, TH2D*> init2Dhists(string name)
{
  map<string, TH2D*> hists;
  
  for(auto params : histParams2D){
    string title = get<0>(params)+name;
    hists[title] = new TH2D(title.c_str(), title.c_str(),
                            get<1>(params), get<2>(params), get<3>(params),
                            get<4>(params), get<5>(params), get<6>(params));
  }
  return hists;
}

int main(int argc, char* argv[])
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters.\n";
    Log(0)<<"./getEfficienciesData configPath sampleName inputPath outputPath\n";
    exit(0);
  }
 
  // read input arguments
  string inputPath = "";
  string sampleName = "";
  string outputPath = "";
  
  if(argc == 5){
    configPath  = argv[1];
    sampleName  = argv[2];
    inputPath   = argv[3];
    outputPath  = argv[4];
  }
  
  // create config manager
  config = ConfigManager(configPath);
  EDataset dataset;
  
  // load events from input file
  if(sampleName == "Data")          dataset = kData;
  else if(sampleName == "QED_SC")   dataset = kMCqedSC;
  else if(sampleName == "QED_SL")   dataset = kMCqedSL;
  else if(sampleName == "LbL")      dataset = kMClbl;
  else if(sampleName == "CEP")      dataset = kMCcep;
  else{
    Log(0)<<"Unrecognised sample name: "<<sampleName<<"!!\n";
    exit(0);
  }
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  // fill histograms
  map<string, TH1D*> hists = init1Dhists(sampleName);
  map<string, TH2D*> hists2D = init2Dhists(sampleName);
  fillHistograms(events, hists, hists2D, sampleName);
  
  // save output files
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  for(auto hist : hists)    hist.second->Write();
  for(auto hist : hists2D)  hist.second->Write();
  outFile->Close();
}
