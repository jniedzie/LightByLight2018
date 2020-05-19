#define DumpEvent_cxx
#include "DumpEvent.hpp"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>

#include <iostream>

using namespace std;

void DumpEvent::Loop(TString histfilename, bool dolowaco)
{
//   In a ROOT session, you can do:
//      root> .L DumpEvent.C
//      root> DumpEvent t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile *fhist = TFile::Open(histfilename, "RECREATE");

   // histogram declaration

   TH1F *h_run = new TH1F("h_run","run",10,326545,327561); // mean = 326970
   TH1F *h_event = new TH1F("h_event","event",10,0,5.26122e+08); // mean = 1.5994e+08
   TH1F *h_lumis = new TH1F("h_lumis","lumis",10,0,1170); // mean = 365.156
   TH1F *h_nSC = new TH1F("h_nSC","nSC",10,0,10); // mean = 3.46721
   TH1F *h_scE = new TH1F("h_scE","scE",25,0.,25.); // mean = 5.58546
   TH1F *h_scRawE = new TH1F("h_scRawE","scRawE",10,0.,20); // mean = 3.81686
   TH1F *h_scEta = new TH1F("h_scEta","scEta",12,-3,3); // mean = -0.0267188
   TH1F *h_scPhi = new TH1F("h_scPhi","scPhi",10,-3.14,3.14); // mean = 0.0605542
   TH1F *h_nPho = new TH1F("h_nPho","nPho",10,0,10); // mean = 3.36066
   TH1F *h_phoE = new TH1F("h_phoE","phoE",20,0.,20); // mean = 4.84635
   TH1F *h_phoEt = new TH1F("h_phoEt","phoEt",7,0.,7); // mean = 2.57078
   TH1F *h_phoEta = new TH1F("h_phoEta","phoEta",12,-3,3); // mean = -0.0243092
   TH1F *h_phoPhi = new TH1F("h_phoPhi","phoPhi",10,-3.14,3.14); // mean = 0.0482306
   TH1F *h_phoEcorrStdEcal = new TH1F("h_phoEcorrStdEcal","phoEcorrStdEcal",20,0,20); // mean = 4.09131
   TH1F *h_phoEcorrPhoEcal = new TH1F("h_phoEcorrPhoEcal","phoEcorrPhoEcal",20,0,20); // mean = 4.01922
   TH1F *h_phoEcorrRegr1 = new TH1F("h_phoEcorrRegr1","phoEcorrRegr1",20,0,20); // mean = 4.84635
   TH1F *h_phoEcorrRegr2 = new TH1F("h_phoEcorrRegr2","phoEcorrRegr2",20,0,20); // mean = 4.84635
   TH1F *h_phoEcorrErrStdEcal = new TH1F("h_phoEcorrErrStdEcal","phoEcorrErrStdEcal",10,-9999,-9998); // mean = -9999
   TH1F *h_phoEcorrErrPhoEcal = new TH1F("h_phoEcorrErrPhoEcal","phoEcorrErrPhoEcal",30,-10,20); // mean = 0.260301
   TH1F *h_phoEcorrErrRegr1 = new TH1F("h_phoEcorrErrRegr1","phoEcorrErrRegr1",10,0,5); // mean = 0.595804
   TH1F *h_phoEcorrErrRegr2 = new TH1F("h_phoEcorrErrRegr2","phoEcorrErrRegr2",10,0,5); // mean = 0.595804
   TH1F *h_phoSCE = new TH1F("h_phoSCE","phoSCE",20,0,20); // mean = 4.44097
   TH1F *h_phoSCEt = new TH1F("h_phoSCEt","phoSCEt",10,0,10); // mean = 2.43645
   TH1F *h_phoSCRawE = new TH1F("h_phoSCRawE","phoSCRawE",20,0,20); // mean = 3.90007
   TH1F *h_phoSCEta = new TH1F("h_phoSCEta","phoSCEta",12,-3,3); // mean = -0.0217982
   TH1F *h_phoSCPhi = new TH1F("h_phoSCPhi","phoSCPhi",10,-3.14,3.14); // mean = 0.0482237
   TH1F *h_phoSCEtaWidth = new TH1F("h_phoSCEtaWidth","phoSCEtaWidth",10,0,0.05); // mean = 0.00527372
   TH1F *h_phoSCPhiWidth = new TH1F("h_phoSCPhiWidth","phoSCPhiWidth",10,0,0.3); // mean = 0.0186633
   TH1F *h_phoSCBrem = new TH1F("h_phoSCBrem","phoSCBrem",20,0,2000); // mean = 29.3623
   TH1F *h_phoSCnHits = new TH1F("h_phoSCnHits","phoSCnHits",20,0,20); // mean = 3.30976
   TH1F *h_phoSCflags = new TH1F("h_phoSCflags","phoSCflags",10,0,1); // mean = 0
   TH1F *h_phoSCinClean = new TH1F("h_phoSCinClean","phoSCinClean",10,0,1); // mean = 1
   TH1F *h_phoSCinUnClean = new TH1F("h_phoSCinUnClean","phoSCinUnClean",10,0,1); // mean = 0
   TH1F *h_phoSCnBC = new TH1F("h_phoSCnBC","phoSCnBC",6,0,6); // mean = 1.20488
   TH1F *h_phoESEn = new TH1F("h_phoESEn","phoESEn",10,0,5); // mean = 0.0917759
   TH1F *h_phoPSCE = new TH1F("h_phoPSCE","phoPSCE",30,0,30); // mean = 5.71188
   TH1F *h_phoPSCRawE = new TH1F("h_phoPSCRawE","phoPSCRawE",20,0,20); // mean = 3.90007
   TH1F *h_phoPSCEta = new TH1F("h_phoPSCEta","phoPSCEta",12,-3,3); // mean = -0.0217982
   TH1F *h_phoPSCPhi = new TH1F("h_phoPSCPhi","phoPSCPhi",10,-3.14,3.14); // mean = 0.0482237
   TH1F *h_phoPSCEtaWidth = new TH1F("h_phoPSCEtaWidth","phoPSCEtaWidth",10,0,0.05); // mean = 0.00527372
   TH1F *h_phoPSCPhiWidth = new TH1F("h_phoPSCPhiWidth","phoPSCPhiWidth",10,0,0.3); // mean = 0.0186633
   TH1F *h_phoPSCBrem = new TH1F("h_phoPSCBrem","phoPSCBrem",20,0,2000); // mean = 29.3623
   TH1F *h_phoPSCnHits = new TH1F("h_phoPSCnHits","phoPSCnHits",20,1,20); // mean = 3.30976
   TH1F *h_phoPSCflags = new TH1F("h_phoPSCflags","phoPSCflags",10,0,1); // mean = 0
   TH1F *h_phoPSCinClean = new TH1F("h_phoPSCinClean","phoPSCinClean",10,0,1); // mean = 1
   TH1F *h_phoPSCinUnClean = new TH1F("h_phoPSCinUnClean","phoPSCinUnClean",10,0,1); // mean = 0
   TH1F *h_phoPSCnBC = new TH1F("h_phoPSCnBC","phoPSCnBC",5,0,5); // mean = 1.20488
   TH1F *h_phoPESEn = new TH1F("h_phoPESEn","phoPESEn",10,0,5); // mean = 0.0919352
   TH1F *h_phoIsPFPhoton = new TH1F("h_phoIsPFPhoton","phoIsPFPhoton",10,0,1); // mean = 1
   TH1F *h_phoIsStandardPhoton = new TH1F("h_phoIsStandardPhoton","phoIsStandardPhoton",10,0,1); // mean = 0
   TH1F *h_phoHasPixelSeed = new TH1F("h_phoHasPixelSeed","phoHasPixelSeed",10,0,1); // mean = 0
   TH1F *h_phoHasConversionTracks = new TH1F("h_phoHasConversionTracks","phoHasConversionTracks",10,0,1); // mean = 0
   TH1F *h_phoHadTowerOverEm = new TH1F("h_phoHadTowerOverEm","phoHadTowerOverEm",10,0,0.5); // mean = 0.00240707
   TH1F *h_phoHoverE = new TH1F("h_phoHoverE","phoHoverE",10,0,0.5); // mean = 0.00756698
   TH1F *h_phoHoverEValid = new TH1F("h_phoHoverEValid","phoHoverEValid",2,0,2); // mean = 0.992683
   TH1F *h_phoSigmaIEtaIEta = new TH1F("h_phoSigmaIEtaIEta","phoSigmaIEtaIEta",10,0,0.04); // mean = 0.0067999
   TH1F *h_phoR9 = new TH1F("h_phoR9","phoR9",10,0.,1); // mean = 0.948868
   TH1F *h_phoE1x5 = new TH1F("h_phoE1x5","phoE1x5",20,0,20); // mean = 3.26007
   TH1F *h_phoE2x5 = new TH1F("h_phoE2x5","phoE2x5",20,0,20); // mean = 3.69213
   TH1F *h_phoE3x3 = new TH1F("h_phoE3x3","phoE3x3",20,0,20); // mean = 3.707
   TH1F *h_phoE5x5 = new TH1F("h_phoE5x5","phoE5x5",20,0,20); // mean = 3.737
   TH1F *h_phoMaxEnergyXtal = new TH1F("h_phoMaxEnergyXtal","phoMaxEnergyXtal",20,0,20); // mean = 2.82148
   TH1F *h_phoSigmaEtaEta = new TH1F("h_phoSigmaEtaEta","phoSigmaEtaEta",10,0,0.03); // mean = 0.00592712
   TH1F *h_phoSigmaIEtaIEta_2012 = new TH1F("h_phoSigmaIEtaIEta_2012","phoSigmaIEtaIEta_2012",10,0,0.07); // mean = 0.0125909
   TH1F *h_phoR9_2012 = new TH1F("h_phoR9_2012","phoR9_2012",10,0,6); // mean = 1.02615
   TH1F *h_phoE1x5_2012 = new TH1F("h_phoE1x5_2012","phoE1x5_2012",10,0,20); // mean = 3.41167
   TH1F *h_phoE2x5_2012 = new TH1F("h_phoE2x5_2012","phoE2x5_2012",10,0,20); // mean = 4.00395
   TH1F *h_phoE3x3_2012 = new TH1F("h_phoE3x3_2012","phoE3x3_2012",10,0,20); // mean = 3.95017
   TH1F *h_phoE5x5_2012 = new TH1F("h_phoE5x5_2012","phoE5x5_2012",10,0,20); // mean = 4.39971
   TH1F *h_phoMaxEnergyXtal_2012 = new TH1F("h_phoMaxEnergyXtal_2012","phoMaxEnergyXtal_2012",10,0,20); // mean = 2.82387
   TH1F *h_phoSigmaEtaEta_2012 = new TH1F("h_phoSigmaEtaEta_2012","phoSigmaEtaEta_2012",10,0,0.07); // mean = 0.0115667
   TH1F *h_phoHadTowerOverEm1 = new TH1F("h_phoHadTowerOverEm1","phoHadTowerOverEm1",10,0,0.5); // mean = 0.00240707
   TH1F *h_phoHadTowerOverEm2 = new TH1F("h_phoHadTowerOverEm2","phoHadTowerOverEm2",10,0,1); // mean = 0
   TH1F *h_phoHoverE1 = new TH1F("h_phoHoverE1","phoHoverE1",10,0,0.5); // mean = 0.00756698
   TH1F *h_phoHoverE2 = new TH1F("h_phoHoverE2","phoHoverE2",10,0,1); // mean = 0
   TH1F *h_phoSigmaIEtaIPhi = new TH1F("h_phoSigmaIEtaIPhi","phoSigmaIEtaIPhi",10,-0.000741122,0.000537525); // mean = -2.14377e-06
   TH1F *h_phoSigmaIPhiIPhi = new TH1F("h_phoSigmaIPhiIPhi","phoSigmaIPhiIPhi",10,0,0.05); // mean = 0.00903597
   TH1F *h_phoR1x5 = new TH1F("h_phoR1x5","phoR1x5",10,0.35,1); // mean = 0.867336
   TH1F *h_phoR2x5 = new TH1F("h_phoR2x5","phoR2x5",10,0.68,1); // mean = 0.990697
   TH1F *h_phoE2nd = new TH1F("h_phoE2nd","phoE2nd",10,0,3.5); // mean = 0.569127
   TH1F *h_phoETop = new TH1F("h_phoETop","phoETop",10,0,3); // mean = 0.218858
   TH1F *h_phoEBottom = new TH1F("h_phoEBottom","phoEBottom",10,0,2.6); // mean = 0.20716
   TH1F *h_phoELeft = new TH1F("h_phoELeft","phoELeft",14,0,3.5); // mean = 0.164758
   TH1F *h_phoERight = new TH1F("h_phoERight","phoERight",10,0,2.); // mean = 0.144209
   TH1F *h_phoE1x3 = new TH1F("h_phoE1x3","phoE1x3",10,0.,20); // mean = 3.2475
   TH1F *h_phoE2x2 = new TH1F("h_phoE2x2","phoE2x2",10,0.,20); // mean = 3.62634
   TH1F *h_phoE2x5Max = new TH1F("h_phoE2x5Max","phoE2x5Max",10,0.,20); // mean = 3.69213
   TH1F *h_phoE2x5Top = new TH1F("h_phoE2x5Top","phoE2x5Top",10,0,6); // mean = 0.302888
   TH1F *h_phoE2x5Bottom = new TH1F("h_phoE2x5Bottom","phoE2x5Bottom",10,0,3.5); // mean = 0.298086
   TH1F *h_phoE2x5Left = new TH1F("h_phoE2x5Left","phoE2x5Left",10,0,6.); // mean = 0.254649
   TH1F *h_phoE2x5Right = new TH1F("h_phoE2x5Right","phoE2x5Right",10,0,3.5); // mean = 0.222282
   TH1F *h_phoSigmaIEtaIPhi_2012 = new TH1F("h_phoSigmaIEtaIPhi_2012","phoSigmaIEtaIPhi_2012",10,-0.000942351,0.00134364); // mean = 7.73404e-06
   TH1F *h_phoSigmaIPhiIPhi_2012 = new TH1F("h_phoSigmaIPhiIPhi_2012","phoSigmaIPhiIPhi_2012",10,0,0.0625306); // mean = 0.0143301
   TH1F *h_phoR1x5_2012 = new TH1F("h_phoR1x5_2012","phoR1x5_2012",10,0.210652,1); // mean = 0.796443
   TH1F *h_phoR2x5_2012 = new TH1F("h_phoR2x5_2012","phoR2x5_2012",10,0.259023,1); // mean = 0.932368
   TH1F *h_phoE2nd_2012 = new TH1F("h_phoE2nd_2012","phoE2nd_2012",10,0,3.43789); // mean = 0.576608
   TH1F *h_phoETop_2012 = new TH1F("h_phoETop_2012","phoETop_2012",10,0,5.10477); // mean = 0.273562
   TH1F *h_phoEBottom_2012 = new TH1F("h_phoEBottom_2012","phoEBottom_2012",10,0,2.60152); // mean = 0.235115
   TH1F *h_phoELeft_2012 = new TH1F("h_phoELeft_2012","phoELeft_2012",10,0,4.98249); // mean = 0.204989
   TH1F *h_phoERight_2012 = new TH1F("h_phoERight_2012","phoERight_2012",10,0,3.68955); // mean = 0.171011
   TH1F *h_phoE1x3_2012 = new TH1F("h_phoE1x3_2012","phoE1x3_2012",10,0.261951,21.348); // mean = 3.33255
   TH1F *h_phoE2x2_2012 = new TH1F("h_phoE2x2_2012","phoE2x2_2012",10,0.502563,21.348); // mean = 3.77389
   TH1F *h_phoE2x5Max_2012 = new TH1F("h_phoE2x5Max_2012","phoE2x5Max_2012",10,0.502563,22.4283); // mean = 4.00395
   TH1F *h_phoE2x5Top_2012 = new TH1F("h_phoE2x5Top_2012","phoE2x5Top_2012",10,0,8.01952); // mean = 0.565254
   TH1F *h_phoE2x5Bottom_2012 = new TH1F("h_phoE2x5Bottom_2012","phoE2x5Bottom_2012",10,0,17.0296); // mean = 0.564366
   TH1F *h_phoE2x5Left_2012 = new TH1F("h_phoE2x5Left_2012","phoE2x5Left_2012",10,0,10.679); // mean = 0.500265
   TH1F *h_phoE2x5Right_2012 = new TH1F("h_phoE2x5Right_2012","phoE2x5Right_2012",10,0,11.1482); // mean = 0.487771
   TH1F *h_phoBC1E = new TH1F("h_phoBC1E","phoBC1E",10,0.644087,16.2432); // mean = 3.73786
   TH1F *h_phoBC1Ecorr = new TH1F("h_phoBC1Ecorr","phoBC1Ecorr",10,0.808848,18.0292); // mean = 4.25067
   TH1F *h_phoBC1Eta = new TH1F("h_phoBC1Eta","phoBC1Eta",10,-2.89672,2.87717); // mean = -0.0218635
   TH1F *h_phoBC1Phi = new TH1F("h_phoBC1Phi","phoBC1Phi",10,-3.12199,3.11546); // mean = 0.0497754
   TH1F *h_phoBC1size = new TH1F("h_phoBC1size","phoBC1size",10,0,10); // mean = 2.94878
   TH1F *h_phoBC1flags = new TH1F("h_phoBC1flags","phoBC1flags",10,0,1); // mean = 0
   TH1F *h_phoBC1inClean = new TH1F("h_phoBC1inClean","phoBC1inClean",10,0,1); // mean = 1
   TH1F *h_phoBC1inUnClean = new TH1F("h_phoBC1inUnClean","phoBC1inUnClean",10,0,1); // mean = 0
   TH1F *h_phoBC1rawID = new TH1F("h_phoBC1rawID","phoBC1rawID",10,8.38861e+08,8.72443e+08); // mean = 8.46349e+08
   TH1F *h_nTower = new TH1F("h_nTower","nTower",10,251,450); // mean = 353.311
   TH1F *h_CaloTower_hadE = new TH1F("h_CaloTower_hadE","CaloTower_hadE",10,0,14.5328); // mean = 0.58846
   TH1F *h_CaloTower_emE = new TH1F("h_CaloTower_emE","CaloTower_emE",10,-7.26641,21.348); // mean = 0.382385
   TH1F *h_CaloTower_e = new TH1F("h_CaloTower_e","CaloTower_e",10,1.54415e-09,21.348); // mean = 0.970845
   TH1F *h_CaloTower_et = new TH1F("h_CaloTower_et","CaloTower_et",10,1e-09,6.65881); // mean = 0.147848
   TH1F *h_CaloTower_eta = new TH1F("h_CaloTower_eta","CaloTower_eta",10,-5.03328,5.03328); // mean = -0.0521839
   TH1F *h_CaloTower_phi = new TH1F("h_CaloTower_phi","CaloTower_phi",10,-3.13431,3.14159); // mean = 0.0422055
   TH1F *h_nTrackerHits = new TH1F("h_nTrackerHits","nTrackerHits",10,0,1); // mean = 0
   TH1F *h_nPixelClusters = new TH1F("h_nPixelClusters","nPixelClusters",10,22,326); // mean = 123.762
   TH1F *h_nPixelRecHits = new TH1F("h_nPixelRecHits","nPixelRecHits",10,22,326); // mean = 123.762

   // eta rings for calo towers
   const int ncalohist = 20;
   TH1F *h_CaloTower_e_etaring[ncalohist] = {0};
   TH1F *h_CaloTower_et_etaring[ncalohist] = {0};
   TH1F *h_CaloTower_e_etaring_noSC[ncalohist] = {0};
   TH1F *h_CaloTower_et_etaring_noSC[ncalohist] = {0};
   for (int i=0; i<ncalohist; i++) {
      double maxe, maxet;
      if (i<=4 || i>=15) {
         maxe = 100;
         maxet = 10;
      } else if (i==14 || i==15) {
         maxe = 15;
         maxet = 25;
      } else {
         maxe = 30;
         maxet = 10;
      }
      h_CaloTower_e_etaring[i] = new TH1F(Form("h_CaloTower_e_etaring_%d",i),Form("CaloTower_e (%.1f<#eta<%.1f)",-5+i*0.5,-5+(i+1)*0.5),10,0,maxe);
      h_CaloTower_et_etaring[i] = new TH1F(Form("h_CaloTower_et_etaring_%d",i),Form("CaloTower_et (%.1f<#eta<%.1f)",-5+i*0.5,-5+(i+1)*0.5),10,0,maxet);
      h_CaloTower_e_etaring_noSC[i] = new TH1F(Form("h_CaloTower_e_etaring_noSC_%d",i),Form("CaloTower_e (no SC) (%.1f<#eta<%.1f)",-5+i*0.5,-5+(i+1)*0.5),10,0,maxe);
      h_CaloTower_et_etaring_noSC[i] = new TH1F(Form("h_CaloTower_et_etaring_noSC_%d",i),Form("CaloTower_et (no SC) (%.1f<#eta<%.1f)",-5+i*0.5,-5+(i+1)*0.5),10,0,maxet);
   }
   cout << __LINE__ << endl;

   TH1F *haco = new TH1F("haco","acoplanarity",20,0,0.2);

   // stat variables declaration
   double min_run(1e99), max_run(-1e99), mean_run(0);
   double min_event(1e99), max_event(-1e99), mean_event(0);
   double min_lumis(1e99), max_lumis(-1e99), mean_lumis(0);
   double min_isData(1e99), max_isData(-1e99), mean_isData(0);
   double min_rho(1e99), max_rho(-1e99), mean_rho(0);
   double min_nSC(1e99), max_nSC(-1e99), mean_nSC(0);
   double min_scE(1e99), max_scE(-1e99), mean_scE(0);
   double min_scRawE(1e99), max_scRawE(-1e99), mean_scRawE(0);
   double min_scEta(1e99), max_scEta(-1e99), mean_scEta(0);
   double min_scPhi(1e99), max_scPhi(-1e99), mean_scPhi(0);
   double min_nPho(1e99), max_nPho(-1e99), mean_nPho(0);
   double min_phoE(1e99), max_phoE(-1e99), mean_phoE(0);
   double min_phoEt(1e99), max_phoEt(-1e99), mean_phoEt(0);
   double min_phoEta(1e99), max_phoEta(-1e99), mean_phoEta(0);
   double min_phoPhi(1e99), max_phoPhi(-1e99), mean_phoPhi(0);
   double min_phoEcorrStdEcal(1e99), max_phoEcorrStdEcal(-1e99), mean_phoEcorrStdEcal(0);
   double min_phoEcorrPhoEcal(1e99), max_phoEcorrPhoEcal(-1e99), mean_phoEcorrPhoEcal(0);
   double min_phoEcorrRegr1(1e99), max_phoEcorrRegr1(-1e99), mean_phoEcorrRegr1(0);
   double min_phoEcorrRegr2(1e99), max_phoEcorrRegr2(-1e99), mean_phoEcorrRegr2(0);
   double min_phoEcorrErrStdEcal(1e99), max_phoEcorrErrStdEcal(-1e99), mean_phoEcorrErrStdEcal(0);
   double min_phoEcorrErrPhoEcal(1e99), max_phoEcorrErrPhoEcal(-1e99), mean_phoEcorrErrPhoEcal(0);
   double min_phoEcorrErrRegr1(1e99), max_phoEcorrErrRegr1(-1e99), mean_phoEcorrErrRegr1(0);
   double min_phoEcorrErrRegr2(1e99), max_phoEcorrErrRegr2(-1e99), mean_phoEcorrErrRegr2(0);
   double min_phoSCE(1e99), max_phoSCE(-1e99), mean_phoSCE(0);
   double min_phoSCEt(1e99), max_phoSCEt(-1e99), mean_phoSCEt(0);
   double min_phoSCRawE(1e99), max_phoSCRawE(-1e99), mean_phoSCRawE(0);
   double min_phoSCEta(1e99), max_phoSCEta(-1e99), mean_phoSCEta(0);
   double min_phoSCPhi(1e99), max_phoSCPhi(-1e99), mean_phoSCPhi(0);
   double min_phoSCEtaWidth(1e99), max_phoSCEtaWidth(-1e99), mean_phoSCEtaWidth(0);
   double min_phoSCPhiWidth(1e99), max_phoSCPhiWidth(-1e99), mean_phoSCPhiWidth(0);
   double min_phoSCBrem(1e99), max_phoSCBrem(-1e99), mean_phoSCBrem(0);
   double min_phoSCnHits(1e99), max_phoSCnHits(-1e99), mean_phoSCnHits(0);
   double min_phoSCflags(1e99), max_phoSCflags(-1e99), mean_phoSCflags(0);
   double min_phoSCinClean(1e99), max_phoSCinClean(-1e99), mean_phoSCinClean(0);
   double min_phoSCinUnClean(1e99), max_phoSCinUnClean(-1e99), mean_phoSCinUnClean(0);
   double min_phoSCnBC(1e99), max_phoSCnBC(-1e99), mean_phoSCnBC(0);
   double min_phoESEn(1e99), max_phoESEn(-1e99), mean_phoESEn(0);
   double min_phoPSCE(1e99), max_phoPSCE(-1e99), mean_phoPSCE(0);
   double min_phoPSCRawE(1e99), max_phoPSCRawE(-1e99), mean_phoPSCRawE(0);
   double min_phoPSCEta(1e99), max_phoPSCEta(-1e99), mean_phoPSCEta(0);
   double min_phoPSCPhi(1e99), max_phoPSCPhi(-1e99), mean_phoPSCPhi(0);
   double min_phoPSCEtaWidth(1e99), max_phoPSCEtaWidth(-1e99), mean_phoPSCEtaWidth(0);
   double min_phoPSCPhiWidth(1e99), max_phoPSCPhiWidth(-1e99), mean_phoPSCPhiWidth(0);
   double min_phoPSCBrem(1e99), max_phoPSCBrem(-1e99), mean_phoPSCBrem(0);
   double min_phoPSCnHits(1e99), max_phoPSCnHits(-1e99), mean_phoPSCnHits(0);
   double min_phoPSCflags(1e99), max_phoPSCflags(-1e99), mean_phoPSCflags(0);
   double min_phoPSCinClean(1e99), max_phoPSCinClean(-1e99), mean_phoPSCinClean(0);
   double min_phoPSCinUnClean(1e99), max_phoPSCinUnClean(-1e99), mean_phoPSCinUnClean(0);
   double min_phoPSCnBC(1e99), max_phoPSCnBC(-1e99), mean_phoPSCnBC(0);
   double min_phoPESEn(1e99), max_phoPESEn(-1e99), mean_phoPESEn(0);
   double min_phoIsPFPhoton(1e99), max_phoIsPFPhoton(-1e99), mean_phoIsPFPhoton(0);
   double min_phoIsStandardPhoton(1e99), max_phoIsStandardPhoton(-1e99), mean_phoIsStandardPhoton(0);
   double min_phoHasPixelSeed(1e99), max_phoHasPixelSeed(-1e99), mean_phoHasPixelSeed(0);
   double min_phoHasConversionTracks(1e99), max_phoHasConversionTracks(-1e99), mean_phoHasConversionTracks(0);
   double min_phoHadTowerOverEm(1e99), max_phoHadTowerOverEm(-1e99), mean_phoHadTowerOverEm(0);
   double min_phoHoverE(1e99), max_phoHoverE(-1e99), mean_phoHoverE(0);
   double min_phoHoverEValid(1e99), max_phoHoverEValid(-1e99), mean_phoHoverEValid(0);
   double min_phoSigmaIEtaIEta(1e99), max_phoSigmaIEtaIEta(-1e99), mean_phoSigmaIEtaIEta(0);
   double min_phoR9(1e99), max_phoR9(-1e99), mean_phoR9(0);
   double min_phoE1x5(1e99), max_phoE1x5(-1e99), mean_phoE1x5(0);
   double min_phoE2x5(1e99), max_phoE2x5(-1e99), mean_phoE2x5(0);
   double min_phoE3x3(1e99), max_phoE3x3(-1e99), mean_phoE3x3(0);
   double min_phoE5x5(1e99), max_phoE5x5(-1e99), mean_phoE5x5(0);
   double min_phoMaxEnergyXtal(1e99), max_phoMaxEnergyXtal(-1e99), mean_phoMaxEnergyXtal(0);
   double min_phoSigmaEtaEta(1e99), max_phoSigmaEtaEta(-1e99), mean_phoSigmaEtaEta(0);
   double min_phoSigmaIEtaIEta_2012(1e99), max_phoSigmaIEtaIEta_2012(-1e99), mean_phoSigmaIEtaIEta_2012(0);
   double min_phoR9_2012(1e99), max_phoR9_2012(-1e99), mean_phoR9_2012(0);
   double min_phoE1x5_2012(1e99), max_phoE1x5_2012(-1e99), mean_phoE1x5_2012(0);
   double min_phoE2x5_2012(1e99), max_phoE2x5_2012(-1e99), mean_phoE2x5_2012(0);
   double min_phoE3x3_2012(1e99), max_phoE3x3_2012(-1e99), mean_phoE3x3_2012(0);
   double min_phoE5x5_2012(1e99), max_phoE5x5_2012(-1e99), mean_phoE5x5_2012(0);
   double min_phoMaxEnergyXtal_2012(1e99), max_phoMaxEnergyXtal_2012(-1e99), mean_phoMaxEnergyXtal_2012(0);
   double min_phoSigmaEtaEta_2012(1e99), max_phoSigmaEtaEta_2012(-1e99), mean_phoSigmaEtaEta_2012(0);
   double min_phoHadTowerOverEm1(1e99), max_phoHadTowerOverEm1(-1e99), mean_phoHadTowerOverEm1(0);
   double min_phoHadTowerOverEm2(1e99), max_phoHadTowerOverEm2(-1e99), mean_phoHadTowerOverEm2(0);
   double min_phoHoverE1(1e99), max_phoHoverE1(-1e99), mean_phoHoverE1(0);
   double min_phoHoverE2(1e99), max_phoHoverE2(-1e99), mean_phoHoverE2(0);
   double min_phoSigmaIEtaIPhi(1e99), max_phoSigmaIEtaIPhi(-1e99), mean_phoSigmaIEtaIPhi(0);
   double min_phoSigmaIPhiIPhi(1e99), max_phoSigmaIPhiIPhi(-1e99), mean_phoSigmaIPhiIPhi(0);
   double min_phoR1x5(1e99), max_phoR1x5(-1e99), mean_phoR1x5(0);
   double min_phoR2x5(1e99), max_phoR2x5(-1e99), mean_phoR2x5(0);
   double min_phoE2nd(1e99), max_phoE2nd(-1e99), mean_phoE2nd(0);
   double min_phoETop(1e99), max_phoETop(-1e99), mean_phoETop(0);
   double min_phoEBottom(1e99), max_phoEBottom(-1e99), mean_phoEBottom(0);
   double min_phoELeft(1e99), max_phoELeft(-1e99), mean_phoELeft(0);
   double min_phoERight(1e99), max_phoERight(-1e99), mean_phoERight(0);
   double min_phoE1x3(1e99), max_phoE1x3(-1e99), mean_phoE1x3(0);
   double min_phoE2x2(1e99), max_phoE2x2(-1e99), mean_phoE2x2(0);
   double min_phoE2x5Max(1e99), max_phoE2x5Max(-1e99), mean_phoE2x5Max(0);
   double min_phoE2x5Top(1e99), max_phoE2x5Top(-1e99), mean_phoE2x5Top(0);
   double min_phoE2x5Bottom(1e99), max_phoE2x5Bottom(-1e99), mean_phoE2x5Bottom(0);
   double min_phoE2x5Left(1e99), max_phoE2x5Left(-1e99), mean_phoE2x5Left(0);
   double min_phoE2x5Right(1e99), max_phoE2x5Right(-1e99), mean_phoE2x5Right(0);
   double min_phoSigmaIEtaIPhi_2012(1e99), max_phoSigmaIEtaIPhi_2012(-1e99), mean_phoSigmaIEtaIPhi_2012(0);
   double min_phoSigmaIPhiIPhi_2012(1e99), max_phoSigmaIPhiIPhi_2012(-1e99), mean_phoSigmaIPhiIPhi_2012(0);
   double min_phoR1x5_2012(1e99), max_phoR1x5_2012(-1e99), mean_phoR1x5_2012(0);
   double min_phoR2x5_2012(1e99), max_phoR2x5_2012(-1e99), mean_phoR2x5_2012(0);
   double min_phoE2nd_2012(1e99), max_phoE2nd_2012(-1e99), mean_phoE2nd_2012(0);
   double min_phoETop_2012(1e99), max_phoETop_2012(-1e99), mean_phoETop_2012(0);
   double min_phoEBottom_2012(1e99), max_phoEBottom_2012(-1e99), mean_phoEBottom_2012(0);
   double min_phoELeft_2012(1e99), max_phoELeft_2012(-1e99), mean_phoELeft_2012(0);
   double min_phoERight_2012(1e99), max_phoERight_2012(-1e99), mean_phoERight_2012(0);
   double min_phoE1x3_2012(1e99), max_phoE1x3_2012(-1e99), mean_phoE1x3_2012(0);
   double min_phoE2x2_2012(1e99), max_phoE2x2_2012(-1e99), mean_phoE2x2_2012(0);
   double min_phoE2x5Max_2012(1e99), max_phoE2x5Max_2012(-1e99), mean_phoE2x5Max_2012(0);
   double min_phoE2x5Top_2012(1e99), max_phoE2x5Top_2012(-1e99), mean_phoE2x5Top_2012(0);
   double min_phoE2x5Bottom_2012(1e99), max_phoE2x5Bottom_2012(-1e99), mean_phoE2x5Bottom_2012(0);
   double min_phoE2x5Left_2012(1e99), max_phoE2x5Left_2012(-1e99), mean_phoE2x5Left_2012(0);
   double min_phoE2x5Right_2012(1e99), max_phoE2x5Right_2012(-1e99), mean_phoE2x5Right_2012(0);
   double min_phoBC1E(1e99), max_phoBC1E(-1e99), mean_phoBC1E(0);
   double min_phoBC1Ecorr(1e99), max_phoBC1Ecorr(-1e99), mean_phoBC1Ecorr(0);
   double min_phoBC1Eta(1e99), max_phoBC1Eta(-1e99), mean_phoBC1Eta(0);
   double min_phoBC1Phi(1e99), max_phoBC1Phi(-1e99), mean_phoBC1Phi(0);
   double min_phoBC1size(1e99), max_phoBC1size(-1e99), mean_phoBC1size(0);
   double min_phoBC1flags(1e99), max_phoBC1flags(-1e99), mean_phoBC1flags(0);
   double min_phoBC1inClean(1e99), max_phoBC1inClean(-1e99), mean_phoBC1inClean(0);
   double min_phoBC1inUnClean(1e99), max_phoBC1inUnClean(-1e99), mean_phoBC1inUnClean(0);
   double min_phoBC1rawID(1e99), max_phoBC1rawID(-1e99), mean_phoBC1rawID(0);
   // double min_pho_ecalClusterIsoR2(1e99), max_pho_ecalClusterIsoR2(-1e99), mean_pho_ecalClusterIsoR2(0);
   // double min_pho_ecalClusterIsoR3(1e99), max_pho_ecalClusterIsoR3(-1e99), mean_pho_ecalClusterIsoR3(0);
   // double min_pho_ecalClusterIsoR4(1e99), max_pho_ecalClusterIsoR4(-1e99), mean_pho_ecalClusterIsoR4(0);
   // double min_pho_ecalClusterIsoR5(1e99), max_pho_ecalClusterIsoR5(-1e99), mean_pho_ecalClusterIsoR5(0);
   // double min_pho_hcalRechitIsoR1(1e99), max_pho_hcalRechitIsoR1(-1e99), mean_pho_hcalRechitIsoR1(0);
   // double min_pho_hcalRechitIsoR2(1e99), max_pho_hcalRechitIsoR2(-1e99), mean_pho_hcalRechitIsoR2(0);
   // double min_pho_hcalRechitIsoR3(1e99), max_pho_hcalRechitIsoR3(-1e99), mean_pho_hcalRechitIsoR3(0);
   // double min_pho_hcalRechitIsoR4(1e99), max_pho_hcalRechitIsoR4(-1e99), mean_pho_hcalRechitIsoR4(0);
   // double min_pho_hcalRechitIsoR5(1e99), max_pho_hcalRechitIsoR5(-1e99), mean_pho_hcalRechitIsoR5(0);
   // double min_pho_trackIsoR1PtCut20(1e99), max_pho_trackIsoR1PtCut20(-1e99), mean_pho_trackIsoR1PtCut20(0);
   // double min_pho_trackIsoR2PtCut20(1e99), max_pho_trackIsoR2PtCut20(-1e99), mean_pho_trackIsoR2PtCut20(0);
   // double min_pho_trackIsoR3PtCut20(1e99), max_pho_trackIsoR3PtCut20(-1e99), mean_pho_trackIsoR3PtCut20(0);
   // double min_pho_trackIsoR4PtCut20(1e99), max_pho_trackIsoR4PtCut20(-1e99), mean_pho_trackIsoR4PtCut20(0);
   // double min_pho_trackIsoR5PtCut20(1e99), max_pho_trackIsoR5PtCut20(-1e99), mean_pho_trackIsoR5PtCut20(0);
   // double min_pho_swissCrx(1e99), max_pho_swissCrx(-1e99), mean_pho_swissCrx(0);
   // double min_pho_seedTime(1e99), max_pho_seedTime(-1e99), mean_pho_seedTime(0);
   double min_nTower(1e99), max_nTower(-1e99), mean_nTower(0);
   double min_CaloTower_hadE(1e99), max_CaloTower_hadE(-1e99), mean_CaloTower_hadE(0);
   double min_CaloTower_emE(1e99), max_CaloTower_emE(-1e99), mean_CaloTower_emE(0);
   double min_CaloTower_e(1e99), max_CaloTower_e(-1e99), mean_CaloTower_e(0);
   double min_CaloTower_et(1e99), max_CaloTower_et(-1e99), mean_CaloTower_et(0);
   double min_CaloTower_eta(1e99), max_CaloTower_eta(-1e99), mean_CaloTower_eta(0);
   double min_CaloTower_phi(1e99), max_CaloTower_phi(-1e99), mean_CaloTower_phi(0);
   double min_nTrackerHits(1e99), max_nTrackerHits(-1e99), mean_nTrackerHits(0);
   double min_nPixelClusters(1e99), max_nPixelClusters(-1e99), mean_nPixelClusters(0);
   double min_nPixelRecHits(1e99), max_nPixelRecHits(-1e99), mean_nPixelRecHits(0);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;


      // first check if this event is in our list
      b_run->GetEntry(ientry); //read only this branch
      b_event->GetEntry(ientry); //read only this branch
      b_lumis->GetEntry(ientry); //read only this branch
      vector<int> v; v.push_back(run); v.push_back(lumis); v.push_back(event);
      double aco = goodevents[v];
      if (aco==0) continue;

      // we'll fill separate histograms for low and high aco
      if (dolowaco && aco>aco_cut) continue;
      if (!dolowaco && aco<=aco_cut) continue;

      cout << "PASSING! " << run << " " << lumis << " " << event << " " << aco << endl;
      haco->Fill(aco);

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // fill histos etc.
      if (run < min_run) min_run = run;
      if (run > max_run) max_run = run;
      mean_run += run;
      h_run->Fill(run);
      if (event < min_event) min_event = event;
      if (event > max_event) max_event = event;
      mean_event += event;
      h_event->Fill(event);
      if (lumis < min_lumis) min_lumis = lumis;
      if (lumis > max_lumis) max_lumis = lumis;
      mean_lumis += lumis;
      h_lumis->Fill(lumis);
      if (nSC < min_nSC) min_nSC = nSC;
      if (nSC > max_nSC) max_nSC = nSC;
      mean_nSC += nSC;
      h_nSC->Fill(nSC);
      for (int i=0; i<nSC; i++) {
         if (scE->at(i) < min_scE) min_scE = scE->at(i);
         if (scE->at(i) > max_scE) max_scE = scE->at(i);
         mean_scE += scE->at(i);
         h_scE->Fill(scE->at(i));
         if (scRawE->at(i) < min_scRawE) min_scRawE = scRawE->at(i);
         if (scRawE->at(i) > max_scRawE) max_scRawE = scRawE->at(i);
         mean_scRawE += scRawE->at(i);
         h_scRawE->Fill(scRawE->at(i));
         if (scEta->at(i) < min_scEta) min_scEta = scEta->at(i);
         if (scEta->at(i) > max_scEta) max_scEta = scEta->at(i);
         mean_scEta += scEta->at(i);
         h_scEta->Fill(scEta->at(i));
         if (scPhi->at(i) < min_scPhi) min_scPhi = scPhi->at(i);
         if (scPhi->at(i) > max_scPhi) max_scPhi = scPhi->at(i);
         mean_scPhi += scPhi->at(i);
         h_scPhi->Fill(scPhi->at(i));
      }
      if (nPho < min_nPho) min_nPho = nPho;
      if (nPho > max_nPho) max_nPho = nPho;
      mean_nPho += nPho;
      h_nPho->Fill(nPho);
      for (int i=0; i<nPho; i++) {
         if (phoE->at(i) < min_phoE) min_phoE = phoE->at(i);
         if (phoE->at(i) > max_phoE) max_phoE = phoE->at(i);
         mean_phoE += phoE->at(i);
         h_phoE->Fill(phoE->at(i));
         if (phoEt->at(i) < min_phoEt) min_phoEt = phoEt->at(i);
         if (phoEt->at(i) > max_phoEt) max_phoEt = phoEt->at(i);
         mean_phoEt += phoEt->at(i);
         h_phoEt->Fill(phoEt->at(i));
         if (phoEta->at(i) < min_phoEta) min_phoEta = phoEta->at(i);
         if (phoEta->at(i) > max_phoEta) max_phoEta = phoEta->at(i);
         mean_phoEta += phoEta->at(i);
         h_phoEta->Fill(phoEta->at(i));
         if (phoPhi->at(i) < min_phoPhi) min_phoPhi = phoPhi->at(i);
         if (phoPhi->at(i) > max_phoPhi) max_phoPhi = phoPhi->at(i);
         mean_phoPhi += phoPhi->at(i);
         h_phoPhi->Fill(phoPhi->at(i));
         if (phoEcorrStdEcal->at(i) < min_phoEcorrStdEcal) min_phoEcorrStdEcal = phoEcorrStdEcal->at(i);
         if (phoEcorrStdEcal->at(i) > max_phoEcorrStdEcal) max_phoEcorrStdEcal = phoEcorrStdEcal->at(i);
         mean_phoEcorrStdEcal += phoEcorrStdEcal->at(i);
         h_phoEcorrStdEcal->Fill(phoEcorrStdEcal->at(i));
         if (phoEcorrPhoEcal->at(i) < min_phoEcorrPhoEcal) min_phoEcorrPhoEcal = phoEcorrPhoEcal->at(i);
         if (phoEcorrPhoEcal->at(i) > max_phoEcorrPhoEcal) max_phoEcorrPhoEcal = phoEcorrPhoEcal->at(i);
         mean_phoEcorrPhoEcal += phoEcorrPhoEcal->at(i);
         h_phoEcorrPhoEcal->Fill(phoEcorrPhoEcal->at(i));
         if (phoEcorrRegr1->at(i) < min_phoEcorrRegr1) min_phoEcorrRegr1 = phoEcorrRegr1->at(i);
         if (phoEcorrRegr1->at(i) > max_phoEcorrRegr1) max_phoEcorrRegr1 = phoEcorrRegr1->at(i);
         mean_phoEcorrRegr1 += phoEcorrRegr1->at(i);
         h_phoEcorrRegr1->Fill(phoEcorrRegr1->at(i));
         if (phoEcorrRegr2->at(i) < min_phoEcorrRegr2) min_phoEcorrRegr2 = phoEcorrRegr2->at(i);
         if (phoEcorrRegr2->at(i) > max_phoEcorrRegr2) max_phoEcorrRegr2 = phoEcorrRegr2->at(i);
         mean_phoEcorrRegr2 += phoEcorrRegr2->at(i);
         h_phoEcorrRegr2->Fill(phoEcorrRegr2->at(i));
         if (phoEcorrErrStdEcal->at(i) < min_phoEcorrErrStdEcal) min_phoEcorrErrStdEcal = phoEcorrErrStdEcal->at(i);
         if (phoEcorrErrStdEcal->at(i) > max_phoEcorrErrStdEcal) max_phoEcorrErrStdEcal = phoEcorrErrStdEcal->at(i);
         mean_phoEcorrErrStdEcal += phoEcorrErrStdEcal->at(i);
         h_phoEcorrErrStdEcal->Fill(phoEcorrErrStdEcal->at(i));
         if (phoEcorrErrPhoEcal->at(i) < min_phoEcorrErrPhoEcal) min_phoEcorrErrPhoEcal = phoEcorrErrPhoEcal->at(i);
         if (phoEcorrErrPhoEcal->at(i) > max_phoEcorrErrPhoEcal) max_phoEcorrErrPhoEcal = phoEcorrErrPhoEcal->at(i);
         mean_phoEcorrErrPhoEcal += phoEcorrErrPhoEcal->at(i);
         h_phoEcorrErrPhoEcal->Fill(phoEcorrErrPhoEcal->at(i));
         if (phoEcorrErrRegr1->at(i) < min_phoEcorrErrRegr1) min_phoEcorrErrRegr1 = phoEcorrErrRegr1->at(i);
         if (phoEcorrErrRegr1->at(i) > max_phoEcorrErrRegr1) max_phoEcorrErrRegr1 = phoEcorrErrRegr1->at(i);
         mean_phoEcorrErrRegr1 += phoEcorrErrRegr1->at(i);
         h_phoEcorrErrRegr1->Fill(phoEcorrErrRegr1->at(i));
         if (phoEcorrErrRegr2->at(i) < min_phoEcorrErrRegr2) min_phoEcorrErrRegr2 = phoEcorrErrRegr2->at(i);
         if (phoEcorrErrRegr2->at(i) > max_phoEcorrErrRegr2) max_phoEcorrErrRegr2 = phoEcorrErrRegr2->at(i);
         mean_phoEcorrErrRegr2 += phoEcorrErrRegr2->at(i);
         h_phoEcorrErrRegr2->Fill(phoEcorrErrRegr2->at(i));
         if (phoSCE->at(i) < min_phoSCE) min_phoSCE = phoSCE->at(i);
         if (phoSCE->at(i) > max_phoSCE) max_phoSCE = phoSCE->at(i);
         mean_phoSCE += phoSCE->at(i);
         h_phoSCE->Fill(phoSCE->at(i));
         if (phoSCEt->at(i) < min_phoSCEt) min_phoSCEt = phoSCEt->at(i);
         if (phoSCEt->at(i) > max_phoSCEt) max_phoSCEt = phoSCEt->at(i);
         mean_phoSCEt += phoSCEt->at(i);
         h_phoSCEt->Fill(phoSCEt->at(i));
         if (phoSCRawE->at(i) < min_phoSCRawE) min_phoSCRawE = phoSCRawE->at(i);
         if (phoSCRawE->at(i) > max_phoSCRawE) max_phoSCRawE = phoSCRawE->at(i);
         mean_phoSCRawE += phoSCRawE->at(i);
         h_phoSCRawE->Fill(phoSCRawE->at(i));
         if (phoSCEta->at(i) < min_phoSCEta) min_phoSCEta = phoSCEta->at(i);
         if (phoSCEta->at(i) > max_phoSCEta) max_phoSCEta = phoSCEta->at(i);
         mean_phoSCEta += phoSCEta->at(i);
         h_phoSCEta->Fill(phoSCEta->at(i));
         if (phoSCPhi->at(i) < min_phoSCPhi) min_phoSCPhi = phoSCPhi->at(i);
         if (phoSCPhi->at(i) > max_phoSCPhi) max_phoSCPhi = phoSCPhi->at(i);
         mean_phoSCPhi += phoSCPhi->at(i);
         h_phoSCPhi->Fill(phoSCPhi->at(i));
         if (phoSCEtaWidth->at(i) < min_phoSCEtaWidth) min_phoSCEtaWidth = phoSCEtaWidth->at(i);
         if (phoSCEtaWidth->at(i) > max_phoSCEtaWidth) max_phoSCEtaWidth = phoSCEtaWidth->at(i);
         mean_phoSCEtaWidth += phoSCEtaWidth->at(i);
         h_phoSCEtaWidth->Fill(phoSCEtaWidth->at(i));
         if (phoSCPhiWidth->at(i) < min_phoSCPhiWidth) min_phoSCPhiWidth = phoSCPhiWidth->at(i);
         if (phoSCPhiWidth->at(i) > max_phoSCPhiWidth) max_phoSCPhiWidth = phoSCPhiWidth->at(i);
         mean_phoSCPhiWidth += phoSCPhiWidth->at(i);
         h_phoSCPhiWidth->Fill(phoSCPhiWidth->at(i));
         if (phoSCBrem->at(i) < min_phoSCBrem) min_phoSCBrem = phoSCBrem->at(i);
         if (phoSCBrem->at(i) > max_phoSCBrem) max_phoSCBrem = phoSCBrem->at(i);
         mean_phoSCBrem += phoSCBrem->at(i);
         h_phoSCBrem->Fill(phoSCBrem->at(i));
         if (phoSCnHits->at(i) < min_phoSCnHits) min_phoSCnHits = phoSCnHits->at(i);
         if (phoSCnHits->at(i) > max_phoSCnHits) max_phoSCnHits = phoSCnHits->at(i);
         mean_phoSCnHits += phoSCnHits->at(i);
         h_phoSCnHits->Fill(phoSCnHits->at(i));
         if (phoSCflags->at(i) < min_phoSCflags) min_phoSCflags = phoSCflags->at(i);
         if (phoSCflags->at(i) > max_phoSCflags) max_phoSCflags = phoSCflags->at(i);
         mean_phoSCflags += phoSCflags->at(i);
         h_phoSCflags->Fill(phoSCflags->at(i));
         if (phoSCinClean->at(i) < min_phoSCinClean) min_phoSCinClean = phoSCinClean->at(i);
         if (phoSCinClean->at(i) > max_phoSCinClean) max_phoSCinClean = phoSCinClean->at(i);
         mean_phoSCinClean += phoSCinClean->at(i);
         h_phoSCinClean->Fill(phoSCinClean->at(i));
         if (phoSCinUnClean->at(i) < min_phoSCinUnClean) min_phoSCinUnClean = phoSCinUnClean->at(i);
         if (phoSCinUnClean->at(i) > max_phoSCinUnClean) max_phoSCinUnClean = phoSCinUnClean->at(i);
         mean_phoSCinUnClean += phoSCinUnClean->at(i);
         h_phoSCinUnClean->Fill(phoSCinUnClean->at(i));
         if (phoSCnBC->at(i) < min_phoSCnBC) min_phoSCnBC = phoSCnBC->at(i);
         if (phoSCnBC->at(i) > max_phoSCnBC) max_phoSCnBC = phoSCnBC->at(i);
         mean_phoSCnBC += phoSCnBC->at(i);
         h_phoSCnBC->Fill(phoSCnBC->at(i));
         if (phoESEn->at(i) < min_phoESEn) min_phoESEn = phoESEn->at(i);
         if (phoESEn->at(i) > max_phoESEn) max_phoESEn = phoESEn->at(i);
         mean_phoESEn += phoESEn->at(i);
         h_phoESEn->Fill(phoESEn->at(i));
         if (phoPSCE->at(i) < min_phoPSCE) min_phoPSCE = phoPSCE->at(i);
         if (phoPSCE->at(i) > max_phoPSCE) max_phoPSCE = phoPSCE->at(i);
         mean_phoPSCE += phoPSCE->at(i);
         h_phoPSCE->Fill(phoPSCE->at(i));
         if (phoPSCRawE->at(i) < min_phoPSCRawE) min_phoPSCRawE = phoPSCRawE->at(i);
         if (phoPSCRawE->at(i) > max_phoPSCRawE) max_phoPSCRawE = phoPSCRawE->at(i);
         mean_phoPSCRawE += phoPSCRawE->at(i);
         h_phoPSCRawE->Fill(phoPSCRawE->at(i));
         if (phoPSCEta->at(i) < min_phoPSCEta) min_phoPSCEta = phoPSCEta->at(i);
         if (phoPSCEta->at(i) > max_phoPSCEta) max_phoPSCEta = phoPSCEta->at(i);
         mean_phoPSCEta += phoPSCEta->at(i);
         h_phoPSCEta->Fill(phoPSCEta->at(i));
         if (phoPSCPhi->at(i) < min_phoPSCPhi) min_phoPSCPhi = phoPSCPhi->at(i);
         if (phoPSCPhi->at(i) > max_phoPSCPhi) max_phoPSCPhi = phoPSCPhi->at(i);
         mean_phoPSCPhi += phoPSCPhi->at(i);
         h_phoPSCPhi->Fill(phoPSCPhi->at(i));
         if (phoPSCEtaWidth->at(i) < min_phoPSCEtaWidth) min_phoPSCEtaWidth = phoPSCEtaWidth->at(i);
         if (phoPSCEtaWidth->at(i) > max_phoPSCEtaWidth) max_phoPSCEtaWidth = phoPSCEtaWidth->at(i);
         mean_phoPSCEtaWidth += phoPSCEtaWidth->at(i);
         h_phoPSCEtaWidth->Fill(phoPSCEtaWidth->at(i));
         if (phoPSCPhiWidth->at(i) < min_phoPSCPhiWidth) min_phoPSCPhiWidth = phoPSCPhiWidth->at(i);
         if (phoPSCPhiWidth->at(i) > max_phoPSCPhiWidth) max_phoPSCPhiWidth = phoPSCPhiWidth->at(i);
         mean_phoPSCPhiWidth += phoPSCPhiWidth->at(i);
         h_phoPSCPhiWidth->Fill(phoPSCPhiWidth->at(i));
         if (phoPSCBrem->at(i) < min_phoPSCBrem) min_phoPSCBrem = phoPSCBrem->at(i);
         if (phoPSCBrem->at(i) > max_phoPSCBrem) max_phoPSCBrem = phoPSCBrem->at(i);
         mean_phoPSCBrem += phoPSCBrem->at(i);
         h_phoPSCBrem->Fill(phoPSCBrem->at(i));
         if (phoPSCnHits->at(i) < min_phoPSCnHits) min_phoPSCnHits = phoPSCnHits->at(i);
         if (phoPSCnHits->at(i) > max_phoPSCnHits) max_phoPSCnHits = phoPSCnHits->at(i);
         mean_phoPSCnHits += phoPSCnHits->at(i);
         h_phoPSCnHits->Fill(phoPSCnHits->at(i));
         if (phoPSCflags->at(i) < min_phoPSCflags) min_phoPSCflags = phoPSCflags->at(i);
         if (phoPSCflags->at(i) > max_phoPSCflags) max_phoPSCflags = phoPSCflags->at(i);
         mean_phoPSCflags += phoPSCflags->at(i);
         h_phoPSCflags->Fill(phoPSCflags->at(i));
         if (phoPSCinClean->at(i) < min_phoPSCinClean) min_phoPSCinClean = phoPSCinClean->at(i);
         if (phoPSCinClean->at(i) > max_phoPSCinClean) max_phoPSCinClean = phoPSCinClean->at(i);
         mean_phoPSCinClean += phoPSCinClean->at(i);
         h_phoPSCinClean->Fill(phoPSCinClean->at(i));
         if (phoPSCinUnClean->at(i) < min_phoPSCinUnClean) min_phoPSCinUnClean = phoPSCinUnClean->at(i);
         if (phoPSCinUnClean->at(i) > max_phoPSCinUnClean) max_phoPSCinUnClean = phoPSCinUnClean->at(i);
         mean_phoPSCinUnClean += phoPSCinUnClean->at(i);
         h_phoPSCinUnClean->Fill(phoPSCinUnClean->at(i));
         if (phoPSCnBC->at(i) < min_phoPSCnBC) min_phoPSCnBC = phoPSCnBC->at(i);
         if (phoPSCnBC->at(i) > max_phoPSCnBC) max_phoPSCnBC = phoPSCnBC->at(i);
         mean_phoPSCnBC += phoPSCnBC->at(i);
         h_phoPSCnBC->Fill(phoPSCnBC->at(i));
         if (phoPESEn->at(i) < min_phoPESEn) min_phoPESEn = phoPESEn->at(i);
         if (phoPESEn->at(i) > max_phoPESEn) max_phoPESEn = phoPESEn->at(i);
         mean_phoPESEn += phoPESEn->at(i);
         h_phoPESEn->Fill(phoPESEn->at(i));
         if (phoIsPFPhoton->at(i) < min_phoIsPFPhoton) min_phoIsPFPhoton = phoIsPFPhoton->at(i);
         if (phoIsPFPhoton->at(i) > max_phoIsPFPhoton) max_phoIsPFPhoton = phoIsPFPhoton->at(i);
         mean_phoIsPFPhoton += phoIsPFPhoton->at(i);
         h_phoIsPFPhoton->Fill(phoIsPFPhoton->at(i));
         if (phoIsStandardPhoton->at(i) < min_phoIsStandardPhoton) min_phoIsStandardPhoton = phoIsStandardPhoton->at(i);
         if (phoIsStandardPhoton->at(i) > max_phoIsStandardPhoton) max_phoIsStandardPhoton = phoIsStandardPhoton->at(i);
         mean_phoIsStandardPhoton += phoIsStandardPhoton->at(i);
         h_phoIsStandardPhoton->Fill(phoIsStandardPhoton->at(i));
         if (phoHasPixelSeed->at(i) < min_phoHasPixelSeed) min_phoHasPixelSeed = phoHasPixelSeed->at(i);
         if (phoHasPixelSeed->at(i) > max_phoHasPixelSeed) max_phoHasPixelSeed = phoHasPixelSeed->at(i);
         mean_phoHasPixelSeed += phoHasPixelSeed->at(i);
         h_phoHasPixelSeed->Fill(phoHasPixelSeed->at(i));
         if (phoHasConversionTracks->at(i) < min_phoHasConversionTracks) min_phoHasConversionTracks = phoHasConversionTracks->at(i);
         if (phoHasConversionTracks->at(i) > max_phoHasConversionTracks) max_phoHasConversionTracks = phoHasConversionTracks->at(i);
         mean_phoHasConversionTracks += phoHasConversionTracks->at(i);
         h_phoHasConversionTracks->Fill(phoHasConversionTracks->at(i));
         if (phoHadTowerOverEm->at(i) < min_phoHadTowerOverEm) min_phoHadTowerOverEm = phoHadTowerOverEm->at(i);
         if (phoHadTowerOverEm->at(i) > max_phoHadTowerOverEm) max_phoHadTowerOverEm = phoHadTowerOverEm->at(i);
         mean_phoHadTowerOverEm += phoHadTowerOverEm->at(i);
         h_phoHadTowerOverEm->Fill(phoHadTowerOverEm->at(i));
         if (phoHoverE->at(i) < min_phoHoverE) min_phoHoverE = phoHoverE->at(i);
         if (phoHoverE->at(i) > max_phoHoverE) max_phoHoverE = phoHoverE->at(i);
         mean_phoHoverE += phoHoverE->at(i);
         h_phoHoverE->Fill(phoHoverE->at(i));
         if (phoHoverEValid->at(i) < min_phoHoverEValid) min_phoHoverEValid = phoHoverEValid->at(i);
         if (phoHoverEValid->at(i) > max_phoHoverEValid) max_phoHoverEValid = phoHoverEValid->at(i);
         mean_phoHoverEValid += phoHoverEValid->at(i);
         h_phoHoverEValid->Fill(phoHoverEValid->at(i));
         if (phoSigmaIEtaIEta->at(i) < min_phoSigmaIEtaIEta) min_phoSigmaIEtaIEta = phoSigmaIEtaIEta->at(i);
         if (phoSigmaIEtaIEta->at(i) > max_phoSigmaIEtaIEta) max_phoSigmaIEtaIEta = phoSigmaIEtaIEta->at(i);
         mean_phoSigmaIEtaIEta += phoSigmaIEtaIEta->at(i);
         h_phoSigmaIEtaIEta->Fill(phoSigmaIEtaIEta->at(i));
         if (phoR9->at(i) < min_phoR9) min_phoR9 = phoR9->at(i);
         if (phoR9->at(i) > max_phoR9) max_phoR9 = phoR9->at(i);
         mean_phoR9 += phoR9->at(i);
         h_phoR9->Fill(phoR9->at(i));
         if (phoE1x5->at(i) < min_phoE1x5) min_phoE1x5 = phoE1x5->at(i);
         if (phoE1x5->at(i) > max_phoE1x5) max_phoE1x5 = phoE1x5->at(i);
         mean_phoE1x5 += phoE1x5->at(i);
         h_phoE1x5->Fill(phoE1x5->at(i));
         if (phoE2x5->at(i) < min_phoE2x5) min_phoE2x5 = phoE2x5->at(i);
         if (phoE2x5->at(i) > max_phoE2x5) max_phoE2x5 = phoE2x5->at(i);
         mean_phoE2x5 += phoE2x5->at(i);
         h_phoE2x5->Fill(phoE2x5->at(i));
         if (phoE3x3->at(i) < min_phoE3x3) min_phoE3x3 = phoE3x3->at(i);
         if (phoE3x3->at(i) > max_phoE3x3) max_phoE3x3 = phoE3x3->at(i);
         mean_phoE3x3 += phoE3x3->at(i);
         h_phoE3x3->Fill(phoE3x3->at(i));
         if (phoE5x5->at(i) < min_phoE5x5) min_phoE5x5 = phoE5x5->at(i);
         if (phoE5x5->at(i) > max_phoE5x5) max_phoE5x5 = phoE5x5->at(i);
         mean_phoE5x5 += phoE5x5->at(i);
         h_phoE5x5->Fill(phoE5x5->at(i));
         if (phoMaxEnergyXtal->at(i) < min_phoMaxEnergyXtal) min_phoMaxEnergyXtal = phoMaxEnergyXtal->at(i);
         if (phoMaxEnergyXtal->at(i) > max_phoMaxEnergyXtal) max_phoMaxEnergyXtal = phoMaxEnergyXtal->at(i);
         mean_phoMaxEnergyXtal += phoMaxEnergyXtal->at(i);
         h_phoMaxEnergyXtal->Fill(phoMaxEnergyXtal->at(i));
         if (phoSigmaEtaEta->at(i) < min_phoSigmaEtaEta) min_phoSigmaEtaEta = phoSigmaEtaEta->at(i);
         if (phoSigmaEtaEta->at(i) > max_phoSigmaEtaEta) max_phoSigmaEtaEta = phoSigmaEtaEta->at(i);
         mean_phoSigmaEtaEta += phoSigmaEtaEta->at(i);
         h_phoSigmaEtaEta->Fill(phoSigmaEtaEta->at(i));
         if (phoSigmaIEtaIEta_2012->at(i) < min_phoSigmaIEtaIEta_2012) min_phoSigmaIEtaIEta_2012 = phoSigmaIEtaIEta_2012->at(i);
         if (phoSigmaIEtaIEta_2012->at(i) > max_phoSigmaIEtaIEta_2012) max_phoSigmaIEtaIEta_2012 = phoSigmaIEtaIEta_2012->at(i);
         mean_phoSigmaIEtaIEta_2012 += phoSigmaIEtaIEta_2012->at(i);
         h_phoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012->at(i));
         if (phoR9_2012->at(i) < min_phoR9_2012) min_phoR9_2012 = phoR9_2012->at(i);
         if (phoR9_2012->at(i) > max_phoR9_2012) max_phoR9_2012 = phoR9_2012->at(i);
         mean_phoR9_2012 += phoR9_2012->at(i);
         h_phoR9_2012->Fill(phoR9_2012->at(i));
         if (phoE1x5_2012->at(i) < min_phoE1x5_2012) min_phoE1x5_2012 = phoE1x5_2012->at(i);
         if (phoE1x5_2012->at(i) > max_phoE1x5_2012) max_phoE1x5_2012 = phoE1x5_2012->at(i);
         mean_phoE1x5_2012 += phoE1x5_2012->at(i);
         h_phoE1x5_2012->Fill(phoE1x5_2012->at(i));
         if (phoE2x5_2012->at(i) < min_phoE2x5_2012) min_phoE2x5_2012 = phoE2x5_2012->at(i);
         if (phoE2x5_2012->at(i) > max_phoE2x5_2012) max_phoE2x5_2012 = phoE2x5_2012->at(i);
         mean_phoE2x5_2012 += phoE2x5_2012->at(i);
         h_phoE2x5_2012->Fill(phoE2x5_2012->at(i));
         if (phoE3x3_2012->at(i) < min_phoE3x3_2012) min_phoE3x3_2012 = phoE3x3_2012->at(i);
         if (phoE3x3_2012->at(i) > max_phoE3x3_2012) max_phoE3x3_2012 = phoE3x3_2012->at(i);
         mean_phoE3x3_2012 += phoE3x3_2012->at(i);
         h_phoE3x3_2012->Fill(phoE3x3_2012->at(i));
         if (phoE5x5_2012->at(i) < min_phoE5x5_2012) min_phoE5x5_2012 = phoE5x5_2012->at(i);
         if (phoE5x5_2012->at(i) > max_phoE5x5_2012) max_phoE5x5_2012 = phoE5x5_2012->at(i);
         mean_phoE5x5_2012 += phoE5x5_2012->at(i);
         h_phoE5x5_2012->Fill(phoE5x5_2012->at(i));
         if (phoMaxEnergyXtal_2012->at(i) < min_phoMaxEnergyXtal_2012) min_phoMaxEnergyXtal_2012 = phoMaxEnergyXtal_2012->at(i);
         if (phoMaxEnergyXtal_2012->at(i) > max_phoMaxEnergyXtal_2012) max_phoMaxEnergyXtal_2012 = phoMaxEnergyXtal_2012->at(i);
         mean_phoMaxEnergyXtal_2012 += phoMaxEnergyXtal_2012->at(i);
         h_phoMaxEnergyXtal_2012->Fill(phoMaxEnergyXtal_2012->at(i));
         if (phoSigmaEtaEta_2012->at(i) < min_phoSigmaEtaEta_2012) min_phoSigmaEtaEta_2012 = phoSigmaEtaEta_2012->at(i);
         if (phoSigmaEtaEta_2012->at(i) > max_phoSigmaEtaEta_2012) max_phoSigmaEtaEta_2012 = phoSigmaEtaEta_2012->at(i);
         mean_phoSigmaEtaEta_2012 += phoSigmaEtaEta_2012->at(i);
         h_phoSigmaEtaEta_2012->Fill(phoSigmaEtaEta_2012->at(i));
         if (phoHadTowerOverEm1->at(i) < min_phoHadTowerOverEm1) min_phoHadTowerOverEm1 = phoHadTowerOverEm1->at(i);
         if (phoHadTowerOverEm1->at(i) > max_phoHadTowerOverEm1) max_phoHadTowerOverEm1 = phoHadTowerOverEm1->at(i);
         mean_phoHadTowerOverEm1 += phoHadTowerOverEm1->at(i);
         h_phoHadTowerOverEm1->Fill(phoHadTowerOverEm1->at(i));
         if (phoHadTowerOverEm2->at(i) < min_phoHadTowerOverEm2) min_phoHadTowerOverEm2 = phoHadTowerOverEm2->at(i);
         if (phoHadTowerOverEm2->at(i) > max_phoHadTowerOverEm2) max_phoHadTowerOverEm2 = phoHadTowerOverEm2->at(i);
         mean_phoHadTowerOverEm2 += phoHadTowerOverEm2->at(i);
         h_phoHadTowerOverEm2->Fill(phoHadTowerOverEm2->at(i));
         if (phoHoverE1->at(i) < min_phoHoverE1) min_phoHoverE1 = phoHoverE1->at(i);
         if (phoHoverE1->at(i) > max_phoHoverE1) max_phoHoverE1 = phoHoverE1->at(i);
         mean_phoHoverE1 += phoHoverE1->at(i);
         h_phoHoverE1->Fill(phoHoverE1->at(i));
         if (phoHoverE2->at(i) < min_phoHoverE2) min_phoHoverE2 = phoHoverE2->at(i);
         if (phoHoverE2->at(i) > max_phoHoverE2) max_phoHoverE2 = phoHoverE2->at(i);
         mean_phoHoverE2 += phoHoverE2->at(i);
         h_phoHoverE2->Fill(phoHoverE2->at(i));
         if (phoSigmaIEtaIPhi->at(i) < min_phoSigmaIEtaIPhi) min_phoSigmaIEtaIPhi = phoSigmaIEtaIPhi->at(i);
         if (phoSigmaIEtaIPhi->at(i) > max_phoSigmaIEtaIPhi) max_phoSigmaIEtaIPhi = phoSigmaIEtaIPhi->at(i);
         mean_phoSigmaIEtaIPhi += phoSigmaIEtaIPhi->at(i);
         h_phoSigmaIEtaIPhi->Fill(phoSigmaIEtaIPhi->at(i));
         if (phoSigmaIPhiIPhi->at(i) < min_phoSigmaIPhiIPhi) min_phoSigmaIPhiIPhi = phoSigmaIPhiIPhi->at(i);
         if (phoSigmaIPhiIPhi->at(i) > max_phoSigmaIPhiIPhi) max_phoSigmaIPhiIPhi = phoSigmaIPhiIPhi->at(i);
         mean_phoSigmaIPhiIPhi += phoSigmaIPhiIPhi->at(i);
         h_phoSigmaIPhiIPhi->Fill(phoSigmaIPhiIPhi->at(i));
         if (phoR1x5->at(i) < min_phoR1x5) min_phoR1x5 = phoR1x5->at(i);
         if (phoR1x5->at(i) > max_phoR1x5) max_phoR1x5 = phoR1x5->at(i);
         mean_phoR1x5 += phoR1x5->at(i);
         h_phoR1x5->Fill(phoR1x5->at(i));
         if (phoR2x5->at(i) < min_phoR2x5) min_phoR2x5 = phoR2x5->at(i);
         if (phoR2x5->at(i) > max_phoR2x5) max_phoR2x5 = phoR2x5->at(i);
         mean_phoR2x5 += phoR2x5->at(i);
         h_phoR2x5->Fill(phoR2x5->at(i));
         if (phoE2nd->at(i) < min_phoE2nd) min_phoE2nd = phoE2nd->at(i);
         if (phoE2nd->at(i) > max_phoE2nd) max_phoE2nd = phoE2nd->at(i);
         mean_phoE2nd += phoE2nd->at(i);
         h_phoE2nd->Fill(phoE2nd->at(i));
         if (phoETop->at(i) < min_phoETop) min_phoETop = phoETop->at(i);
         if (phoETop->at(i) > max_phoETop) max_phoETop = phoETop->at(i);
         mean_phoETop += phoETop->at(i);
         h_phoETop->Fill(phoETop->at(i));
         if (phoEBottom->at(i) < min_phoEBottom) min_phoEBottom = phoEBottom->at(i);
         if (phoEBottom->at(i) > max_phoEBottom) max_phoEBottom = phoEBottom->at(i);
         mean_phoEBottom += phoEBottom->at(i);
         h_phoEBottom->Fill(phoEBottom->at(i));
         if (phoELeft->at(i) < min_phoELeft) min_phoELeft = phoELeft->at(i);
         if (phoELeft->at(i) > max_phoELeft) max_phoELeft = phoELeft->at(i);
         mean_phoELeft += phoELeft->at(i);
         h_phoELeft->Fill(phoELeft->at(i));
         if (phoERight->at(i) < min_phoERight) min_phoERight = phoERight->at(i);
         if (phoERight->at(i) > max_phoERight) max_phoERight = phoERight->at(i);
         mean_phoERight += phoERight->at(i);
         h_phoERight->Fill(phoERight->at(i));
         if (phoE1x3->at(i) < min_phoE1x3) min_phoE1x3 = phoE1x3->at(i);
         if (phoE1x3->at(i) > max_phoE1x3) max_phoE1x3 = phoE1x3->at(i);
         mean_phoE1x3 += phoE1x3->at(i);
         h_phoE1x3->Fill(phoE1x3->at(i));
         if (phoE2x2->at(i) < min_phoE2x2) min_phoE2x2 = phoE2x2->at(i);
         if (phoE2x2->at(i) > max_phoE2x2) max_phoE2x2 = phoE2x2->at(i);
         mean_phoE2x2 += phoE2x2->at(i);
         h_phoE2x2->Fill(phoE2x2->at(i));
         if (phoE2x5Max->at(i) < min_phoE2x5Max) min_phoE2x5Max = phoE2x5Max->at(i);
         if (phoE2x5Max->at(i) > max_phoE2x5Max) max_phoE2x5Max = phoE2x5Max->at(i);
         mean_phoE2x5Max += phoE2x5Max->at(i);
         h_phoE2x5Max->Fill(phoE2x5Max->at(i));
         if (phoE2x5Top->at(i) < min_phoE2x5Top) min_phoE2x5Top = phoE2x5Top->at(i);
         if (phoE2x5Top->at(i) > max_phoE2x5Top) max_phoE2x5Top = phoE2x5Top->at(i);
         mean_phoE2x5Top += phoE2x5Top->at(i);
         h_phoE2x5Top->Fill(phoE2x5Top->at(i));
         if (phoE2x5Bottom->at(i) < min_phoE2x5Bottom) min_phoE2x5Bottom = phoE2x5Bottom->at(i);
         if (phoE2x5Bottom->at(i) > max_phoE2x5Bottom) max_phoE2x5Bottom = phoE2x5Bottom->at(i);
         mean_phoE2x5Bottom += phoE2x5Bottom->at(i);
         h_phoE2x5Bottom->Fill(phoE2x5Bottom->at(i));
         if (phoE2x5Left->at(i) < min_phoE2x5Left) min_phoE2x5Left = phoE2x5Left->at(i);
         if (phoE2x5Left->at(i) > max_phoE2x5Left) max_phoE2x5Left = phoE2x5Left->at(i);
         mean_phoE2x5Left += phoE2x5Left->at(i);
         h_phoE2x5Left->Fill(phoE2x5Left->at(i));
         if (phoE2x5Right->at(i) < min_phoE2x5Right) min_phoE2x5Right = phoE2x5Right->at(i);
         if (phoE2x5Right->at(i) > max_phoE2x5Right) max_phoE2x5Right = phoE2x5Right->at(i);
         mean_phoE2x5Right += phoE2x5Right->at(i);
         h_phoE2x5Right->Fill(phoE2x5Right->at(i));
         if (phoSigmaIEtaIPhi_2012->at(i) < min_phoSigmaIEtaIPhi_2012) min_phoSigmaIEtaIPhi_2012 = phoSigmaIEtaIPhi_2012->at(i);
         if (phoSigmaIEtaIPhi_2012->at(i) > max_phoSigmaIEtaIPhi_2012) max_phoSigmaIEtaIPhi_2012 = phoSigmaIEtaIPhi_2012->at(i);
         mean_phoSigmaIEtaIPhi_2012 += phoSigmaIEtaIPhi_2012->at(i);
         h_phoSigmaIEtaIPhi_2012->Fill(phoSigmaIEtaIPhi_2012->at(i));
         if (phoSigmaIPhiIPhi_2012->at(i) < min_phoSigmaIPhiIPhi_2012) min_phoSigmaIPhiIPhi_2012 = phoSigmaIPhiIPhi_2012->at(i);
         if (phoSigmaIPhiIPhi_2012->at(i) > max_phoSigmaIPhiIPhi_2012) max_phoSigmaIPhiIPhi_2012 = phoSigmaIPhiIPhi_2012->at(i);
         mean_phoSigmaIPhiIPhi_2012 += phoSigmaIPhiIPhi_2012->at(i);
         h_phoSigmaIPhiIPhi_2012->Fill(phoSigmaIPhiIPhi_2012->at(i));
         if (phoR1x5_2012->at(i) < min_phoR1x5_2012) min_phoR1x5_2012 = phoR1x5_2012->at(i);
         if (phoR1x5_2012->at(i) > max_phoR1x5_2012) max_phoR1x5_2012 = phoR1x5_2012->at(i);
         mean_phoR1x5_2012 += phoR1x5_2012->at(i);
         h_phoR1x5_2012->Fill(phoR1x5_2012->at(i));
         if (phoR2x5_2012->at(i) < min_phoR2x5_2012) min_phoR2x5_2012 = phoR2x5_2012->at(i);
         if (phoR2x5_2012->at(i) > max_phoR2x5_2012) max_phoR2x5_2012 = phoR2x5_2012->at(i);
         mean_phoR2x5_2012 += phoR2x5_2012->at(i);
         h_phoR2x5_2012->Fill(phoR2x5_2012->at(i));
         if (phoE2nd_2012->at(i) < min_phoE2nd_2012) min_phoE2nd_2012 = phoE2nd_2012->at(i);
         if (phoE2nd_2012->at(i) > max_phoE2nd_2012) max_phoE2nd_2012 = phoE2nd_2012->at(i);
         mean_phoE2nd_2012 += phoE2nd_2012->at(i);
         h_phoE2nd_2012->Fill(phoE2nd_2012->at(i));
         if (phoETop_2012->at(i) < min_phoETop_2012) min_phoETop_2012 = phoETop_2012->at(i);
         if (phoETop_2012->at(i) > max_phoETop_2012) max_phoETop_2012 = phoETop_2012->at(i);
         mean_phoETop_2012 += phoETop_2012->at(i);
         h_phoETop_2012->Fill(phoETop_2012->at(i));
         if (phoEBottom_2012->at(i) < min_phoEBottom_2012) min_phoEBottom_2012 = phoEBottom_2012->at(i);
         if (phoEBottom_2012->at(i) > max_phoEBottom_2012) max_phoEBottom_2012 = phoEBottom_2012->at(i);
         mean_phoEBottom_2012 += phoEBottom_2012->at(i);
         h_phoEBottom_2012->Fill(phoEBottom_2012->at(i));
         if (phoELeft_2012->at(i) < min_phoELeft_2012) min_phoELeft_2012 = phoELeft_2012->at(i);
         if (phoELeft_2012->at(i) > max_phoELeft_2012) max_phoELeft_2012 = phoELeft_2012->at(i);
         mean_phoELeft_2012 += phoELeft_2012->at(i);
         h_phoELeft_2012->Fill(phoELeft_2012->at(i));
         if (phoERight_2012->at(i) < min_phoERight_2012) min_phoERight_2012 = phoERight_2012->at(i);
         if (phoERight_2012->at(i) > max_phoERight_2012) max_phoERight_2012 = phoERight_2012->at(i);
         mean_phoERight_2012 += phoERight_2012->at(i);
         h_phoERight_2012->Fill(phoERight_2012->at(i));
         if (phoE1x3_2012->at(i) < min_phoE1x3_2012) min_phoE1x3_2012 = phoE1x3_2012->at(i);
         if (phoE1x3_2012->at(i) > max_phoE1x3_2012) max_phoE1x3_2012 = phoE1x3_2012->at(i);
         mean_phoE1x3_2012 += phoE1x3_2012->at(i);
         h_phoE1x3_2012->Fill(phoE1x3_2012->at(i));
         if (phoE2x2_2012->at(i) < min_phoE2x2_2012) min_phoE2x2_2012 = phoE2x2_2012->at(i);
         if (phoE2x2_2012->at(i) > max_phoE2x2_2012) max_phoE2x2_2012 = phoE2x2_2012->at(i);
         mean_phoE2x2_2012 += phoE2x2_2012->at(i);
         h_phoE2x2_2012->Fill(phoE2x2_2012->at(i));
         if (phoE2x5Max_2012->at(i) < min_phoE2x5Max_2012) min_phoE2x5Max_2012 = phoE2x5Max_2012->at(i);
         if (phoE2x5Max_2012->at(i) > max_phoE2x5Max_2012) max_phoE2x5Max_2012 = phoE2x5Max_2012->at(i);
         mean_phoE2x5Max_2012 += phoE2x5Max_2012->at(i);
         h_phoE2x5Max_2012->Fill(phoE2x5Max_2012->at(i));
         if (phoE2x5Top_2012->at(i) < min_phoE2x5Top_2012) min_phoE2x5Top_2012 = phoE2x5Top_2012->at(i);
         if (phoE2x5Top_2012->at(i) > max_phoE2x5Top_2012) max_phoE2x5Top_2012 = phoE2x5Top_2012->at(i);
         mean_phoE2x5Top_2012 += phoE2x5Top_2012->at(i);
         h_phoE2x5Top_2012->Fill(phoE2x5Top_2012->at(i));
         if (phoE2x5Bottom_2012->at(i) < min_phoE2x5Bottom_2012) min_phoE2x5Bottom_2012 = phoE2x5Bottom_2012->at(i);
         if (phoE2x5Bottom_2012->at(i) > max_phoE2x5Bottom_2012) max_phoE2x5Bottom_2012 = phoE2x5Bottom_2012->at(i);
         mean_phoE2x5Bottom_2012 += phoE2x5Bottom_2012->at(i);
         h_phoE2x5Bottom_2012->Fill(phoE2x5Bottom_2012->at(i));
         if (phoE2x5Left_2012->at(i) < min_phoE2x5Left_2012) min_phoE2x5Left_2012 = phoE2x5Left_2012->at(i);
         if (phoE2x5Left_2012->at(i) > max_phoE2x5Left_2012) max_phoE2x5Left_2012 = phoE2x5Left_2012->at(i);
         mean_phoE2x5Left_2012 += phoE2x5Left_2012->at(i);
         h_phoE2x5Left_2012->Fill(phoE2x5Left_2012->at(i));
         if (phoE2x5Right_2012->at(i) < min_phoE2x5Right_2012) min_phoE2x5Right_2012 = phoE2x5Right_2012->at(i);
         if (phoE2x5Right_2012->at(i) > max_phoE2x5Right_2012) max_phoE2x5Right_2012 = phoE2x5Right_2012->at(i);
         mean_phoE2x5Right_2012 += phoE2x5Right_2012->at(i);
         h_phoE2x5Right_2012->Fill(phoE2x5Right_2012->at(i));
         if (phoBC1E->at(i) < min_phoBC1E) min_phoBC1E = phoBC1E->at(i);
         if (phoBC1E->at(i) > max_phoBC1E) max_phoBC1E = phoBC1E->at(i);
         mean_phoBC1E += phoBC1E->at(i);
         h_phoBC1E->Fill(phoBC1E->at(i));
         if (phoBC1Ecorr->at(i) < min_phoBC1Ecorr) min_phoBC1Ecorr = phoBC1Ecorr->at(i);
         if (phoBC1Ecorr->at(i) > max_phoBC1Ecorr) max_phoBC1Ecorr = phoBC1Ecorr->at(i);
         mean_phoBC1Ecorr += phoBC1Ecorr->at(i);
         h_phoBC1Ecorr->Fill(phoBC1Ecorr->at(i));
         if (phoBC1Eta->at(i) < min_phoBC1Eta) min_phoBC1Eta = phoBC1Eta->at(i);
         if (phoBC1Eta->at(i) > max_phoBC1Eta) max_phoBC1Eta = phoBC1Eta->at(i);
         mean_phoBC1Eta += phoBC1Eta->at(i);
         h_phoBC1Eta->Fill(phoBC1Eta->at(i));
         if (phoBC1Phi->at(i) < min_phoBC1Phi) min_phoBC1Phi = phoBC1Phi->at(i);
         if (phoBC1Phi->at(i) > max_phoBC1Phi) max_phoBC1Phi = phoBC1Phi->at(i);
         mean_phoBC1Phi += phoBC1Phi->at(i);
         h_phoBC1Phi->Fill(phoBC1Phi->at(i));
         if (phoBC1size->at(i) < min_phoBC1size) min_phoBC1size = phoBC1size->at(i);
         if (phoBC1size->at(i) > max_phoBC1size) max_phoBC1size = phoBC1size->at(i);
         mean_phoBC1size += phoBC1size->at(i);
         h_phoBC1size->Fill(phoBC1size->at(i));
         if (phoBC1flags->at(i) < min_phoBC1flags) min_phoBC1flags = phoBC1flags->at(i);
         if (phoBC1flags->at(i) > max_phoBC1flags) max_phoBC1flags = phoBC1flags->at(i);
         mean_phoBC1flags += phoBC1flags->at(i);
         h_phoBC1flags->Fill(phoBC1flags->at(i));
         if (phoBC1inClean->at(i) < min_phoBC1inClean) min_phoBC1inClean = phoBC1inClean->at(i);
         if (phoBC1inClean->at(i) > max_phoBC1inClean) max_phoBC1inClean = phoBC1inClean->at(i);
         mean_phoBC1inClean += phoBC1inClean->at(i);
         h_phoBC1inClean->Fill(phoBC1inClean->at(i));
         if (phoBC1inUnClean->at(i) < min_phoBC1inUnClean) min_phoBC1inUnClean = phoBC1inUnClean->at(i);
         if (phoBC1inUnClean->at(i) > max_phoBC1inUnClean) max_phoBC1inUnClean = phoBC1inUnClean->at(i);
         mean_phoBC1inUnClean += phoBC1inUnClean->at(i);
         h_phoBC1inUnClean->Fill(phoBC1inUnClean->at(i));
         if (phoBC1rawID->at(i) < min_phoBC1rawID) min_phoBC1rawID = phoBC1rawID->at(i);
         if (phoBC1rawID->at(i) > max_phoBC1rawID) max_phoBC1rawID = phoBC1rawID->at(i);
         mean_phoBC1rawID += phoBC1rawID->at(i);
         h_phoBC1rawID->Fill(phoBC1rawID->at(i));
         // if (pho_ecalClusterIsoR2->at(i) < min_pho_ecalClusterIsoR2) min_pho_ecalClusterIsoR2 = pho_ecalClusterIsoR2->at(i);
         // if (pho_ecalClusterIsoR2->at(i) > max_pho_ecalClusterIsoR2) max_pho_ecalClusterIsoR2 = pho_ecalClusterIsoR2->at(i);
         // mean_pho_ecalClusterIsoR2 += pho_ecalClusterIsoR2->at(i);
         // h_pho_ecalClusterIsoR2->Fill(pho_ecalClusterIsoR2->at(i));
      //    if (pho_ecalClusterIsoR3->at(i) < min_pho_ecalClusterIsoR3) min_pho_ecalClusterIsoR3 = pho_ecalClusterIsoR3->at(i);
      //    if (pho_ecalClusterIsoR3->at(i) > max_pho_ecalClusterIsoR3) max_pho_ecalClusterIsoR3 = pho_ecalClusterIsoR3->at(i);
      //    mean_pho_ecalClusterIsoR3 += pho_ecalClusterIsoR3->at(i);
      //    h_pho_ecalClusterIsoR3->Fill(pho_ecalClusterIsoR3->at(i));
      //    if (pho_ecalClusterIsoR4->at(i) < min_pho_ecalClusterIsoR4) min_pho_ecalClusterIsoR4 = pho_ecalClusterIsoR4->at(i);
      //    if (pho_ecalClusterIsoR4->at(i) > max_pho_ecalClusterIsoR4) max_pho_ecalClusterIsoR4 = pho_ecalClusterIsoR4->at(i);
      //    mean_pho_ecalClusterIsoR4 += pho_ecalClusterIsoR4->at(i);
      //    h_pho_ecalClusterIsoR4->Fill(pho_ecalClusterIsoR4->at(i));
      //    if (pho_ecalClusterIsoR5->at(i) < min_pho_ecalClusterIsoR5) min_pho_ecalClusterIsoR5 = pho_ecalClusterIsoR5->at(i);
      //    if (pho_ecalClusterIsoR5->at(i) > max_pho_ecalClusterIsoR5) max_pho_ecalClusterIsoR5 = pho_ecalClusterIsoR5->at(i);
      //    mean_pho_ecalClusterIsoR5 += pho_ecalClusterIsoR5->at(i);
      //    h_pho_ecalClusterIsoR5->Fill(pho_ecalClusterIsoR5->at(i));
      //    if (pho_hcalRechitIsoR1->at(i) < min_pho_hcalRechitIsoR1) min_pho_hcalRechitIsoR1 = pho_hcalRechitIsoR1->at(i);
      //    if (pho_hcalRechitIsoR1->at(i) > max_pho_hcalRechitIsoR1) max_pho_hcalRechitIsoR1 = pho_hcalRechitIsoR1->at(i);
      //    mean_pho_hcalRechitIsoR1 += pho_hcalRechitIsoR1->at(i);
      //    h_pho_hcalRechitIsoR1->Fill(pho_hcalRechitIsoR1->at(i));
      //    if (pho_hcalRechitIsoR2->at(i) < min_pho_hcalRechitIsoR2) min_pho_hcalRechitIsoR2 = pho_hcalRechitIsoR2->at(i);
      //    if (pho_hcalRechitIsoR2->at(i) > max_pho_hcalRechitIsoR2) max_pho_hcalRechitIsoR2 = pho_hcalRechitIsoR2->at(i);
      //    mean_pho_hcalRechitIsoR2 += pho_hcalRechitIsoR2->at(i);
      //    h_pho_hcalRechitIsoR2->Fill(pho_hcalRechitIsoR2->at(i));
         // if (pho_hcalRechitIsoR3->at(i) < min_pho_hcalRechitIsoR3) min_pho_hcalRechitIsoR3 = pho_hcalRechitIsoR3->at(i);
         // if (pho_hcalRechitIsoR3->at(i) > max_pho_hcalRechitIsoR3) max_pho_hcalRechitIsoR3 = pho_hcalRechitIsoR3->at(i);
         // mean_pho_hcalRechitIsoR3 += pho_hcalRechitIsoR3->at(i);
         // h_pho_hcalRechitIsoR3->Fill(pho_hcalRechitIsoR3->at(i));
         // if (pho_hcalRechitIsoR4->at(i) < min_pho_hcalRechitIsoR4) min_pho_hcalRechitIsoR4 = pho_hcalRechitIsoR4->at(i);
         // if (pho_hcalRechitIsoR4->at(i) > max_pho_hcalRechitIsoR4) max_pho_hcalRechitIsoR4 = pho_hcalRechitIsoR4->at(i);
         // mean_pho_hcalRechitIsoR4 += pho_hcalRechitIsoR4->at(i);
         // h_pho_hcalRechitIsoR4->Fill(pho_hcalRechitIsoR4->at(i));
         // if (pho_hcalRechitIsoR5->at(i) < min_pho_hcalRechitIsoR5) min_pho_hcalRechitIsoR5 = pho_hcalRechitIsoR5->at(i);
         // if (pho_hcalRechitIsoR5->at(i) > max_pho_hcalRechitIsoR5) max_pho_hcalRechitIsoR5 = pho_hcalRechitIsoR5->at(i);
         // mean_pho_hcalRechitIsoR5 += pho_hcalRechitIsoR5->at(i);
         // h_pho_hcalRechitIsoR5->Fill(pho_hcalRechitIsoR5->at(i));
         // if (pho_trackIsoR1PtCut20->at(i) < min_pho_trackIsoR1PtCut20) min_pho_trackIsoR1PtCut20 = pho_trackIsoR1PtCut20->at(i);
         // if (pho_trackIsoR1PtCut20->at(i) > max_pho_trackIsoR1PtCut20) max_pho_trackIsoR1PtCut20 = pho_trackIsoR1PtCut20->at(i);
         // mean_pho_trackIsoR1PtCut20 += pho_trackIsoR1PtCut20->at(i);
         // h_pho_trackIsoR1PtCut20->Fill(pho_trackIsoR1PtCut20->at(i));
         // if (pho_trackIsoR2PtCut20->at(i) < min_pho_trackIsoR2PtCut20) min_pho_trackIsoR2PtCut20 = pho_trackIsoR2PtCut20->at(i);
         // if (pho_trackIsoR2PtCut20->at(i) > max_pho_trackIsoR2PtCut20) max_pho_trackIsoR2PtCut20 = pho_trackIsoR2PtCut20->at(i);
         // mean_pho_trackIsoR2PtCut20 += pho_trackIsoR2PtCut20->at(i);
         // h_pho_trackIsoR2PtCut20->Fill(pho_trackIsoR2PtCut20->at(i));
         // if (pho_trackIsoR3PtCut20->at(i) < min_pho_trackIsoR3PtCut20) min_pho_trackIsoR3PtCut20 = pho_trackIsoR3PtCut20->at(i);
         // if (pho_trackIsoR3PtCut20->at(i) > max_pho_trackIsoR3PtCut20) max_pho_trackIsoR3PtCut20 = pho_trackIsoR3PtCut20->at(i);
         // mean_pho_trackIsoR3PtCut20 += pho_trackIsoR3PtCut20->at(i);
         // h_pho_trackIsoR3PtCut20->Fill(pho_trackIsoR3PtCut20->at(i));
         // if (pho_trackIsoR4PtCut20->at(i) < min_pho_trackIsoR4PtCut20) min_pho_trackIsoR4PtCut20 = pho_trackIsoR4PtCut20->at(i);
         // if (pho_trackIsoR4PtCut20->at(i) > max_pho_trackIsoR4PtCut20) max_pho_trackIsoR4PtCut20 = pho_trackIsoR4PtCut20->at(i);
         // mean_pho_trackIsoR4PtCut20 += pho_trackIsoR4PtCut20->at(i);
         // h_pho_trackIsoR4PtCut20->Fill(pho_trackIsoR4PtCut20->at(i));
         // if (pho_trackIsoR5PtCut20->at(i) < min_pho_trackIsoR5PtCut20) min_pho_trackIsoR5PtCut20 = pho_trackIsoR5PtCut20->at(i);
         // if (pho_trackIsoR5PtCut20->at(i) > max_pho_trackIsoR5PtCut20) max_pho_trackIsoR5PtCut20 = pho_trackIsoR5PtCut20->at(i);
         // mean_pho_trackIsoR5PtCut20 += pho_trackIsoR5PtCut20->at(i);
         // h_pho_trackIsoR5PtCut20->Fill(pho_trackIsoR5PtCut20->at(i));
         // if (pho_swissCrx->at(i) < min_pho_swissCrx) min_pho_swissCrx = pho_swissCrx->at(i);
         // if (pho_swissCrx->at(i) > max_pho_swissCrx) max_pho_swissCrx = pho_swissCrx->at(i);
         // mean_pho_swissCrx += pho_swissCrx->at(i);
         // h_pho_swissCrx->Fill(pho_swissCrx->at(i));
         // if (pho_seedTime->at(i) < min_pho_seedTime) min_pho_seedTime = pho_seedTime->at(i);
         // if (pho_seedTime->at(i) > max_pho_seedTime) max_pho_seedTime = pho_seedTime->at(i);
         // mean_pho_seedTime += pho_seedTime->at(i);
         // h_pho_seedTime->Fill(pho_seedTime->at(i));
      }
      if (nTower < min_nTower) min_nTower = nTower;
      if (nTower > max_nTower) max_nTower = nTower;
      mean_nTower += nTower;
      h_nTower->Fill(nTower);

      // etaring histos
      double CaloTower_e_etaring[ncalohist] = {0};
      double CaloTower_et_etaring[ncalohist] = {0};
      double CaloTower_e_etaring_noSC[ncalohist] = {0};
      double CaloTower_et_etaring_noSC[ncalohist] = {0};
      for (int i=0; i<nTower; i++) {
         if (CaloTower_hadE->at(i) < min_CaloTower_hadE) min_CaloTower_hadE = CaloTower_hadE->at(i);
         if (CaloTower_hadE->at(i) > max_CaloTower_hadE) max_CaloTower_hadE = CaloTower_hadE->at(i);
         mean_CaloTower_hadE += CaloTower_hadE->at(i);
         h_CaloTower_hadE->Fill(CaloTower_hadE->at(i));
         if (CaloTower_emE->at(i) < min_CaloTower_emE) min_CaloTower_emE = CaloTower_emE->at(i);
         if (CaloTower_emE->at(i) > max_CaloTower_emE) max_CaloTower_emE = CaloTower_emE->at(i);
         mean_CaloTower_emE += CaloTower_emE->at(i);
         h_CaloTower_emE->Fill(CaloTower_emE->at(i));
         if (CaloTower_e->at(i) < min_CaloTower_e) min_CaloTower_e = CaloTower_e->at(i);
         if (CaloTower_e->at(i) > max_CaloTower_e) max_CaloTower_e = CaloTower_e->at(i);
         mean_CaloTower_e += CaloTower_e->at(i);
         h_CaloTower_e->Fill(CaloTower_e->at(i));
         if (CaloTower_et->at(i) < min_CaloTower_et) min_CaloTower_et = CaloTower_et->at(i);
         if (CaloTower_et->at(i) > max_CaloTower_et) max_CaloTower_et = CaloTower_et->at(i);
         mean_CaloTower_et += CaloTower_et->at(i);
         h_CaloTower_et->Fill(CaloTower_et->at(i));
         if (CaloTower_eta->at(i) < min_CaloTower_eta) min_CaloTower_eta = CaloTower_eta->at(i);
         if (CaloTower_eta->at(i) > max_CaloTower_eta) max_CaloTower_eta = CaloTower_eta->at(i);
         mean_CaloTower_eta += CaloTower_eta->at(i);
         h_CaloTower_eta->Fill(CaloTower_eta->at(i));
         if (CaloTower_phi->at(i) < min_CaloTower_phi) min_CaloTower_phi = CaloTower_phi->at(i);
         if (CaloTower_phi->at(i) > max_CaloTower_phi) max_CaloTower_phi = CaloTower_phi->at(i);
         mean_CaloTower_phi += CaloTower_phi->at(i);
         h_CaloTower_phi->Fill(CaloTower_phi->at(i));

         double e = CaloTower_e->at(i);
         double et = CaloTower_et->at(i);
         double eta = CaloTower_eta->at(i);
         double phi = CaloTower_phi->at(i);
         TVector3 tv3; tv3.SetPtEtaPhi(1,eta,phi);
         for (int ie=0; ie<ncalohist; ie++) {
            if (eta>-5+ie*0.5 && eta<-5+(ie+1)*0.5) {
               CaloTower_e_etaring[ie] += e;
               CaloTower_et_etaring[ie] += et;

               bool scmatch=false;
               for (int is=0; is<nSC; is++) {
                  TVector3 tsc; tsc.SetPtEtaPhi(1,scEta->at(is),scPhi->at(is));
                  if (tv3.DeltaR(tsc)<0.05) {
                     scmatch = true;
                     break;
                  }
               }

               if (!scmatch) {
                  CaloTower_e_etaring_noSC[ie] += e;
                  CaloTower_et_etaring_noSC[ie] += et;
               }
            }
         }
      }
      for (int ie=0; ie<ncalohist; ie++) {
         h_CaloTower_e_etaring[ie]->Fill(CaloTower_e_etaring[ie]);
         h_CaloTower_et_etaring[ie]->Fill(CaloTower_et_etaring[ie]);
         h_CaloTower_e_etaring_noSC[ie]->Fill(CaloTower_e_etaring_noSC[ie]);
         h_CaloTower_et_etaring_noSC[ie]->Fill(CaloTower_et_etaring_noSC[ie]);
         // cout << ie << ": " << CaloTower_e_etaring[ie] << " " << CaloTower_et_etaring[ie] << " " << CaloTower_e_etaring_noSC[ie] << " " << CaloTower_et_etaring_noSC[ie] << endl;
      }
      if (nTrackerHits < min_nTrackerHits) min_nTrackerHits = nTrackerHits;
      if (nTrackerHits > max_nTrackerHits) max_nTrackerHits = nTrackerHits;
      mean_nTrackerHits += nTrackerHits;
      h_nTrackerHits->Fill(nTrackerHits);
      if (nPixelClusters < min_nPixelClusters) min_nPixelClusters = nPixelClusters;
      if (nPixelClusters > max_nPixelClusters) max_nPixelClusters = nPixelClusters;
      mean_nPixelClusters += nPixelClusters;
      h_nPixelClusters->Fill(nPixelClusters);
      if (nPixelRecHits < min_nPixelRecHits) min_nPixelRecHits = nPixelRecHits;
      if (nPixelRecHits > max_nPixelRecHits) max_nPixelRecHits = nPixelRecHits;
      mean_nPixelRecHits += nPixelRecHits;
      h_nPixelRecHits->Fill(nPixelRecHits);
   }

   // print what histo declarations should be
   if (h_run->GetEntries() > 0) mean_run = mean_run / h_run->GetEntries();
   cout << "TH1F *h_run = new TH1F(\"h_run\",\"run\",10," << min_run << "," << max_run << "); // mean = " << mean_run << endl;
   if (h_event->GetEntries() > 0) mean_event = mean_event / h_event->GetEntries();
   cout << "TH1F *h_event = new TH1F(\"h_event\",\"event\",10," << min_event << "," << max_event << "); // mean = " << mean_event << endl;
   if (h_lumis->GetEntries() > 0) mean_lumis = mean_lumis / h_lumis->GetEntries();
   cout << "TH1F *h_lumis = new TH1F(\"h_lumis\",\"lumis\",10," << min_lumis << "," << max_lumis << "); // mean = " << mean_lumis << endl;
   if (h_nSC->GetEntries() > 0) mean_nSC = mean_nSC / h_nSC->GetEntries();
   cout << "TH1F *h_nSC = new TH1F(\"h_nSC\",\"nSC\",10," << min_nSC << "," << max_nSC << "); // mean = " << mean_nSC << endl;
   if (h_scE->GetEntries() > 0) mean_scE = mean_scE / h_scE->GetEntries();
   cout << "TH1F *h_scE = new TH1F(\"h_scE\",\"scE\",10," << min_scE << "," << max_scE << "); // mean = " << mean_scE << endl;
   if (h_scRawE->GetEntries() > 0) mean_scRawE = mean_scRawE / h_scRawE->GetEntries();
   cout << "TH1F *h_scRawE = new TH1F(\"h_scRawE\",\"scRawE\",10," << min_scRawE << "," << max_scRawE << "); // mean = " << mean_scRawE << endl;
   if (h_scEta->GetEntries() > 0) mean_scEta = mean_scEta / h_scEta->GetEntries();
   cout << "TH1F *h_scEta = new TH1F(\"h_scEta\",\"scEta\",10," << min_scEta << "," << max_scEta << "); // mean = " << mean_scEta << endl;
   if (h_scPhi->GetEntries() > 0) mean_scPhi = mean_scPhi / h_scPhi->GetEntries();
   cout << "TH1F *h_scPhi = new TH1F(\"h_scPhi\",\"scPhi\",10," << min_scPhi << "," << max_scPhi << "); // mean = " << mean_scPhi << endl;
   if (h_nPho->GetEntries() > 0) mean_nPho = mean_nPho / h_nPho->GetEntries();
   cout << "TH1F *h_nPho = new TH1F(\"h_nPho\",\"nPho\",10," << min_nPho << "," << max_nPho << "); // mean = " << mean_nPho << endl;
   if (h_phoE->GetEntries() > 0) mean_phoE = mean_phoE / h_phoE->GetEntries();
   cout << "TH1F *h_phoE = new TH1F(\"h_phoE\",\"phoE\",10," << min_phoE << "," << max_phoE << "); // mean = " << mean_phoE << endl;
   if (h_phoEt->GetEntries() > 0) mean_phoEt = mean_phoEt / h_phoEt->GetEntries();
   cout << "TH1F *h_phoEt = new TH1F(\"h_phoEt\",\"phoEt\",10," << min_phoEt << "," << max_phoEt << "); // mean = " << mean_phoEt << endl;
   if (h_phoEta->GetEntries() > 0) mean_phoEta = mean_phoEta / h_phoEta->GetEntries();
   cout << "TH1F *h_phoEta = new TH1F(\"h_phoEta\",\"phoEta\",10," << min_phoEta << "," << max_phoEta << "); // mean = " << mean_phoEta << endl;
   if (h_phoPhi->GetEntries() > 0) mean_phoPhi = mean_phoPhi / h_phoPhi->GetEntries();
   cout << "TH1F *h_phoPhi = new TH1F(\"h_phoPhi\",\"phoPhi\",10," << min_phoPhi << "," << max_phoPhi << "); // mean = " << mean_phoPhi << endl;
   if (h_phoEcorrStdEcal->GetEntries() > 0) mean_phoEcorrStdEcal = mean_phoEcorrStdEcal / h_phoEcorrStdEcal->GetEntries();
   cout << "TH1F *h_phoEcorrStdEcal = new TH1F(\"h_phoEcorrStdEcal\",\"phoEcorrStdEcal\",10," << min_phoEcorrStdEcal << "," << max_phoEcorrStdEcal << "); // mean = " << mean_phoEcorrStdEcal << endl;
   if (h_phoEcorrPhoEcal->GetEntries() > 0) mean_phoEcorrPhoEcal = mean_phoEcorrPhoEcal / h_phoEcorrPhoEcal->GetEntries();
   cout << "TH1F *h_phoEcorrPhoEcal = new TH1F(\"h_phoEcorrPhoEcal\",\"phoEcorrPhoEcal\",10," << min_phoEcorrPhoEcal << "," << max_phoEcorrPhoEcal << "); // mean = " << mean_phoEcorrPhoEcal << endl;
   if (h_phoEcorrRegr1->GetEntries() > 0) mean_phoEcorrRegr1 = mean_phoEcorrRegr1 / h_phoEcorrRegr1->GetEntries();
   cout << "TH1F *h_phoEcorrRegr1 = new TH1F(\"h_phoEcorrRegr1\",\"phoEcorrRegr1\",10," << min_phoEcorrRegr1 << "," << max_phoEcorrRegr1 << "); // mean = " << mean_phoEcorrRegr1 << endl;
   if (h_phoEcorrRegr2->GetEntries() > 0) mean_phoEcorrRegr2 = mean_phoEcorrRegr2 / h_phoEcorrRegr2->GetEntries();
   cout << "TH1F *h_phoEcorrRegr2 = new TH1F(\"h_phoEcorrRegr2\",\"phoEcorrRegr2\",10," << min_phoEcorrRegr2 << "," << max_phoEcorrRegr2 << "); // mean = " << mean_phoEcorrRegr2 << endl;
   if (h_phoEcorrErrStdEcal->GetEntries() > 0) mean_phoEcorrErrStdEcal = mean_phoEcorrErrStdEcal / h_phoEcorrErrStdEcal->GetEntries();
   cout << "TH1F *h_phoEcorrErrStdEcal = new TH1F(\"h_phoEcorrErrStdEcal\",\"phoEcorrErrStdEcal\",10," << min_phoEcorrErrStdEcal << "," << max_phoEcorrErrStdEcal << "); // mean = " << mean_phoEcorrErrStdEcal << endl;
   if (h_phoEcorrErrPhoEcal->GetEntries() > 0) mean_phoEcorrErrPhoEcal = mean_phoEcorrErrPhoEcal / h_phoEcorrErrPhoEcal->GetEntries();
   cout << "TH1F *h_phoEcorrErrPhoEcal = new TH1F(\"h_phoEcorrErrPhoEcal\",\"phoEcorrErrPhoEcal\",10," << min_phoEcorrErrPhoEcal << "," << max_phoEcorrErrPhoEcal << "); // mean = " << mean_phoEcorrErrPhoEcal << endl;
   if (h_phoEcorrErrRegr1->GetEntries() > 0) mean_phoEcorrErrRegr1 = mean_phoEcorrErrRegr1 / h_phoEcorrErrRegr1->GetEntries();
   cout << "TH1F *h_phoEcorrErrRegr1 = new TH1F(\"h_phoEcorrErrRegr1\",\"phoEcorrErrRegr1\",10," << min_phoEcorrErrRegr1 << "," << max_phoEcorrErrRegr1 << "); // mean = " << mean_phoEcorrErrRegr1 << endl;
   if (h_phoEcorrErrRegr2->GetEntries() > 0) mean_phoEcorrErrRegr2 = mean_phoEcorrErrRegr2 / h_phoEcorrErrRegr2->GetEntries();
   cout << "TH1F *h_phoEcorrErrRegr2 = new TH1F(\"h_phoEcorrErrRegr2\",\"phoEcorrErrRegr2\",10," << min_phoEcorrErrRegr2 << "," << max_phoEcorrErrRegr2 << "); // mean = " << mean_phoEcorrErrRegr2 << endl;
   if (h_phoSCE->GetEntries() > 0) mean_phoSCE = mean_phoSCE / h_phoSCE->GetEntries();
   cout << "TH1F *h_phoSCE = new TH1F(\"h_phoSCE\",\"phoSCE\",10," << min_phoSCE << "," << max_phoSCE << "); // mean = " << mean_phoSCE << endl;
   if (h_phoSCEt->GetEntries() > 0) mean_phoSCEt = mean_phoSCEt / h_phoSCEt->GetEntries();
   cout << "TH1F *h_phoSCEt = new TH1F(\"h_phoSCEt\",\"phoSCEt\",10," << min_phoSCEt << "," << max_phoSCEt << "); // mean = " << mean_phoSCEt << endl;
   if (h_phoSCRawE->GetEntries() > 0) mean_phoSCRawE = mean_phoSCRawE / h_phoSCRawE->GetEntries();
   cout << "TH1F *h_phoSCRawE = new TH1F(\"h_phoSCRawE\",\"phoSCRawE\",10," << min_phoSCRawE << "," << max_phoSCRawE << "); // mean = " << mean_phoSCRawE << endl;
   if (h_phoSCEta->GetEntries() > 0) mean_phoSCEta = mean_phoSCEta / h_phoSCEta->GetEntries();
   cout << "TH1F *h_phoSCEta = new TH1F(\"h_phoSCEta\",\"phoSCEta\",10," << min_phoSCEta << "," << max_phoSCEta << "); // mean = " << mean_phoSCEta << endl;
   if (h_phoSCPhi->GetEntries() > 0) mean_phoSCPhi = mean_phoSCPhi / h_phoSCPhi->GetEntries();
   cout << "TH1F *h_phoSCPhi = new TH1F(\"h_phoSCPhi\",\"phoSCPhi\",10," << min_phoSCPhi << "," << max_phoSCPhi << "); // mean = " << mean_phoSCPhi << endl;
   if (h_phoSCEtaWidth->GetEntries() > 0) mean_phoSCEtaWidth = mean_phoSCEtaWidth / h_phoSCEtaWidth->GetEntries();
   cout << "TH1F *h_phoSCEtaWidth = new TH1F(\"h_phoSCEtaWidth\",\"phoSCEtaWidth\",10," << min_phoSCEtaWidth << "," << max_phoSCEtaWidth << "); // mean = " << mean_phoSCEtaWidth << endl;
   if (h_phoSCPhiWidth->GetEntries() > 0) mean_phoSCPhiWidth = mean_phoSCPhiWidth / h_phoSCPhiWidth->GetEntries();
   cout << "TH1F *h_phoSCPhiWidth = new TH1F(\"h_phoSCPhiWidth\",\"phoSCPhiWidth\",10," << min_phoSCPhiWidth << "," << max_phoSCPhiWidth << "); // mean = " << mean_phoSCPhiWidth << endl;
   if (h_phoSCBrem->GetEntries() > 0) mean_phoSCBrem = mean_phoSCBrem / h_phoSCBrem->GetEntries();
   cout << "TH1F *h_phoSCBrem = new TH1F(\"h_phoSCBrem\",\"phoSCBrem\",10," << min_phoSCBrem << "," << max_phoSCBrem << "); // mean = " << mean_phoSCBrem << endl;
   if (h_phoSCnHits->GetEntries() > 0) mean_phoSCnHits = mean_phoSCnHits / h_phoSCnHits->GetEntries();
   cout << "TH1F *h_phoSCnHits = new TH1F(\"h_phoSCnHits\",\"phoSCnHits\",10," << min_phoSCnHits << "," << max_phoSCnHits << "); // mean = " << mean_phoSCnHits << endl;
   if (h_phoSCflags->GetEntries() > 0) mean_phoSCflags = mean_phoSCflags / h_phoSCflags->GetEntries();
   cout << "TH1F *h_phoSCflags = new TH1F(\"h_phoSCflags\",\"phoSCflags\",10," << min_phoSCflags << "," << max_phoSCflags << "); // mean = " << mean_phoSCflags << endl;
   if (h_phoSCinClean->GetEntries() > 0) mean_phoSCinClean = mean_phoSCinClean / h_phoSCinClean->GetEntries();
   cout << "TH1F *h_phoSCinClean = new TH1F(\"h_phoSCinClean\",\"phoSCinClean\",10," << min_phoSCinClean << "," << max_phoSCinClean << "); // mean = " << mean_phoSCinClean << endl;
   if (h_phoSCinUnClean->GetEntries() > 0) mean_phoSCinUnClean = mean_phoSCinUnClean / h_phoSCinUnClean->GetEntries();
   cout << "TH1F *h_phoSCinUnClean = new TH1F(\"h_phoSCinUnClean\",\"phoSCinUnClean\",10," << min_phoSCinUnClean << "," << max_phoSCinUnClean << "); // mean = " << mean_phoSCinUnClean << endl;
   if (h_phoSCnBC->GetEntries() > 0) mean_phoSCnBC = mean_phoSCnBC / h_phoSCnBC->GetEntries();
   cout << "TH1F *h_phoSCnBC = new TH1F(\"h_phoSCnBC\",\"phoSCnBC\",10," << min_phoSCnBC << "," << max_phoSCnBC << "); // mean = " << mean_phoSCnBC << endl;
   if (h_phoESEn->GetEntries() > 0) mean_phoESEn = mean_phoESEn / h_phoESEn->GetEntries();
   cout << "TH1F *h_phoESEn = new TH1F(\"h_phoESEn\",\"phoESEn\",10," << min_phoESEn << "," << max_phoESEn << "); // mean = " << mean_phoESEn << endl;
   if (h_phoPSCE->GetEntries() > 0) mean_phoPSCE = mean_phoPSCE / h_phoPSCE->GetEntries();
   cout << "TH1F *h_phoPSCE = new TH1F(\"h_phoPSCE\",\"phoPSCE\",10," << min_phoPSCE << "," << max_phoPSCE << "); // mean = " << mean_phoPSCE << endl;
   if (h_phoPSCRawE->GetEntries() > 0) mean_phoPSCRawE = mean_phoPSCRawE / h_phoPSCRawE->GetEntries();
   cout << "TH1F *h_phoPSCRawE = new TH1F(\"h_phoPSCRawE\",\"phoPSCRawE\",10," << min_phoPSCRawE << "," << max_phoPSCRawE << "); // mean = " << mean_phoPSCRawE << endl;
   if (h_phoPSCEta->GetEntries() > 0) mean_phoPSCEta = mean_phoPSCEta / h_phoPSCEta->GetEntries();
   cout << "TH1F *h_phoPSCEta = new TH1F(\"h_phoPSCEta\",\"phoPSCEta\",10," << min_phoPSCEta << "," << max_phoPSCEta << "); // mean = " << mean_phoPSCEta << endl;
   if (h_phoPSCPhi->GetEntries() > 0) mean_phoPSCPhi = mean_phoPSCPhi / h_phoPSCPhi->GetEntries();
   cout << "TH1F *h_phoPSCPhi = new TH1F(\"h_phoPSCPhi\",\"phoPSCPhi\",10," << min_phoPSCPhi << "," << max_phoPSCPhi << "); // mean = " << mean_phoPSCPhi << endl;
   if (h_phoPSCEtaWidth->GetEntries() > 0) mean_phoPSCEtaWidth = mean_phoPSCEtaWidth / h_phoPSCEtaWidth->GetEntries();
   cout << "TH1F *h_phoPSCEtaWidth = new TH1F(\"h_phoPSCEtaWidth\",\"phoPSCEtaWidth\",10," << min_phoPSCEtaWidth << "," << max_phoPSCEtaWidth << "); // mean = " << mean_phoPSCEtaWidth << endl;
   if (h_phoPSCPhiWidth->GetEntries() > 0) mean_phoPSCPhiWidth = mean_phoPSCPhiWidth / h_phoPSCPhiWidth->GetEntries();
   cout << "TH1F *h_phoPSCPhiWidth = new TH1F(\"h_phoPSCPhiWidth\",\"phoPSCPhiWidth\",10," << min_phoPSCPhiWidth << "," << max_phoPSCPhiWidth << "); // mean = " << mean_phoPSCPhiWidth << endl;
   if (h_phoPSCBrem->GetEntries() > 0) mean_phoPSCBrem = mean_phoPSCBrem / h_phoPSCBrem->GetEntries();
   cout << "TH1F *h_phoPSCBrem = new TH1F(\"h_phoPSCBrem\",\"phoPSCBrem\",10," << min_phoPSCBrem << "," << max_phoPSCBrem << "); // mean = " << mean_phoPSCBrem << endl;
   if (h_phoPSCnHits->GetEntries() > 0) mean_phoPSCnHits = mean_phoPSCnHits / h_phoPSCnHits->GetEntries();
   cout << "TH1F *h_phoPSCnHits = new TH1F(\"h_phoPSCnHits\",\"phoPSCnHits\",10," << min_phoPSCnHits << "," << max_phoPSCnHits << "); // mean = " << mean_phoPSCnHits << endl;
   if (h_phoPSCflags->GetEntries() > 0) mean_phoPSCflags = mean_phoPSCflags / h_phoPSCflags->GetEntries();
   cout << "TH1F *h_phoPSCflags = new TH1F(\"h_phoPSCflags\",\"phoPSCflags\",10," << min_phoPSCflags << "," << max_phoPSCflags << "); // mean = " << mean_phoPSCflags << endl;
   if (h_phoPSCinClean->GetEntries() > 0) mean_phoPSCinClean = mean_phoPSCinClean / h_phoPSCinClean->GetEntries();
   cout << "TH1F *h_phoPSCinClean = new TH1F(\"h_phoPSCinClean\",\"phoPSCinClean\",10," << min_phoPSCinClean << "," << max_phoPSCinClean << "); // mean = " << mean_phoPSCinClean << endl;
   if (h_phoPSCinUnClean->GetEntries() > 0) mean_phoPSCinUnClean = mean_phoPSCinUnClean / h_phoPSCinUnClean->GetEntries();
   cout << "TH1F *h_phoPSCinUnClean = new TH1F(\"h_phoPSCinUnClean\",\"phoPSCinUnClean\",10," << min_phoPSCinUnClean << "," << max_phoPSCinUnClean << "); // mean = " << mean_phoPSCinUnClean << endl;
   if (h_phoPSCnBC->GetEntries() > 0) mean_phoPSCnBC = mean_phoPSCnBC / h_phoPSCnBC->GetEntries();
   cout << "TH1F *h_phoPSCnBC = new TH1F(\"h_phoPSCnBC\",\"phoPSCnBC\",10," << min_phoPSCnBC << "," << max_phoPSCnBC << "); // mean = " << mean_phoPSCnBC << endl;
   if (h_phoPESEn->GetEntries() > 0) mean_phoPESEn = mean_phoPESEn / h_phoPESEn->GetEntries();
   cout << "TH1F *h_phoPESEn = new TH1F(\"h_phoPESEn\",\"phoPESEn\",10," << min_phoPESEn << "," << max_phoPESEn << "); // mean = " << mean_phoPESEn << endl;
   if (h_phoIsPFPhoton->GetEntries() > 0) mean_phoIsPFPhoton = mean_phoIsPFPhoton / h_phoIsPFPhoton->GetEntries();
   cout << "TH1F *h_phoIsPFPhoton = new TH1F(\"h_phoIsPFPhoton\",\"phoIsPFPhoton\",10," << min_phoIsPFPhoton << "," << max_phoIsPFPhoton << "); // mean = " << mean_phoIsPFPhoton << endl;
   if (h_phoIsStandardPhoton->GetEntries() > 0) mean_phoIsStandardPhoton = mean_phoIsStandardPhoton / h_phoIsStandardPhoton->GetEntries();
   cout << "TH1F *h_phoIsStandardPhoton = new TH1F(\"h_phoIsStandardPhoton\",\"phoIsStandardPhoton\",10," << min_phoIsStandardPhoton << "," << max_phoIsStandardPhoton << "); // mean = " << mean_phoIsStandardPhoton << endl;
   if (h_phoHasPixelSeed->GetEntries() > 0) mean_phoHasPixelSeed = mean_phoHasPixelSeed / h_phoHasPixelSeed->GetEntries();
   cout << "TH1F *h_phoHasPixelSeed = new TH1F(\"h_phoHasPixelSeed\",\"phoHasPixelSeed\",10," << min_phoHasPixelSeed << "," << max_phoHasPixelSeed << "); // mean = " << mean_phoHasPixelSeed << endl;
   if (h_phoHasConversionTracks->GetEntries() > 0) mean_phoHasConversionTracks = mean_phoHasConversionTracks / h_phoHasConversionTracks->GetEntries();
   cout << "TH1F *h_phoHasConversionTracks = new TH1F(\"h_phoHasConversionTracks\",\"phoHasConversionTracks\",10," << min_phoHasConversionTracks << "," << max_phoHasConversionTracks << "); // mean = " << mean_phoHasConversionTracks << endl;
   if (h_phoHadTowerOverEm->GetEntries() > 0) mean_phoHadTowerOverEm = mean_phoHadTowerOverEm / h_phoHadTowerOverEm->GetEntries();
   cout << "TH1F *h_phoHadTowerOverEm = new TH1F(\"h_phoHadTowerOverEm\",\"phoHadTowerOverEm\",10," << min_phoHadTowerOverEm << "," << max_phoHadTowerOverEm << "); // mean = " << mean_phoHadTowerOverEm << endl;
   if (h_phoHoverE->GetEntries() > 0) mean_phoHoverE = mean_phoHoverE / h_phoHoverE->GetEntries();
   cout << "TH1F *h_phoHoverE = new TH1F(\"h_phoHoverE\",\"phoHoverE\",10," << min_phoHoverE << "," << max_phoHoverE << "); // mean = " << mean_phoHoverE << endl;
   if (h_phoHoverEValid->GetEntries() > 0) mean_phoHoverEValid = mean_phoHoverEValid / h_phoHoverEValid->GetEntries();
   cout << "TH1F *h_phoHoverEValid = new TH1F(\"h_phoHoverEValid\",\"phoHoverEValid\",10," << min_phoHoverEValid << "," << max_phoHoverEValid << "); // mean = " << mean_phoHoverEValid << endl;
   if (h_phoSigmaIEtaIEta->GetEntries() > 0) mean_phoSigmaIEtaIEta = mean_phoSigmaIEtaIEta / h_phoSigmaIEtaIEta->GetEntries();
   cout << "TH1F *h_phoSigmaIEtaIEta = new TH1F(\"h_phoSigmaIEtaIEta\",\"phoSigmaIEtaIEta\",10," << min_phoSigmaIEtaIEta << "," << max_phoSigmaIEtaIEta << "); // mean = " << mean_phoSigmaIEtaIEta << endl;
   if (h_phoR9->GetEntries() > 0) mean_phoR9 = mean_phoR9 / h_phoR9->GetEntries();
   cout << "TH1F *h_phoR9 = new TH1F(\"h_phoR9\",\"phoR9\",10," << min_phoR9 << "," << max_phoR9 << "); // mean = " << mean_phoR9 << endl;
   if (h_phoE1x5->GetEntries() > 0) mean_phoE1x5 = mean_phoE1x5 / h_phoE1x5->GetEntries();
   cout << "TH1F *h_phoE1x5 = new TH1F(\"h_phoE1x5\",\"phoE1x5\",10," << min_phoE1x5 << "," << max_phoE1x5 << "); // mean = " << mean_phoE1x5 << endl;
   if (h_phoE2x5->GetEntries() > 0) mean_phoE2x5 = mean_phoE2x5 / h_phoE2x5->GetEntries();
   cout << "TH1F *h_phoE2x5 = new TH1F(\"h_phoE2x5\",\"phoE2x5\",10," << min_phoE2x5 << "," << max_phoE2x5 << "); // mean = " << mean_phoE2x5 << endl;
   if (h_phoE3x3->GetEntries() > 0) mean_phoE3x3 = mean_phoE3x3 / h_phoE3x3->GetEntries();
   cout << "TH1F *h_phoE3x3 = new TH1F(\"h_phoE3x3\",\"phoE3x3\",10," << min_phoE3x3 << "," << max_phoE3x3 << "); // mean = " << mean_phoE3x3 << endl;
   if (h_phoE5x5->GetEntries() > 0) mean_phoE5x5 = mean_phoE5x5 / h_phoE5x5->GetEntries();
   cout << "TH1F *h_phoE5x5 = new TH1F(\"h_phoE5x5\",\"phoE5x5\",10," << min_phoE5x5 << "," << max_phoE5x5 << "); // mean = " << mean_phoE5x5 << endl;
   if (h_phoMaxEnergyXtal->GetEntries() > 0) mean_phoMaxEnergyXtal = mean_phoMaxEnergyXtal / h_phoMaxEnergyXtal->GetEntries();
   cout << "TH1F *h_phoMaxEnergyXtal = new TH1F(\"h_phoMaxEnergyXtal\",\"phoMaxEnergyXtal\",10," << min_phoMaxEnergyXtal << "," << max_phoMaxEnergyXtal << "); // mean = " << mean_phoMaxEnergyXtal << endl;
   if (h_phoSigmaEtaEta->GetEntries() > 0) mean_phoSigmaEtaEta = mean_phoSigmaEtaEta / h_phoSigmaEtaEta->GetEntries();
   cout << "TH1F *h_phoSigmaEtaEta = new TH1F(\"h_phoSigmaEtaEta\",\"phoSigmaEtaEta\",10," << min_phoSigmaEtaEta << "," << max_phoSigmaEtaEta << "); // mean = " << mean_phoSigmaEtaEta << endl;
   if (h_phoSigmaIEtaIEta_2012->GetEntries() > 0) mean_phoSigmaIEtaIEta_2012 = mean_phoSigmaIEtaIEta_2012 / h_phoSigmaIEtaIEta_2012->GetEntries();
   cout << "TH1F *h_phoSigmaIEtaIEta_2012 = new TH1F(\"h_phoSigmaIEtaIEta_2012\",\"phoSigmaIEtaIEta_2012\",10," << min_phoSigmaIEtaIEta_2012 << "," << max_phoSigmaIEtaIEta_2012 << "); // mean = " << mean_phoSigmaIEtaIEta_2012 << endl;
   if (h_phoR9_2012->GetEntries() > 0) mean_phoR9_2012 = mean_phoR9_2012 / h_phoR9_2012->GetEntries();
   cout << "TH1F *h_phoR9_2012 = new TH1F(\"h_phoR9_2012\",\"phoR9_2012\",10," << min_phoR9_2012 << "," << max_phoR9_2012 << "); // mean = " << mean_phoR9_2012 << endl;
   if (h_phoE1x5_2012->GetEntries() > 0) mean_phoE1x5_2012 = mean_phoE1x5_2012 / h_phoE1x5_2012->GetEntries();
   cout << "TH1F *h_phoE1x5_2012 = new TH1F(\"h_phoE1x5_2012\",\"phoE1x5_2012\",10," << min_phoE1x5_2012 << "," << max_phoE1x5_2012 << "); // mean = " << mean_phoE1x5_2012 << endl;
   if (h_phoE2x5_2012->GetEntries() > 0) mean_phoE2x5_2012 = mean_phoE2x5_2012 / h_phoE2x5_2012->GetEntries();
   cout << "TH1F *h_phoE2x5_2012 = new TH1F(\"h_phoE2x5_2012\",\"phoE2x5_2012\",10," << min_phoE2x5_2012 << "," << max_phoE2x5_2012 << "); // mean = " << mean_phoE2x5_2012 << endl;
   if (h_phoE3x3_2012->GetEntries() > 0) mean_phoE3x3_2012 = mean_phoE3x3_2012 / h_phoE3x3_2012->GetEntries();
   cout << "TH1F *h_phoE3x3_2012 = new TH1F(\"h_phoE3x3_2012\",\"phoE3x3_2012\",10," << min_phoE3x3_2012 << "," << max_phoE3x3_2012 << "); // mean = " << mean_phoE3x3_2012 << endl;
   if (h_phoE5x5_2012->GetEntries() > 0) mean_phoE5x5_2012 = mean_phoE5x5_2012 / h_phoE5x5_2012->GetEntries();
   cout << "TH1F *h_phoE5x5_2012 = new TH1F(\"h_phoE5x5_2012\",\"phoE5x5_2012\",10," << min_phoE5x5_2012 << "," << max_phoE5x5_2012 << "); // mean = " << mean_phoE5x5_2012 << endl;
   if (h_phoMaxEnergyXtal_2012->GetEntries() > 0) mean_phoMaxEnergyXtal_2012 = mean_phoMaxEnergyXtal_2012 / h_phoMaxEnergyXtal_2012->GetEntries();
   cout << "TH1F *h_phoMaxEnergyXtal_2012 = new TH1F(\"h_phoMaxEnergyXtal_2012\",\"phoMaxEnergyXtal_2012\",10," << min_phoMaxEnergyXtal_2012 << "," << max_phoMaxEnergyXtal_2012 << "); // mean = " << mean_phoMaxEnergyXtal_2012 << endl;
   if (h_phoSigmaEtaEta_2012->GetEntries() > 0) mean_phoSigmaEtaEta_2012 = mean_phoSigmaEtaEta_2012 / h_phoSigmaEtaEta_2012->GetEntries();
   cout << "TH1F *h_phoSigmaEtaEta_2012 = new TH1F(\"h_phoSigmaEtaEta_2012\",\"phoSigmaEtaEta_2012\",10," << min_phoSigmaEtaEta_2012 << "," << max_phoSigmaEtaEta_2012 << "); // mean = " << mean_phoSigmaEtaEta_2012 << endl;
   if (h_phoHadTowerOverEm1->GetEntries() > 0) mean_phoHadTowerOverEm1 = mean_phoHadTowerOverEm1 / h_phoHadTowerOverEm1->GetEntries();
   cout << "TH1F *h_phoHadTowerOverEm1 = new TH1F(\"h_phoHadTowerOverEm1\",\"phoHadTowerOverEm1\",10," << min_phoHadTowerOverEm1 << "," << max_phoHadTowerOverEm1 << "); // mean = " << mean_phoHadTowerOverEm1 << endl;
   if (h_phoHadTowerOverEm2->GetEntries() > 0) mean_phoHadTowerOverEm2 = mean_phoHadTowerOverEm2 / h_phoHadTowerOverEm2->GetEntries();
   cout << "TH1F *h_phoHadTowerOverEm2 = new TH1F(\"h_phoHadTowerOverEm2\",\"phoHadTowerOverEm2\",10," << min_phoHadTowerOverEm2 << "," << max_phoHadTowerOverEm2 << "); // mean = " << mean_phoHadTowerOverEm2 << endl;
   if (h_phoHoverE1->GetEntries() > 0) mean_phoHoverE1 = mean_phoHoverE1 / h_phoHoverE1->GetEntries();
   cout << "TH1F *h_phoHoverE1 = new TH1F(\"h_phoHoverE1\",\"phoHoverE1\",10," << min_phoHoverE1 << "," << max_phoHoverE1 << "); // mean = " << mean_phoHoverE1 << endl;
   if (h_phoHoverE2->GetEntries() > 0) mean_phoHoverE2 = mean_phoHoverE2 / h_phoHoverE2->GetEntries();
   cout << "TH1F *h_phoHoverE2 = new TH1F(\"h_phoHoverE2\",\"phoHoverE2\",10," << min_phoHoverE2 << "," << max_phoHoverE2 << "); // mean = " << mean_phoHoverE2 << endl;
   if (h_phoSigmaIEtaIPhi->GetEntries() > 0) mean_phoSigmaIEtaIPhi = mean_phoSigmaIEtaIPhi / h_phoSigmaIEtaIPhi->GetEntries();
   cout << "TH1F *h_phoSigmaIEtaIPhi = new TH1F(\"h_phoSigmaIEtaIPhi\",\"phoSigmaIEtaIPhi\",10," << min_phoSigmaIEtaIPhi << "," << max_phoSigmaIEtaIPhi << "); // mean = " << mean_phoSigmaIEtaIPhi << endl;
   if (h_phoSigmaIPhiIPhi->GetEntries() > 0) mean_phoSigmaIPhiIPhi = mean_phoSigmaIPhiIPhi / h_phoSigmaIPhiIPhi->GetEntries();
   cout << "TH1F *h_phoSigmaIPhiIPhi = new TH1F(\"h_phoSigmaIPhiIPhi\",\"phoSigmaIPhiIPhi\",10," << min_phoSigmaIPhiIPhi << "," << max_phoSigmaIPhiIPhi << "); // mean = " << mean_phoSigmaIPhiIPhi << endl;
   if (h_phoR1x5->GetEntries() > 0) mean_phoR1x5 = mean_phoR1x5 / h_phoR1x5->GetEntries();
   cout << "TH1F *h_phoR1x5 = new TH1F(\"h_phoR1x5\",\"phoR1x5\",10," << min_phoR1x5 << "," << max_phoR1x5 << "); // mean = " << mean_phoR1x5 << endl;
   if (h_phoR2x5->GetEntries() > 0) mean_phoR2x5 = mean_phoR2x5 / h_phoR2x5->GetEntries();
   cout << "TH1F *h_phoR2x5 = new TH1F(\"h_phoR2x5\",\"phoR2x5\",10," << min_phoR2x5 << "," << max_phoR2x5 << "); // mean = " << mean_phoR2x5 << endl;
   if (h_phoE2nd->GetEntries() > 0) mean_phoE2nd = mean_phoE2nd / h_phoE2nd->GetEntries();
   cout << "TH1F *h_phoE2nd = new TH1F(\"h_phoE2nd\",\"phoE2nd\",10," << min_phoE2nd << "," << max_phoE2nd << "); // mean = " << mean_phoE2nd << endl;
   if (h_phoETop->GetEntries() > 0) mean_phoETop = mean_phoETop / h_phoETop->GetEntries();
   cout << "TH1F *h_phoETop = new TH1F(\"h_phoETop\",\"phoETop\",10," << min_phoETop << "," << max_phoETop << "); // mean = " << mean_phoETop << endl;
   if (h_phoEBottom->GetEntries() > 0) mean_phoEBottom = mean_phoEBottom / h_phoEBottom->GetEntries();
   cout << "TH1F *h_phoEBottom = new TH1F(\"h_phoEBottom\",\"phoEBottom\",10," << min_phoEBottom << "," << max_phoEBottom << "); // mean = " << mean_phoEBottom << endl;
   if (h_phoELeft->GetEntries() > 0) mean_phoELeft = mean_phoELeft / h_phoELeft->GetEntries();
   cout << "TH1F *h_phoELeft = new TH1F(\"h_phoELeft\",\"phoELeft\",10," << min_phoELeft << "," << max_phoELeft << "); // mean = " << mean_phoELeft << endl;
   if (h_phoERight->GetEntries() > 0) mean_phoERight = mean_phoERight / h_phoERight->GetEntries();
   cout << "TH1F *h_phoERight = new TH1F(\"h_phoERight\",\"phoERight\",10," << min_phoERight << "," << max_phoERight << "); // mean = " << mean_phoERight << endl;
   if (h_phoE1x3->GetEntries() > 0) mean_phoE1x3 = mean_phoE1x3 / h_phoE1x3->GetEntries();
   cout << "TH1F *h_phoE1x3 = new TH1F(\"h_phoE1x3\",\"phoE1x3\",10," << min_phoE1x3 << "," << max_phoE1x3 << "); // mean = " << mean_phoE1x3 << endl;
   if (h_phoE2x2->GetEntries() > 0) mean_phoE2x2 = mean_phoE2x2 / h_phoE2x2->GetEntries();
   cout << "TH1F *h_phoE2x2 = new TH1F(\"h_phoE2x2\",\"phoE2x2\",10," << min_phoE2x2 << "," << max_phoE2x2 << "); // mean = " << mean_phoE2x2 << endl;
   if (h_phoE2x5Max->GetEntries() > 0) mean_phoE2x5Max = mean_phoE2x5Max / h_phoE2x5Max->GetEntries();
   cout << "TH1F *h_phoE2x5Max = new TH1F(\"h_phoE2x5Max\",\"phoE2x5Max\",10," << min_phoE2x5Max << "," << max_phoE2x5Max << "); // mean = " << mean_phoE2x5Max << endl;
   if (h_phoE2x5Top->GetEntries() > 0) mean_phoE2x5Top = mean_phoE2x5Top / h_phoE2x5Top->GetEntries();
   cout << "TH1F *h_phoE2x5Top = new TH1F(\"h_phoE2x5Top\",\"phoE2x5Top\",10," << min_phoE2x5Top << "," << max_phoE2x5Top << "); // mean = " << mean_phoE2x5Top << endl;
   if (h_phoE2x5Bottom->GetEntries() > 0) mean_phoE2x5Bottom = mean_phoE2x5Bottom / h_phoE2x5Bottom->GetEntries();
   cout << "TH1F *h_phoE2x5Bottom = new TH1F(\"h_phoE2x5Bottom\",\"phoE2x5Bottom\",10," << min_phoE2x5Bottom << "," << max_phoE2x5Bottom << "); // mean = " << mean_phoE2x5Bottom << endl;
   if (h_phoE2x5Left->GetEntries() > 0) mean_phoE2x5Left = mean_phoE2x5Left / h_phoE2x5Left->GetEntries();
   cout << "TH1F *h_phoE2x5Left = new TH1F(\"h_phoE2x5Left\",\"phoE2x5Left\",10," << min_phoE2x5Left << "," << max_phoE2x5Left << "); // mean = " << mean_phoE2x5Left << endl;
   if (h_phoE2x5Right->GetEntries() > 0) mean_phoE2x5Right = mean_phoE2x5Right / h_phoE2x5Right->GetEntries();
   cout << "TH1F *h_phoE2x5Right = new TH1F(\"h_phoE2x5Right\",\"phoE2x5Right\",10," << min_phoE2x5Right << "," << max_phoE2x5Right << "); // mean = " << mean_phoE2x5Right << endl;
   if (h_phoSigmaIEtaIPhi_2012->GetEntries() > 0) mean_phoSigmaIEtaIPhi_2012 = mean_phoSigmaIEtaIPhi_2012 / h_phoSigmaIEtaIPhi_2012->GetEntries();
   cout << "TH1F *h_phoSigmaIEtaIPhi_2012 = new TH1F(\"h_phoSigmaIEtaIPhi_2012\",\"phoSigmaIEtaIPhi_2012\",10," << min_phoSigmaIEtaIPhi_2012 << "," << max_phoSigmaIEtaIPhi_2012 << "); // mean = " << mean_phoSigmaIEtaIPhi_2012 << endl;
   if (h_phoSigmaIPhiIPhi_2012->GetEntries() > 0) mean_phoSigmaIPhiIPhi_2012 = mean_phoSigmaIPhiIPhi_2012 / h_phoSigmaIPhiIPhi_2012->GetEntries();
   cout << "TH1F *h_phoSigmaIPhiIPhi_2012 = new TH1F(\"h_phoSigmaIPhiIPhi_2012\",\"phoSigmaIPhiIPhi_2012\",10," << min_phoSigmaIPhiIPhi_2012 << "," << max_phoSigmaIPhiIPhi_2012 << "); // mean = " << mean_phoSigmaIPhiIPhi_2012 << endl;
   if (h_phoR1x5_2012->GetEntries() > 0) mean_phoR1x5_2012 = mean_phoR1x5_2012 / h_phoR1x5_2012->GetEntries();
   cout << "TH1F *h_phoR1x5_2012 = new TH1F(\"h_phoR1x5_2012\",\"phoR1x5_2012\",10," << min_phoR1x5_2012 << "," << max_phoR1x5_2012 << "); // mean = " << mean_phoR1x5_2012 << endl;
   if (h_phoR2x5_2012->GetEntries() > 0) mean_phoR2x5_2012 = mean_phoR2x5_2012 / h_phoR2x5_2012->GetEntries();
   cout << "TH1F *h_phoR2x5_2012 = new TH1F(\"h_phoR2x5_2012\",\"phoR2x5_2012\",10," << min_phoR2x5_2012 << "," << max_phoR2x5_2012 << "); // mean = " << mean_phoR2x5_2012 << endl;
   if (h_phoE2nd_2012->GetEntries() > 0) mean_phoE2nd_2012 = mean_phoE2nd_2012 / h_phoE2nd_2012->GetEntries();
   cout << "TH1F *h_phoE2nd_2012 = new TH1F(\"h_phoE2nd_2012\",\"phoE2nd_2012\",10," << min_phoE2nd_2012 << "," << max_phoE2nd_2012 << "); // mean = " << mean_phoE2nd_2012 << endl;
   if (h_phoETop_2012->GetEntries() > 0) mean_phoETop_2012 = mean_phoETop_2012 / h_phoETop_2012->GetEntries();
   cout << "TH1F *h_phoETop_2012 = new TH1F(\"h_phoETop_2012\",\"phoETop_2012\",10," << min_phoETop_2012 << "," << max_phoETop_2012 << "); // mean = " << mean_phoETop_2012 << endl;
   if (h_phoEBottom_2012->GetEntries() > 0) mean_phoEBottom_2012 = mean_phoEBottom_2012 / h_phoEBottom_2012->GetEntries();
   cout << "TH1F *h_phoEBottom_2012 = new TH1F(\"h_phoEBottom_2012\",\"phoEBottom_2012\",10," << min_phoEBottom_2012 << "," << max_phoEBottom_2012 << "); // mean = " << mean_phoEBottom_2012 << endl;
   if (h_phoELeft_2012->GetEntries() > 0) mean_phoELeft_2012 = mean_phoELeft_2012 / h_phoELeft_2012->GetEntries();
   cout << "TH1F *h_phoELeft_2012 = new TH1F(\"h_phoELeft_2012\",\"phoELeft_2012\",10," << min_phoELeft_2012 << "," << max_phoELeft_2012 << "); // mean = " << mean_phoELeft_2012 << endl;
   if (h_phoERight_2012->GetEntries() > 0) mean_phoERight_2012 = mean_phoERight_2012 / h_phoERight_2012->GetEntries();
   cout << "TH1F *h_phoERight_2012 = new TH1F(\"h_phoERight_2012\",\"phoERight_2012\",10," << min_phoERight_2012 << "," << max_phoERight_2012 << "); // mean = " << mean_phoERight_2012 << endl;
   if (h_phoE1x3_2012->GetEntries() > 0) mean_phoE1x3_2012 = mean_phoE1x3_2012 / h_phoE1x3_2012->GetEntries();
   cout << "TH1F *h_phoE1x3_2012 = new TH1F(\"h_phoE1x3_2012\",\"phoE1x3_2012\",10," << min_phoE1x3_2012 << "," << max_phoE1x3_2012 << "); // mean = " << mean_phoE1x3_2012 << endl;
   if (h_phoE2x2_2012->GetEntries() > 0) mean_phoE2x2_2012 = mean_phoE2x2_2012 / h_phoE2x2_2012->GetEntries();
   cout << "TH1F *h_phoE2x2_2012 = new TH1F(\"h_phoE2x2_2012\",\"phoE2x2_2012\",10," << min_phoE2x2_2012 << "," << max_phoE2x2_2012 << "); // mean = " << mean_phoE2x2_2012 << endl;
   if (h_phoE2x5Max_2012->GetEntries() > 0) mean_phoE2x5Max_2012 = mean_phoE2x5Max_2012 / h_phoE2x5Max_2012->GetEntries();
   cout << "TH1F *h_phoE2x5Max_2012 = new TH1F(\"h_phoE2x5Max_2012\",\"phoE2x5Max_2012\",10," << min_phoE2x5Max_2012 << "," << max_phoE2x5Max_2012 << "); // mean = " << mean_phoE2x5Max_2012 << endl;
   if (h_phoE2x5Top_2012->GetEntries() > 0) mean_phoE2x5Top_2012 = mean_phoE2x5Top_2012 / h_phoE2x5Top_2012->GetEntries();
   cout << "TH1F *h_phoE2x5Top_2012 = new TH1F(\"h_phoE2x5Top_2012\",\"phoE2x5Top_2012\",10," << min_phoE2x5Top_2012 << "," << max_phoE2x5Top_2012 << "); // mean = " << mean_phoE2x5Top_2012 << endl;
   if (h_phoE2x5Bottom_2012->GetEntries() > 0) mean_phoE2x5Bottom_2012 = mean_phoE2x5Bottom_2012 / h_phoE2x5Bottom_2012->GetEntries();
   cout << "TH1F *h_phoE2x5Bottom_2012 = new TH1F(\"h_phoE2x5Bottom_2012\",\"phoE2x5Bottom_2012\",10," << min_phoE2x5Bottom_2012 << "," << max_phoE2x5Bottom_2012 << "); // mean = " << mean_phoE2x5Bottom_2012 << endl;
   if (h_phoE2x5Left_2012->GetEntries() > 0) mean_phoE2x5Left_2012 = mean_phoE2x5Left_2012 / h_phoE2x5Left_2012->GetEntries();
   cout << "TH1F *h_phoE2x5Left_2012 = new TH1F(\"h_phoE2x5Left_2012\",\"phoE2x5Left_2012\",10," << min_phoE2x5Left_2012 << "," << max_phoE2x5Left_2012 << "); // mean = " << mean_phoE2x5Left_2012 << endl;
   if (h_phoE2x5Right_2012->GetEntries() > 0) mean_phoE2x5Right_2012 = mean_phoE2x5Right_2012 / h_phoE2x5Right_2012->GetEntries();
   cout << "TH1F *h_phoE2x5Right_2012 = new TH1F(\"h_phoE2x5Right_2012\",\"phoE2x5Right_2012\",10," << min_phoE2x5Right_2012 << "," << max_phoE2x5Right_2012 << "); // mean = " << mean_phoE2x5Right_2012 << endl;
   if (h_phoBC1E->GetEntries() > 0) mean_phoBC1E = mean_phoBC1E / h_phoBC1E->GetEntries();
   cout << "TH1F *h_phoBC1E = new TH1F(\"h_phoBC1E\",\"phoBC1E\",10," << min_phoBC1E << "," << max_phoBC1E << "); // mean = " << mean_phoBC1E << endl;
   if (h_phoBC1Ecorr->GetEntries() > 0) mean_phoBC1Ecorr = mean_phoBC1Ecorr / h_phoBC1Ecorr->GetEntries();
   cout << "TH1F *h_phoBC1Ecorr = new TH1F(\"h_phoBC1Ecorr\",\"phoBC1Ecorr\",10," << min_phoBC1Ecorr << "," << max_phoBC1Ecorr << "); // mean = " << mean_phoBC1Ecorr << endl;
   if (h_phoBC1Eta->GetEntries() > 0) mean_phoBC1Eta = mean_phoBC1Eta / h_phoBC1Eta->GetEntries();
   cout << "TH1F *h_phoBC1Eta = new TH1F(\"h_phoBC1Eta\",\"phoBC1Eta\",10," << min_phoBC1Eta << "," << max_phoBC1Eta << "); // mean = " << mean_phoBC1Eta << endl;
   if (h_phoBC1Phi->GetEntries() > 0) mean_phoBC1Phi = mean_phoBC1Phi / h_phoBC1Phi->GetEntries();
   cout << "TH1F *h_phoBC1Phi = new TH1F(\"h_phoBC1Phi\",\"phoBC1Phi\",10," << min_phoBC1Phi << "," << max_phoBC1Phi << "); // mean = " << mean_phoBC1Phi << endl;
   if (h_phoBC1size->GetEntries() > 0) mean_phoBC1size = mean_phoBC1size / h_phoBC1size->GetEntries();
   cout << "TH1F *h_phoBC1size = new TH1F(\"h_phoBC1size\",\"phoBC1size\",10," << min_phoBC1size << "," << max_phoBC1size << "); // mean = " << mean_phoBC1size << endl;
   if (h_phoBC1flags->GetEntries() > 0) mean_phoBC1flags = mean_phoBC1flags / h_phoBC1flags->GetEntries();
   cout << "TH1F *h_phoBC1flags = new TH1F(\"h_phoBC1flags\",\"phoBC1flags\",10," << min_phoBC1flags << "," << max_phoBC1flags << "); // mean = " << mean_phoBC1flags << endl;
   if (h_phoBC1inClean->GetEntries() > 0) mean_phoBC1inClean = mean_phoBC1inClean / h_phoBC1inClean->GetEntries();
   cout << "TH1F *h_phoBC1inClean = new TH1F(\"h_phoBC1inClean\",\"phoBC1inClean\",10," << min_phoBC1inClean << "," << max_phoBC1inClean << "); // mean = " << mean_phoBC1inClean << endl;
   if (h_phoBC1inUnClean->GetEntries() > 0) mean_phoBC1inUnClean = mean_phoBC1inUnClean / h_phoBC1inUnClean->GetEntries();
   cout << "TH1F *h_phoBC1inUnClean = new TH1F(\"h_phoBC1inUnClean\",\"phoBC1inUnClean\",10," << min_phoBC1inUnClean << "," << max_phoBC1inUnClean << "); // mean = " << mean_phoBC1inUnClean << endl;
   if (h_phoBC1rawID->GetEntries() > 0) mean_phoBC1rawID = mean_phoBC1rawID / h_phoBC1rawID->GetEntries();
   cout << "TH1F *h_phoBC1rawID = new TH1F(\"h_phoBC1rawID\",\"phoBC1rawID\",10," << min_phoBC1rawID << "," << max_phoBC1rawID << "); // mean = " << mean_phoBC1rawID << endl;
   // if (h_pho_ecalClusterIsoR2->GetEntries() > 0) mean_pho_ecalClusterIsoR2 = mean_pho_ecalClusterIsoR2 / h_pho_ecalClusterIsoR2->GetEntries();
   // cout << "TH1F *h_pho_ecalClusterIsoR2 = new TH1F(\"h_pho_ecalClusterIsoR2\",\"pho_ecalClusterIsoR2\",10," << min_pho_ecalClusterIsoR2 << "," << max_pho_ecalClusterIsoR2 << "); // mean = " << mean_pho_ecalClusterIsoR2 << endl;
   // if (h_pho_ecalClusterIsoR3->GetEntries() > 0) mean_pho_ecalClusterIsoR3 = mean_pho_ecalClusterIsoR3 / h_pho_ecalClusterIsoR3->GetEntries();
   // cout << "TH1F *h_pho_ecalClusterIsoR3 = new TH1F(\"h_pho_ecalClusterIsoR3\",\"pho_ecalClusterIsoR3\",10," << min_pho_ecalClusterIsoR3 << "," << max_pho_ecalClusterIsoR3 << "); // mean = " << mean_pho_ecalClusterIsoR3 << endl;
   // if (h_pho_ecalClusterIsoR4->GetEntries() > 0) mean_pho_ecalClusterIsoR4 = mean_pho_ecalClusterIsoR4 / h_pho_ecalClusterIsoR4->GetEntries();
   // cout << "TH1F *h_pho_ecalClusterIsoR4 = new TH1F(\"h_pho_ecalClusterIsoR4\",\"pho_ecalClusterIsoR4\",10," << min_pho_ecalClusterIsoR4 << "," << max_pho_ecalClusterIsoR4 << "); // mean = " << mean_pho_ecalClusterIsoR4 << endl;
   // if (h_pho_ecalClusterIsoR5->GetEntries() > 0) mean_pho_ecalClusterIsoR5 = mean_pho_ecalClusterIsoR5 / h_pho_ecalClusterIsoR5->GetEntries();
   // cout << "TH1F *h_pho_ecalClusterIsoR5 = new TH1F(\"h_pho_ecalClusterIsoR5\",\"pho_ecalClusterIsoR5\",10," << min_pho_ecalClusterIsoR5 << "," << max_pho_ecalClusterIsoR5 << "); // mean = " << mean_pho_ecalClusterIsoR5 << endl;
   // if (h_pho_hcalRechitIsoR1->GetEntries() > 0) mean_pho_hcalRechitIsoR1 = mean_pho_hcalRechitIsoR1 / h_pho_hcalRechitIsoR1->GetEntries();
   // cout << "TH1F *h_pho_hcalRechitIsoR1 = new TH1F(\"h_pho_hcalRechitIsoR1\",\"pho_hcalRechitIsoR1\",10," << min_pho_hcalRechitIsoR1 << "," << max_pho_hcalRechitIsoR1 << "); // mean = " << mean_pho_hcalRechitIsoR1 << endl;
   // if (h_pho_hcalRechitIsoR2->GetEntries() > 0) mean_pho_hcalRechitIsoR2 = mean_pho_hcalRechitIsoR2 / h_pho_hcalRechitIsoR2->GetEntries();
   // cout << "TH1F *h_pho_hcalRechitIsoR2 = new TH1F(\"h_pho_hcalRechitIsoR2\",\"pho_hcalRechitIsoR2\",10," << min_pho_hcalRechitIsoR2 << "," << max_pho_hcalRechitIsoR2 << "); // mean = " << mean_pho_hcalRechitIsoR2 << endl;
   // if (h_pho_hcalRechitIsoR3->GetEntries() > 0) mean_pho_hcalRechitIsoR3 = mean_pho_hcalRechitIsoR3 / h_pho_hcalRechitIsoR3->GetEntries();
   // cout << "TH1F *h_pho_hcalRechitIsoR3 = new TH1F(\"h_pho_hcalRechitIsoR3\",\"pho_hcalRechitIsoR3\",10," << min_pho_hcalRechitIsoR3 << "," << max_pho_hcalRechitIsoR3 << "); // mean = " << mean_pho_hcalRechitIsoR3 << endl;
   // if (h_pho_hcalRechitIsoR4->GetEntries() > 0) mean_pho_hcalRechitIsoR4 = mean_pho_hcalRechitIsoR4 / h_pho_hcalRechitIsoR4->GetEntries();
   // cout << "TH1F *h_pho_hcalRechitIsoR4 = new TH1F(\"h_pho_hcalRechitIsoR4\",\"pho_hcalRechitIsoR4\",10," << min_pho_hcalRechitIsoR4 << "," << max_pho_hcalRechitIsoR4 << "); // mean = " << mean_pho_hcalRechitIsoR4 << endl;
   // if (h_pho_hcalRechitIsoR5->GetEntries() > 0) mean_pho_hcalRechitIsoR5 = mean_pho_hcalRechitIsoR5 / h_pho_hcalRechitIsoR5->GetEntries();
   // cout << "TH1F *h_pho_hcalRechitIsoR5 = new TH1F(\"h_pho_hcalRechitIsoR5\",\"pho_hcalRechitIsoR5\",10," << min_pho_hcalRechitIsoR5 << "," << max_pho_hcalRechitIsoR5 << "); // mean = " << mean_pho_hcalRechitIsoR5 << endl;
   // if (h_pho_trackIsoR1PtCut20->GetEntries() > 0) mean_pho_trackIsoR1PtCut20 = mean_pho_trackIsoR1PtCut20 / h_pho_trackIsoR1PtCut20->GetEntries();
   // cout << "TH1F *h_pho_trackIsoR1PtCut20 = new TH1F(\"h_pho_trackIsoR1PtCut20\",\"pho_trackIsoR1PtCut20\",10," << min_pho_trackIsoR1PtCut20 << "," << max_pho_trackIsoR1PtCut20 << "); // mean = " << mean_pho_trackIsoR1PtCut20 << endl;
   // if (h_pho_trackIsoR2PtCut20->GetEntries() > 0) mean_pho_trackIsoR2PtCut20 = mean_pho_trackIsoR2PtCut20 / h_pho_trackIsoR2PtCut20->GetEntries();
   // cout << "TH1F *h_pho_trackIsoR2PtCut20 = new TH1F(\"h_pho_trackIsoR2PtCut20\",\"pho_trackIsoR2PtCut20\",10," << min_pho_trackIsoR2PtCut20 << "," << max_pho_trackIsoR2PtCut20 << "); // mean = " << mean_pho_trackIsoR2PtCut20 << endl;
   // if (h_pho_trackIsoR3PtCut20->GetEntries() > 0) mean_pho_trackIsoR3PtCut20 = mean_pho_trackIsoR3PtCut20 / h_pho_trackIsoR3PtCut20->GetEntries();
   // cout << "TH1F *h_pho_trackIsoR3PtCut20 = new TH1F(\"h_pho_trackIsoR3PtCut20\",\"pho_trackIsoR3PtCut20\",10," << min_pho_trackIsoR3PtCut20 << "," << max_pho_trackIsoR3PtCut20 << "); // mean = " << mean_pho_trackIsoR3PtCut20 << endl;
   // if (h_pho_trackIsoR4PtCut20->GetEntries() > 0) mean_pho_trackIsoR4PtCut20 = mean_pho_trackIsoR4PtCut20 / h_pho_trackIsoR4PtCut20->GetEntries();
   // cout << "TH1F *h_pho_trackIsoR4PtCut20 = new TH1F(\"h_pho_trackIsoR4PtCut20\",\"pho_trackIsoR4PtCut20\",10," << min_pho_trackIsoR4PtCut20 << "," << max_pho_trackIsoR4PtCut20 << "); // mean = " << mean_pho_trackIsoR4PtCut20 << endl;
   // if (h_pho_trackIsoR5PtCut20->GetEntries() > 0) mean_pho_trackIsoR5PtCut20 = mean_pho_trackIsoR5PtCut20 / h_pho_trackIsoR5PtCut20->GetEntries();
   // cout << "TH1F *h_pho_trackIsoR5PtCut20 = new TH1F(\"h_pho_trackIsoR5PtCut20\",\"pho_trackIsoR5PtCut20\",10," << min_pho_trackIsoR5PtCut20 << "," << max_pho_trackIsoR5PtCut20 << "); // mean = " << mean_pho_trackIsoR5PtCut20 << endl;
   // if (h_pho_swissCrx->GetEntries() > 0) mean_pho_swissCrx = mean_pho_swissCrx / h_pho_swissCrx->GetEntries();
   // cout << "TH1F *h_pho_swissCrx = new TH1F(\"h_pho_swissCrx\",\"pho_swissCrx\",10," << min_pho_swissCrx << "," << max_pho_swissCrx << "); // mean = " << mean_pho_swissCrx << endl;
   // if (h_pho_seedTime->GetEntries() > 0) mean_pho_seedTime = mean_pho_seedTime / h_pho_seedTime->GetEntries();
   // cout << "TH1F *h_pho_seedTime = new TH1F(\"h_pho_seedTime\",\"pho_seedTime\",10," << min_pho_seedTime << "," << max_pho_seedTime << "); // mean = " << mean_pho_seedTime << endl;
   if (h_nTower->GetEntries() > 0) mean_nTower = mean_nTower / h_nTower->GetEntries();
   cout << "TH1F *h_nTower = new TH1F(\"h_nTower\",\"nTower\",10," << min_nTower << "," << max_nTower << "); // mean = " << mean_nTower << endl;
   if (h_CaloTower_hadE->GetEntries() > 0) mean_CaloTower_hadE = mean_CaloTower_hadE / h_CaloTower_hadE->GetEntries();
   cout << "TH1F *h_CaloTower_hadE = new TH1F(\"h_CaloTower_hadE\",\"CaloTower_hadE\",10," << min_CaloTower_hadE << "," << max_CaloTower_hadE << "); // mean = " << mean_CaloTower_hadE << endl;
   if (h_CaloTower_emE->GetEntries() > 0) mean_CaloTower_emE = mean_CaloTower_emE / h_CaloTower_emE->GetEntries();
   cout << "TH1F *h_CaloTower_emE = new TH1F(\"h_CaloTower_emE\",\"CaloTower_emE\",10," << min_CaloTower_emE << "," << max_CaloTower_emE << "); // mean = " << mean_CaloTower_emE << endl;
   if (h_CaloTower_e->GetEntries() > 0) mean_CaloTower_e = mean_CaloTower_e / h_CaloTower_e->GetEntries();
   cout << "TH1F *h_CaloTower_e = new TH1F(\"h_CaloTower_e\",\"CaloTower_e\",10," << min_CaloTower_e << "," << max_CaloTower_e << "); // mean = " << mean_CaloTower_e << endl;
   if (h_CaloTower_et->GetEntries() > 0) mean_CaloTower_et = mean_CaloTower_et / h_CaloTower_et->GetEntries();
   cout << "TH1F *h_CaloTower_et = new TH1F(\"h_CaloTower_et\",\"CaloTower_et\",10," << min_CaloTower_et << "," << max_CaloTower_et << "); // mean = " << mean_CaloTower_et << endl;
   if (h_CaloTower_eta->GetEntries() > 0) mean_CaloTower_eta = mean_CaloTower_eta / h_CaloTower_eta->GetEntries();
   cout << "TH1F *h_CaloTower_eta = new TH1F(\"h_CaloTower_eta\",\"CaloTower_eta\",10," << min_CaloTower_eta << "," << max_CaloTower_eta << "); // mean = " << mean_CaloTower_eta << endl;
   if (h_CaloTower_phi->GetEntries() > 0) mean_CaloTower_phi = mean_CaloTower_phi / h_CaloTower_phi->GetEntries();
   cout << "TH1F *h_CaloTower_phi = new TH1F(\"h_CaloTower_phi\",\"CaloTower_phi\",10," << min_CaloTower_phi << "," << max_CaloTower_phi << "); // mean = " << mean_CaloTower_phi << endl;
   if (h_nTrackerHits->GetEntries() > 0) mean_nTrackerHits = mean_nTrackerHits / h_nTrackerHits->GetEntries();
   cout << "TH1F *h_nTrackerHits = new TH1F(\"h_nTrackerHits\",\"nTrackerHits\",10," << min_nTrackerHits << "," << max_nTrackerHits << "); // mean = " << mean_nTrackerHits << endl;
   if (h_nPixelClusters->GetEntries() > 0) mean_nPixelClusters = mean_nPixelClusters / h_nPixelClusters->GetEntries();
   cout << "TH1F *h_nPixelClusters = new TH1F(\"h_nPixelClusters\",\"nPixelClusters\",10," << min_nPixelClusters << "," << max_nPixelClusters << "); // mean = " << mean_nPixelClusters << endl;
   if (h_nPixelRecHits->GetEntries() > 0) mean_nPixelRecHits = mean_nPixelRecHits / h_nPixelRecHits->GetEntries();
   cout << "TH1F *h_nPixelRecHits = new TH1F(\"h_nPixelRecHits\",\"nPixelRecHits\",10," << min_nPixelRecHits << "," << max_nPixelRecHits << "); // mean = " << mean_nPixelRecHits << endl;

   fhist->Write();
   fhist->Close();
}

