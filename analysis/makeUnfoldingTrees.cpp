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

float gen_Pt1;
float gen_Eta1;
float gen_Phi1;
float gen_Pt2;
float gen_Eta2;
float gen_Phi2;
float gen_diPho_M;
float gen_diPho_Pt;
float gen_diPho_Rapidity;


int run;
int ls;
int evtnb;
int    nPho;
float  phoEt_1;
float  phoEta_1;
float  phoPhi_1;
float  phoSCEt_1;
float  phoSCEta_1;
float  phoSCPhi_1;
float  phoEtaWidth_1;
float  phoHoverE_1;
float  phoEnergyTop_1;
float  phoEnergyBottom_1;
float  phoEnergyLeft_1;
float  phoEnergyRight_1;
float  phoEnergyCrysMax_1;
float  phoSwissCross_1;
float  phoSeedTime_1;
float  phoSigmaIEta_1;


float  phoEt_2;
float  phoEta_2;
float  phoPhi_2;
float  phoSCEt_2;
float  phoSCEta_2;
float  phoSCPhi_2;
float  phoEtaWidth_2;
float  phoHoverE_2;
float  phoEnergyTop_2;
float  phoEnergyBottom_2;
float  phoEnergyLeft_2;
float  phoEnergyRight_2;
float  phoEnergyCrysMax_2;
float  phoSwissCross_2;
float  phoSeedTime_2;
float  phoSigmaIEta_2;

float vSum_diPho_M;
float vSum_diPho_Energy;
float vSum_diPho_Pt;
float vSum_diPho_Eta;
float vSum_diPho_Phi;
float vSum_diPho_Rapidity;
float pho_dpt;
float pho_deta;
float pho_dphi;
float pho_acop;
int ok_neuexcl;
int ok_trigger;

int ok_chexcl;
int ok_chexcl_tracks;
int ok_chexcl_electrons;
int ok_chexcl_muons;
int ok_chexcl_goodtracks;
int ok_chexcl_goodelectrons;

float SFweight_reco[16];
float SFweight_trig[16];
int   nPixelCluster;
int   nPixelRecHits;

/// initialise gen tree
void InitGenTree(TTree *genTree) {
  genTree->Branch("gen_Pt1",  &gen_Pt1, "gen_Pt1/F");
  genTree->Branch("gen_Eta1", &gen_Eta1, "gen_Eta1/F");
  genTree->Branch("gen_Phi1", &gen_Phi1, "gen_Phi1/F");

  genTree->Branch("gen_Pt2",  &gen_Pt2, "gen_Pt2/F");
  genTree->Branch("gen_Eta2", &gen_Eta2, "gen_Eta2/F");
  genTree->Branch("gen_Phi2", &gen_Phi2, "gen_Phi2/F");

  genTree->Branch("gen_diPho_M",  &gen_diPho_M,  "gen_diPho_M/F");
  genTree->Branch("gen_diPho_Pt", &gen_diPho_Pt, "gen_diPho_Pt/F");
  genTree->Branch("gen_diPho_Rapidity", &gen_diPho_Rapidity, "gen_diPho_Rapidity/F");
}


