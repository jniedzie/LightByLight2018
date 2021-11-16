//  SelectQEDEvents
//
//  Created by Ruchi Chudasama on 18/03/2021
//
//  Selects anomalous events in data

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
int    mono_nPho;
float  monoPhoEt;
float  monoPhoEta;
float  monoPhoPhi;
float  monoPhoSCEt;
float  monoPhoSCEta;
float  monoPhoSCPhi;
int    monoPhook_zdcexcl;
float  monoPhoEtaWidth;
float  monoPhoHoverE;
float  monoPhoEnergyTop;
float  monoPhoEnergyBottom;
float  monoPhoEnergyLeft;
float  monoPhoEnergyRight;
float  monoPhoEnergyCrysMax;
float  monoPhoSeedTime;
float  monoPhoSigmaIEta;
float  leadingEmEnergy_EB;
float  leadingEmEnergy_EE;
float  leadingHadEnergy_HB; 
float  leadingHadEnergy_HE;
float  leadingHadEnergy_HF_Plus;
float  leadingHadEnergy_HF_Minus;
int    mono_nL1Pho;
std::vector<float>  monoPhoL1Et;
std::vector<float>  monoPhoL1Eta;
std::vector<float>  monoPhoL1Phi;
std::vector<float>  monoPhoL1deta;
std::vector<float>  monoPhoL1dphi;
std::vector<float>  monoPhoL1dr;
int    monoPho_nPixelCluster;
int    monoPho_nPixelRecHits;

int    mono_nEle;
int    monoEleCharge;
float  monoElePt;
float  monoEleEta;
float  monoElePhi;
int    monoEleok_zdcexcl;
int    monoEleok_chexcl_extrk;
int    monoEle_nmatchedTrk;
std::vector<int>     monoEle_matchedTrkCharge;
std::vector<float>   monoEle_matchedTrkPt;
std::vector<float>   monoEle_matchedTrkEta;
std::vector<float>   monoEle_matchedTrkPhi;
int    monoEle_nExtraTrk;
std::vector<int>     monoEle_ExtraTrkCharge;
std::vector<float>   monoEle_ExtraTrkPt;
std::vector<float>   monoEle_ExtraTrkEta;
std::vector<float>   monoEle_ExtraTrkPhi;
int    monoEle_nPixelCluster;
int    monoEle_nPixelRecHits;

int    tri_nPho;
std::vector<float>  triPhoEt;
std::vector<float>  triPhoEta;
std::vector<float>  triPhoPhi;
std::vector<float>  triPhoEtaWidth;
std::vector<float>  triPhoHoverE;
std::vector<float>  triPhoEnergyTop;
std::vector<float>  triPhoEnergyBottom;
std::vector<float>  triPhoEnergyLeft;
std::vector<float>  triPhoEnergyRight;
std::vector<float>  triPhoEnergyCrysMax;
std::vector<float>  triPhoSeedTime;
std::vector<float>  triPhoSigmaIEta;
int    triPhook_zdcexcl;
int    triPhook_neuexcl;
int    triPhook_chexcl;
float  triPho_invmass;
float  triPho_pt;
float  triPho_rapidity;
int    triPho_nPixelCluster;
int    triPho_nPixelRecHits;

int    tri_nEle;
std::vector<int>    triEleCharge;
std::vector<float>  triElePt;
std::vector<float>  triEleEta;
std::vector<float>  triElePhi;
int    triEleok_zdcexcl;
int    triEleok_neuexcl;
int    triEleok_chexcl_extrk;
float  triEle_invmass;
float  triEle_pt;
float  triEle_rapidity;
int    triEle_nmatchedTrk;
std::vector<int>     triEle_matchedTrkCharge;
std::vector<float>   triEle_matchedTrkPt;
std::vector<float>   triEle_matchedTrkEta;
std::vector<float>   triEle_matchedTrkPhi;
int    triEle_nExtraTrk;
std::vector<int>     triEle_ExtraTrkCharge;
std::vector<float>   triEle_ExtraTrkPt;
std::vector<float>   triEle_ExtraTrkEta;
std::vector<float>   triEle_ExtraTrkPhi;
int    triEle_nPixelCluster;
int    triEle_nPixelRecHits;


