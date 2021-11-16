//  SelectQEDEvents
//
//  Created by Ruchi Chudasama on 04/03/2021
//
//  Selects diphoton events in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"
#include "TLorentzVector.h"
#include "Event.hpp"

int ireg(double et, double eta);
double SF_reco(double et, double eta);
double SF_uncert_reco(double et, double eta);
double SF_trig(double et, double eta);
double SF_uncert_trig(double et, double eta);

const double eleMass = 0.5109989461e-3;
Double_t getDR  ( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t getDETA(Double_t eta1, Double_t eta2);

int nGen;
float gen_Et[10];
float gen_Eta[10];
float gen_Phi[10];
float gen_diPhotonPt;
float gen_diPhotonM;

int run;
int ls;
int evtnb;
int    nPho;
float  phoEt[100];
float  phoEta[100];
float  phoPhi[100];
float  phoSCEt[100];
float  phoSCEta[100];
float  phoSCPhi[100];
float  phoEtaWidth[100];
float  phoHoverE[100];
float  phoEnergyTop[100];
float  phoEnergyBottom[100];
float  phoEnergyLeft[100];
float  phoEnergyRight[100];
float  phoEnergyCrysMax[100];
float  phoSwissCross[100];
float  phoSeedTime[100];
float  phoSigmaIEta[100];

int    nGoodPho;
float  goodPhoEt[100];
float  goodPhoEta[100];
float  goodPhoPhi[100];
float  goodPhoSCEt[100];
float  goodPhoSCEta[100];
float  goodPhoSCPhi[100];
float  goodPhoEtaWidth[100];
float  goodPhoHoverE[100];
float  goodPhoEnergyTop[100];
float  goodPhoEnergyBottom[100];
float  goodPhoEnergyLeft[100];
float  goodPhoEnergyRight[100];
float  goodPhoEnergyCrysMax[100];
float  goodPhoSwissCross[100];
float  goodPhoSeedTime[100];
float  goodPhoSigmaIEta[100];

float  diPhotonPt;
float  diPhotonM;

int nMissPho;
float missedPhotonEta[2];
float missedPhotonPhi[2];

int nTrk;
float trkPt[100];
float trkEta[100];
float trkPhi[100];
int trkCharge[100];
float trkPurity[100];
float trkChi2[100];
float trkD0[100];
float trkDxy[100];
float trkDz[100];
float trkDxyErr[100];
float trkDzErr[100];
float trkVx[100];
float trkVy[100];
float trkVz[100];

int ok_neuexcl;
int ok_zdcexcl;
int ok_chexcl;
int ok_chexcl_tracks;
int ok_chexcl_electrons;
int ok_chexcl_muons;
int ok_chexcl_goodtracks;
int ok_chexcl_goodelectrons;
int ok_twophotons;
int ok_twogoodphotons;
int ok_twophotons_and_twogoodphotons;

float SFweight_reco[16];
float SFweight_trig[16];
int   nPixelCluster;
int   nPixelRecHits;

/// initialise gen tree
void InitGenTree(TTree *genTree) {
  genTree->Branch("nGen", &nGen, "nGen/I");
  genTree->Branch("gen_Et",  gen_Et, "gen_Et[nGen]/F");
  genTree->Branch("gen_Eta", gen_Eta, "gen_Eta[nGen]/F");
  genTree->Branch("gen_Phi", gen_Phi, "gen_Phi[nGen]/F");
  genTree->Branch("gen_diPhotonPt", &gen_diPhotonPt, "gen_diPhotonPt/F");
  genTree->Branch("gen_diPhotonM", &gen_diPhotonM, "gen_diPhotonM/F");
}


/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("run",                 &run,           "run/I");
  tr->Branch("ls",                  &ls,            "ls/I");
  tr->Branch("evtnb",               &evtnb,         "evtnb/I");
  tr->Branch("nPho",                &nPho,          "nPho/I");
  tr->Branch("phoEt",             phoEt,       "phoEt[nPho]/F");
  tr->Branch("phoEta",            phoEta,      "phoEta[nPho]/F");
  tr->Branch("phoPhi",            phoPhi,      "phoPhi[nPho]/F");
  tr->Branch("phoSCEt",           phoSCEt,     "phoSCEt[nPho]/F");
  tr->Branch("phoSCEta",          phoSCEta,    "phoSCEta[nPho]/F");
  tr->Branch("phoSCPhi",          phoSCPhi,    "phoSCPhi[nPho]/F");
  tr->Branch("phoEtaWidth",       phoEtaWidth,  "phoEtaWidth[nPho]/F");
  tr->Branch("phoHoverE",         phoHoverE,    "phoHoverE[nPho]/F");
  tr->Branch("phoEnergyTop",      phoEnergyTop, "phoEnergyTop[nPho]/F");
  tr->Branch("phoEnergyBottom",   phoEnergyBottom, "phoEnergyBottom[nPho]/F");
  tr->Branch("phoEnergyLeft",     phoEnergyLeft,   "phoEnergyLeft[nPho]/F");
  tr->Branch("phoEnergyRight",    phoEnergyRight,  "phoEnergyRight[nPho]/F");
  tr->Branch("phoEnergyCrysMax",  phoEnergyCrysMax,"phoEnergyCrysMax[nPho]/F");
  tr->Branch("phoSwissCross",     phoSwissCross,   "phoSwissCross[nPho]/F");
  tr->Branch("phoSeedTime",       phoSeedTime,     "phoSeedTime[nPho]/F");
  tr->Branch("phoSigmaIEta",      phoSigmaIEta,    "phoSigmaIEta[nPho]/F");

  tr->Branch("nGoodPho",                &nGoodPho,          "nGoodPho/I");
  tr->Branch("goodPhoEt",             goodPhoEt,       "goodPhoEt[nGoodPho]/F");
  tr->Branch("goodPhoEta",            goodPhoEta,      "goodPhoEta[nGoodPho]/F");
  tr->Branch("goodPhoPhi",            goodPhoPhi,      "goodPhoPhi[nGoodPho]/F");
  tr->Branch("goodPhoSCEt",           goodPhoSCEt,     "goodPhoSCEt[nGoodPho]/F");
  tr->Branch("goodPhoSCEta",          goodPhoSCEta,    "goodPhoSCEta[nGoodPho]/F");
  tr->Branch("goodPhoSCPhi",          goodPhoSCPhi,    "goodPhoSCPhi[nGoodPho]/F");
  tr->Branch("goodPhoEtaWidth",       goodPhoEtaWidth,  "goodPhoEtaWidth[nGoodPho]/F");
  tr->Branch("goodPhoHoverE",         goodPhoHoverE,    "goodPhoHoverE[nGoodPho]/F");
  tr->Branch("goodPhoEnergyTop",      goodPhoEnergyTop, "goodPhoEnergyTop[nGoodPho]/F");
  tr->Branch("goodPhoEnergyBottom",   goodPhoEnergyBottom, "goodPhoEnergyBottom[nGoodPho]/F");
  tr->Branch("goodPhoEnergyLeft",     goodPhoEnergyLeft,   "goodPhoEnergyLeft[nGoodPho]/F");
  tr->Branch("goodPhoEnergyRight",    goodPhoEnergyRight,  "goodPhoEnergyRight[nGoodPho]/F");
  tr->Branch("goodPhoEnergyCrysMax",  goodPhoEnergyCrysMax,"goodPhoEnergyCrysMax[nGoodPho]/F");
  tr->Branch("goodPhoSwissCross",     goodPhoSwissCross,   "goodPhoSwissCross[nGoodPho]/F");
  tr->Branch("goodPhoSeedTime",       goodPhoSeedTime,     "goodPhoSeedTime[nGoodPho]/F");
  tr->Branch("goodPhoSigmaIEta",      goodPhoSigmaIEta,    "goodPhoSigmaIEta[nGoodPho]/F");

  tr->Branch("diPhotonPt",            &diPhotonPt,      "diPhotonPt/F");
  tr->Branch("diPhotonM",             &diPhotonM,       "diPhotonM/F");

  tr->Branch("nMissPho",              &nMissPho,        "nMissPho/I");
  tr->Branch("missedPhotonEta",       missedPhotonEta, "missedPhotonEta[nMissPho]/F");
  tr->Branch("missedPhotonPhi",       missedPhotonPhi, "missedPhotonPhi[nMissPho]/F");

  tr->Branch("nTrk",        &nTrk,    "nTrk/I");
  tr->Branch("trkPt",trkPt,"trkPt[nTrk]/F");
  tr->Branch("trkEta",trkEta,"trkEta[nTrk]/F");
  tr->Branch("trkPhi",trkPhi,"trkPhi[nTrk]/F");
  tr->Branch("trkCharge",trkCharge,"trkCharge[nTrk]/I");
  tr->Branch("trkChi2",trkChi2,"trkChi2[nTrk]/F");
  tr->Branch("trkPurity",trkPurity,"trkPurity[nTrk]/F");
  tr->Branch("trkD0",trkD0,"trkD0[nTrk]/F");
  tr->Branch("trkDxy",trkDxy,"trkDxy[nTrk]/F");
  tr->Branch("trkDz",trkDz,"trkDz[nTrk]/F");
  tr->Branch("trkDxyErr",trkDxyErr,"trkDxyErr[nTrk]/F");
  tr->Branch("trkDzErr",trkDzErr,"trkDzErr[nTrk]/F");
  tr->Branch("trkVx",trkVx,"trkVx[nTrk]/F");
  tr->Branch("trkVy",trkVy,"trkVy[nTrk]/F");
  tr->Branch("trkVz",trkVz,"trkVz[nTrk]/F");

  tr->Branch("ok_neuexcl",          &ok_neuexcl,      "ok_neuexcl/I");
  tr->Branch("ok_zdcexcl",          &ok_zdcexcl,      "ok_zdcexcl/I");
  tr->Branch("ok_chexcl",           &ok_chexcl,       "ok_chexcl/I");
  tr->Branch("ok_chexcl_tracks",    &ok_chexcl_tracks,       "ok_chexcl_tracks/I");
  tr->Branch("ok_chexcl_electrons", &ok_chexcl_electrons,       "ok_chexcl_electrons/I");
  tr->Branch("ok_chexcl_muons",     &ok_chexcl_muons,       "ok_chexcl_muons/I");
  tr->Branch("ok_chexcl_goodtracks",&ok_chexcl_goodtracks,       "ok_chexcl_goodtracks/I");
  tr->Branch("ok_chexcl_goodelectrons",&ok_chexcl_goodelectrons,       "ok_chexcl_goodelectrons/I");
  tr->Branch("ok_twophotons",       &ok_twophotons,   "ok_twophotons/I");
  tr->Branch("ok_twogoodphotons",       &ok_twogoodphotons,   "ok_twogoodphotons/I");
  tr->Branch("ok_twophotons_and_twogoodphotons",       &ok_twophotons_and_twogoodphotons,   "ok_twophotons_and_twogoodphotons/I");

  tr->Branch("SFweight_reco",       SFweight_reco,    "SFweight_reco[16]/F");
  tr->Branch("SFweight_trig",       SFweight_trig,    "SFweight_trig[16]/F");

  tr->Branch("nPixelCluster",      &nPixelCluster,    "nPixelCluster/I");
  tr->Branch("nPixelRecHits",      &nPixelRecHits,    "nPixelRecHits/I");

}