/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("gen_Pt1",  &gen_Pt1, "gen_Pt1/F");
  tr->Branch("gen_Eta1", &gen_Eta1, "gen_Eta1/F");
  tr->Branch("gen_Phi1", &gen_Phi1, "gen_Phi1/F");

  tr->Branch("gen_Pt2",  &gen_Pt2, "gen_Pt2/F");
  tr->Branch("gen_Eta2", &gen_Eta2, "gen_Eta2/F");
  tr->Branch("gen_Phi2", &gen_Phi2, "gen_Phi2/F");

  tr->Branch("gen_diPho_M",  &gen_diPho_M,  "gen_diPho_M/F");
  tr->Branch("gen_diPho_Pt", &gen_diPho_Pt, "gen_diPho_Pt/F");
  tr->Branch("gen_diPho_Rapidity", &gen_diPho_Rapidity, "gen_diPho_Rapidity/F");
 
  tr->Branch("run",                 &run,           "run/I");
  tr->Branch("ls",                  &ls,            "ls/I");
  tr->Branch("evtnb",               &evtnb,         "evtnb/I");
  tr->Branch("nPho",                &nPho,          "nPho/I");
  tr->Branch("phoEt_1",             &phoEt_1,       "phoEt_1/F");
  tr->Branch("phoEta_1",            &phoEta_1,      "phoEta_1/F");
  tr->Branch("phoPhi_1",            &phoPhi_1,      "phoPhi_1/F");
  tr->Branch("phoSCEt_1",           &phoSCEt_1,     "phoSCEt_1/F");
  tr->Branch("phoSCEta_1",          &phoSCEta_1,    "phoSCEta_1/F");
  tr->Branch("phoSCPhi_1",          &phoSCPhi_1,    "phoSCPhi_1/F");
  tr->Branch("phoEtaWidth_1",       &phoEtaWidth_1,  "phoEtaWidth_1/F");
  tr->Branch("phoHoverE_1",         &phoHoverE_1,    "phoHoverE_1/F");
  tr->Branch("phoEnergyTop_1",      &phoEnergyTop_1, "phoEnergyTop_1/F");
  tr->Branch("phoEnergyBottom_1",   &phoEnergyBottom_1, "phoEnergyBottom_1/F");
  tr->Branch("phoEnergyLeft_1",     &phoEnergyLeft_1,   "phoEnergyLeft_1/F");
  tr->Branch("phoEnergyRight_1",    &phoEnergyRight_1,  "phoEnergyRight_1/F");
  tr->Branch("phoEnergyCrysMax_1",  &phoEnergyCrysMax_1,"phoEnergyCrysMax_1/F");
  tr->Branch("phoSwissCross_1",     &phoSwissCross_1,   "phoSwissCross_1/F");
  tr->Branch("phoSeedTime_1",       &phoSeedTime_1,     "phoSeedTime_1/F");
  tr->Branch("phoSigmaIEta_1",      &phoSigmaIEta_1,    "phoSigmaIEta_1/F");


 
  tr->Branch("phoEt_2",             &phoEt_2,       "phoEt_2/F");
  tr->Branch("phoEta_2",            &phoEta_2,      "phoEta_2/F");
  tr->Branch("phoPhi_2",            &phoPhi_2,      "phoPhi_2/F");
  tr->Branch("phoSCEt_2",           &phoSCEt_2,     "phoSCEt_2/F");
  tr->Branch("phoSCEta_2",          &phoSCEta_2,    "phoSCEta_2/F");
  tr->Branch("phoSCPhi_2",          &phoSCPhi_2,    "phoSCPhi_2/F");
  tr->Branch("phoEtaWidth_2",       &phoEtaWidth_2,  "phoEtaWidth_2/F");
  tr->Branch("phoHoverE_2",         &phoHoverE_2,    "phoHoverE_2/F");
  tr->Branch("phoEnergyTop_2",      &phoEnergyTop_2, "phoEnergyTop_2/F");
  tr->Branch("phoEnergyBottom_2",   &phoEnergyBottom_2, "phoEnergyBottom_2/F");
  tr->Branch("phoEnergyLeft_2",     &phoEnergyLeft_2,   "phoEnergyLeft_2/F");
  tr->Branch("phoEnergyRight_2",    &phoEnergyRight_2,  "phoEnergyRight_2/F");
  tr->Branch("phoEnergyCrysMax_2",  &phoEnergyCrysMax_2,"phoEnergyCrysMax_2/F");
  tr->Branch("phoSwissCross_2",     &phoSwissCross_2,   "phoSwissCross_2/F");
  tr->Branch("phoSeedTime_2",       &phoSeedTime_2,     "phoSeedTime_2/F");
  tr->Branch("phoSigmaIEta_2",      &phoSigmaIEta_2,    "phoSigmaIEta_2/F");
  
  tr->Branch("vSum_M",              &vSum_diPho_M,       "vSum_diPho_M/F");
  tr->Branch("vSum_Energy",         &vSum_diPho_Energy,  "vSum_diPho_Energy/F");
  tr->Branch("vSum_Pt",             &vSum_diPho_Pt,      "vSum_diPho_Pt/F");
  tr->Branch("vSum_Eta",            &vSum_diPho_Eta,     "vSum_diPho_Eta/F");
  tr->Branch("vSum_Phi",            &vSum_diPho_Phi,     "vSum_diPho_Phi/F");
  tr->Branch("vSum_Rapidity",       &vSum_diPho_Rapidity,"vSum_diPho_Rapidity/F");
  tr->Branch("pho_dpt",             &pho_dpt,         "pho_dpt/F");
  tr->Branch("pho_deta",            &pho_deta,        "pho_deta/F");
  tr->Branch("pho_dphi",            &pho_dphi,        "pho_dphi/F");
  tr->Branch("pho_acop",            &pho_acop,        "pho_acop/F");
  tr->Branch("ok_trigger",          &ok_trigger,      "ok_trigger/I");
  tr->Branch("ok_neuexcl",          &ok_neuexcl,      "ok_neuexcl/I");

  tr->Branch("ok_chexcl",           &ok_chexcl,       "ok_chexcl/I");
  tr->Branch("ok_chexcl_tracks",           &ok_chexcl_tracks,       "ok_chexcl_tracks/I");
  tr->Branch("ok_chexcl_electrons",           &ok_chexcl_electrons,       "ok_chexcl_electrons/I");
  tr->Branch("ok_chexcl_muons",           &ok_chexcl_muons,       "ok_chexcl_muons/I");
  tr->Branch("ok_chexcl_goodtracks",           &ok_chexcl_goodtracks,       "ok_chexcl_goodtracks/I");
  tr->Branch("ok_chexcl_goodelectrons",           &ok_chexcl_goodelectrons,       "ok_chexcl_goodelectrons/I");

  tr->Branch("SFweight_reco",       SFweight_reco,    "SFweight_reco[16]/F");
  tr->Branch("SFweight_trig",       SFweight_trig,    "SFweight_trig[16]/F");

  tr->Branch("nPixelCluster",      &nPixelCluster,    "nPixelCluster/I");
  tr->Branch("nPixelRecHits",      &nPixelRecHits,    "nPixelRecHits/I");

}

