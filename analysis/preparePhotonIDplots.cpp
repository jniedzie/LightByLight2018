//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"

int run;
int ls;
int evtnb;
float photon_Et;
float photon_Eta;
float photon_Phi;
float photon_SCEt;
float photon_SCEta;
float photon_SCPhi;
float photon_SwissCross;
float photon_EtaWidth;
float photon_HoverE;
float photon_SigmaIEtaIEta;
float photon_SeedTime;
int ok_neuexcl;
int ok_zdcexcl;
int ok_chexcl;


/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("run",       &run,         "run/I");
  tr->Branch("ls",        &ls,          "ls/I");
  tr->Branch("evtnb",     &evtnb,       "evtnb/I");
  tr->Branch("photon_Et",           &photon_Et,           "photon_Et/F");
  tr->Branch("photon_Eta",          &photon_Eta,          "photon_Eta/F");
  tr->Branch("photon_Phi",          &photon_Phi,          "photon_Phi/F");
  tr->Branch("photon_SCEt",         &photon_SCEt,         "photon_SCEt/F");
  tr->Branch("photon_SCEta",        &photon_SCEta,        "photon_SCEta/F");
  tr->Branch("photon_SCPhi",        &photon_SCPhi,        "photon_SCPhi/F");
  tr->Branch("photon_SwissCross",   &photon_SwissCross,   "photon_SwissCross/F");
  tr->Branch("photon_EtaWidth",     &photon_EtaWidth,     "photon_EtaWidth/F");
  tr->Branch("photon_HoverE",       &photon_HoverE,       "photon_HoverE/F");
  tr->Branch("photon_SigmaIEtaIEta",&photon_SigmaIEtaIEta,"photon_SigmaIEtaIEta/F");
  tr->Branch("photon_SeedTime",     &photon_SeedTime,     "photon_SeedTime/F");
  tr->Branch("ok_neuexcl",          &ok_neuexcl,          "ok_neuexcl/I");
  tr->Branch("ok_zdcexcl",          &ok_zdcexcl,          "ok_zdcexcl/I");
  tr->Branch("ok_chexcl",           &ok_chexcl,           "ok_chexcl/I");
}

// reset all variables
void ResetVars() {
  run =-999;
  ls=-999;
  evtnb =-999;
  photon_Et = -999;
  photon_Eta = -999;
  photon_Phi = -999;
  photon_SCEt = -999;
  photon_SCEta = -999;
  photon_SCPhi = -999;
  photon_SwissCross = -999;
  photon_EtaWidth = -999;
  photon_HoverE = -999;
  photon_SigmaIEtaIEta = -999;
  photon_SeedTime = -999;
  ok_neuexcl = -999;
  ok_zdcexcl = -999;
  ok_chexcl  = -999;
}
 

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
  
  double swissCross = 1 - (E4/photon->GetEnergyCrystalMax());
  
  if(E4 < 0){
    Log(1)<<"WARNING -- swiss cross cannot be calculated. The event will pass this selection automatically!!\n";
    swissCross = -999999;
  }
  
  return swissCross;
}

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    const map<string, TH2D*> &hists2D,
                    string datasetName, TTree* tr)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    ResetVars();  
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();

    // Check that event passes cuts
    
    // Triggers and exclusivity
    //    if(!event->HasDoubleEG2Trigger()) continue;
    //    if(event->HasChargedTracks()) continue;
    //    if(event->HasAdditionalTowers()) continue;
    
    // Fill histograms for N-1 photon ID cuts
    for(auto photon : event->GetPhysObjects(EPhysObjType::kPhoton)){
      double eta = fabs(photon->GetEta());
      
      // Check basic cuts:
      if(photon->GetEt() < config.params("photonMinEt")) continue;
      if(physObjectProcessor.IsInCrack(*photon)) continue;
      if(physObjectProcessor.IsInHEM(*photon)) continue;
      
      // event variables
      auto genTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
      auto electrons = event->GetPhysObjects(EPhysObjType::kGoodElectron);
      auto muons     = event->GetPhysObjects(EPhysObjType::kGoodMuon);

      ok_neuexcl = (!event->HasAdditionalTowers());
      ok_chexcl  = (genTracks.size()==0 && electrons.size()==0 && muons.size()==0 );
      
      // start filling photon variables
      photon_Et      = photon->GetEt();
      photon_Eta     = photon->GetEta();
      photon_Phi     = photon->GetPhi();
      photon_SCEt    = photon->GetEnergySC()*sin(2.*atan(exp(-photon->GetEtaSC())));
      photon_SCEta   = photon->GetEtaSC();
      photon_SCPhi   = photon->GetPhiSC();
      photon_SwissCross    = getSwisscross(photon);
      photon_EtaWidth      = photon->GetEtaWidth();
      photon_HoverE        = photon->GetHoverE();
      photon_SigmaIEtaIEta = photon->GetSigmaEta2012();
      photon_SeedTime      = photon->GetSeedTime();
      
      // Check swiss-cross:
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
      } //passes ID cuts N-1 plot
      
      
    } //photon
    tr->Fill();
  }//event
} // fill histogram

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
  string configPath  = argv[1];
  string sampleName  = argv[2];
  string inputPath   = argv[3];
  string outputPath  = argv[4];
  
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
  
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *photonIDVars = new TTree("photonIDVars_tree","");
  InitTree(photonIDVars);

  // fill histograms
  map<string, TH1D*> hists = init1Dhists(sampleName);
  map<string, TH2D*> hists2D = init2Dhists(sampleName);
  fillHistograms(events, hists, hists2D, sampleName,photonIDVars );
  
  // save output files
  //TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  outFile->Write();
  for(auto hist : hists)    hist.second->Write();
  for(auto hist : hists2D)  hist.second->Write();
  outFile->Close();
}