/// initialise tree
void InitmonoPhoTree(TTree *tr) {
  tr->Branch("run",                 &run,           "run/I");
  tr->Branch("ls",                  &ls,            "ls/I");
  tr->Branch("evtnb",               &evtnb,         "evtnb/I");
  tr->Branch("mono_nPho",               &mono_nPho,       "mono_nPho/I");
  tr->Branch("monoPhoEt",               &monoPhoEt,       "monoPhoEt/F");
  tr->Branch("monoPhoEta",              &monoPhoEta,      "monoPhoEta/F");
  tr->Branch("monoPhoPhi",              &monoPhoPhi,      "monoPhoPhi/F");
  tr->Branch("monoPhoSCEt",             &monoPhoSCEt,     "monoPhoSCEt/F");
  tr->Branch("monoPhoSCEta",            &monoPhoSCEta,    "monoPhoSCEta/F");
  tr->Branch("monoPhoSCPhi",            &monoPhoSCPhi,    "monoPhoSCPhi/F");
  tr->Branch("monoPhook_zdcexcl",       &monoPhook_zdcexcl,"monoPhook_zdcexcl/I");
  tr->Branch("monoPhoEtaWidth",         &monoPhoEtaWidth,  "monoPhoEtaWidth/F");
  tr->Branch("monoPhoHoverE",           &monoPhoHoverE,    "monoPhoHoverE/F");
  tr->Branch("monoPhoEnergyTop",        &monoPhoEnergyTop, "monoPhoEnergyTop/F");
  tr->Branch("monoPhoEnergyBottom",     &monoPhoEnergyBottom,"monoPhoEnergyBottom/F");
  tr->Branch("monoPhoEnergyLeft",       &monoPhoEnergyLeft, "monoPhoEnergyLeft/F");
  tr->Branch("monoPhoEnergyRight",      &monoPhoEnergyRight, "monoPhoEnergyRight/F");
  tr->Branch("monoPhoEnergyCrysMax",    &monoPhoEnergyCrysMax, "monoPhoEnergyCrysMax/F");
  tr->Branch("monoPhoSeedTime",         &monoPhoSeedTime,      "monoPhoSeedTime/F");
  tr->Branch("monoPhoSigmaIEta",        &monoPhoSigmaIEta,    "monoPhoSigmaIEta/F");
  tr->Branch("leadingEmEnergy_EB",  &leadingEmEnergy_EB,"leadingEmEnergy_EB/F");
  tr->Branch("leadingEmEnergy_EE",  &leadingEmEnergy_EE,"leadingEmEnergy_EE/F");
  tr->Branch("leadingHadEnergy_HB",  &leadingHadEnergy_HB,"leadingHadEnergy_HB/F");
  tr->Branch("leadingHadEnergy_HE",  &leadingHadEnergy_HE,"leadingHadEnergy_HE/F");
  tr->Branch("leadingHadEnergy_HF_Plus",  &leadingHadEnergy_HF_Plus,"leadingHadEnergy_HF_Plus/F");
  tr->Branch("leadingHadEnergy_HF_Minus",  &leadingHadEnergy_HF_Minus,"leadingHadEnergy_HF_Minus/F");
  tr->Branch("mono_nL1Pho",             &mono_nL1Pho,     "mono_nL1Pho/I");
  tr->Branch("monoPhoL1Et",             &monoPhoL1Et);
  tr->Branch("monoPhoL1Eta",            &monoPhoL1Eta);
  tr->Branch("monoPhoL1Phi",            &monoPhoL1Phi);
  tr->Branch("monoPhoL1deta",           &monoPhoL1deta);
  tr->Branch("monoPhoL1dphi",           &monoPhoL1dphi);
  tr->Branch("monoPhoL1dr",             &monoPhoL1dr);
  tr->Branch("monoPho_nPixelCluster",   &monoPho_nPixelCluster,"monoPho_nPixelCluster/I");
  tr->Branch("monoPho_nPixelRecHits",   &monoPho_nPixelRecHits,"monoPho_nPixelRecHits/I");
}

void InitmonoEleTree(TTree *tr) {
  tr->Branch("mono_nEle",               &mono_nEle,       "mono_nEle/I");
  tr->Branch("monoEleCharge",           &monoEleCharge,   "monoEleCharge/I");
  tr->Branch("monoElePt",               &monoElePt,       "monoElePt/F");
  tr->Branch("monoEleEta",              &monoEleEta,      "monoEleEta/F");
  tr->Branch("monoElePhi",              &monoElePhi,      "monoElePhi/F");
  tr->Branch("monoEleok_zdcexcl",       &monoEleok_zdcexcl,"monoEleok_zdcexcl/I");
  tr->Branch("monoEleok_chexcl_extrk",  &monoEleok_chexcl_extrk,"monoEleok_chexcl_extrk/I");

  tr->Branch("monoEle_nmatchedTrk",               &monoEle_nmatchedTrk,       "monoEle_nmatchedTrk/I");
  tr->Branch("monoEle_matchedTrkCharge",           &monoEle_matchedTrkCharge);
  tr->Branch("monoEle_matchedTrkPt",               &monoEle_matchedTrkPt);
  tr->Branch("monoEle_matchedTrkEta",              &monoEle_matchedTrkEta);
  tr->Branch("monoEle_matchedTrkPhi",              &monoEle_matchedTrkPhi);
  tr->Branch("monoEle_nExtraTrk",                &monoEle_nExtraTrk,       "monoEle_nExtraTrk/I");
  tr->Branch("monoEle_ExtraTrkCharge",           &monoEle_ExtraTrkCharge);
  tr->Branch("monoEle_ExtraTrkPt",               &monoEle_ExtraTrkPt);
  tr->Branch("monoEle_ExtraTrkEta",              &monoEle_ExtraTrkEta);
  tr->Branch("monoEle_ExtraTrkPhi",              &monoEle_ExtraTrkPhi);
  tr->Branch("monoEle_nPixelCluster",   &monoEle_nPixelCluster,"monoEle_nPixelCluster/I");
  tr->Branch("monoEle_nPixelRecHits",   &monoEle_nPixelRecHits,"monoEle_nPixelRecHits/I");
}
  