// reset gen variables
void ResetGenVars() {
  gen_Pt1 = 0;
  gen_Eta1 = 0;
  gen_Phi1 = 0;
  gen_Pt2 = 0;
  gen_Eta2 = 0;
  gen_Phi2 = 0;
  gen_diPho_M = 0;
  gen_diPho_Pt = 0;
  gen_diPho_Rapidity = 0;
}


// reset all variables
void ResetVars() {

  run =0;
  ls=0;
  evtnb =0;
  nPho = 0;
  phoEt_1= -999 ;
  phoEta_1= -999 ;
  phoPhi_1= -999 ;
  phoSCEt_1= -999 ;
  phoSCEta_1= -999 ;
  phoSCPhi_1= -999 ;
  phoEtaWidth_1 = -999 ;
  phoHoverE_1 = -999 ;
  phoEnergyTop_1 = -999 ;
  phoEnergyBottom_1 = -999 ;
  phoEnergyLeft_1 = -999 ;
  phoEnergyRight_1 = -999 ;
  phoEnergyCrysMax_1 = -999 ;
  phoSwissCross_1 = -999;
  phoSeedTime_1 = -999 ;
  phoSigmaIEta_1 = -999 ;

  phoEt_2= -999 ;
  phoEta_2= -999 ;
  phoPhi_2= -999 ;
  phoSCEt_2= -999 ;
  phoSCEta_2= -999 ;
  phoSCPhi_2= -999 ;
  phoEtaWidth_2 = -999 ;
  phoHoverE_2 = -999 ;
  phoEnergyTop_2 = -999 ;
  phoEnergyBottom_2 = -999 ;
  phoEnergyLeft_2 = -999 ;
  phoEnergyRight_2 = -999 ;
  phoEnergyCrysMax_2 = -999 ;
  phoSwissCross_2 = -999;
  phoSeedTime_2 = -999 ;
  phoSigmaIEta_2 = -999 ;
 
  vSum_diPho_M = 0 ;
  vSum_diPho_Energy = 0 ;
  vSum_diPho_Pt = 0 ;
  vSum_diPho_Eta = 0 ;
  vSum_diPho_Phi = 0 ;
  vSum_diPho_Rapidity = 0 ;
  pho_dpt = 0;
  pho_deta = 0;
  pho_dphi = 0;
  pho_acop = 0;
  ok_trigger = 0;
  ok_neuexcl = 0;
 
  ok_chexcl = 0;
  ok_chexcl_tracks = 0;
  ok_chexcl_electrons = 0;
  ok_chexcl_muons = 0;
  ok_chexcl_goodtracks = 0;
  ok_chexcl_goodelectrons = 0;
 
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

  TTree *tr = new TTree("output_tree","");
  InitTree(tr);

  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int trigger_passed=0, twoPho=0, twoGoodPho=0, oppCharge=0, neutral_excl=0, charged_excl=0, diphomass_wozdc=0, diphopt_wozdc=0;
  int acop_cut_wozdc=0, diphomass=0, diphopt=0, acop_cut = 0, zdc_excl=0;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
  //for(int iEvent=0; iEvent<1000; iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    //if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    ResetGenVars();  
    ResetVars();  
    
    if(sampleName == "QED_SC" || sampleName == "QED_SL" || sampleName == "LbL" || sampleName == "CEP"){
      
      //first two gen particle in event has weird PDG ID, its PbPb ion I guess. Therefore I am using 3 and 4th particle which is photon. 
      auto genP1 = event->GetPhysObjects(EPhysObjType::kGenParticle)[2];  
      auto genP2 = event->GetPhysObjects(EPhysObjType::kGenParticle)[3];
      
      
      ResetGenVars();
      if(genP1->GetPID()== 22 && genP2->GetPID()==22){
        //Log(0) << "coming in PID loop :" <<"\n"; 
	gen_Pt1  = genP1->GetEt();
	gen_Eta1 = genP1->GetEta();
	gen_Phi1 = genP1->GetPhi();
	
	gen_Pt2  = genP2->GetEt();
	gen_Eta2 = genP2->GetEta();
	gen_Phi2 = genP2->GetPhi();
	
	TLorentzVector pho1, pho2, dipho;
	pho1.SetPtEtaPhiM(gen_Pt1, gen_Eta1, gen_Phi1, 0);
	pho2.SetPtEtaPhiM(gen_Pt2, gen_Eta2, gen_Phi2, 0);
	
	dipho = pho1 + pho2;
	gen_diPho_M   = dipho.M();
	gen_diPho_Pt  = dipho.Pt();
	gen_diPho_Rapidity = dipho.Rapidity();
	
      } // PID
      
      
      
      ok_trigger = (event->HasTrigger(kDoubleEG2noHF));
      
      trigger_passed++;
      hist->SetBinContent(1,trigger_passed);
      hist_wozdc->SetBinContent(1,trigger_passed);
      
      run = event->GetRunNumber();
      ls = event->GetLumiSection();
      evtnb = event->GetEventNumber();
      
      
      twoPho++;
      hist->SetBinContent(2,twoPho);     hist_wozdc->SetBinContent(2,twoPho);
      
      
      // now require two photons passing ID only
      if(event->GetPhysObjects(EPhysObjType::kGoodPhoton).size() == 2){
	twoGoodPho++;
	hist->SetBinContent(3,twoGoodPho);     hist_wozdc->SetBinContent(3,twoGoodPho);
	
	auto genTracks = event->GetPhysObjects(EPhysObjType::kGeneralTrack);
	auto electrons = event->GetPhysObjects(EPhysObjType::kElectron);
	auto goodGenTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
	auto goodElectrons = event->GetPhysObjects(EPhysObjType::kGoodElectron);
	auto muons     = event->GetPhysObjects(EPhysObjType::kMuon);
	auto photon1   = event->GetPhysObjects(EPhysObjType::kGoodPhoton)[0];
	auto photon2   = event->GetPhysObjects(EPhysObjType::kGoodPhoton)[1];
	auto caloTower = event->GetPhysObjects(EPhysObjType::kCaloTower);
	
	// event variables
	ok_neuexcl = (!event->HasAdditionalTowers());
	
	ok_chexcl  = (genTracks.size()==0 && electrons.size()==0 && muons.size()==0 );
	ok_chexcl_tracks = (genTracks.size()==0);
	ok_chexcl_electrons = (electrons.size()==0);
	ok_chexcl_muons = (muons.size()==0);
	ok_chexcl_goodtracks = (goodGenTracks.size()==0);
	ok_chexcl_goodelectrons = (goodElectrons.size()==0);

	
	// start filling photon information here ........................................
	
	phoEt_1      = photon1->GetEt();
	phoEta_1     = photon1->GetEta();
	phoPhi_1     = photon1->GetPhi();
	phoSCEt_1    = photon1->GetEnergySC()*sin(2.*atan(exp(-photon1->GetEtaSC())));
	phoSCEta_1   = photon1->GetEtaSC();
	phoSCPhi_1   = photon1->GetPhiSC();
	phoEtaWidth_1      = photon1->GetEtaWidth();
	phoHoverE_1        = photon1->GetHoverE();
	phoEnergyTop_1     = photon1->GetEnergyCrystalTop();
	phoEnergyBottom_1  = photon1->GetEnergyCrystalBottom();
	phoEnergyLeft_1    = photon1->GetEnergyCrystalLeft();
	phoEnergyRight_1   = photon1->GetEnergyCrystalRight();
	phoEnergyCrysMax_1 = photon1->GetEnergyCrystalMax();
	phoSeedTime_1      = photon1->GetSeedTime();
	phoSigmaIEta_1     = photon1->GetSigmaEta2012();
	
	double E4 = phoEnergyTop_1 + phoEnergyBottom_1 +  phoEnergyLeft_1 + phoEnergyRight_1;
	phoSwissCross_1 = 1 - (E4/phoEnergyCrysMax_1);
	
	
	phoEt_2      = photon2->GetEt();
	phoEta_2     = photon2->GetEta();
	phoPhi_2     = photon2->GetPhi();
	phoSCEt_2    = photon2->GetEnergySC()*sin(2.*atan(exp(-photon2->GetEtaSC())));
	phoSCEta_2   = photon2->GetEtaSC();
	phoSCPhi_2   = photon2->GetPhiSC();
	phoEtaWidth_2      = photon2->GetEtaWidth();
	phoHoverE_2        = photon2->GetHoverE();
	phoEnergyTop_2     = photon2->GetEnergyCrystalTop();
	phoEnergyBottom_2  = photon2->GetEnergyCrystalBottom();
	phoEnergyLeft_2    = photon2->GetEnergyCrystalLeft();
	phoEnergyRight_2   = photon2->GetEnergyCrystalRight();
	phoEnergyCrysMax_2 = photon2->GetEnergyCrystalMax();
	phoSeedTime_2      = photon2->GetSeedTime();
	phoSigmaIEta_2     = photon2->GetSigmaEta2012();
	
	double E4_2 = phoEnergyTop_2 + phoEnergyBottom_2 +  phoEnergyLeft_2 + phoEnergyRight_2;
	phoSwissCross_2 = 1 - (E4_2/phoEnergyCrysMax_2);
	
	TLorentzVector pho1, pho2, dipho;
	pho1.SetPtEtaPhiE(phoEt_1,phoEta_1,phoPhi_1,photon1->GetEnergy());
	pho2.SetPtEtaPhiE(phoEt_2,phoEta_2,phoPhi_2,photon2->GetEnergy());
	
	dipho = pho1 + pho2;
	vSum_diPho_M = dipho.M();
	vSum_diPho_Energy = dipho.Energy();
	vSum_diPho_Pt  = dipho.Pt();
	vSum_diPho_Eta = dipho.Eta();
	vSum_diPho_Phi = dipho.Phi();
	vSum_diPho_Rapidity = dipho.Rapidity();
	
	pho_dpt  = fabs(phoEt_1  - phoEt_2);
	pho_deta = fabs(phoEta_1 - phoEta_2);
	pho_dphi = getDPHI(phoPhi_1,phoPhi_2);
	pho_acop = 1 - (pho_dphi/3.141592653589);  
	
	nPixelCluster = event->GetNpixelClusters();
	nPixelRecHits =  event->GetNpixelRecHits();
      } // if two good photons
           
      tr->Fill(); 
    } //samplename
  } //nevents
  Log(0) << "Number of events triggered:" << trigger_passed << "\n" ;
  Log(0) << "Number of events with two photons:" << twoPho << "\n" ;
  Log(0) << "Number of events with two good photons:" << twoGoodPho << "\n" ;
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

