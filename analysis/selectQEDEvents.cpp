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

int ireg(double et, double eta);
double SF_reco(double et, double eta);
double SF_uncert_reco(double et, double eta);
double SF_trig(double et, double eta);
double SF_uncert_trig(double et, double eta);

const double eleMass = 0.5109989461e-3;
Double_t getDR  ( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t getDETA(Double_t eta1, Double_t eta2);

double cosphotonpair(TLorentzVector p1, TLorentzVector pair, bool helicityFrame );
double costhetastar_CS(TLorentzVector p1, TLorentzVector pair); 

float gen_Pt1;
float gen_Eta1;
float gen_Phi1;
float gen_Pt2;
float gen_Eta2;
float gen_Phi2;
float gen_diEle_M;
float gen_diEle_Pt;
float gen_diEle_Rapidity;


int run;
int ls;
int evtnb;
int    nEle;
int    eleCharge_1;
float  elePt_1;
float  eleEta_1;
float  elePhi_1;
float  eleSCEt_1;
float  eleSCEta_1;
float  eleSCPhi_1;
float  eleEoverP_1;

int    eleCharge_2;
float  elePt_2;
float  eleEta_2;
float  elePhi_2;
float  eleSCEt_2;
float  eleSCEta_2;
float  eleSCPhi_2;
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

float zdc_energy_pos;
float zdc_energy_neg;
int ok_zdcexcl_1n_pos;
int ok_zdcexcl_1n_neg;
int ok_zdcexcl_3n_pos;
int ok_zdcexcl_3n_neg;
int ok_zdcexcl_4n_pos;
int ok_zdcexcl_4n_neg;
int ok_zdcexcl_5n_pos;
int ok_zdcexcl_5n_neg;
int ok_zdcexcl;
int ok_chexcl;
int ok_chexcl_extrk;
int nExtrk;
float SFweight_reco[16];
float SFweight_trig[16];

float  leadingEmEnergy_EB;
float  leadingEmEnergy_EE;
float  leadingHadEnergy_HB; 
float  leadingHadEnergy_HE;
float  leadingHadEnergy_HF_Plus;
float  leadingHadEnergy_HF_Minus;

float costhetastar;
float cos_photon_pair_helicity0;
float cos_photon_pair_helicity1;

int nVtx;
float xVtx;
float yVtx;
float zVtx;


/// initialise gen tree
void InitGenTree(TTree *genTree) {
  genTree->Branch("gen_Pt1",  &gen_Pt1, "gen_Pt1/F");
  genTree->Branch("gen_Eta1", &gen_Eta1, "gen_Eta1/F");
  genTree->Branch("gen_Phi1", &gen_Phi1, "gen_Phi1/F");

  genTree->Branch("gen_Pt2",  &gen_Pt2, "gen_Pt2/F");
  genTree->Branch("gen_Eta2", &gen_Eta2, "gen_Eta2/F");
  genTree->Branch("gen_Phi2", &gen_Phi2, "gen_Phi2/F");

  genTree->Branch("gen_diEle_M",  &gen_diEle_M,  "gen_diEle_M/F");
  genTree->Branch("gen_diEle_Pt", &gen_diEle_Pt, "gen_diEle_Pt/F");
  genTree->Branch("gen_diEle_Rapidity", &gen_diEle_Rapidity, "gen_diEle_Rapidity/F");


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
  tr->Branch("eleSCEt_1",           &eleSCEt_1,     "eleSCEt_1/F");
  tr->Branch("eleSCEta_1",          &eleSCEta_1,    "eleSCEta_1/F");
  tr->Branch("eleSCPhi_1",          &eleSCPhi_1,    "eleSCPhi_1/F");
  tr->Branch("eleEoverP_1",         &eleEoverP_1,   "eleEoverP_1/F");
 
  tr->Branch("eleCharge_2",         &eleCharge_2,   "eleCharge_2/I");
  tr->Branch("elePt_2",             &elePt_2,       "elePt_2/F");
  tr->Branch("eleEta_2",            &eleEta_2,      "eleEta_2/F");
  tr->Branch("elePhi_2",            &elePhi_2,      "elePhi_2/F");
  tr->Branch("eleSCEt_2",           &eleSCEt_2,     "eleSCEt_2/F");
  tr->Branch("eleSCEta_2",          &eleSCEta_2,    "eleSCEta_2/F");
  tr->Branch("eleSCPhi_2",          &eleSCPhi_2,    "eleSCPhi_2/F");
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

  tr->Branch("zdc_energy_pos",             &zdc_energy_pos,         "zdc_energy_pos/F");
  tr->Branch("zdc_energy_neg",             &zdc_energy_neg,         "zdc_energy_neg/F");
  tr->Branch("ok_zdcexcl_1n_pos",          &ok_zdcexcl_1n_pos,      "ok_zdcexcl_1n_pos/I");
  tr->Branch("ok_zdcexcl_1n_neg",          &ok_zdcexcl_1n_neg,      "ok_zdcexcl_1n_neg/I");

  tr->Branch("ok_zdcexcl_3n_pos",          &ok_zdcexcl_3n_pos,      "ok_zdcexcl_3n_pos/I");
  tr->Branch("ok_zdcexcl_3n_neg",          &ok_zdcexcl_3n_neg,      "ok_zdcexcl_3n_neg/I");
  
  tr->Branch("ok_zdcexcl_4n_pos",          &ok_zdcexcl_4n_pos,      "ok_zdcexcl_4n_pos/I");
  tr->Branch("ok_zdcexcl_4n_neg",          &ok_zdcexcl_4n_neg,      "ok_zdcexcl_4n_neg/I");

  tr->Branch("ok_zdcexcl_5n_pos",          &ok_zdcexcl_5n_pos,      "ok_zdcexcl_5n_pos/I");
  tr->Branch("ok_zdcexcl_5n_neg",          &ok_zdcexcl_5n_neg,      "ok_zdcexcl_5n_neg/I");
  tr->Branch("ok_zdcexcl",          &ok_zdcexcl,      "ok_zdcexcl/I");

  tr->Branch("ok_chexcl",           &ok_chexcl,       "ok_chexcl/I");
  tr->Branch("ok_chexcl_extrk",     &ok_chexcl_extrk, "ok_chexcl_extrk/I");
  tr->Branch("nExtrk",              &nExtrk,          "nExtrk/I");
  tr->Branch("SFweight_reco",       SFweight_reco,    "SFweight_reco[16]/F");
  tr->Branch("SFweight_trig",       SFweight_trig,    "SFweight_trig[16]/F");
  tr->Branch("leadingEmEnergy_EB",  &leadingEmEnergy_EB,"leadingEmEnergy_EB/F");
  tr->Branch("leadingEmEnergy_EE",  &leadingEmEnergy_EE,"leadingEmEnergy_EE/F");
  tr->Branch("leadingHadEnergy_HB",  &leadingHadEnergy_HB,"leadingHadEnergy_HB/F");
  tr->Branch("leadingHadEnergy_HE",  &leadingHadEnergy_HE,"leadingHadEnergy_HE/F");
  tr->Branch("leadingHadEnergy_HF_Plus",  &leadingHadEnergy_HF_Plus,"leadingHadEnergy_HF_Plus/F");
  tr->Branch("leadingHadEnergy_HF_Minus",  &leadingHadEnergy_HF_Minus,"leadingHadEnergy_HF_Minus/F");

  tr->Branch("costhetastar",        &costhetastar,        "costhetastar/F");
  tr->Branch("cos_photon_pair_helicity0",     &cos_photon_pair_helicity0,     "cos_photon_pair_helicity0/F");
  tr->Branch("cos_photon_pair_helicity1",     &cos_photon_pair_helicity1,     "cos_photon_pair_helicity1/F");
  //
  tr->Branch("nVtx",                 &nVtx,                        "nVtx/I");
  tr->Branch("xVtx",                 &xVtx,                        "xVtx/F");
  tr->Branch("yVtx",                 &yVtx,                        "yVtx/F");
  tr->Branch("zVtx",                 &zVtx,                        "zVtx/F");

}

// reset gen variables
void ResetGenVars() {
  gen_Pt1 = 0;
  gen_Eta1 = 0;
  gen_Phi1 = 0;
  gen_Pt2 = 0;
  gen_Eta2 = 0;
  gen_Phi2 = 0;
  gen_diEle_M = 0;
  gen_diEle_Pt = 0;
  gen_diEle_Rapidity = 0;
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
  eleSCEt_1= 0 ;
  eleSCEta_1= 0 ;
  eleSCPhi_1= 0 ;
  eleEoverP_1 = 0 ;
  
  eleCharge_2 = 0 ;
  elePt_2 = 0 ;
  eleEta_2 = 0 ;
  elePhi_2 = 0 ;
  eleSCEt_2 = 0 ;
  eleSCEta_2 = 0 ;
  eleSCPhi_2 = 0 ;
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
  zdc_energy_pos = 0;
  zdc_energy_neg = 0;
  ok_zdcexcl_1n_pos = 0;
  ok_zdcexcl_1n_neg = 0;
  ok_zdcexcl_3n_pos = 0;
  ok_zdcexcl_3n_neg = 0;
  ok_zdcexcl_4n_pos = 0;
  ok_zdcexcl_4n_neg = 0;
  ok_zdcexcl_5n_pos = 0;
  ok_zdcexcl_5n_neg = 0;
  ok_zdcexcl = 0;
  ok_chexcl = 0;
  ok_chexcl_extrk = 0;
  nExtrk = 0;

  leadingEmEnergy_EB = 0;
  leadingEmEnergy_EE = 0;
  leadingHadEnergy_HB = 0; 
  leadingHadEnergy_HE = 0;
  leadingHadEnergy_HF_Plus = 0;
  leadingHadEnergy_HF_Minus = 0;

  costhetastar = -999;
  cos_photon_pair_helicity0 = -999;
  cos_photon_pair_helicity1 = -999;
  //
  nVtx = 0;
  xVtx = -999;
  yVtx = -999;
  zVtx = -999;

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
 
  TH1D *hist       = new TH1D("hist","",9,1,10);
  TH1D *hist_wozdc = new TH1D("hist_wozdc","",9,1,10);
 
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *genTree = new TTree("gen_tree","");
  TTree *tr = new TTree("output_tree","");
  InitTree(tr);
  InitGenTree(genTree);
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int trigger_passed=0, twoGoodEle=0, oppCharge=0, neutral_excl=0, charged_excl=0, dielemass_wozdc=0, dielept_wozdc=0;
  int acop_cut_wozdc=0, dielemass=0, dielept=0, acop_cut = 0, zdc_excl=0;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
  //for(int iEvent=0; iEvent<50000; iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    //if(iEvent >= config.params("maxEvents")) break;
   
    auto event = events->GetEvent(iEvent);
    
    ResetGenVars();  
    ResetVars();  
    
    if(sampleName == "QED_SC"  || sampleName == "QED_SL" ){
      ResetGenVars();
      auto genP1 = event->GetPhysObjects(EPhysObjType::kGenParticle)[0];
      auto genP2 = event->GetPhysObjects(EPhysObjType::kGenParticle)[1];

      if(abs(genP1->GetPID())== 11 && abs(genP2->GetPID())== 11 ){
	//Log(0) << " PID 1:" << genP1->GetPID() << "  two:" << genP2->GetPID() << "\n";
	gen_Pt1  = genP1->GetEt();
	gen_Eta1 = genP1->GetEta();
	gen_Phi1 = genP1->GetPhi();
	
	gen_Pt2  = genP2->GetEt();
	gen_Eta2 = genP2->GetEta();
	gen_Phi2 = genP2->GetPhi();
	
	TLorentzVector ele1, ele2, diele;
	ele1.SetPtEtaPhiM(gen_Pt1, gen_Eta1, gen_Phi1, 0.000511);
	ele2.SetPtEtaPhiM(gen_Pt2, gen_Eta2, gen_Phi2, 0.000511);
	
	diele = ele1 + ele2;
	gen_diEle_M   = diele.M();
	gen_diEle_Pt  = diele.Pt();
	gen_diEle_Rapidity = diele.Rapidity();
	
	genTree->Fill();
      } // PID
    } //samplename
    
    
    // Check trigger
    //if(sampleName != "Data"){
    //if(!event->HasTrigger(kDoubleEG2noHF)) continue;
    //}
    
    trigger_passed++;
    hist->SetBinContent(1,trigger_passed);
    hist_wozdc->SetBinContent(1,trigger_passed);
    
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();
    
    // select two exclusive electrons for QED event selection
    if(event->GetPhysObjects(EPhysObjType::kGoodElectron).size() != 2) continue;
    twoGoodEle++;
    hist->SetBinContent(2,twoGoodEle);     hist_wozdc->SetBinContent(2,twoGoodEle);
    
    auto genTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
    auto electron1 = event->GetPhysObjects(EPhysObjType::kGoodElectron)[0];
    auto electron2 = event->GetPhysObjects(EPhysObjType::kGoodElectron)[1];
    auto caloTower = event->GetPhysObjects(EPhysObjType::kCaloTower);
    //
     auto vertices = event->GetPhysObjects(EPhysObjType::kVertex);

    //
    if(electron1->GetCharge() == electron2->GetCharge()) continue;
    oppCharge++;
    hist->SetBinContent(3,oppCharge);      hist_wozdc->SetBinContent(3,oppCharge);
    
    // event variables
    ok_neuexcl = (!event->HasAdditionalTowers());
    ok_chexcl  = (genTracks.size()==2);

    if(sampleName == "Data"){
      zdc_energy_pos = event->GetTotalZDCenergyPos(); zdc_energy_neg = event->GetTotalZDCenergyNeg();
      
      ok_zdcexcl = event->GetTotalZDCenergyPos() < 10000 && event->GetTotalZDCenergyNeg() < 10000;
      ok_zdcexcl_1n_pos = event->GetTotalZDCenergyPos() < 1500;
      ok_zdcexcl_1n_neg = event->GetTotalZDCenergyNeg() < 1500;
      ok_zdcexcl_3n_pos = event->GetTotalZDCenergyPos() < 8000;
      ok_zdcexcl_3n_neg = event->GetTotalZDCenergyNeg() < 8000;
      ok_zdcexcl_4n_pos = event->GetTotalZDCenergyPos() < 10000;
      ok_zdcexcl_4n_neg = event->GetTotalZDCenergyNeg() < 10000;
      ok_zdcexcl_5n_pos = event->GetTotalZDCenergyPos() < 12000;
      ok_zdcexcl_5n_neg = event->GetTotalZDCenergyNeg() < 12000;

//      Check that the event is not within a run range where ZDC had issues
      auto run = event->GetRunNumber();
      bool ok_zdc_run = (run < 326571) || (run > 326676);
      
      ok_zdcexcl &= ok_zdc_run;
      ok_zdcexcl_1n_pos &= ok_zdc_run;
      ok_zdcexcl_1n_neg &= ok_zdc_run;
      ok_zdcexcl_3n_pos &= ok_zdc_run;
      ok_zdcexcl_3n_neg &= ok_zdc_run;
      ok_zdcexcl_4n_pos &= ok_zdc_run;
      ok_zdcexcl_4n_neg &= ok_zdc_run;
      ok_zdcexcl_5n_pos &= ok_zdc_run;
      ok_zdcexcl_5n_neg &= ok_zdc_run;
    }

    
    // start filling extra track information here ........................................
    int nextratracks =0;
    //Log(0) << "Event:" << iEvent << " track size:" << genTracks.size() << "\n";
    for (auto trk : genTracks) {
      if (getDPHI(trk->GetPhi(), electron1->GetPhi())<0.7 && getDETA(trk->GetEta(), electron1->GetEta())<0.15) continue;
      if (getDPHI(trk->GetPhi(), electron2->GetPhi())<0.7 && getDETA(trk->GetEta(), electron2->GetEta())<0.15) continue;
      nextratracks++;
    }
    if(nextratracks>0)Log(0) << "Event :" << iEvent << " extra tracks:" << nextratracks << "\n";    
    nExtrk = nextratracks ;
    ok_chexcl_extrk = (nExtrk==0);
    
    eleCharge_1  = electron1->GetCharge();
    elePt_1      = electron1->GetPt();
    eleEta_1     = electron1->GetEta();
    elePhi_1     = electron1->GetPhi();
    eleSCEt_1    = electron1->GetEnergySC()*sin(2.*atan(exp(-electron1->GetEtaSC())));
    eleSCEta_1   = electron1->GetEtaSC();
    eleSCPhi_1   = electron1->GetPhiSC();
    eleEoverP_1  = electron1->GetEoverP();
   
    eleCharge_2  = electron2->GetCharge();
    elePt_2      = electron2->GetPt();
    eleEta_2     = electron2->GetEta();
    elePhi_2     = electron2->GetPhi();
    eleSCEt_2    = electron2->GetEnergySC()*sin(2.*atan(exp(-electron2->GetEtaSC())));
    eleSCEta_2   = electron2->GetEtaSC();
    eleSCPhi_2   = electron2->GetPhiSC();
    eleEoverP_2  = electron2->GetEoverP(); 
    ////////////////////////////////////////
    nVtx = vertices.size();
    for(auto vertex : vertices){
     xVtx = vertex->GetPVertexX();
     yVtx = vertex->GetPVertexY();
     zVtx = vertex->GetPVertexZ();
   }
    //////////////////////////////////////////////////
    // reco+ID scale factor   
    double sf1_reco = SF_reco(elePt_1,eleEta_1);
    double sf2_reco = SF_reco(elePt_2,eleEta_2);
    SFweight_reco[0] = sf1_reco*sf2_reco;
    
    for (int ivar=1; ivar<16; ivar++) {
      double sf1p_reco=sf1_reco, sf2p_reco=sf2_reco;
      if (ireg(elePt_1,eleEta_1)==ivar) sf1p_reco += SF_uncert_reco(elePt_1,eleEta_1);
      if (ireg(elePt_2,eleEta_2)==ivar) sf2p_reco += SF_uncert_reco(elePt_2,eleEta_2);
      SFweight_reco[ivar] = sf1p_reco*sf2p_reco;
    }

    // trigger scale factor
    double sf1 = SF_trig(eleSCEt_1,eleSCEta_1);
    double sf2 = SF_trig(eleSCEt_2,eleSCEta_2);
    SFweight_trig[0] = sf1*sf2;
    
    for (int ivar=1; ivar<16; ivar++) {
      double sf1p=sf1, sf2p=sf2;
      if (ireg(eleSCEt_1,eleSCEta_1)==ivar) sf1p += SF_uncert_trig(eleSCEt_1,eleSCEta_1);
      if (ireg(eleSCEt_2,eleSCEta_2)==ivar) sf2p += SF_uncert_trig(eleSCEt_2,eleSCEta_2);
      SFweight_trig[ivar] = sf1p*sf2p;
    }
    
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


   cos_photon_pair_helicity0 = cosphotonpair(ele1, diele, 0); // Boost of one photon in the pair direction (in the rest frame of the pair). The other will be at pi rads from the 1st.
   cos_photon_pair_helicity1 = cosphotonpair(ele1, diele, 1); 
   costhetastar = costhetastar_CS(ele1,diele);

    
    if(ok_chexcl_extrk==1){
      charged_excl++;
      hist->SetBinContent(4,charged_excl);
      hist_wozdc->SetBinContent(4,charged_excl);
      if(ok_neuexcl==1){
	neutral_excl++;
	hist->SetBinContent(5,neutral_excl);
	hist_wozdc->SetBinContent(5,neutral_excl);
	if(vSum_ee_M>5){
	  dielemass_wozdc++;
	  hist_wozdc->SetBinContent(6,dielemass_wozdc);
	  if(vSum_ee_Pt<1){
	    dielept_wozdc++;
	    hist_wozdc->SetBinContent(7,dielept_wozdc);
	    if(ele_acop<0.01){
	      acop_cut_wozdc++;
	      hist_wozdc->SetBinContent(8,acop_cut_wozdc);
	    } //acop cut
	  }//diele pt
	}//mass
      }// neutral excl
    }//charged excl
    
    if(ok_chexcl_extrk==1 && ok_neuexcl==1 && ok_zdcexcl==1){
      zdc_excl++;
      hist->SetBinContent(6,zdc_excl);
      if(vSum_ee_M>5){
	dielemass++;
	hist->SetBinContent(7,dielemass);
	if(vSum_ee_Pt<1){
	  dielept++;
	  hist->SetBinContent(8,dielept);
	  if(ele_acop<0.01){
	    acop_cut++;
	    hist->SetBinContent(9,acop_cut);
	  } //acop cut
	}//diele pt
      }//mass
    }//zdc cut
    
    tr->Fill(); 
  } //nevents
  Log(0) << "Number of events triggered:" << trigger_passed << "\n" ;
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


int ireg(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 1;
      else if (et<4) return 2;
      else if (et<5) return 3;
      else if (et<6) return 4;
      else if (et<7) return 5;
      else if (et<10) return 6;
      else if (et<14) return 7;
      else return 8;
   } else {
      if (et<3) return 9;
      else if (et<4) return 10;
      else if (et<5) return 11;
      else if (et<6) return 12;
      else if (et<7) return 13;
      else if (et<10) return 14;
      else if (et<14) return 15;
      else return 16;
   }
}