// reset gen variables
void ResetGenVars() {
  nGen = 0;
  
  for(int i=0;i<10;i++){
    gen_Et[i] = -999;
    gen_Eta[i] = -999;
    gen_Phi[i] = -999; 
  }

  gen_diPhotonPt = -999;
  gen_diPhotonM = -999;
  
}


// reset all variables
void ResetVars() {
  run =0;
  ls=0;
  evtnb =0;
  nPho = 0;
  nGoodPho = 0;
  nTrk = 0;

  for(int i=0;i<100;i++){
    phoEt[i]= -999 ;
    phoEta[i]= -999 ;
    phoPhi[i]= -999 ;
    phoSCEt[i]= -999 ;
    phoSCEta[i]= -999 ;
    phoSCPhi[i]= -999 ;
    phoEtaWidth[i] = -999 ;
    phoHoverE[i] = -999 ;
    phoEnergyTop[i] = -999 ;
    phoEnergyBottom[i] = -999 ;
    phoEnergyLeft[i] = -999 ;
    phoEnergyRight[i] = -999 ;
    phoEnergyCrysMax[i] = -999 ;
    phoSwissCross[i] = -999;
    phoSeedTime[i] = -999 ;
    phoSigmaIEta[i] = -999 ;

    goodPhoEt[i]= -999 ;
    goodPhoEta[i]= -999 ;
    goodPhoPhi[i]= -999 ;
    goodPhoSCEt[i]= -999 ;
    goodPhoSCEta[i]= -999 ;
    goodPhoSCPhi[i]= -999 ;
    goodPhoEtaWidth[i] = -999 ;
    goodPhoHoverE[i] = -999 ;
    goodPhoEnergyTop[i] = -999 ;
    goodPhoEnergyBottom[i] = -999 ;
    goodPhoEnergyLeft[i] = -999 ;
    goodPhoEnergyRight[i] = -999 ;
    goodPhoEnergyCrysMax[i] = -999 ;
    goodPhoSwissCross[i] = -999;
    goodPhoSeedTime[i] = -999 ;
    goodPhoSigmaIEta[i] = -999 ;

    trkPt[i] = -999;
    trkEta[i] = -999;
    trkPhi[i] = -999;
    trkCharge[i] = -999;
    trkChi2[i] = -999;
    trkPurity[i] = -999;
    trkD0[i] = -999;
    trkDxy[i] = -999;
    trkDz[i] = -999;
    trkDxyErr[i] = -999;
    trkDzErr[i] = -999;
    trkVx[i] = -999;
    trkVy[i] = -999;
    trkVz[i] = -999;

  }

  diPhotonPt = -999;
  diPhotonM = -999;

  nPixelCluster = -999;
  nPixelRecHits = -999;

}