void InittriPhoTree(TTree *tr) {
  tr->Branch("run",                 &run,           "run/I");
  tr->Branch("ls",                  &ls,            "ls/I");
  tr->Branch("evtnb",               &evtnb,         "evtnb/I");
  tr->Branch("tri_nPho",               &tri_nPho,       "tri_nPho/I");
  tr->Branch("triPhoEt",               &triPhoEt);
  tr->Branch("triPhoEta",              &triPhoEta);
  tr->Branch("triPhoPhi",              &triPhoPhi);
  tr->Branch("triPhoEtaWidth",         &triPhoEtaWidth);
  tr->Branch("triPhoHoverE",           &triPhoHoverE);
  tr->Branch("triPhoEnergyTop",        &triPhoEnergyTop);
  tr->Branch("triPhoEnergyBottom",     &triPhoEnergyBottom);
  tr->Branch("triPhoEnergyLeft",       &triPhoEnergyLeft);
  tr->Branch("triPhoEnergyRight",      &triPhoEnergyRight);
  tr->Branch("triPhoEnergyCrysMax",    &triPhoEnergyCrysMax);
  tr->Branch("triPhoSeedTime",         &triPhoSeedTime);
  tr->Branch("triPhoSigmaIEta",        &triPhoSigmaIEta);
  tr->Branch("triPhook_zdcexcl",       &triPhook_zdcexcl,"triPhook_zdcexcl/I");
  tr->Branch("triPhook_neuexcl",       &triPhook_neuexcl,"triPhook_neuexcl/I");
  tr->Branch("triPhook_chexcl",        &triPhook_chexcl, "triPhook_chexcl/I");
  tr->Branch("triPho_invmass",         &triPho_invmass,  "triPho_invmass/F");
  tr->Branch("triPho_pt",              &triPho_pt,       "triPho_pt/F");
  tr->Branch("triPho_rapidity",        &triPho_rapidity,  "triPho_rapidity/F");
  tr->Branch("triPho_nPixelCluster",   &triPho_nPixelCluster,"triPho_nPixelCluster/I");
  tr->Branch("triPho_nPixelRecHits",   &triPho_nPixelRecHits,"triPho_nPixelRecHits/I");
}


void InittriEleTree(TTree *tr) {
  tr->Branch("tri_nEle",               &tri_nEle,       "tri_nEle/I");
  tr->Branch("triEleCharge",           &triEleCharge);
  tr->Branch("triElePt",               &triElePt);
  tr->Branch("triEleEta",              &triEleEta);
  tr->Branch("triElePhi",              &triElePhi);
  
  tr->Branch("triEleok_zdcexcl",       &triEleok_zdcexcl,"triEleok_zdcexcl/I");
  tr->Branch("triEleok_neuexcl",       &triEleok_neuexcl,"triEleok_neuexcl/I");
  tr->Branch("triEleok_chexcl_extrk",  &triEleok_chexcl_extrk, "triEleok_chexcl_extrk/I");
  tr->Branch("triEle_invmass",         &triEle_invmass,  "triEle_invmass/F");
  tr->Branch("triEle_pt",              &triEle_pt,       "triEle_pt/F");
  tr->Branch("triEle_rapidity",        &triEle_rapidity,  "triEle_rapidity/F");
  tr->Branch("triEle_nmatchedTrk",               &triEle_nmatchedTrk,       "triEle_nmatchedTrk/I");
  tr->Branch("triEle_matchedTrkCharge",           &triEle_matchedTrkCharge);
  tr->Branch("triEle_matchedTrkPt",               &triEle_matchedTrkPt);
  tr->Branch("triEle_matchedTrkEta",              &triEle_matchedTrkEta);
  tr->Branch("triEle_matchedTrkPhi",              &triEle_matchedTrkPhi);
  tr->Branch("triEle_nExtraTrk",                &triEle_nExtraTrk,       "triEle_nExtraTrk/I");
  tr->Branch("triEle_ExtraTrkCharge",           &triEle_ExtraTrkCharge);
  tr->Branch("triEle_ExtraTrkPt",               &triEle_ExtraTrkPt);
  tr->Branch("triEle_ExtraTrkEta",              &triEle_ExtraTrkEta);
  tr->Branch("triEle_ExtraTrkPhi",              &triEle_ExtraTrkPhi);
  tr->Branch("triEle_nPixelCluster",            &triEle_nPixelCluster,"triEle_nPixelCluster/I");
  tr->Branch("triEle_nPixelRecHits",            &triEle_nPixelRecHits,"triEle_nPixelRecHits/I");
}