void DumpEvent::dump(Long64_t entry) {
   fChain->SetBranchStatus("*",1);  // enable all branches

   Long64_t ientry = LoadTree(entry);
   if (ientry < 0) return;
   fChain->GetEntry(entry);

   cout << "run: " << run << endl;
   cout << "event: " << event << endl;
   cout << "lumis: " << lumis << endl;
   cout << "rho: " << rho << endl;
   cout << "#####################" << endl;
   cout << "nSC: " << nSC << endl;
   cout << "E, RawE, Eta, Phi" << endl;
   for (int i=0; i<nSC; i++) {
      cout << scE->at(i) << ", ";
      cout << scRawE->at(i) << ", ";
      cout << scEta->at(i) << ", ";
      cout << scPhi->at(i) << endl;
   }
   // cout << "#####################" << endl;
   cout << "nEle: " << nEle << endl << endl;
   // cout << "Charge, ChargeConsistent, SCPixCharge, CtfCharge," << endl;
   // cout << "En, D0, Dz, IP3D, D0Err, DzErr, IP3DErr" << endl;
   // cout << "TrkPt, TrkEta, TrkPhi, TrkCharge, TrkPtErr, TrkChi2, TrkNdof, TrkNormalizedChi2, TrkValidHits, TrkLayers," << endl;
   // cout << "Pt, Eta, Phi, SCEn, ESEn, SCEta, SCPhi, SCRawEn, SCEtaWidth, SCPhiWidth," << endl;
   // cout << "HoverE, HoverEBc, EoverP, EoverPInv, EcalE, " << endl;
   // cout << "PAtVtx, PAtSC, PAtCluster, PAtSeed, Brem, EtaAtVtx, PhiAtVtx, EtaSeedAtVtx, " << endl;
   // cout << "SigmaIEtaIEta, SigmaIEtaIEta_2012, SigmaIPhiIPhi, ConvVeto, MissHits, ESEffAreaTimesRho, " << endl;
   // cout << "PFChIso, PFPhoIso, PFNeuIso, PFPUIso, PFRelIsoWithEA, PFReoIsoWithDBeta, EffAreaTimesRho, " << endl;
   cout << "nPho: " << nPho << endl;
   cout << "nMu: " << nMu << endl;
   cout << "nTrk: " << nTrk << endl;
   cout << "nTower: " << nTower << endl;
   cout << "nTrackerHits: " << nTrackerHits << endl;
   cout << "nPixelClusters: " << nPixelClusters << endl;
   cout << "nPixelRecHits: " << nPixelRecHits << endl;

}

void DumpEvent::Loop_evtlist()
{
   fChain->SetBranchStatus("*",0);  // disable all branches
   fChain->SetBranchStatus("run",1);  // activate branchname
   fChain->SetBranchStatus("lumis",1);  // activate branchname
   fChain->SetBranchStatus("event",1);  // activate branchname

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      cout << run << ":" << lumis << ":" << event << endl;
   } // event loop
}