double SF_reco(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 3.0043;
      else if (et<4) return 1.1693;
      else if (et<5) return 0.94329;
      else if (et<6) return 0.963789;
      else if (et<7) return 0.966706;
      else if (et<10) return 0.971721;
      else if (et<14) return 0.997961;
      else return 0.974345;
   } else {
      if (et<3) return 3.55878;
      else if (et<4) return 1.23809;
      else if (et<5) return 1.0068;
      else if (et<6) return 1.04464;
      else if (et<7) return 1.09334;
      else if (et<10) return 1.05342;
      else if (et<14) return 1.02881;
      else return 1.10496;
   }
}

double SF_uncert_reco(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 0.438893;
      else if (et<4) return 0.0392326;
      else if (et<5) return 0.011089;
      else if (et<6) return 0.00769222;
      else if (et<7) return 0.00751307;
      else if (et<10) return 0.00577934;
      else if (et<14) return 0.00887761;
      else return 0.0183508;
   } else {
     if (et<3) return 1.46253;
      else if (et<4) return 0.0953307;
      else if (et<5) return 0.041571;
      else if (et<6) return 0.0359209;
      else if (et<7) return 0.0359005;
      else if (et<10) return 0.0295281;
      else if (et<14) return 0.0625413;
      else return 0.198791;
   }
}