// reset all variables
void ResetmonoPhoVars() {
  run = -999;
  ls= -999;
  evtnb = -999;
  mono_nPho = 0 ;
  monoPhoEt= -999 ;
  monoPhoEta= -999 ;
  monoPhoPhi= -999 ;
  monoPhoSCEt= -999 ;
  monoPhoSCEta= -999 ;
  monoPhoSCPhi= -999 ;
  monoPhook_zdcexcl = -999 ;
  monoPhoEtaWidth = -999 ;
  monoPhoHoverE = -999 ;
  monoPhoEnergyTop = -999 ;
  monoPhoEnergyBottom = -999 ;
  monoPhoEnergyLeft = -999 ;
  monoPhoEnergyRight = -999 ;
  monoPhoEnergyCrysMax = -999 ;
  monoPhoSeedTime = -999 ;
  monoPhoSigmaIEta = -999 ;
  leadingEmEnergy_EB = -999;
  leadingEmEnergy_EE = -999;
  leadingHadEnergy_HB = -999; 
  leadingHadEnergy_HE = -999;
  leadingHadEnergy_HF_Plus = -999;
  leadingHadEnergy_HF_Minus = -999;
  mono_nL1Pho = 0;
  monoPhoL1Et.clear();
  monoPhoL1Eta.clear();
  monoPhoL1Phi.clear();
  monoPhoL1deta.clear();
  monoPhoL1dphi.clear();
  monoPhoL1dr.clear();
  monoPho_nPixelCluster = -999;
  monoPho_nPixelRecHits = -999;
}

void ResetmonoEleVars() {
  mono_nEle = 0 ;
  monoEleCharge = -999 ;
  monoElePt = -999 ;
  monoEleEta = -999 ;
  monoElePhi = -999 ;
  monoEleok_zdcexcl = -999 ;
  monoEleok_chexcl_extrk = -999 ;
  monoEle_nmatchedTrk = -999 ;
  monoEle_matchedTrkCharge .clear();
  monoEle_matchedTrkPt .clear();
  monoEle_matchedTrkEta .clear();
  monoEle_matchedTrkPhi.clear();
  monoEle_nExtraTrk = -999 ;
  monoEle_ExtraTrkCharge .clear();
  monoEle_ExtraTrkPt .clear();
  monoEle_ExtraTrkEta .clear();
  monoEle_ExtraTrkPhi .clear();
  monoEle_nPixelCluster = -999;
  monoEle_nPixelRecHits = -999;

}
 
void ResettriPhoVars() {
  tri_nPho = 0 ;
  triPhoEt.clear();
  triPhoEta.clear();
  triPhoPhi.clear();
  triPhoEtaWidth.clear() ;
  triPhoHoverE.clear() ;
  triPhoEnergyTop.clear() ;
  triPhoEnergyBottom.clear() ;
  triPhoEnergyLeft.clear() ;
  triPhoEnergyRight.clear() ;
  triPhoEnergyCrysMax.clear() ;
  triPhoSeedTime.clear() ;
  triPhoSigmaIEta.clear() ;
  triPhook_zdcexcl = -999 ;
  triPhook_neuexcl = -999 ;
  triPhook_chexcl = -999 ;
  triPho_invmass = -999 ;
  triPho_pt    = -999 ;
  triPho_rapidity = -999 ;
  triPho_nPixelCluster = -999;
  triPho_nPixelRecHits = -999;
}