/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters:\n";
    Log(0)<<"./selectDiphotonEvents configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }
  
  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
}


/// Application starting point
int main(int argc, char* argv[])
{
  string configPath, inputPath, outputPath, sampleName;
  ReadInputArguments(argc, argv, configPath, inputPath, outputPath, sampleName);

  config = ConfigManager(configPath);
  EDataset dataset = datasetForName.at(sampleName);
 
  TH1D *hist       = new TH1D("hist","",9,1,10);
  TH1D *hist_wozdc = new TH1D("hist_wozdc","",9,1,10);
 
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *genTree = new TTree("gen_tree","");
  TTree *tr = new TTree("output_tree","");
  InitTree(tr);
  InitGenTree(genTree);
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int all=0, all_kin=0, trigger_passed=0, twoPho=0, twoGoodPho=0, oppCharge=0, neutral_excl=0, charged_excl=0, diphomass_wozdc=0, diphopt_wozdc=0;
  int acop_cut_wozdc=0, diphomass=0, diphopt=0, acop_cut = 0, zdc_excl=0;
  int n0photon=0, n0photon_plustrack=0,n1photon=0, n1photon_plustrack=0;      
  int nRecoPhoton=0;

  // ofstreams for events to visualize
  std::ofstream outputNoDiPhoton("pick_noDiPhoton.txt");
  std::ofstream outputNoZeroTrack("pick_noZeroTrack.txt");

  Log(0) << events->GetNevents() << "\n";
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;

    auto event = events->GetEvent(iEvent);

    ResetGenVars();  
    ResetVars();  
    
    all++;

    TLorentzVector v1, v2;
    TLorentzVector result;

    if(sampleName == "QED_SC" || sampleName == "QED_SL" || sampleName == "LbL" || sampleName == "CEP"){
      auto genP = event->GetPhysObjects(EPhysObjType::kGenParticle);
            
      nGen = genP.size();

      int i = 0;
      for(auto gen : genP ){
	      //Log(0) << gen->GetPID() << "\n";
        //if(/*gen->GetPID()== 11 || gen->GetPID()== -11 || */gen->GetPID()== 22){

        if(fabs(gen->GetEta()) < 5.0){
          gen_Et[i]  = gen->GetEt();
	        gen_Eta[i] = gen->GetEta();
	        gen_Phi[i] = gen->GetPhi();

          if(i == 0)
            v1.SetPtEtaPhiE(gen->GetEt(),gen->GetEta(),gen->GetPhi(),gen->GetEt()*cosh( gen->GetEta() ) );
          else if(i == 1)
            v2.SetPtEtaPhiE(gen->GetEt(),gen->GetEta(),gen->GetPhi(),gen->GetEt()*cosh( gen->GetEta() ) );

          i++;

        } 
          	      //} // PID
      } //genpartcle

      result = v1 + v2;
      gen_diPhotonPt = result.Pt();
      gen_diPhotonM = result.M();

	    genTree->Fill();
    } //samplename
    
    if(fabs(gen_Eta[0]) > 2.4 || gen_Et[0] < 2) continue;
    if(fabs(gen_Eta[1]) > 2.4 || gen_Et[1] < 2) continue;
    if(gen_diPhotonM < 5 || gen_diPhotonPt > 1) continue;

    all_kin++;
 
    // Check trigger
    //if(sampleName != "Data"){
    //  if(!event->HasTrigger(kDoubleEG2noHF)) continue;
    //}

    trigger_passed++;
    hist->SetBinContent(1,trigger_passed);
    hist_wozdc->SetBinContent(1,trigger_passed);

    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();
   

    // select two exclusive photons 
    //if(event->GetPhysObjects(EPhysObjType::kGoodPhoton).size() != 2) continue; applying cut on good photon ==2  retains photons with pT less than 2 GeV and there can be more than 2 photons passing the criteria and others not passing... 

    // use normal photon size 2
    /*if(event->GetPhysObjects(EPhysObjType::kPhoton).size() != 2) continue;
    twoPho++;
    hist->SetBinContent(2,twoPho);     hist_wozdc->SetBinContent(2,twoPho);
    // now require two photons passing ID only
    if(event->GetPhysObjects(EPhysObjType::kGoodPhoton).size() != 2) continue;
    twoGoodPho++;
    hist->SetBinContent(3,twoGoodPho);     hist_wozdc->SetBinContent(3,twoGoodPho);
    */

    auto genTracks = event->GetPhysObjects(EPhysObjType::kGeneralTrack);
    auto electrons = event->GetPhysObjects(EPhysObjType::kElectron);
    auto goodGenTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
    auto goodElectrons = event->GetPhysObjects(EPhysObjType::kGoodElectron);
    auto muons     = event->GetPhysObjects(EPhysObjType::kMuon);
    auto photons   = event->GetPhysObjects(EPhysObjType::kPhoton);
    auto goodPhotons   = event->GetPhysObjects(EPhysObjType::kGoodPhoton);
    auto caloTower = event->GetPhysObjects(EPhysObjType::kCaloTower);

       // event variables
    ok_twophotons = (photons.size() == 2);
    ok_twogoodphotons = (goodPhotons.size() == 2);
 
    ok_neuexcl = (!event->HasAdditionalTowers());
    ok_chexcl  = (genTracks.size()==0 && electrons.size()==0 && muons.size()==0 );
    ok_chexcl_tracks = (genTracks.size()==0);
    ok_chexcl_electrons = (electrons.size()==0);
    ok_chexcl_muons = (muons.size()==0);
    ok_chexcl_goodtracks = (goodGenTracks.size()==0);
    ok_chexcl_goodelectrons = (goodElectrons.size()==0);
  
    if(sampleName == "Data")ok_zdcexcl = event->GetTotalZDCenergyPos() < 10000 && event->GetTotalZDCenergyNeg() < 10000;

    // cuts
    if(goodPhotons.size() == 0){
      n0photon++;
      if(goodGenTracks.size() > 0)
        n0photon_plustrack++;      
     
      nMissPho = 2;
      missedPhotonEta[0] = v1.Eta();  
      missedPhotonEta[1] = v2.Eta();  
      missedPhotonPhi[0] = v1.Phi();  
      missedPhotonPhi[1] = v2.Phi();
    }
    if(goodPhotons.size() == 1){
      n1photon++;
     
      if(goodGenTracks.size() > 0)
        n1photon_plustrack++;      

      nMissPho = 1;
      float dr1 = pow(v1.Eta()-goodPhotons[0]->GetEta(),2) + pow(v1.Phi()-goodPhotons[0]->GetPhi(),2);
      float dr2 = pow(v2.Eta()-goodPhotons[0]->GetEta(),2) + pow(v2.Phi()-goodPhotons[0]->GetPhi(),2);
      if(dr1 > dr2){
        missedPhotonEta[0] = v1.Eta();
        missedPhotonPhi[0] = v1.Phi();
      }
      else{
        missedPhotonEta[1] = v2.Eta();
        missedPhotonPhi[1] = v2.Phi();
      }

      if(dr1 < 0.2 || dr2 < 0.2)
        nRecoPhoton++;
    }

    if(goodPhotons.size() == 2){
      float dr11 = pow(v1.Eta()-goodPhotons[0]->GetEta(),2) + pow(v1.Phi()-goodPhotons[0]->GetPhi(),2);
      float dr12 = pow(v2.Eta()-goodPhotons[0]->GetEta(),2) + pow(v2.Phi()-goodPhotons[0]->GetPhi(),2);
      float dr21 = pow(v1.Eta()-goodPhotons[1]->GetEta(),2) + pow(v1.Phi()-goodPhotons[1]->GetPhi(),2);
      float dr22 = pow(v2.Eta()-goodPhotons[1]->GetEta(),2) + pow(v2.Phi()-goodPhotons[1]->GetPhi(),2);
    
      if(dr11 < 0.2 || dr12 < 0.2)
        nRecoPhoton++;
      if(dr21 < 0.2 || dr22 < 0.2)
        nRecoPhoton++;
    }

    //tr->Fill();
    //continue;

    if(goodPhotons.size() != 2) continue;
    twoGoodPho++;

    if(goodPhotons.size() == 2){
      TLorentzVector vec1, vec2, result;
      vec1.SetPtEtaPhiE(goodPhotons[0]->GetEt(),goodPhotons[0]->GetEta(),goodPhotons[0]->GetPhi(),goodPhotons[0]->GetEnergy());
      vec2.SetPtEtaPhiE(goodPhotons[1]->GetEt(),goodPhotons[1]->GetEta(),goodPhotons[1]->GetPhi(),goodPhotons[1]->GetEnergy());
      result = vec1 + vec2;

      diPhotonPt = result.Pt();
      diPhotonM = result.M();

      if(diPhotonM < 5) continue;
      diphomass++;
    }

    if(goodGenTracks.size() != 0) continue;
    charged_excl++;

    if(event->HasAdditionalTowers()) continue;
    neutral_excl++;


    nPho = photons.size();
    int i = 0;
    for(auto photon : photons){

      // start filling photon information here ........................................

      phoEt[i]      = photon->GetEt();
      phoEta[i]     = photon->GetEta();
      phoPhi[i]     = photon->GetPhi();
      phoSCEt[i]    = photon->GetEnergySC()*sin(2.*atan(exp(-photon->GetEtaSC())));
      phoSCEta[i]   = photon->GetEtaSC();
      phoSCPhi[i]   = photon->GetPhiSC();
      phoEtaWidth[i]      = photon->GetEtaWidth();
      phoHoverE[i]        = photon->GetHoverE();
      phoEnergyTop[i]     = photon->GetEnergyCrystalTop();
      phoEnergyBottom[i]  = photon->GetEnergyCrystalBottom();
      phoEnergyLeft[i]    = photon->GetEnergyCrystalLeft();
      phoEnergyRight[i]   = photon->GetEnergyCrystalRight();
      phoEnergyCrysMax[i] = photon->GetEnergyCrystalMax();
      phoSeedTime[i]      = photon->GetSeedTime();
      phoSigmaIEta[i]     = photon->GetSigmaEta2012();

      double E4 = phoEnergyTop[i] + phoEnergyBottom[i] +  phoEnergyLeft[i] + phoEnergyRight[i];
      phoSwissCross[i] = 1 - (E4/phoEnergyCrysMax[i]);
    
      i++;
    }

    nGoodPho = goodPhotons.size();
    i = 0;
    for(auto goodPhoton : goodPhotons){

      // start filling goodPhoton information here ........................................

      goodPhoEt[i]      = goodPhoton->GetEt();
      goodPhoEta[i]     = goodPhoton->GetEta();
      goodPhoPhi[i]     = goodPhoton->GetPhi();
      goodPhoSCEt[i]    = goodPhoton->GetEnergySC()*sin(2.*atan(exp(-goodPhoton->GetEtaSC())));
      goodPhoSCEta[i]   = goodPhoton->GetEtaSC();
      goodPhoSCPhi[i]   = goodPhoton->GetPhiSC();
      goodPhoEtaWidth[i]      = goodPhoton->GetEtaWidth();
      goodPhoHoverE[i]        = goodPhoton->GetHoverE();
      goodPhoEnergyTop[i]     = goodPhoton->GetEnergyCrystalTop();
      goodPhoEnergyBottom[i]  = goodPhoton->GetEnergyCrystalBottom();
      goodPhoEnergyLeft[i]    = goodPhoton->GetEnergyCrystalLeft();
      goodPhoEnergyRight[i]   = goodPhoton->GetEnergyCrystalRight();
      goodPhoEnergyCrysMax[i] = goodPhoton->GetEnergyCrystalMax();
      goodPhoSeedTime[i]      = goodPhoton->GetSeedTime();
      goodPhoSigmaIEta[i]     = goodPhoton->GetSigmaEta2012();

      double E4 = goodPhoEnergyTop[i] + goodPhoEnergyBottom[i] +  goodPhoEnergyLeft[i] + goodPhoEnergyRight[i];
      goodPhoSwissCross[i] = 1 - (E4/goodPhoEnergyCrysMax[i]);

      i++;
    }


    nTrk = genTracks.size();
    i = 0;
    for(auto track : genTracks){
      trkPt[i] = track->GetPt();
      trkEta[i] = track->GetEta();
      trkPhi[i] = track->GetPhi();
      trkCharge[i] = track->GetCharge();
      trkChi2[i] = track->GetChi2();
      trkPurity[i] = track->GetPurity();
      trkD0[i] = track->GetD0();
      trkDxy[i] = track->GetDxy();
      trkDz[i] = track->GetDz();
      trkDxyErr[i] = track->GetDxyErr();
      trkDzErr[i] = track->GetDzErr();
      trkVx[i] = track->GetVertexX();
      trkVy[i] = track->GetVertexY();
      trkVz[i] = track->GetVertexZ();
    
      i++;
    }

    //tr->Fill(); 

    if(nPho > 2)
      outputNoDiPhoton << run << ":" << ls << ":" << evtnb << std::endl;
    if(nTrk > 0)
      outputNoZeroTrack << run << ":" << ls << ":" << evtnb << std::endl;

    if(goodPhotons.size() == 2){
      TLorentzVector vec1, vec2, result;
      vec1.SetPtEtaPhiE(goodPhotons[0]->GetEt(),goodPhotons[0]->GetEta(),goodPhotons[0]->GetPhi(),goodPhotons[0]->GetEnergy());
      vec2.SetPtEtaPhiE(goodPhotons[1]->GetEt(),goodPhotons[1]->GetEta(),goodPhotons[1]->GetPhi(),goodPhotons[1]->GetEnergy());
      result = vec1 + vec2;

      diPhotonPt = result.Pt();
      diPhotonM = result.M();
      
      //if(diPhotonM < 5) continue;
      //diphomass++;
      if(diPhotonPt > 1) continue;
      diphopt++;
      double pho_dphi = vec1.DeltaPhi(vec2);
      double pho_acop = 1 - (fabs(pho_dphi)/3.141592653589);  

      if(pho_acop > 0.01) continue;
      acop_cut++;

      tr->Fill(); 
    }

  } //nevents
  Log(0) << "All:\t" << all*1635.123139823*2.59/466000 << "\n";
  Log(0) << "All within kinematic region:\t" << all_kin*1635.123139823*2.59/466000 << "\n";
  //Log(0) << "Triggered: " << trigger_passed << "\n" ;
  //Log(0) << "Number of events with two photons:" << twoPho << "\n" ;
  Log(0) << "Two good photons:\t" << twoGoodPho*1635.123139823*2.59/466000 << "\n" ;
  Log(0) << "M_inv > 5 GeV:\t" << diphomass*1635.123139823*2.59/466000 << "\n";
  Log(0) << "Charged exclusivity:\t" << charged_excl*1635.123139823*2.59/466000 << "\n";
  Log(0) << "Neutral exclusivity:\t" << neutral_excl*1635.123139823*2.59/466000 << "\n";
  Log(0) << "p_T < 1 GeV:\t" << diphopt*1635.123139823*2.59/466000 << "\n";
  Log(0) << "A_phi < 0.01:\t" << acop_cut*1635.123139823*2.59/466000 << "\n";

  Log(0) << n0photon << "\t" <<  n0photon_plustrack << "\t" << n1photon << "\t" << n1photon_plustrack << "\n";      
  //Log(0) << "Fraction of reconstructed good photons matched to gen photon: " << (float)nRecoPhoton/(2*twoGoodPho) << "\n";
  Log(0) << "Single photon reco efficiency: " << (float)nRecoPhoton / (2*all_kin) << "\n";
  Log(0) << "LbL cross section in fiducial region: " << (float)all_kin/466000*2.59*1000 << " nb" << "\n";

  outFile->cd();
  hist->Write(); 
  hist_wozdc->Write(); 
  outFile->Write();
  outFile->Close();
  
  return 0;
} // main loop 


Double_t getDR( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
  Double_t theDphi = getDPHI( phi1, phi2);
  Double_t theDeta = eta1 - eta2;
  return TMath::Sqrt ( theDphi*theDphi + theDeta*theDeta);
}

Double_t getDPHI( Double_t phi1, Double_t phi2) {
  Double_t dphi = phi1 - phi2;
  
  if ( dphi > 3.141592653589 )
    dphi = dphi - 2. * 3.141592653589;
  if ( dphi <= -3.141592653589 )
    dphi = dphi + 2. * 3.141592653589;
  
  if ( TMath::Abs(dphi) > 3.141592653589 ) {
    cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
  }
  
  return TMath::Abs(dphi);
  //return dphi;
}

Double_t getDETA(Double_t eta1, Double_t eta2){
  return TMath::Abs(eta1 - eta2);
}

bool outside_HEM(Double_t SCEta, Double_t SCPhi){
  if(SCEta < -1.39 && SCEta > -3 && SCPhi > -1.6 && SCPhi < -0.9) return false;
  
  return true;
}