double SF_trig(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 1.20499;
      else if (et<4) return 1.08971;
      else if (et<5) return 1.04186;
      else if (et<6) return 1.02313;
      else if (et<7) return 1.02668;
      else if (et<10) return 1.02;
      else if (et<14) return 1.01338;
      else return 1.00665;
   } else {
      if (et<3) return 0.964039;
      else if (et<4) return 0.960585;
      else if (et<5) return 0.961264;
      else if (et<6) return 0.813962;
      else if (et<7) return 0.872495;
      else if (et<10) return 0.857176;
      else if (et<14) return 0.812907;
      else return 1.06977;
   }
}

double SF_uncert_trig(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 0.0650598;
      else if (et<4) return 0.0145146;
      else if (et<5) return 0.0051025;
      else if (et<6) return 0.00298585;
      else if (et<7) return 0.00243375;
      else if (et<10) return 0.00162252;
      else if (et<14) return 0.00201474;
      else return 0.00607588;
   } else {
     if (et<3) return 0.151598;
      else if (et<4) return 0.0556211;
      else if (et<5) return 0.03333;
      else if (et<6) return 0.0318;
      else if (et<7) return 0.0305721;
      else if (et<10) return 0.0275402;
      else if (et<14) return 0.0718492;
      else return 0.12731;
   }
}