void ResettriEleVars() {
  tri_nEle = 0 ;
  triEleCharge.clear();
  triElePt.clear();
  triEleEta.clear();
  triElePhi.clear();

  triEleok_zdcexcl = -999 ;
  triEleok_neuexcl = -999 ;
  triEleok_chexcl_extrk = -999 ;
  triEle_invmass = -999 ;
  triEle_pt    = -999 ;
  triEle_rapidity = -999 ;
  triEle_nmatchedTrk = -999 ;
  triEle_matchedTrkCharge .clear();
  triEle_matchedTrkPt .clear();
  triEle_matchedTrkEta .clear();
  triEle_matchedTrkPhi.clear();
  triEle_nExtraTrk = -999 ;
  triEle_ExtraTrkCharge .clear();
  triEle_ExtraTrkPt .clear();
  triEle_ExtraTrkEta .clear();
  triEle_ExtraTrkPhi .clear();
  triEle_nPixelCluster = -999;
  triEle_nPixelRecHits = -999;
}

  

/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters:\n";
    Log(0)<<"./selectAnomalousEvents configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }
  
  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
}


void FillmonoPhotonTree(Event &event, TTree* tr, string datasetName){
  
  ResetmonoPhoVars();  
  
  run = event.GetRunNumber();
  ls = event.GetLumiSection();
  evtnb = event.GetEventNumber();

  // select one exclusive photon
  if(event.GetPhysObjects(EPhysObjType::kPhoton).size() != 1) return;
  
  // select one photon passing ID criteria
  if(event.GetPhysObjects(EPhysObjType::kGoodPhoton).size() != 1) return;
  
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  auto electrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  auto muons     = event.GetPhysObjects(EPhysObjType::kGoodMuon);
  auto photon    = event.GetPhysObjects(EPhysObjType::kGoodPhoton)[0];
  auto caloTower = event.GetPhysObjects(EPhysObjType::kCaloTower);
  auto L1EGs     = event.GetPhysObjects(EPhysObjType::kL1EG);
  
  // apply charged and neutral exclusivity
  
  if(genTracks.size()!=0 || electrons.size()!=0 || muons.size()!=0) return;

  if(event.HasAdditionalTowers())return;

  if(datasetName=="Data")monoPhook_zdcexcl = event.GetTotalZDCenergyPos() < 10000 && event.GetTotalZDCenergyNeg() < 10000;
 
  monoPho_nPixelCluster = event.GetNpixelClusters();
  monoPho_nPixelRecHits =  event.GetNpixelRecHits();

  // start filling photon variables
  monoPhoEt      = photon->GetEt();
  monoPhoEta     = photon->GetEta();
  monoPhoPhi     = photon->GetPhi();
  monoPhoSCEt    = photon->GetEnergySC()*sin(2.*atan(exp(-photon->GetEtaSC())));
  monoPhoSCEta   = photon->GetEtaSC();
  monoPhoSCPhi   = photon->GetPhiSC();
  monoPhoEtaWidth      = photon->GetEtaWidth();
  monoPhoHoverE        = photon->GetHoverE();
  monoPhoEnergyTop     = photon->GetEnergyCrystalTop();
  monoPhoEnergyBottom  = photon->GetEnergyCrystalBottom(); 
  monoPhoEnergyLeft    = photon->GetEnergyCrystalLeft();
  monoPhoEnergyRight   = photon->GetEnergyCrystalRight();
  monoPhoEnergyCrysMax = photon->GetEnergyCrystalMax();
  monoPhoSeedTime      = photon->GetSeedTime();
  monoPhoSigmaIEta     = photon->GetSigmaEta2012();

  for (auto L1EG : L1EGs) {
  monoPhoL1Et    .push_back(L1EG->GetEt());
  monoPhoL1Eta   .push_back(L1EG->GetEta());
  monoPhoL1Phi   .push_back(L1EG->GetPhi());
  monoPhoL1deta  .push_back(getDETA(L1EG->GetEta(), monoPhoEta));
  monoPhoL1dphi  .push_back(getDPHI(L1EG->GetPhi(), monoPhoPhi));
  monoPhoL1dr    .push_back(getDR(L1EG->GetEta(), L1EG->GetPhi(), monoPhoEta , monoPhoPhi));
  mono_nL1Pho++;
  }
  
  float  EmEnergy_EB = 0;
  float  EmEnergy_EE = 0;
  float  HadEnergy_HB = 0;
  float  HadEnergy_HE = 0;
  float  HadEnergy_HF_Plus = 0;
  float  HadEnergy_HF_Minus = 0;
  
  for(auto tower : caloTower){
    
    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    if(subdetEm==kEB){ // check EB exclusivity
      if (getDPHI(tower->GetPhi(), monoPhoPhi)< config.params("maxDeltaPhiEB") && getDETA(tower->GetEta(), monoPhoEta)<config.params("maxDeltaEtaEB")) continue;
      if (tower->GetEnergyEm() > EmEnergy_EB){                         
	EmEnergy_EB = tower->GetEnergyEm();
      }
    }
    
    if(subdetEm==kEE){ // Check EE exclusivity
      if(fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
      if (getDPHI(tower->GetPhi(), monoPhoPhi)< config.params("maxDeltaPhiEE") && getDETA(tower->GetEta(), monoPhoEta)<config.params("maxDeltaEtaEE")) continue;
      if (tower->GetEnergyEm() > EmEnergy_EE){                         
	EmEnergy_EE = tower->GetEnergyEm();
      }
    }
    
    if(subdetHad==kHB){ // Check HB exclusivity
      if(tower->GetEnergyHad() > HadEnergy_HB){
	HadEnergy_HB = tower->GetEnergyHad();
      }
    }
    
    if(subdetHad==kHE){ // Check HE exclusivity
      if(tower->GetEnergyHad() > HadEnergy_HE){
	HadEnergy_HE = tower->GetEnergyHad();
      }
    }
    
    if(subdetHad==kHFp){ // Check HF exclusivity
      if(tower->GetEnergy() > HadEnergy_HF_Plus){
	HadEnergy_HF_Plus = tower->GetEnergy();
      }
    } // HF exclusivity plus
    
    if(subdetHad==kHFm){ // Check HF exclusivity
      if(tower->GetEnergy() > HadEnergy_HF_Minus){
	HadEnergy_HF_Minus = tower->GetEnergy();
      }
    } // HF exclusivity minus
  }//tower
 
  leadingEmEnergy_EB        = EmEnergy_EB;
  leadingEmEnergy_EE        = EmEnergy_EE;
  leadingHadEnergy_HB       = HadEnergy_HB;
  leadingHadEnergy_HE       = HadEnergy_HE;
  leadingHadEnergy_HF_Plus  = HadEnergy_HF_Plus;
  leadingHadEnergy_HF_Minus = HadEnergy_HF_Minus;
  
  mono_nPho++;
  tr->Fill(); 
} //fill mono photon tree


void FillmonoEleTree(Event &event, TTree* tr , string datasetName){
  
  ResetmonoEleVars();  
  
  // select one exclusive electron
  if(event.GetPhysObjects(EPhysObjType::kGoodElectron).size() != 1) return;
  
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  auto electron  = event.GetPhysObjects(EPhysObjType::kGoodElectron)[0];
  auto caloTower = event.GetPhysObjects(EPhysObjType::kCaloTower);
  
  // apply neutral exclusivity
  if(event.HasAdditionalTowers())return;
  if(datasetName=="Data")monoEleok_zdcexcl = event.GetTotalZDCenergyPos() < 10000 && event.GetTotalZDCenergyNeg() < 10000;

  monoEle_nPixelCluster = event.GetNpixelClusters();
  monoEle_nPixelRecHits =  event.GetNpixelRecHits();
  
  // Find tracks that match electrons
  PhysObjects matchingTracks;
  PhysObjects extraTracks;
  
  for (auto trk : genTracks) {
    if (getDPHI(trk->GetPhi(), electron->GetPhi())<0.7 && getDETA(trk->GetEta(), electron->GetEta())<0.15) matchingTracks.push_back(trk);
    else                                                                                                   extraTracks.push_back(trk);
  }
    
  // start filling electron variables
  monoEle_nmatchedTrk = matchingTracks.size() ;
  for (auto matchingTrack : matchingTracks) {
    monoEle_matchedTrkCharge .push_back(matchingTrack->GetCharge());
    monoEle_matchedTrkPt     .push_back(matchingTrack->GetPt());
    monoEle_matchedTrkEta    .push_back(matchingTrack->GetEta());
    monoEle_matchedTrkPhi    .push_back(matchingTrack->GetPhi());
  }
  
  monoEle_nExtraTrk = extraTracks.size() ;
  monoEleok_chexcl_extrk = monoEle_nExtraTrk==0;
  for (auto extraTrack : extraTracks) {
    monoEle_ExtraTrkCharge  .push_back(extraTrack->GetCharge());
    monoEle_ExtraTrkPt      .push_back(extraTrack->GetPt());
    monoEle_ExtraTrkEta     .push_back(extraTrack->GetEta());
    monoEle_ExtraTrkPhi     .push_back(extraTrack->GetPhi());
  }
  monoEleCharge  = electron->GetCharge();
  monoElePt      = electron->GetPt();
  monoEleEta     = electron->GetEta();
  monoElePhi     = electron->GetPhi();
  mono_nEle++ ;
  tr->Fill(); 
} //fill mono electron tree


void FilltriPhotonTree(Event &event, TTree* tr, string datasetName){
  
  ResettriPhoVars();  
  
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  auto electrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  auto muons     = event.GetPhysObjects(EPhysObjType::kGoodMuon);
  auto caloTower = event.GetPhysObjects(EPhysObjType::kCaloTower);
  
  // apply charged and neutral exclusivity
  
  triPhook_chexcl  = genTracks.size()==0 && electrons.size()==0 && muons.size()==0;
  triPhook_neuexcl = (!event.HasAdditionalTowers());
  if(datasetName=="Data")triPhook_zdcexcl = event.GetTotalZDCenergyPos() < 10000 && event.GetTotalZDCenergyNeg() < 10000;
  
  auto photons = event.GetPhysObjects(EPhysObjType::kGoodPhoton);
  PhysObjects isolatedPhotons;
  
  for(int i=0; i<photons.size(); i++){
    bool hasNerbyPhotons = false;
    for(int j=0; j<photons.size(); j++){
      if(i==j) continue;
      
      double deltaR = physObjectProcessor.GetDeltaR(*photons[i], *photons[j]);
      
      if(deltaR < 0.3){
        hasNerbyPhotons = true;
        break;
      }
    }
    if(!hasNerbyPhotons) isolatedPhotons.push_back(photons[i]);
  }
  
  if(isolatedPhotons.size() != 3) return;
  TLorentzVector triphoton = physObjectProcessor.GetTriphoton(*isolatedPhotons[0],
							      *isolatedPhotons[1],
							      *isolatedPhotons[2]);
  
  triPho_nPixelCluster = event.GetNpixelClusters();
  triPho_nPixelRecHits =  event.GetNpixelRecHits();

  triPho_invmass  = triphoton.M();
  triPho_pt       = triphoton.Pt();
  triPho_rapidity = triphoton.Rapidity();
 
  for( auto isolatedPhoton : isolatedPhotons){
    triPhoEt            .push_back(isolatedPhoton->GetEt());
    triPhoEta           .push_back(isolatedPhoton->GetEta());
    triPhoPhi           .push_back(isolatedPhoton->GetPhi());
    triPhoEtaWidth      .push_back(isolatedPhoton->GetEtaWidth());
    triPhoHoverE        .push_back(isolatedPhoton->GetHoverE());
    triPhoEnergyTop     .push_back(isolatedPhoton->GetEnergyCrystalTop());
    triPhoEnergyBottom  .push_back(isolatedPhoton->GetEnergyCrystalBottom()); 
    triPhoEnergyLeft    .push_back(isolatedPhoton->GetEnergyCrystalLeft());
    triPhoEnergyRight   .push_back(isolatedPhoton->GetEnergyCrystalRight());
    triPhoEnergyCrysMax .push_back(isolatedPhoton->GetEnergyCrystalMax());
    triPhoSeedTime      .push_back(isolatedPhoton->GetSeedTime());
    triPhoSigmaIEta     .push_back(isolatedPhoton->GetSigmaEta2012());
  } 
  
  tri_nPho++;
  tr->Fill(); 
} //fill tri photon tree


void FilltriElectronTree(Event &event, TTree* tr, string datasetName){
  
  ResettriEleVars();  
  
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  auto muons     = event.GetPhysObjects(EPhysObjType::kGoodMuon);
  auto caloTower = event.GetPhysObjects(EPhysObjType::kCaloTower);
  
  // apply charged and neutral exclusivity
  triEleok_neuexcl = (!event.HasAdditionalTowers());
  if(datasetName=="Data")triEleok_zdcexcl = event.GetTotalZDCenergyPos() < 10000 && event.GetTotalZDCenergyNeg() < 10000;
  
  auto electrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  PhysObjects isolatedElectrons;
  
  for(int i=0; i<electrons.size(); i++){
    bool hasNerbyElectrons = false;
    for(int j=0; j<electrons.size(); j++){
      if(i==j) continue;
      
      double deltaR = physObjectProcessor.GetDeltaR(*electrons[i], *electrons[j]);
      
      if(deltaR < 0.3){
        hasNerbyElectrons = true;
        break;
      }
    }
    if(!hasNerbyElectrons) isolatedElectrons.push_back(electrons[i]);
  }

  if(isolatedElectrons.size() != 3) return;
  std::cout << "isolatedElectrons size" << isolatedElectrons.size() << "  electron size:" << electrons.size() <<  std::endl; 

  triEle_nPixelCluster = event.GetNpixelClusters();
  triEle_nPixelRecHits =  event.GetNpixelRecHits();  
  
  double eleMass = 0.5109989461e-3;

  TLorentzVector ele1, ele2, ele3;
  ele1.SetPtEtaPhiM(isolatedElectrons[0]->GetPt(),isolatedElectrons[0]->GetEta(),isolatedElectrons[0]->GetPhi(),eleMass);
  ele2.SetPtEtaPhiM(isolatedElectrons[1]->GetPt(),isolatedElectrons[1]->GetEta(),isolatedElectrons[1]->GetPhi(),eleMass);
  ele3.SetPtEtaPhiM(isolatedElectrons[2]->GetPt(),isolatedElectrons[2]->GetEta(),isolatedElectrons[2]->GetPhi(),eleMass);

  TLorentzVector trielectron = ele1 + ele2 + ele3;
  
  triEle_invmass  = trielectron.M();
  triEle_pt       = trielectron.Pt();
  triEle_rapidity = trielectron.Rapidity();
 
  for( auto isolatedElectron : isolatedElectrons){
    triEleCharge  .push_back(isolatedElectron->GetCharge());
    triElePt      .push_back(isolatedElectron->GetPt());
    triEleEta     .push_back(isolatedElectron->GetEta());
    triElePhi     .push_back(isolatedElectron->GetPhi());
   } 

  // Find tracks that match electrons
  PhysObjects matchingTracks;
  PhysObjects extraTracks;
  
  for (auto trk : genTracks) {
    if ((getDPHI(trk->GetPhi(), isolatedElectrons[0]->GetPhi())<0.7 && getDETA(trk->GetEta(), isolatedElectrons[0]->GetEta())<0.15) ||
	(getDPHI(trk->GetPhi(), isolatedElectrons[1]->GetPhi())<0.7 && getDETA(trk->GetEta(), isolatedElectrons[1]->GetEta())<0.15) ||
	(getDPHI(trk->GetPhi(), isolatedElectrons[2]->GetPhi())<0.7 && getDETA(trk->GetEta(), isolatedElectrons[2]->GetEta())<0.15)) matchingTracks.push_back(trk);
    else                                                                                                   extraTracks.push_back(trk);
  }

  // start filling electron variables
  triEle_nmatchedTrk = matchingTracks.size() ;
  for (auto matchingTrack : matchingTracks) {
    triEle_matchedTrkCharge .push_back(matchingTrack->GetCharge());
    triEle_matchedTrkPt     .push_back(matchingTrack->GetPt());
    triEle_matchedTrkEta    .push_back(matchingTrack->GetEta());
    triEle_matchedTrkPhi    .push_back(matchingTrack->GetPhi());
  }
  
  triEle_nExtraTrk = extraTracks.size() ;
  triEleok_chexcl_extrk = triEle_nExtraTrk==0;
  for (auto extraTrack : extraTracks) {
    triEle_ExtraTrkCharge  .push_back(extraTrack->GetCharge());
    triEle_ExtraTrkPt      .push_back(extraTrack->GetPt());
    triEle_ExtraTrkEta     .push_back(extraTrack->GetEta());
    triEle_ExtraTrkPhi     .push_back(extraTrack->GetPhi());
  }

  tri_nEle++;
  tr->Fill(); 
} //fill tri Electron tree

/// Application starting point
int main(int argc, char* argv[])
{
  string configPath, inputPath, outputPath, sampleName;
  ReadInputArguments(argc, argv, configPath, inputPath, outputPath, sampleName);

  config = ConfigManager(configPath);
  EDataset dataset = datasetForName.at(sampleName);
 

  TH1D *hist_wozdc = new TH1D("hist_wozdc","",9,1,10);
 
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *monoPhotree = new TTree("monoPhoton_tree","");
  InitmonoPhoTree(monoPhotree);
  TTree *monoEletree = new TTree("monoElectron_tree","");
  InitmonoEleTree(monoEletree);
  TTree *triPhotree = new TTree("triPhoton_tree","");
  InittriPhoTree(triPhotree);
  TTree *triEletree = new TTree("triElectron_tree","");
  InittriEleTree(triEletree);

  TH1D *hist       = new TH1D("hist","",9,1,10);

  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int trigger_passed=0, twoGoodPho=0, oppCharge=0, neutral_excl=0, charged_excl=0, diphomass_wozdc=0, diphopt_wozdc=0;
  int acop_cut_wozdc=0, diphomass=0, diphopt=0, acop_cut = 0, zdc_excl=0;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
  //for(int iEvent=0; iEvent<5000; iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);

   // Check trigger
    //if(!event->HasTrigger(kSingleEG3noHF) && !event->HasTrigger(kSingleEG5noHF)) continue;
    if(!event->HasTrigger(kDoubleEG2noHF))continue;
 
    FillmonoPhotonTree(*event,monoPhotree,sampleName);
    FillmonoEleTree(*event,monoEletree,sampleName);
    FilltriPhotonTree(*event,triPhotree,sampleName);
    FilltriElectronTree(*event,triEletree,sampleName);
  } //event
  outFile->cd();
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

