//  SelectQEDEvents
//
//  Created by Ruchi Chudasama on 24/12/2020
//
//  Selects QED events in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"
#include "TLorentzVector.h"
#include "Event.hpp"

const double eleMass = 0.5109989461e-3;
Double_t getDR  ( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t getDETA(Double_t eta1, Double_t eta2);

float gen_Pt;
float gen_Eta;
float gen_Phi;

int run;
int ls;
int evtnb;
int    nEle;
int    eleCharge_1;
float  elePt_1;
float  eleEta_1;
float  elePhi_1;
float  eleEoverP_1;

int    eleCharge_2;
float  elePt_2;
float  eleEta_2;
float  elePhi_2;
float  eleEoverP_2;

float vSum_ee_M;
float vSum_ee_Energy;
float vSum_ee_Pt;
float vSum_ee_Eta;
float vSum_ee_Phi;
float vSum_ee_Rapidity;
float ele_dpt;
float ele_deta;
float ele_dphi;
float ele_acop;
int ok_neuexcl;
int ok_chexcl;
int ok_chexcl_extrk;
int nExtrk;
   
/// initialise gen tree
void InitGenTree(TTree *genTree) {
  genTree->Branch("gen_Pt",  &gen_Pt, "gen_Pt/F");
  genTree->Branch("gen_Eta", &gen_Eta, "gen_Eta/F");
  genTree->Branch("gen_Phi", &gen_Phi, "gen_Phi/F");
}


/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("run",                 &run,           "run/I");
  tr->Branch("ls",                  &ls,            "ls/I");
  tr->Branch("evtnb",               &evtnb,         "evtnb/I");
  tr->Branch("nEle",                &nEle,          "nEle/I");
  tr->Branch("eleCharge_1",         &eleCharge_1,   "eleCharge_1/I");
  tr->Branch("elePt_1",             &elePt_1,       "elePt_1/F");
  tr->Branch("eleEta_1",            &eleEta_1,      "eleEta_1/F");
  tr->Branch("elePhi_1",            &elePhi_1,      "elePhi_1/F");
  tr->Branch("eleEoverP_1",         &eleEoverP_1,   "eleEoverP_1/F");
 
  tr->Branch("eleCharge_2",         &eleCharge_2,   "eleCharge_2/I");
  tr->Branch("elePt_2",             &elePt_2,       "elePt_2/F");
  tr->Branch("eleEta_2",            &eleEta_2,      "eleEta_2/F");
  tr->Branch("elePhi_2",            &elePhi_2,      "elePhi_2/F");
  tr->Branch("eleEoverP_2",         &eleEoverP_2,   "eleEoverP_2/F");
  
  tr->Branch("vSum_M",              &vSum_ee_M,       "vSum_ee_M/F");
  tr->Branch("vSum_Energy",         &vSum_ee_Energy,  "vSum_ee_Energy/F");
  tr->Branch("vSum_Pt",             &vSum_ee_Pt,      "vSum_ee_Pt/F");
  tr->Branch("vSum_Eta",            &vSum_ee_Eta,     "vSum_ee_Eta/F");
  tr->Branch("vSum_Phi",            &vSum_ee_Phi,     "vSum_ee_Phi/F");
  tr->Branch("vSum_Rapidity",       &vSum_ee_Rapidity,"vSum_ee_Rapidity/F");
  tr->Branch("ele_dpt",             &ele_dpt,         "ele_dpt/F");
  tr->Branch("ele_deta",            &ele_deta,        "ele_deta/F");
  tr->Branch("ele_dphi",            &ele_dphi,        "ele_dphi/F");
  tr->Branch("ele_acop",            &ele_acop,        "ele_acop/F");
  tr->Branch("ok_neuexcl",          &ok_neuexcl,      "ok_neuexcl/I");
  tr->Branch("ok_chexcl",           &ok_chexcl,       "ok_chexcl/I");
  tr->Branch("ok_chexcl_extrk",     &ok_chexcl_extrk, "ok_chexcl_extrk/I");
  tr->Branch("nExtrk",              &nExtrk,          "nExtrk/I");

}

// reset gen variables
void ResetGenVars() {
  gen_Pt = -999;
  gen_Eta = -999;
  gen_Phi = -999;

}


// reset all variables
void ResetVars() {
  run =0;
  ls=0;
  evtnb =0;
  nEle = 0;
  eleCharge_1= 0 ;
  elePt_1= 0 ;
  eleEta_1= 0 ;
  elePhi_1= 0 ;
  eleEoverP_1 = 0 ;
  
  eleCharge_2 = 0 ;
  elePt_2 = 0 ;
  eleEta_2 = 0 ;
  elePhi_2 = 0 ;
  eleEoverP_2 = 0 ;
 
  vSum_ee_M = 0 ;
  vSum_ee_Energy = 0 ;
  vSum_ee_Pt = 0 ;
  vSum_ee_Eta = 0 ;
  vSum_ee_Phi = 0 ;
  vSum_ee_Rapidity = 0 ;
  ele_dpt = 0;
  ele_deta = 0;
  ele_dphi = 0;
  ele_acop = 0;
  ok_neuexcl = 0;
  ok_chexcl = 0;
  ok_chexcl_extrk = 0;
  nExtrk = 0;
}