//_____________________________________________________________________________
//     Angle between direction of P1 in the restframe of the pair (P1+P2)
//    and the direction of the pair (P1+P2) in the labframe.
/*

• Collins‐Soper frame: Simplest anisotropy (purely polar)
• Helicity frame: smallest polar and largest azimuthal anisotropies, indefinite tilt
• Gottfried‐Jackson frame: midway between Collins‐Soper and helicity frames

*/

double cosphotonpair(TLorentzVector p1, TLorentzVector pair, bool helicityFrame )
{

  double cos = 0.;

  // Boost of one photon in the pair direction (i.e. to the rest frame of the pair). The other will be at pi rads from the 1st.
  //TVector3 vpair = pair.Vect();
  TVector3 vpair = pair.BoostVector();
  p1.Boost(-vpair);

  // Angle of the boosted-vector with respect to the direction of the pair (Helicity frame)
  cos = TMath::Cos( p1.Angle( pair.Vect() ));

  if (helicityFrame) return cos;

  // Angle of the boosted-vector with respect to the direction of the z-axis (Gottfrid-Jackson frame)
  TVector3 zaxis = TVector3(0.,0.,1.);
  cos = TMath::Cos( p1.Angle( zaxis ));

  return cos;

}

//_____________________________________________________________________________
//  costheta(angle) of the photon in the Collins-Soper frame
/* 

Eq. (2.54) of https://www-d0.fnal.gov/results/publications_talks/thesis/guo_feng/thesis.pdf (SUNY, 2010)
Eq. page 8 of ATLAS paper: arXiv:2107.09330v1 [hep-ex]
*/

//double LbL_QED_lhe_analysis::costhetastar_CS(TLorentzVector p1, TLorentzVector p2, TLorentzVector pair)
double costhetastar_CS(TLorentzVector p1, TLorentzVector pair)
{

  //double Q2 = pair*pair;
  //double QT = pair.Pt();
  //double pp1 = (p1.E()+p1.Pz())/TMath::Sqrt(2); //P^0 and P^3 represent the energy and z component
  //double pm1 = (p1.E()-p1.Pz())/TMath::Sqrt(2);
  //double pp2 = (p2.E()+p2.Pz())/TMath::Sqrt(2);
  //double pm2 = (p2.E()-p2.Pz())/TMath::Sqrt(2);

  //double costhetastarCS = 2.*(pp1*pm2-pm1*pp2)/TMath::Sqrt(Q2*(Q2+QT*QT));

  //double costhetastarCS = 2.*(pair.E()*p1.Pz()-pair.Pz()*p1.E())/(pair.M()*pair.Mt());

  double costhetastarCS = 2.*(pair.E()*p1.Pz()-pair.Pz()*p1.E())/(pair.M()*pair.Mt());

  return costhetastarCS;

}
