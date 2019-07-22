//  getDiphotonEfficiency
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Calculates diphoton efficiency, defined as:
// Eff^{\gamma\gamma} = N^{reco}/N^{gen}
//
// where:
//
// N^{reco}: number of reconstructed diphoton events with E_T^{reco} > 2 GeV, |\eta^{reco}|<2.4,
// passing trigger, identification and exclusivity cuts
//
// N^{gen}: number of generated events with E_T^{gen} > 2 GeV, |\eta^{gen}|<2.4

#include "Helpers.hpp"

const double maxEta = 2.4;
const double minEt = 2; // GeV

const string inFileName = "ntuples/ntuples_mc_lbl_small_sample.root";

// List of allowed LbL triggers
vector<string> triggerNames = {
  "HLT_HIUPC_DoubleEG5_NotMBHF2AND_v1",
  "HLT_HIUPC_SingleEG3_NotMBHF2AND_v1"
};

// You can limit number of events analyzed here:
const int maxEvents = 10000;


int main()
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inFileName.c_str());
  TTree *eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  TTree *hltTree = (TTree*)inFile->Get("hltanalysis/HltTree");
  
  // Setup branches
  vector<int> triggers(triggerNames.size());
  
  int nGenPhotons;
  vector<double> *genEta = nullptr;
  vector<double> *genEt = nullptr;
  
  int nRecPhotonSCs;
  vector<double> *photonSCEta = nullptr;;
  vector<double> *photonSCEt = nullptr;
  
  for(int iTrigger=0; iTrigger<triggerNames.size(); iTrigger++){
    hltTree->SetBranchAddress(triggerNames[iTrigger].c_str(), &triggers[iTrigger]);
  }
  eventTree->SetBranchAddress("nMC"   , &nGenPhotons);
  eventTree->SetBranchAddress("mcEta" , &genEta);
  eventTree->SetBranchAddress("mcEt"  , &genEt);
  
  eventTree->SetBranchAddress("nPho"    , &nRecPhotonSCs);
  eventTree->SetBranchAddress("phoSCEta", &photonSCEta);
  eventTree->SetBranchAddress("phoSCEt" , &photonSCEt);
  
  int nGenEvents = 0;
  int nRecEvents = 0;
  
  cout<<"N events in the tree: "<<eventTree->GetEntries()<<endl;
  
  for(int iEvent=0; iEvent<eventTree->GetEntries(); iEvent++){
    if(iEvent >= maxEvents) break;
    
    eventTree->GetEntry(iEvent);
    hltTree->GetEntry(iEvent);
    
    // Check if gen event is within η and Et limits
    int nGenPhotonsPassing=0;
    
    for(int iGenPhoton=0; iGenPhoton<nGenPhotons; iGenPhoton++){
      if((fabs(genEta->at(iGenPhoton)) < maxEta) &&
         genEt->at(iGenPhoton) > minEt){
        nGenPhotonsPassing++;
      }
    }
    if(nGenPhotonsPassing == 2) nGenEvents++;
    
    // Check if rec event is within η and Et limits, has LbL trigger and passes other selections
    bool triggerFired=false;
    
    for(int iTrigger=0; iTrigger<triggerNames.size(); iTrigger++){
      if(triggers[iTrigger]){
        triggerFired = true;
        break;
      }
    }
    
    if(!triggerFired) continue;
    
    int nRecPhotonSCsPassing = 0;
    for(int iRecPhotonSC=0; iRecPhotonSC<nRecPhotonSCs; iRecPhotonSC++){
      if(fabs(photonSCEta->at(iRecPhotonSC)) < maxEta &&
         photonSCEt->at(iRecPhotonSC) > minEt){
        nRecPhotonSCsPassing++;
      }
    }
    
    if(nRecPhotonSCsPassing != 2) continue;
    
    // Here check also other selections!
    // ...
    
    nRecEvents++;
  }
  
  cout<<"N gen events within limits: "<<nGenEvents<<endl;
  cout<<"N rec events passing selection: "<<nRecEvents<<endl;
  
  cout<<"Diphoton efficiency : "<<(double)nRecEvents/nGenEvents<<endl;
  
  return 0;
}