/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters:\n";
    Log(0)<<"./selectQEDEvents configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
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
 
  TH1D *hist = new TH1D("hist","",9,1,10);
 
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *genTree = new TTree("gen_tree","");
  TTree *tr = new TTree("output_tree","");
  InitTree(tr);
  InitGenTree(genTree);
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int trigger_passed=0, twoGoodEle=0, oppCharge=0, neutral_excl=0, charged_excl=0, zdcCut=0, diphotonmass=0, diphotonpt=0, diphorap=0;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    ResetGenVars();  
    ResetVars();  
    
    if(sampleName == "QED_SC" || sampleName == "QED_SL" || sampleName == "LbL" || sampleName == "CEP"){
    auto genP = event->GetPhysObjects(EPhysObjType::kGenParticle);
     for(auto gen : genP ){
	ResetGenVars();
	if(gen->GetPID()== 11 || gen->GetPID()== -11 || gen->GetPID()== 22){
	  gen_Pt  = gen->GetEt();
	  gen_Eta = gen->GetEta();
	  gen_Phi = gen->GetPhi();
	  genTree->Fill();
	} // PID
     } //genpartcle 
    } //samplename
    
    
    // Check trigger
    if(!event->HasTrigger(kDoubleEG2noHF)) continue;
    trigger_passed++;
    hist->SetBinContent(1,trigger_passed);

    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();
    
    nEle = event->GetPhysObjects(EPhysObjType::kElectron).size() == 2;
    
    // select two exclusive electrons for QED event selection
    if(event->GetPhysObjects(EPhysObjType::kGoodElectron).size() != 2) continue;
    twoGoodEle++;
    hist->SetBinContent(2,twoGoodEle);
    
    auto genTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
    auto electron1 = event->GetPhysObjects(EPhysObjType::kGoodElectron)[0];
    auto electron2 = event->GetPhysObjects(EPhysObjType::kGoodElectron)[1];
    
    if(electron1->GetCharge() == electron2->GetCharge()) continue;
    oppCharge++;
    hist->SetBinContent(3,oppCharge);
    
    // event variables
    ok_neuexcl = (!event->HasAdditionalTowers());
    ok_chexcl = (genTracks.size()==2);
    
    
    // start filling extra track information here ........................................
    int nextratracks =0;
    for (auto trk : genTracks) {
      if (getDPHI(trk->GetPhi(), electron1->GetPhi())<0.7 && getDETA(trk->GetEta(), electron1->GetEta())<0.15) continue;
      if (getDPHI(trk->GetPhi(), electron2->GetPhi())<0.7 && getDETA(trk->GetEta(), electron2->GetEta())<0.15) continue;
      nextratracks++;
    }
    
    nExtrk = nextratracks ;
    ok_chexcl_extrk = (nExtrk==0);
    
    eleCharge_1  = electron1->GetCharge();
    elePt_1      = electron1->GetPt();
    eleEta_1     = electron1->GetEta();
    elePhi_1     = electron1->GetPhi();
    eleEoverP_1  = electron1->GetEoverP();
    
    eleCharge_2  = electron2->GetCharge();
    elePt_2      = electron2->GetPt();
    eleEta_2     = electron2->GetEta();
    elePhi_2     = electron2->GetPhi();
    eleEoverP_2  = electron2->GetEoverP(); 
    
    TLorentzVector ele1, ele2, diele;
    ele1.SetPtEtaPhiM(elePt_1,eleEta_1,elePhi_1,eleMass);
    ele2.SetPtEtaPhiM(elePt_2,eleEta_2,elePhi_2,eleMass);
    
    diele = ele1 + ele2;
    vSum_ee_M = diele.M();
    vSum_ee_Energy = diele.Energy();
    vSum_ee_Pt  = diele.Pt();
    vSum_ee_Eta = diele.Eta();
    vSum_ee_Phi = diele.Phi();
    vSum_ee_Rapidity = diele.Rapidity();
    
    ele_dpt  = fabs(elePt_1  - elePt_2);
    ele_deta = fabs(eleEta_1 - eleEta_2);
    ele_dphi = getDPHI(elePhi_1,elePhi_2);
    ele_acop = 1- (ele_dphi/3.141592653589);  

    if(ok_chexcl_extrk==1){
      charged_excl++;
      hist->SetBinContent(4,charged_excl);
      if(ok_neuexcl==1){
	neutral_excl++;
	hist->SetBinContent(5,neutral_excl);
	if(vSum_ee_M>5){
	  diphotonmass++;
	  hist->SetBinContent(6,diphotonmass);
	}//mass
      }// neutral excl
    }//charged excl
    tr->Fill(); 
  } //nevents
  Log(0) << "Number of events triggered:" << trigger_passed << "\n" ;
  outFile->cd();
  hist->Write(); 
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


