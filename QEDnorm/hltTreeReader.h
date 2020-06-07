//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 20 17:18:22 2017 by ROOT version 6.04/02
// from TTree HltTree/
// found on file: /eos/cms/store/group/phys_diffraction/diphoton/qed_ee/hiforest_noptcut_3-53_invmass_more_var3/0002/hiForest_qedee_4.root
//////////////////////////////////////////////////////////

#ifndef hltTreeReader_h
#define hltTreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class hltTreeReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           NL1IsolEm;
   Float_t         L1IsolEmEt[4];   //[NL1IsolEm]
   Float_t         L1IsolEmE[4];   //[NL1IsolEm]
   Float_t         L1IsolEmEta[4];   //[NL1IsolEm]
   Float_t         L1IsolEmPhi[4];   //[NL1IsolEm]
   Int_t           NL1NIsolEm;
   Float_t         L1NIsolEmEt[4];   //[NL1NIsolEm]
   Float_t         L1NIsolEmE[4];   //[NL1NIsolEm]
   Float_t         L1NIsolEmEta[4];   //[NL1NIsolEm]
   Float_t         L1NIsolEmPhi[4];   //[NL1NIsolEm]
   Int_t           NL1Mu;
   Float_t         L1MuPt[4];   //[NL1Mu]
   Float_t         L1MuE[4];   //[NL1Mu]
   Float_t         L1MuEta[4];   //[NL1Mu]
   Float_t         L1MuPhi[4];   //[NL1Mu]
   Int_t           L1MuIsol[4];   //[NL1Mu]
   Int_t           L1MuMip[4];   //[NL1Mu]
   Int_t           L1MuFor[4];   //[NL1Mu]
   Int_t           L1MuRPC[4];   //[NL1Mu]
   Int_t           L1MuQal[4];   //[NL1Mu]
   Int_t           L1MuChg[4];   //[NL1Mu]
   Int_t           NL1CenJet;
   Float_t         L1CenJetEt[4];   //[NL1CenJet]
   Float_t         L1CenJetE[4];   //[NL1CenJet]
   Float_t         L1CenJetEta[4];   //[NL1CenJet]
   Float_t         L1CenJetPhi[4];   //[NL1CenJet]
   Int_t           NL1ForJet;
   Float_t         L1ForJetEt[4];   //[NL1ForJet]
   Float_t         L1ForJetE[4];   //[NL1ForJet]
   Float_t         L1ForJetEta[4];   //[NL1ForJet]
   Float_t         L1ForJetPhi[4];   //[NL1ForJet]
   Int_t           NL1Tau;
   Float_t         L1TauEt[4];   //[NL1Tau]
   Float_t         L1TauE[4];   //[NL1Tau]
   Float_t         L1TauEta[4];   //[NL1Tau]
   Float_t         L1TauPhi[4];   //[NL1Tau]
   Float_t         L1Met;
   Float_t         L1MetPhi;
   Float_t         L1EtTot;
   Float_t         L1Mht;
   Float_t         L1MhtPhi;
   Float_t         L1EtHad;
   Int_t           L1HfRing1EtSumPositiveEta;
   Int_t           L1HfRing2EtSumPositiveEta;
   Int_t           L1HfRing1EtSumNegativeEta;
   Int_t           L1HfRing2EtSumNegativeEta;
   Int_t           L1HfTowerCountPositiveEtaRing1;
   Int_t           L1HfTowerCountNegativeEtaRing1;
   Int_t           L1HfTowerCountPositiveEtaRing2;
   Int_t           L1HfTowerCountNegativeEtaRing2;
   ULong64_t       Event;
   Int_t           LumiBlock;
   Int_t           Run;
   Int_t           Bx;
   Int_t           Orbit;
   Double_t        AvgInstDelLumi;
   Int_t           digitisation_step;
   Int_t           digitisation_step_Prescl;
   Int_t           L1simulation_step;
   Int_t           L1simulation_step_Prescl;
   Int_t           digi2raw_step;
   Int_t           digi2raw_step_Prescl;
   Int_t           HLTriggerFirstPath;
   Int_t           HLTriggerFirstPath_Prescl;
   Int_t           DST_Physics_v1;
   Int_t           DST_Physics_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet110_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet110_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet120_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet120_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet150_Eta5p1_v2;
   Int_t           HLT_HIPuAK4CaloJet150_Eta5p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloDJet60_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloDJet60_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloDJet80_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloDJet80_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2;
   Int_t           HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt50_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt50_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt70_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt70_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton10_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton15_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton20_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton30_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton40_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton50_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton50_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton60_Eta1p5_v2;
   Int_t           HLT_HISinglePhoton60_Eta1p5_v2_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta2p1_v2;
   Int_t           HLT_HISinglePhoton40_Eta2p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton10_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton15_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton20_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton30_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton40_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton50_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton50_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton60_Eta3p1_v2;
   Int_t           HLT_HISinglePhoton60_Eta3p1_v2_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2;
   Int_t           HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2;
   Int_t           HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2_Prescl;
   Int_t           HLT_HIUCC100_v2;
   Int_t           HLT_HIUCC100_v2_Prescl;
   Int_t           HLT_HIUCC020_v2;
   Int_t           HLT_HIUCC020_v2_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v2;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v2_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality1030_v2;
   Int_t           HLT_HIQ2Top005_Centrality1030_v2_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v2;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v2_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality3050_v2;
   Int_t           HLT_HIQ2Top005_Centrality3050_v2_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v2;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v2_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality5070_v2;
   Int_t           HLT_HIQ2Top005_Centrality5070_v2_Prescl;
   Int_t           HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2;
   Int_t           HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2_Prescl;
   Int_t           HLT_HIFullTrack12_L1Centrality010_v2;
   Int_t           HLT_HIFullTrack12_L1Centrality010_v2_Prescl;
   Int_t           HLT_HIFullTrack12_L1Centrality30100_v2;
   Int_t           HLT_HIFullTrack12_L1Centrality30100_v2_Prescl;
   Int_t           HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2;
   Int_t           HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2_Prescl;
   Int_t           HLT_HIFullTrack18_L1Centrality010_v2;
   Int_t           HLT_HIFullTrack18_L1Centrality010_v2_Prescl;
   Int_t           HLT_HIFullTrack18_L1Centrality30100_v2;
   Int_t           HLT_HIFullTrack18_L1Centrality30100_v2_Prescl;
   Int_t           HLT_HIFullTrack24_v2;
   Int_t           HLT_HIFullTrack24_v2_Prescl;
   Int_t           HLT_HIFullTrack24_L1Centrality30100_v2;
   Int_t           HLT_HIFullTrack24_L1Centrality30100_v2_Prescl;
   Int_t           HLT_HIFullTrack34_v2;
   Int_t           HLT_HIFullTrack34_v2_Prescl;
   Int_t           HLT_HIFullTrack34_L1Centrality30100_v2;
   Int_t           HLT_HIFullTrack34_L1Centrality30100_v2_Prescl;
   Int_t           HLT_HIFullTrack45_v2;
   Int_t           HLT_HIFullTrack45_v2_Prescl;
   Int_t           HLT_HIFullTrack45_L1Centrality30100_v2;
   Int_t           HLT_HIFullTrack45_L1Centrality30100_v2_Prescl;
   Int_t           HLT_HIL1DoubleMu0_v1;
   Int_t           HLT_HIL1DoubleMu0_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_2HF_v1;
   Int_t           HLT_HIL1DoubleMu0_2HF_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_2HF0_v1;
   Int_t           HLT_HIL1DoubleMu0_2HF0_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu10_v1;
   Int_t           HLT_HIL1DoubleMu10_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v2;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v2_Prescl;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_2HF_v1;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_2HF_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_2HF0_v1;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_2HF0_v1_Prescl;
   Int_t           HLT_HIL2Mu3_NHitQ10_2HF_v1;
   Int_t           HLT_HIL2Mu3_NHitQ10_2HF_v1_Prescl;
   Int_t           HLT_HIL2Mu3_NHitQ10_2HF0_v1;
   Int_t           HLT_HIL2Mu3_NHitQ10_2HF0_v1_Prescl;
   Int_t           HLT_HIL3Mu3_NHitQ15_2HF_v1;
   Int_t           HLT_HIL3Mu3_NHitQ15_2HF_v1_Prescl;
   Int_t           HLT_HIL3Mu3_NHitQ15_2HF0_v1;
   Int_t           HLT_HIL3Mu3_NHitQ15_2HF0_v1_Prescl;
   Int_t           HLT_HIL2Mu5_NHitQ10_2HF_v1;
   Int_t           HLT_HIL2Mu5_NHitQ10_2HF_v1_Prescl;
   Int_t           HLT_HIL2Mu5_NHitQ10_2HF0_v1;
   Int_t           HLT_HIL2Mu5_NHitQ10_2HF0_v1_Prescl;
   Int_t           HLT_HIL3Mu5_NHitQ15_2HF_v1;
   Int_t           HLT_HIL3Mu5_NHitQ15_2HF_v1_Prescl;
   Int_t           HLT_HIL3Mu5_NHitQ15_2HF0_v1;
   Int_t           HLT_HIL3Mu5_NHitQ15_2HF0_v1_Prescl;
   Int_t           HLT_HIL2Mu7_NHitQ10_2HF_v1;
   Int_t           HLT_HIL2Mu7_NHitQ10_2HF_v1_Prescl;
   Int_t           HLT_HIL2Mu7_NHitQ10_2HF0_v1;
   Int_t           HLT_HIL2Mu7_NHitQ10_2HF0_v1_Prescl;
   Int_t           HLT_HIL3Mu7_NHitQ15_2HF_v1;
   Int_t           HLT_HIL3Mu7_NHitQ15_2HF_v1_Prescl;
   Int_t           HLT_HIL3Mu7_NHitQ15_2HF0_v1;
   Int_t           HLT_HIL3Mu7_NHitQ15_2HF0_v1_Prescl;
   Int_t           HLT_HIL2Mu15_v2;
   Int_t           HLT_HIL2Mu15_v2_Prescl;
   Int_t           HLT_HIL2Mu15_2HF_v1;
   Int_t           HLT_HIL2Mu15_2HF_v1_Prescl;
   Int_t           HLT_HIL2Mu15_2HF0_v1;
   Int_t           HLT_HIL2Mu15_2HF0_v1_Prescl;
   Int_t           HLT_HIL3Mu15_v1;
   Int_t           HLT_HIL3Mu15_v1_Prescl;
   Int_t           HLT_HIL3Mu15_2HF_v1;
   Int_t           HLT_HIL3Mu15_2HF_v1_Prescl;
   Int_t           HLT_HIL3Mu15_2HF0_v1;
   Int_t           HLT_HIL3Mu15_2HF0_v1_Prescl;
   Int_t           HLT_HIL2Mu20_v1;
   Int_t           HLT_HIL2Mu20_v1_Prescl;
   Int_t           HLT_HIL2Mu20_2HF_v1;
   Int_t           HLT_HIL2Mu20_2HF_v1_Prescl;
   Int_t           HLT_HIL2Mu20_2HF0_v1;
   Int_t           HLT_HIL2Mu20_2HF0_v1_Prescl;
   Int_t           HLT_HIL3Mu20_v1;
   Int_t           HLT_HIL3Mu20_v1_Prescl;
   Int_t           HLT_HIL3Mu20_2HF_v1;
   Int_t           HLT_HIL3Mu20_2HF_v1_Prescl;
   Int_t           HLT_HIL3Mu20_2HF0_v1;
   Int_t           HLT_HIL3Mu20_2HF0_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_2HF_Cent30100_v1;
   Int_t           HLT_HIL1DoubleMu0_2HF_Cent30100_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_2HF0_Cent30100_v1;
   Int_t           HLT_HIL1DoubleMu0_2HF0_Cent30100_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_Cent30_v1;
   Int_t           HLT_HIL1DoubleMu0_Cent30_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_Cent30_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_Cent30_NHitQ_v1_Prescl;
   Int_t           HLT_HIL3DoubleMu0_Cent30_v1;
   Int_t           HLT_HIL3DoubleMu0_Cent30_v1_Prescl;
   Int_t           HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1;
   Int_t           HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1_Prescl;
   Int_t           HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1;
   Int_t           HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1_Prescl;
   Int_t           HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1;
   Int_t           HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1_Prescl;
   Int_t           HLT_HIL3DoubleMu0_OS_m7to14_v1;
   Int_t           HLT_HIL3DoubleMu0_OS_m7to14_v1_Prescl;
   Int_t           HLT_HIUPCL1SingleMuOpenNotHF2_v1;
   Int_t           HLT_HIUPCL1SingleMuOpenNotHF2_v1_Prescl;
   Int_t           HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHF2_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHF2_v1_Prescl;
   Int_t           HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1SingleEG2NotHF2_v1;
   Int_t           HLT_HIUPCL1SingleEG2NotHF2_v1_Prescl;
   Int_t           HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleEG2NotHF2_v1;
   Int_t           HLT_HIUPCL1DoubleEG2NotHF2_v1_Prescl;
   Int_t           HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1SingleEG5NotHF2_v1;
   Int_t           HLT_HIUPCL1SingleEG5NotHF2_v1_Prescl;
   Int_t           HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHF1_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHF1_v1_Prescl;
   Int_t           HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleEG2NotZDCAND_v1;
   Int_t           HLT_HIUPCL1DoubleEG2NotZDCAND_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1EG2NotZDCAND_v1;
   Int_t           HLT_HIUPCL1EG2NotZDCAND_v1_Prescl;
   Int_t           HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1MuOpenNotZDCAND_v1;
   Int_t           HLT_HIUPCL1MuOpenNotZDCAND_v1_Prescl;
   Int_t           HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1;
   Int_t           HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1_Prescl;
   Int_t           HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2_Prescl;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl;
   Int_t           HLT_HIL1CastorMediumJet_v1;
   Int_t           HLT_HIL1CastorMediumJet_v1_Prescl;
   Int_t           HLT_HIL1CastorMediumJetAK4CaloJet20_v2;
   Int_t           HLT_HIL1CastorMediumJetAK4CaloJet20_v2_Prescl;
   Int_t           HLT_HICastorMediumJetPixel_SingleTrack_v1;
   Int_t           HLT_HICastorMediumJetPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1NotMinimumBiasHF2_AND_v1;
   Int_t           HLT_HIUPCL1NotMinimumBiasHF2_AND_v1_Prescl;
   Int_t           HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1ZdcOR_BptxAND_v1;
   Int_t           HLT_HIUPCL1ZdcOR_BptxAND_v1_Prescl;
   Int_t           HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1ZdcXOR_BptxAND_v1;
   Int_t           HLT_HIUPCL1ZdcXOR_BptxAND_v1_Prescl;
   Int_t           HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1NotZdcOR_BptxAND_v1;
   Int_t           HLT_HIUPCL1NotZdcOR_BptxAND_v1_Prescl;
   Int_t           HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIZeroBias_v1;
   Int_t           HLT_HIZeroBias_v1_Prescl;
   Int_t           HLT_HICentralityVeto_v1;
   Int_t           HLT_HICentralityVeto_v1_Prescl;
   Int_t           HLT_HIL1Tech5_BPTX_PlusOnly_v1;
   Int_t           HLT_HIL1Tech5_BPTX_PlusOnly_v1_Prescl;
   Int_t           HLT_HIL1Tech6_BPTX_MinusOnly_v1;
   Int_t           HLT_HIL1Tech6_BPTX_MinusOnly_v1_Prescl;
   Int_t           HLT_HIL1Tech7_NoBPTX_v1;
   Int_t           HLT_HIL1Tech7_NoBPTX_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF1OR_v1;
   Int_t           HLT_HIL1MinimumBiasHF1OR_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2OR_v1;
   Int_t           HLT_HIL1MinimumBiasHF2OR_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF1AND_v1;
   Int_t           HLT_HIL1MinimumBiasHF1AND_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIZeroBiasPixel_SingleTrack_v1;
   Int_t           HLT_HIZeroBiasPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1;
   Int_t           HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1_Prescl;
   Int_t           HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1_Prescl;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIPhysics_v1;
   Int_t           HLT_HIPhysics_v1_Prescl;
   Int_t           HLT_HIRandom_v1;
   Int_t           HLT_HIRandom_v1_Prescl;
   Int_t           HLT_EcalCalibration_v2;
   Int_t           HLT_EcalCalibration_v2_Prescl;
   Int_t           HLT_HcalCalibration_v1;
   Int_t           HLT_HcalCalibration_v1_Prescl;
   Int_t           AlCa_EcalPhiSymForHI_v2;
   Int_t           AlCa_EcalPhiSymForHI_v2_Prescl;
   Int_t           AlCa_RPCMuonNoTriggersForHI_v1;
   Int_t           AlCa_RPCMuonNoTriggersForHI_v1_Prescl;
   Int_t           AlCa_RPCMuonNoHitsForHI_v1;
   Int_t           AlCa_RPCMuonNoHitsForHI_v1_Prescl;
   Int_t           AlCa_RPCMuonNormalisationForHI_v1;
   Int_t           AlCa_RPCMuonNormalisationForHI_v1_Prescl;
   Int_t           AlCa_LumiPixels_Random_v1;
   Int_t           AlCa_LumiPixels_Random_v1_Prescl;
   Int_t           AlCa_LumiPixels_ZeroBias_v2;
   Int_t           AlCa_LumiPixels_ZeroBias_v2_Prescl;
   Int_t           HLTriggerFinalPath;
   Int_t           HLTriggerFinalPath_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet110_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet110_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet120_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet120_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet150_Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet150_Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1;
   Int_t           HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1;
   Int_t           HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1;
   Int_t           HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1;
   Int_t           HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1;
   Int_t           HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloDJet60_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloDJet60_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloDJet80_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloDJet80_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1;
   Int_t           HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt50_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt50_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt70_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt70_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1_Prescl;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1;
   Int_t           HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton10_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton15_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton20_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton30_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton40_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton50_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton50_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton60_Eta1p5_v1;
   Int_t           HLT_HISinglePhoton60_Eta1p5_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta2p1_v1;
   Int_t           HLT_HISinglePhoton40_Eta2p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton10_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton15_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton20_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton30_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton40_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton50_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton50_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton60_Eta3p1_v1;
   Int_t           HLT_HISinglePhoton60_Eta3p1_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1;
   Int_t           HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1;
   Int_t           HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1;
   Int_t           HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1_Prescl;
   Int_t           HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1;
   Int_t           HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1_Prescl;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1;
   Int_t           HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1_Prescl;
   Int_t           HLT_HIUCC100_v1;
   Int_t           HLT_HIUCC100_v1_Prescl;
   Int_t           HLT_HIUCC100_v3;
   Int_t           HLT_HIUCC100_v3_Prescl;
   Int_t           HLT_HIUCC020_v1;
   Int_t           HLT_HIUCC020_v1_Prescl;
   Int_t           HLT_HIUCC020_v3;
   Int_t           HLT_HIUCC020_v3_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v1;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v1_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v3;
   Int_t           HLT_HIQ2Bottom005_Centrality1030_v3_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality1030_v1;
   Int_t           HLT_HIQ2Top005_Centrality1030_v1_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality1030_v3;
   Int_t           HLT_HIQ2Top005_Centrality1030_v3_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v1;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v1_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v3;
   Int_t           HLT_HIQ2Bottom005_Centrality3050_v3_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality3050_v1;
   Int_t           HLT_HIQ2Top005_Centrality3050_v1_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality3050_v3;
   Int_t           HLT_HIQ2Top005_Centrality3050_v3_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v1;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v1_Prescl;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v3;
   Int_t           HLT_HIQ2Bottom005_Centrality5070_v3_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality5070_v1;
   Int_t           HLT_HIQ2Top005_Centrality5070_v1_Prescl;
   Int_t           HLT_HIQ2Top005_Centrality5070_v3;
   Int_t           HLT_HIQ2Top005_Centrality5070_v3_Prescl;
   Int_t           HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1;
   Int_t           HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1_Prescl;
   Int_t           HLT_HIFullTrack12_L1Centrality010_v1;
   Int_t           HLT_HIFullTrack12_L1Centrality010_v1_Prescl;
   Int_t           HLT_HIFullTrack12_L1Centrality30100_v1;
   Int_t           HLT_HIFullTrack12_L1Centrality30100_v1_Prescl;
   Int_t           HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1;
   Int_t           HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1_Prescl;
   Int_t           HLT_HIFullTrack18_L1Centrality010_v1;
   Int_t           HLT_HIFullTrack18_L1Centrality010_v1_Prescl;
   Int_t           HLT_HIFullTrack18_L1Centrality30100_v1;
   Int_t           HLT_HIFullTrack18_L1Centrality30100_v1_Prescl;
   Int_t           HLT_HIFullTrack24_v1;
   Int_t           HLT_HIFullTrack24_v1_Prescl;
   Int_t           HLT_HIFullTrack24_L1Centrality30100_v1;
   Int_t           HLT_HIFullTrack24_L1Centrality30100_v1_Prescl;
   Int_t           HLT_HIFullTrack34_v1;
   Int_t           HLT_HIFullTrack34_v1_Prescl;
   Int_t           HLT_HIFullTrack34_L1Centrality30100_v1;
   Int_t           HLT_HIFullTrack34_L1Centrality30100_v1_Prescl;
   Int_t           HLT_HIFullTrack45_v1;
   Int_t           HLT_HIFullTrack45_v1_Prescl;
   Int_t           HLT_HIFullTrack45_L1Centrality30100_v1;
   Int_t           HLT_HIFullTrack45_L1Centrality30100_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_part1_v1;
   Int_t           HLT_HIL1DoubleMu0_part1_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_part2_v1;
   Int_t           HLT_HIL1DoubleMu0_part2_v1_Prescl;
   Int_t           HLT_HIL1DoubleMu0_part3_v1;
   Int_t           HLT_HIL1DoubleMu0_part3_v1_Prescl;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v1_Prescl;
   Int_t           HLT_HIL2Mu15_v1;
   Int_t           HLT_HIL2Mu15_v1_Prescl;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1_Prescl;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1_Prescl;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1;
   Int_t           HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIL1CastorMediumJetAK4CaloJet20_v1;
   Int_t           HLT_HIL1CastorMediumJetAK4CaloJet20_v1_Prescl;
   Int_t           HLT_HICastorMediumJetPixel_SingleTrack_v2;
   Int_t           HLT_HICastorMediumJetPixel_SingleTrack_v2_Prescl;
   Int_t           HLT_HICentralityVeto_v2;
   Int_t           HLT_HICentralityVeto_v2_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF1ANDExpress_v1;
   Int_t           HLT_HIL1MinimumBiasHF1ANDExpress_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part1_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part1_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part2_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part2_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part3_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part3_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part4_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part4_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part5_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part5_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part6_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part6_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part7_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part7_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part8_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part8_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part9_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part9_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part10_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part10_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part11_v1;
   Int_t           HLT_HIL1MinimumBiasHF2AND_part11_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2ANDExpress_v1;
   Int_t           HLT_HIL1MinimumBiasHF2ANDExpress_v1_Prescl;
   Int_t           HLT_HIL1HFplusANDminusTH0Express_v1;
   Int_t           HLT_HIL1HFplusANDminusTH0Express_v1_Prescl;
   Int_t           HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1;
   Int_t           HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1_Prescl;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1;
   Int_t           HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1_Prescl;
   Int_t           HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1;
   Int_t           HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1_Prescl;
   Int_t           HLT_HIPhysicsForZS_v1;
   Int_t           HLT_HIPhysicsForZS_v1_Prescl;
   Int_t           HLT_EcalCalibration_v1;
   Int_t           HLT_EcalCalibration_v1_Prescl;
   Int_t           HLT_HIPhysicsNoZS_v1;
   Int_t           HLT_HIPhysicsNoZS_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1;
   Int_t           HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1_Prescl;
   Int_t           HLT_HIL1Centralityext30100HFplusANDminusTH0_v1;
   Int_t           HLT_HIL1Centralityext30100HFplusANDminusTH0_v1_Prescl;
   Int_t           HLT_HIL1Centralityext50100HFplusANDminusTH0_v1;
   Int_t           HLT_HIL1Centralityext50100HFplusANDminusTH0_v1_Prescl;
   Int_t           HLT_HIL1Centralityext70100HFplusANDminusTH0_v1;
   Int_t           HLT_HIL1Centralityext70100HFplusANDminusTH0_v1_Prescl;
   Int_t           L1_BptxMinus_NotBptxPlus;
   Int_t           L1_BptxMinus_NotBptxPlus_Prescl;
   Int_t           L1_BptxPlusORMinus;
   Int_t           L1_BptxPlusORMinus_Prescl;
   Int_t           L1_BptxPlus_NotBptxMinus;
   Int_t           L1_BptxPlus_NotBptxMinus_Prescl;
   Int_t           L1_CastorHighJet_BptxAND;
   Int_t           L1_CastorHighJet_BptxAND_Prescl;
   Int_t           L1_CastorMediumJet_BptxAND;
   Int_t           L1_CastorMediumJet_BptxAND_Prescl;
   Int_t           L1_CastorMuon_BptxAND;
   Int_t           L1_CastorMuon_BptxAND_Prescl;
   Int_t           L1_Centrality_ext0_100_HFplusORminusTH0;
   Int_t           L1_Centrality_ext0_100_HFplusORminusTH0_Prescl;
   Int_t           L1_Centrality_ext0_100_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext0_100_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext0_10_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext0_10_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext0_5_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext0_5_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext30_100_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext30_100_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext30_50_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext30_50_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext50_100_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext50_100_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_Centrality_ext70_100_MinimumumBiasHF1_AND;
   Int_t           L1_Centrality_ext70_100_MinimumumBiasHF1_AND_Prescl;
   Int_t           L1_DoubleEG10;
   Int_t           L1_DoubleEG10_Prescl;
   Int_t           L1_DoubleEG2_BptxAND;
   Int_t           L1_DoubleEG2_BptxAND_Prescl;
   Int_t           L1_DoubleEG2_NotMinimumBiasHF2_AND;
   Int_t           L1_DoubleEG2_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_DoubleEG2_NotZdc_AND_BptxAND;
   Int_t           L1_DoubleEG2_NotZdc_AND_BptxAND_Prescl;
   Int_t           L1_DoubleEG5_BptxAND;
   Int_t           L1_DoubleEG5_BptxAND_Prescl;
   Int_t           L1_DoubleEG8_BptxAND;
   Int_t           L1_DoubleEG8_BptxAND_Prescl;
   Int_t           L1_DoubleEG_13_7;
   Int_t           L1_DoubleEG_13_7_Prescl;
   Int_t           L1_DoubleMu0_BptxAND;
   Int_t           L1_DoubleMu0_BptxAND_Prescl;
   Int_t           L1_DoubleMu0_HFplusANDminusTH0_BptxAND;
   Int_t           L1_DoubleMu0_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND;
   Int_t           L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND_Prescl;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND_Prescl;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND_Prescl;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND;
   Int_t           L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_DoubleMu10_BptxAND;
   Int_t           L1_DoubleMu10_BptxAND_Prescl;
   Int_t           L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND;
   Int_t           L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_DoubleMuOpen_BptxAND;
   Int_t           L1_DoubleMuOpen_BptxAND_Prescl;
   Int_t           L1_DoubleMuOpen_NotMinimumBiasHF1_AND;
   Int_t           L1_DoubleMuOpen_NotMinimumBiasHF1_AND_Prescl;
   Int_t           L1_DoubleMuOpen_NotMinimumBiasHF2_AND;
   Int_t           L1_DoubleMuOpen_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_DoubleMuOpen_NotZdc_AND_BptxAND;
   Int_t           L1_DoubleMuOpen_NotZdc_AND_BptxAND_Prescl;
   Int_t           L1_EG2_NotMinimumBiasHF2_AND;
   Int_t           L1_EG2_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_EG5_NotMinimumBiasHF2_AND;
   Int_t           L1_EG5_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_HF_2reg_plusANDminusTH0;
   Int_t           L1_HF_2reg_plusANDminusTH0_Prescl;
   Int_t           L1_HF_2reg_plusANDminusTH1;
   Int_t           L1_HF_2reg_plusANDminusTH1_Prescl;
   Int_t           L1_HFplusANDminusTH0;
   Int_t           L1_HFplusANDminusTH0_Prescl;
   Int_t           L1_HFplusANDminusTH1;
   Int_t           L1_HFplusANDminusTH1_Prescl;
   Int_t           L1_HFplusORminusTH0;
   Int_t           L1_HFplusORminusTH0_Prescl;
   Int_t           L1_HFplusORminusTH1;
   Int_t           L1_HFplusORminusTH1_Prescl;
   Int_t           L1_MinimumBiasHF1_AND;
   Int_t           L1_MinimumBiasHF1_AND_Prescl;
   Int_t           L1_MinimumBiasHF1_OR;
   Int_t           L1_MinimumBiasHF1_OR_Prescl;
   Int_t           L1_MinimumBiasHF1_OR_NotInUse;
   Int_t           L1_MinimumBiasHF1_OR_NotInUse_Prescl;
   Int_t           L1_MinimumBiasHF1_XOR;
   Int_t           L1_MinimumBiasHF1_XOR_Prescl;
   Int_t           L1_MinimumBiasHF2_AND;
   Int_t           L1_MinimumBiasHF2_AND_Prescl;
   Int_t           L1_MinimumBiasHF2_OR;
   Int_t           L1_MinimumBiasHF2_OR_Prescl;
   Int_t           L1_MuOpen_NotMinimumBiasHF1_AND;
   Int_t           L1_MuOpen_NotMinimumBiasHF1_AND_Prescl;
   Int_t           L1_MuOpen_NotMinimumBiasHF2_AND;
   Int_t           L1_MuOpen_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_MuOpen_NotZdc_AND_BptxAND;
   Int_t           L1_MuOpen_NotZdc_AND_BptxAND_Prescl;
   Int_t           L1_NotHFplusANDminusTH0_BptxAND;
   Int_t           L1_NotHFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_NotMinimumBiasHF1_OR;
   Int_t           L1_NotMinimumBiasHF1_OR_Prescl;
   Int_t           L1_NotMinimumBiasHF2_AND;
   Int_t           L1_NotMinimumBiasHF2_AND_Prescl;
   Int_t           L1_NotZdcOR_BptxAND;
   Int_t           L1_NotZdcOR_BptxAND_Prescl;
   Int_t           L1_SingleEG12_BptxAND;
   Int_t           L1_SingleEG12_BptxAND_Prescl;
   Int_t           L1_SingleEG15_BptxAND;
   Int_t           L1_SingleEG15_BptxAND_Prescl;
   Int_t           L1_SingleEG21_BptxAND;
   Int_t           L1_SingleEG21_BptxAND_Prescl;
   Int_t           L1_SingleEG21_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleEG21_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleEG21_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleEG21_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleEG2_NotZDC_AND_BptxAND;
   Int_t           L1_SingleEG2_NotZDC_AND_BptxAND_Prescl;
   Int_t           L1_SingleEG30_BptxAND;
   Int_t           L1_SingleEG30_BptxAND_Prescl;
   Int_t           L1_SingleEG3_BptxAND;
   Int_t           L1_SingleEG3_BptxAND_Prescl;
   Int_t           L1_SingleEG3_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleEG3_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleEG3_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleEG3_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleEG5;
   Int_t           L1_SingleEG5_Prescl;
   Int_t           L1_SingleEG5_BptxAND;
   Int_t           L1_SingleEG5_BptxAND_Prescl;
   Int_t           L1_SingleEG5_NotZdc_AND_BptxAND;
   Int_t           L1_SingleEG5_NotZdc_AND_BptxAND_Prescl;
   Int_t           L1_SingleEG7_BptxAND;
   Int_t           L1_SingleEG7_BptxAND_Prescl;
   Int_t           L1_SingleEG7_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleEG7_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleEG7_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleEG7_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleIsoEG3_BptxAND;
   Int_t           L1_SingleIsoEG3_BptxAND_Prescl;
   Int_t           L1_SingleIsoEG7_BptxAND;
   Int_t           L1_SingleIsoEG7_BptxAND_Prescl;
   Int_t           L1_SingleMu12_BptxAND;
   Int_t           L1_SingleMu12_BptxAND_Prescl;
   Int_t           L1_SingleMu12_HFplusANDminusTH0_BptxAND;
   Int_t           L1_SingleMu12_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_SingleMu12_MinimumBiasHF1_AND_BptxAND;
   Int_t           L1_SingleMu12_MinimumBiasHF1_AND_BptxAND_Prescl;
   Int_t           L1_SingleMu12_SingleEG7;
   Int_t           L1_SingleMu12_SingleEG7_Prescl;
   Int_t           L1_SingleMu16_BptxAND;
   Int_t           L1_SingleMu16_BptxAND_Prescl;
   Int_t           L1_SingleMu16_HFplusANDminusTH0_BptxAND;
   Int_t           L1_SingleMu16_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_SingleMu16_MinimumBiasHF1_AND_BptxAND;
   Int_t           L1_SingleMu16_MinimumBiasHF1_AND_BptxAND_Prescl;
   Int_t           L1_SingleMu3_HFplusANDminusTH0_BptxAND;
   Int_t           L1_SingleMu3_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_SingleMu3_MinimumBiasHF1_AND;
   Int_t           L1_SingleMu3_MinimumBiasHF1_AND_Prescl;
   Int_t           L1_SingleMu3_SingleCenJet28;
   Int_t           L1_SingleMu3_SingleCenJet28_Prescl;
   Int_t           L1_SingleMu3_SingleCenJet32;
   Int_t           L1_SingleMu3_SingleCenJet32_Prescl;
   Int_t           L1_SingleMu3_SingleCenJet40;
   Int_t           L1_SingleMu3_SingleCenJet40_Prescl;
   Int_t           L1_SingleMu3_SingleEG12;
   Int_t           L1_SingleMu3_SingleEG12_Prescl;
   Int_t           L1_SingleMu3_SingleEG20;
   Int_t           L1_SingleMu3_SingleEG20_Prescl;
   Int_t           L1_SingleMu5_HFplusANDminusTH0_BptxAND;
   Int_t           L1_SingleMu5_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_SingleMu5_MinimumBiasHF1_AND;
   Int_t           L1_SingleMu5_MinimumBiasHF1_AND_Prescl;
   Int_t           L1_SingleMu5_SingleEG20;
   Int_t           L1_SingleMu5_SingleEG20_Prescl;
   Int_t           L1_SingleMu7_HFplusANDminusTH0_BptxAND;
   Int_t           L1_SingleMu7_HFplusANDminusTH0_BptxAND_Prescl;
   Int_t           L1_SingleMu7_MinimumBiasHF1_AND;
   Int_t           L1_SingleMu7_MinimumBiasHF1_AND_Prescl;
   Int_t           L1_SingleMu7_SingleEG12;
   Int_t           L1_SingleMu7_SingleEG12_Prescl;
   Int_t           L1_SingleMuOpen;
   Int_t           L1_SingleMuOpen_Prescl;
   Int_t           L1_SingleMuOpen_BptxAND;
   Int_t           L1_SingleMuOpen_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet16_BptxAND;
   Int_t           L1_SingleS1Jet16_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet16_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleS1Jet16_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet16_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleS1Jet16_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet28_BptxAND;
   Int_t           L1_SingleS1Jet28_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet28_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleS1Jet28_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet28_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleS1Jet28_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet32_BptxAND;
   Int_t           L1_SingleS1Jet32_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet32_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleS1Jet32_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet32_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleS1Jet32_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet36_BptxAND;
   Int_t           L1_SingleS1Jet36_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet40_BptxAND;
   Int_t           L1_SingleS1Jet40_BptxAND_Prescl;
   Int_t           L1_SingleJet44_BptxAND;
   Int_t           L1_SingleJet44_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet44_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleS1Jet44_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet44_Centrality_ext50_100_BptxAND;
   Int_t           L1_SingleS1Jet44_Centrality_ext50_100_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet48_BptxAND;
   Int_t           L1_SingleS1Jet48_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet52_BptxAND;
   Int_t           L1_SingleS1Jet52_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet56_BptxAND;
   Int_t           L1_SingleS1Jet56_BptxAND_Prescl;
   Int_t           L1_SingleS1Jet64_BptxAND;
   Int_t           L1_SingleS1Jet64_BptxAND_Prescl;
   Int_t           L1_SingleS1JetC20_NotBptxOR;
   Int_t           L1_SingleS1JetC20_NotBptxOR_Prescl;
   Int_t           L1_SingleS1JetC32_NotBptxOR;
   Int_t           L1_SingleS1JetC32_NotBptxOR_Prescl;
   Int_t           L1_SingleTrack12_BptxAND;
   Int_t           L1_SingleTrack12_BptxAND_Prescl;
   Int_t           L1_SingleTrack12_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleTrack12_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleTrack16_BptxAND;
   Int_t           L1_SingleTrack16_BptxAND_Prescl;
   Int_t           L1_SingleTrack16_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleTrack16_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleTrack20_BptxAND;
   Int_t           L1_SingleTrack20_BptxAND_Prescl;
   Int_t           L1_SingleTrack20_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleTrack20_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleTrack24_BptxAND;
   Int_t           L1_SingleTrack24_BptxAND_Prescl;
   Int_t           L1_SingleTrack24_Centrality_ext30_100_BptxAND;
   Int_t           L1_SingleTrack24_Centrality_ext30_100_BptxAND_Prescl;
   Int_t           L1_SingleTrack28_BptxAND;
   Int_t           L1_SingleTrack28_BptxAND_Prescl;
   Int_t           L1_TOTEM_1;
   Int_t           L1_TOTEM_1_Prescl;
   Int_t           L1_TOTEM_2;
   Int_t           L1_TOTEM_2_Prescl;
   Int_t           L1_ZdcOR_BptxAND;
   Int_t           L1_ZdcOR_BptxAND_Prescl;
   Int_t           L1_ZdcXOR_BptxAND;
   Int_t           L1_ZdcXOR_BptxAND_Prescl;
   Int_t           L1_ZeroBias;
   Int_t           L1_ZeroBias_Prescl;
   Int_t           L1Tech_BPTX_PreBPTX_v0;
   Int_t           L1Tech_BPTX_PreBPTX_v0_Prescl;
   Int_t           L1Tech_BPTX_minus_v0;
   Int_t           L1Tech_BPTX_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_v0;
   Int_t           L1Tech_BPTX_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_quiet_v0;
   Int_t           L1Tech_BPTX_quiet_v0_Prescl;
   Int_t           L1Tech_BRIL_bit28;
   Int_t           L1Tech_BRIL_bit28_Prescl;
   Int_t           L1Tech_BRIL_bit29;
   Int_t           L1Tech_BRIL_bit29_Prescl;
   Int_t           L1Tech_BRIL_bit30;
   Int_t           L1Tech_BRIL_bit30_Prescl;
   Int_t           L1Tech_BRIL_bit31;
   Int_t           L1Tech_BRIL_bit31_Prescl;
   Int_t           L1Tech_BRIL_bit32;
   Int_t           L1Tech_BRIL_bit32_Prescl;
   Int_t           L1Tech_BRIL_bit33;
   Int_t           L1Tech_BRIL_bit33_Prescl;
   Int_t           L1Tech_BRIL_bit34;
   Int_t           L1Tech_BRIL_bit34_Prescl;
   Int_t           L1Tech_BRIL_bit35;
   Int_t           L1Tech_BRIL_bit35_Prescl;
   Int_t           L1Tech_BRIL_bit36;
   Int_t           L1Tech_BRIL_bit36_Prescl;
   Int_t           L1Tech_BRIL_bit37;
   Int_t           L1Tech_BRIL_bit37_Prescl;
   Int_t           L1Tech_BRIL_bit38;
   Int_t           L1Tech_BRIL_bit38_Prescl;
   Int_t           L1Tech_BRIL_bit39;
   Int_t           L1Tech_BRIL_bit39_Prescl;
   Int_t           L1Tech_BRIL_bit40;
   Int_t           L1Tech_BRIL_bit40_Prescl;
   Int_t           L1Tech_BRIL_bit41;
   Int_t           L1Tech_BRIL_bit41_Prescl;
   Int_t           L1Tech_BRIL_bit42;
   Int_t           L1Tech_BRIL_bit42_Prescl;
   Int_t           L1Tech_BRIL_bit43;
   Int_t           L1Tech_BRIL_bit43_Prescl;
   Int_t           L1Tech_CASTOR_Gap_v0;
   Int_t           L1Tech_CASTOR_Gap_v0_Prescl;
   Int_t           L1Tech_CASTOR_HaloMuon_v0;
   Int_t           L1Tech_CASTOR_HaloMuon_v0_Prescl;
   Int_t           L1Tech_CASTOR_HighJet_v0;
   Int_t           L1Tech_CASTOR_HighJet_v0_Prescl;
   Int_t           L1Tech_CASTOR_MediumJet_v0;
   Int_t           L1Tech_CASTOR_MediumJet_v0_Prescl;
   Int_t           L1Tech_DT_GlobalOR_v0;
   Int_t           L1Tech_DT_GlobalOR_v0_Prescl;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0_Prescl;
   Int_t           L1Tech_HCAL_HF_MMP_or_MPP_v1;
   Int_t           L1Tech_HCAL_HF_MMP_or_MPP_v1_Prescl;
   Int_t           L1Tech_HCAL_HF_coincidence_PM_v2;
   Int_t           L1Tech_HCAL_HF_coincidence_PM_v2_Prescl;
   Int_t           L1Tech_HCAL_HF_single_channel_v0;
   Int_t           L1Tech_HCAL_HF_single_channel_v0_Prescl;
   Int_t           L1Tech_HCAL_HO_totalOR_v0;
   Int_t           L1Tech_HCAL_HO_totalOR_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;
   Int_t           L1Tech_TOTEM_0;
   Int_t           L1Tech_TOTEM_0_Prescl;
   Int_t           L1Tech_TOTEM_1;
   Int_t           L1Tech_TOTEM_1_Prescl;
   Int_t           L1Tech_TOTEM_2;
   Int_t           L1Tech_TOTEM_2_Prescl;
   Int_t           L1Tech_TOTEM_3;
   Int_t           L1Tech_TOTEM_3_Prescl;
   Int_t           L1Tech_ZDC_minus;
   Int_t           L1Tech_ZDC_minus_Prescl;
   Int_t           L1Tech_ZDC_plus;
   Int_t           L1Tech_ZDC_plus_Prescl;

   // List of branches
   TBranch        *b_NL1IsolEm;   //!
   TBranch        *b_L1IsolEmEt;   //!
   TBranch        *b_L1IsolEmE;   //!
   TBranch        *b_L1IsolEmEta;   //!
   TBranch        *b_L1IsolEmPhi;   //!
   TBranch        *b_NL1NIsolEm;   //!
   TBranch        *b_L1NIsolEmEt;   //!
   TBranch        *b_L1NIsolEmE;   //!
   TBranch        *b_L1NIsolEmEta;   //!
   TBranch        *b_L1NIsolEmPhi;   //!
   TBranch        *b_NL1Mu;   //!
   TBranch        *b_L1MuPt;   //!
   TBranch        *b_L1MuE;   //!
   TBranch        *b_L1MuEta;   //!
   TBranch        *b_L1MuPhi;   //!
   TBranch        *b_L1MuIsol;   //!
   TBranch        *b_L1MuMip;   //!
   TBranch        *b_L1MuFor;   //!
   TBranch        *b_L1MuRPC;   //!
   TBranch        *b_L1MuQal;   //!
   TBranch        *b_L1MuChg;   //!
   TBranch        *b_NL1CenJet;   //!
   TBranch        *b_L1CenJetEt;   //!
   TBranch        *b_L1CenJetE;   //!
   TBranch        *b_L1CenJetEta;   //!
   TBranch        *b_L1CenJetPhi;   //!
   TBranch        *b_NL1ForJet;   //!
   TBranch        *b_L1ForJetEt;   //!
   TBranch        *b_L1ForJetE;   //!
   TBranch        *b_L1ForJetEta;   //!
   TBranch        *b_L1ForJetPhi;   //!
   TBranch        *b_NL1Tau;   //!
   TBranch        *b_L1TauEt;   //!
   TBranch        *b_L1TauE;   //!
   TBranch        *b_L1TauEta;   //!
   TBranch        *b_L1TauPhi;   //!
   TBranch        *b_L1Met;   //!
   TBranch        *b_L1MetPhi;   //!
   TBranch        *b_L1EtTot;   //!
   TBranch        *b_L1Mht;   //!
   TBranch        *b_L1MhtPhi;   //!
   TBranch        *b_L1EtHad;   //!
   TBranch        *b_L1HfRing1EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing2EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing1EtSumNegativeEta;   //!
   TBranch        *b_L1HfRing2EtSumNegativeEta;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing1;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing1;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing2;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing2;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Bx;   //!
   TBranch        *b_Orbit;   //!
   TBranch        *b_AvgInstDelLumi;   //!
   TBranch        *b_digitisation_step;   //!
   TBranch        *b_digitisation_step_Prescl;   //!
   TBranch        *b_L1simulation_step;   //!
   TBranch        *b_L1simulation_step_Prescl;   //!
   TBranch        *b_digi2raw_step;   //!
   TBranch        *b_digi2raw_step_Prescl;   //!
   TBranch        *b_HLTriggerFirstPath;   //!
   TBranch        *b_HLTriggerFirstPath_Prescl;   //!
   TBranch        *b_DST_Physics_v1;   //!
   TBranch        *b_DST_Physics_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet110_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet110_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet150_Eta5p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet150_Eta5p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet60_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet60_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet80_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet80_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt50_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt50_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt70_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt70_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta1p5_v2;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta2p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta3p1_v2;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta3p1_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2_Prescl;   //!
   TBranch        *b_HLT_HIUCC100_v2;   //!
   TBranch        *b_HLT_HIUCC100_v2_Prescl;   //!
   TBranch        *b_HLT_HIUCC020_v2;   //!
   TBranch        *b_HLT_HIUCC020_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v2;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v2;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v2;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v2;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v2;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v2_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v2;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2;   //!
   TBranch        *b_HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality010_v2;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality010_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality30100_v2;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality30100_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2;   //!
   TBranch        *b_HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality010_v2;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality010_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality30100_v2;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality30100_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack24_v2;   //!
   TBranch        *b_HLT_HIFullTrack24_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack24_L1Centrality30100_v2;   //!
   TBranch        *b_HLT_HIFullTrack24_L1Centrality30100_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack34_v2;   //!
   TBranch        *b_HLT_HIFullTrack34_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack34_L1Centrality30100_v2;   //!
   TBranch        *b_HLT_HIFullTrack34_L1Centrality30100_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack45_v2;   //!
   TBranch        *b_HLT_HIFullTrack45_v2_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack45_L1Centrality30100_v2;   //!
   TBranch        *b_HLT_HIFullTrack45_L1Centrality30100_v2_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF0_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu10_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu10_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v2;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_2HF_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3_NHitQ10_2HF_v1;   //!
   TBranch        *b_HLT_HIL2Mu3_NHitQ10_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3_NHitQ10_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2Mu3_NHitQ10_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu3_NHitQ15_2HF_v1;   //!
   TBranch        *b_HLT_HIL3Mu3_NHitQ15_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu3_NHitQ15_2HF0_v1;   //!
   TBranch        *b_HLT_HIL3Mu3_NHitQ15_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu5_NHitQ10_2HF_v1;   //!
   TBranch        *b_HLT_HIL2Mu5_NHitQ10_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu5_NHitQ10_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2Mu5_NHitQ10_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu5_NHitQ15_2HF_v1;   //!
   TBranch        *b_HLT_HIL3Mu5_NHitQ15_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu5_NHitQ15_2HF0_v1;   //!
   TBranch        *b_HLT_HIL3Mu5_NHitQ15_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu7_NHitQ10_2HF_v1;   //!
   TBranch        *b_HLT_HIL2Mu7_NHitQ10_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu7_NHitQ10_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2Mu7_NHitQ10_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu7_NHitQ15_2HF_v1;   //!
   TBranch        *b_HLT_HIL3Mu7_NHitQ15_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu7_NHitQ15_2HF0_v1;   //!
   TBranch        *b_HLT_HIL3Mu7_NHitQ15_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu15_v2;   //!
   TBranch        *b_HLT_HIL2Mu15_v2_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu15_2HF_v1;   //!
   TBranch        *b_HLT_HIL2Mu15_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu15_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2Mu15_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu15_v1;   //!
   TBranch        *b_HLT_HIL3Mu15_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu15_2HF_v1;   //!
   TBranch        *b_HLT_HIL3Mu15_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu15_2HF0_v1;   //!
   TBranch        *b_HLT_HIL3Mu15_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu20_v1;   //!
   TBranch        *b_HLT_HIL2Mu20_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu20_2HF_v1;   //!
   TBranch        *b_HLT_HIL2Mu20_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu20_2HF0_v1;   //!
   TBranch        *b_HLT_HIL2Mu20_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu20_v1;   //!
   TBranch        *b_HLT_HIL3Mu20_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu20_2HF_v1;   //!
   TBranch        *b_HLT_HIL3Mu20_2HF_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu20_2HF0_v1;   //!
   TBranch        *b_HLT_HIL3Mu20_2HF0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF_Cent30100_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF_Cent30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF0_Cent30100_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_2HF0_Cent30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_Cent30_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_Cent30_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_Cent30_NHitQ_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_Cent30_NHitQ_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_OS_m7to14_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMu0_OS_m7to14_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1SingleMuOpenNotHF2_v1;   //!
   TBranch        *b_HLT_HIUPCL1SingleMuOpenNotHF2_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHF2_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHF2_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1SingleEG2NotHF2_v1;   //!
   TBranch        *b_HLT_HIUPCL1SingleEG2NotHF2_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotHF2_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotHF2_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1SingleEG5NotHF2_v1;   //!
   TBranch        *b_HLT_HIUPCL1SingleEG5NotHF2_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHF1_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHF1_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotZDCAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotZDCAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1EG2NotZDCAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1EG2NotZDCAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1MuOpenNotZDCAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1MuOpenNotZDCAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl;   //!
   TBranch        *b_HLT_HIL1CastorMediumJet_v1;   //!
   TBranch        *b_HLT_HIL1CastorMediumJet_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1CastorMediumJetAK4CaloJet20_v2;   //!
   TBranch        *b_HLT_HIL1CastorMediumJetAK4CaloJet20_v2_Prescl;   //!
   TBranch        *b_HLT_HICastorMediumJetPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HICastorMediumJetPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotMinimumBiasHF2_AND_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotMinimumBiasHF2_AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1ZdcOR_BptxAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1ZdcOR_BptxAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1ZdcXOR_BptxAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1ZdcXOR_BptxAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotZdcOR_BptxAND_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotZdcOR_BptxAND_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIZeroBias_v1;   //!
   TBranch        *b_HLT_HIZeroBias_v1_Prescl;   //!
   TBranch        *b_HLT_HICentralityVeto_v1;   //!
   TBranch        *b_HLT_HICentralityVeto_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Tech5_BPTX_PlusOnly_v1;   //!
   TBranch        *b_HLT_HIL1Tech5_BPTX_PlusOnly_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Tech6_BPTX_MinusOnly_v1;   //!
   TBranch        *b_HLT_HIL1Tech6_BPTX_MinusOnly_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Tech7_NoBPTX_v1;   //!
   TBranch        *b_HLT_HIL1Tech7_NoBPTX_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1OR_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1OR_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2OR_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2OR_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1AND_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIZeroBiasPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIZeroBiasPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIPhysics_v1;   //!
   TBranch        *b_HLT_HIPhysics_v1_Prescl;   //!
   TBranch        *b_HLT_HIRandom_v1;   //!
   TBranch        *b_HLT_HIRandom_v1_Prescl;   //!
   TBranch        *b_HLT_EcalCalibration_v2;   //!
   TBranch        *b_HLT_EcalCalibration_v2_Prescl;   //!
   TBranch        *b_HLT_HcalCalibration_v1;   //!
   TBranch        *b_HLT_HcalCalibration_v1_Prescl;   //!
   TBranch        *b_AlCa_EcalPhiSymForHI_v2;   //!
   TBranch        *b_AlCa_EcalPhiSymForHI_v2_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNoTriggersForHI_v1;   //!
   TBranch        *b_AlCa_RPCMuonNoTriggersForHI_v1_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNoHitsForHI_v1;   //!
   TBranch        *b_AlCa_RPCMuonNoHitsForHI_v1_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNormalisationForHI_v1;   //!
   TBranch        *b_AlCa_RPCMuonNormalisationForHI_v1_Prescl;   //!
   TBranch        *b_AlCa_LumiPixels_Random_v1;   //!
   TBranch        *b_AlCa_LumiPixels_Random_v1_Prescl;   //!
   TBranch        *b_AlCa_LumiPixels_ZeroBias_v2;   //!
   TBranch        *b_AlCa_LumiPixels_ZeroBias_v2_Prescl;   //!
   TBranch        *b_HLTriggerFinalPath;   //!
   TBranch        *b_HLTriggerFinalPath_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet110_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet110_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet150_Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet150_Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet60_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet60_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet80_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloDJet80_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt50_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt50_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt70_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt70_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1;   //!
   TBranch        *b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta1p5_v1;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta2p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton50_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta3p1_v1;   //!
   TBranch        *b_HLT_HISinglePhoton60_Eta3p1_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1;   //!
   TBranch        *b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1;   //!
   TBranch        *b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1;   //!
   TBranch        *b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1_Prescl;   //!
   TBranch        *b_HLT_HIUCC100_v1;   //!
   TBranch        *b_HLT_HIUCC100_v1_Prescl;   //!
   TBranch        *b_HLT_HIUCC100_v3;   //!
   TBranch        *b_HLT_HIUCC100_v3_Prescl;   //!
   TBranch        *b_HLT_HIUCC020_v1;   //!
   TBranch        *b_HLT_HIUCC020_v1_Prescl;   //!
   TBranch        *b_HLT_HIUCC020_v3;   //!
   TBranch        *b_HLT_HIUCC020_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v1;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v3;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality1030_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v1;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v3;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality1030_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v1;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v3;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality3050_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v1;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v3;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality3050_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v1;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v3;   //!
   TBranch        *b_HLT_HIQ2Bottom005_Centrality5070_v3_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v1;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v1_Prescl;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v3;   //!
   TBranch        *b_HLT_HIQ2Top005_Centrality5070_v3_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1;   //!
   TBranch        *b_HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality010_v1;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality010_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality30100_v1;   //!
   TBranch        *b_HLT_HIFullTrack12_L1Centrality30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1;   //!
   TBranch        *b_HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality010_v1;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality010_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality30100_v1;   //!
   TBranch        *b_HLT_HIFullTrack18_L1Centrality30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack24_v1;   //!
   TBranch        *b_HLT_HIFullTrack24_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack24_L1Centrality30100_v1;   //!
   TBranch        *b_HLT_HIFullTrack24_L1Centrality30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack34_v1;   //!
   TBranch        *b_HLT_HIFullTrack34_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack34_L1Centrality30100_v1;   //!
   TBranch        *b_HLT_HIFullTrack34_L1Centrality30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack45_v1;   //!
   TBranch        *b_HLT_HIFullTrack45_v1_Prescl;   //!
   TBranch        *b_HLT_HIFullTrack45_L1Centrality30100_v1;   //!
   TBranch        *b_HLT_HIFullTrack45_L1Centrality30100_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part1_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part2_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part2_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part3_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMu0_part3_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v1_Prescl;   //!
   TBranch        *b_HLT_HIL2Mu15_v1;   //!
   TBranch        *b_HLT_HIL2Mu15_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1_Prescl;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1CastorMediumJetAK4CaloJet20_v1;   //!
   TBranch        *b_HLT_HIL1CastorMediumJetAK4CaloJet20_v1_Prescl;   //!
   TBranch        *b_HLT_HICastorMediumJetPixel_SingleTrack_v2;   //!
   TBranch        *b_HLT_HICastorMediumJetPixel_SingleTrack_v2_Prescl;   //!
   TBranch        *b_HLT_HICentralityVeto_v2;   //!
   TBranch        *b_HLT_HICentralityVeto_v2_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1ANDExpress_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF1ANDExpress_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part1_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part2_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part2_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part3_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part3_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part4_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part4_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part5_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part5_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part6_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part6_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part7_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part7_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part8_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part8_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part9_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part9_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part10_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part10_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part11_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2AND_part11_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2ANDExpress_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2ANDExpress_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1HFplusANDminusTH0Express_v1;   //!
   TBranch        *b_HLT_HIL1HFplusANDminusTH0Express_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1_Prescl;   //!
   TBranch        *b_HLT_HIPhysicsForZS_v1;   //!
   TBranch        *b_HLT_HIPhysicsForZS_v1_Prescl;   //!
   TBranch        *b_HLT_EcalCalibration_v1;   //!
   TBranch        *b_HLT_EcalCalibration_v1_Prescl;   //!
   TBranch        *b_HLT_HIPhysicsNoZS_v1;   //!
   TBranch        *b_HLT_HIPhysicsNoZS_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext30100HFplusANDminusTH0_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext30100HFplusANDminusTH0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext50100HFplusANDminusTH0_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext50100HFplusANDminusTH0_v1_Prescl;   //!
   TBranch        *b_HLT_HIL1Centralityext70100HFplusANDminusTH0_v1;   //!
   TBranch        *b_HLT_HIL1Centralityext70100HFplusANDminusTH0_v1_Prescl;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus_Prescl;   //!
   TBranch        *b_L1_BptxPlusORMinus;   //!
   TBranch        *b_L1_BptxPlusORMinus_Prescl;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus_Prescl;   //!
   TBranch        *b_L1_CastorHighJet_BptxAND;   //!
   TBranch        *b_L1_CastorHighJet_BptxAND_Prescl;   //!
   TBranch        *b_L1_CastorMediumJet_BptxAND;   //!
   TBranch        *b_L1_CastorMediumJet_BptxAND_Prescl;   //!
   TBranch        *b_L1_CastorMuon_BptxAND;   //!
   TBranch        *b_L1_CastorMuon_BptxAND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext0_100_HFplusORminusTH0;   //!
   TBranch        *b_L1_Centrality_ext0_100_HFplusORminusTH0_Prescl;   //!
   TBranch        *b_L1_Centrality_ext0_100_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext0_100_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext0_10_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext0_10_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext0_5_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext0_5_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext30_100_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext30_100_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext30_50_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext30_50_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext50_100_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext50_100_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_Centrality_ext70_100_MinimumumBiasHF1_AND;   //!
   TBranch        *b_L1_Centrality_ext70_100_MinimumumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_DoubleEG10;   //!
   TBranch        *b_L1_DoubleEG10_Prescl;   //!
   TBranch        *b_L1_DoubleEG2_BptxAND;   //!
   TBranch        *b_L1_DoubleEG2_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleEG2_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_DoubleEG2_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_DoubleEG2_NotZdc_AND_BptxAND;   //!
   TBranch        *b_L1_DoubleEG2_NotZdc_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleEG5_BptxAND;   //!
   TBranch        *b_L1_DoubleEG5_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleEG8_BptxAND;   //!
   TBranch        *b_L1_DoubleEG8_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleEG_13_7;   //!
   TBranch        *b_L1_DoubleEG_13_7_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_BptxAND;   //!
   TBranch        *b_L1_DoubleMu0_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_DoubleMu0_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND;   //!
   TBranch        *b_L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMu10_BptxAND;   //!
   TBranch        *b_L1_DoubleMu10_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_NotMinimumBiasHF1_AND;   //!
   TBranch        *b_L1_DoubleMuOpen_NotMinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_DoubleMuOpen_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_NotZdc_AND_BptxAND;   //!
   TBranch        *b_L1_DoubleMuOpen_NotZdc_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_EG2_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_EG2_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_EG5_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_EG5_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_HF_2reg_plusANDminusTH0;   //!
   TBranch        *b_L1_HF_2reg_plusANDminusTH0_Prescl;   //!
   TBranch        *b_L1_HF_2reg_plusANDminusTH1;   //!
   TBranch        *b_L1_HF_2reg_plusANDminusTH1_Prescl;   //!
   TBranch        *b_L1_HFplusANDminusTH0;   //!
   TBranch        *b_L1_HFplusANDminusTH0_Prescl;   //!
   TBranch        *b_L1_HFplusANDminusTH1;   //!
   TBranch        *b_L1_HFplusANDminusTH1_Prescl;   //!
   TBranch        *b_L1_HFplusORminusTH0;   //!
   TBranch        *b_L1_HFplusORminusTH0_Prescl;   //!
   TBranch        *b_L1_HFplusORminusTH1;   //!
   TBranch        *b_L1_HFplusORminusTH1_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF1_AND;   //!
   TBranch        *b_L1_MinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF1_OR;   //!
   TBranch        *b_L1_MinimumBiasHF1_OR_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF1_OR_NotInUse;   //!
   TBranch        *b_L1_MinimumBiasHF1_OR_NotInUse_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF1_XOR;   //!
   TBranch        *b_L1_MinimumBiasHF1_XOR_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF2_AND;   //!
   TBranch        *b_L1_MinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_MinimumBiasHF2_OR;   //!
   TBranch        *b_L1_MinimumBiasHF2_OR_Prescl;   //!
   TBranch        *b_L1_MuOpen_NotMinimumBiasHF1_AND;   //!
   TBranch        *b_L1_MuOpen_NotMinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_MuOpen_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_MuOpen_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_MuOpen_NotZdc_AND_BptxAND;   //!
   TBranch        *b_L1_MuOpen_NotZdc_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_NotHFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_NotHFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_NotMinimumBiasHF1_OR;   //!
   TBranch        *b_L1_NotMinimumBiasHF1_OR_Prescl;   //!
   TBranch        *b_L1_NotMinimumBiasHF2_AND;   //!
   TBranch        *b_L1_NotMinimumBiasHF2_AND_Prescl;   //!
   TBranch        *b_L1_NotZdcOR_BptxAND;   //!
   TBranch        *b_L1_NotZdcOR_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG12_BptxAND;   //!
   TBranch        *b_L1_SingleEG12_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG15_BptxAND;   //!
   TBranch        *b_L1_SingleEG15_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG21_BptxAND;   //!
   TBranch        *b_L1_SingleEG21_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG21_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG21_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG21_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG21_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG2_NotZDC_AND_BptxAND;   //!
   TBranch        *b_L1_SingleEG2_NotZDC_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG30_BptxAND;   //!
   TBranch        *b_L1_SingleEG30_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG3_BptxAND;   //!
   TBranch        *b_L1_SingleEG3_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG3_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG3_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG3_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG3_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG5;   //!
   TBranch        *b_L1_SingleEG5_Prescl;   //!
   TBranch        *b_L1_SingleEG5_BptxAND;   //!
   TBranch        *b_L1_SingleEG5_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG5_NotZdc_AND_BptxAND;   //!
   TBranch        *b_L1_SingleEG5_NotZdc_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG7_BptxAND;   //!
   TBranch        *b_L1_SingleEG7_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG7_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG7_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG7_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleEG7_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleIsoEG3_BptxAND;   //!
   TBranch        *b_L1_SingleIsoEG3_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleIsoEG7_BptxAND;   //!
   TBranch        *b_L1_SingleIsoEG7_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu12_BptxAND;   //!
   TBranch        *b_L1_SingleMu12_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu12_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_SingleMu12_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu12_MinimumBiasHF1_AND_BptxAND;   //!
   TBranch        *b_L1_SingleMu12_MinimumBiasHF1_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu12_SingleEG7;   //!
   TBranch        *b_L1_SingleMu12_SingleEG7_Prescl;   //!
   TBranch        *b_L1_SingleMu16_BptxAND;   //!
   TBranch        *b_L1_SingleMu16_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu16_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_SingleMu16_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu16_MinimumBiasHF1_AND_BptxAND;   //!
   TBranch        *b_L1_SingleMu16_MinimumBiasHF1_AND_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu3_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_SingleMu3_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu3_MinimumBiasHF1_AND;   //!
   TBranch        *b_L1_SingleMu3_MinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet28;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet28_Prescl;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet32;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet32_Prescl;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet40;   //!
   TBranch        *b_L1_SingleMu3_SingleCenJet40_Prescl;   //!
   TBranch        *b_L1_SingleMu3_SingleEG12;   //!
   TBranch        *b_L1_SingleMu3_SingleEG12_Prescl;   //!
   TBranch        *b_L1_SingleMu3_SingleEG20;   //!
   TBranch        *b_L1_SingleMu3_SingleEG20_Prescl;   //!
   TBranch        *b_L1_SingleMu5_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_SingleMu5_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu5_MinimumBiasHF1_AND;   //!
   TBranch        *b_L1_SingleMu5_MinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_SingleMu5_SingleEG20;   //!
   TBranch        *b_L1_SingleMu5_SingleEG20_Prescl;   //!
   TBranch        *b_L1_SingleMu7_HFplusANDminusTH0_BptxAND;   //!
   TBranch        *b_L1_SingleMu7_HFplusANDminusTH0_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu7_MinimumBiasHF1_AND;   //!
   TBranch        *b_L1_SingleMu7_MinimumBiasHF1_AND_Prescl;   //!
   TBranch        *b_L1_SingleMu7_SingleEG12;   //!
   TBranch        *b_L1_SingleMu7_SingleEG12_Prescl;   //!
   TBranch        *b_L1_SingleMuOpen;   //!
   TBranch        *b_L1_SingleMuOpen_Prescl;   //!
   TBranch        *b_L1_SingleMuOpen_BptxAND;   //!
   TBranch        *b_L1_SingleMuOpen_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet16_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet16_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet16_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet16_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet16_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet16_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet28_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet28_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet28_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet28_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet28_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet28_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet32_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet32_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet32_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet32_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet32_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet32_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet36_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet36_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet40_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet40_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleJet44_BptxAND;   //!
   TBranch        *b_L1_SingleJet44_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet44_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet44_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet44_Centrality_ext50_100_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet44_Centrality_ext50_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet48_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet48_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet52_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet52_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet56_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet56_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1Jet64_BptxAND;   //!
   TBranch        *b_L1_SingleS1Jet64_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleS1JetC20_NotBptxOR;   //!
   TBranch        *b_L1_SingleS1JetC20_NotBptxOR_Prescl;   //!
   TBranch        *b_L1_SingleS1JetC32_NotBptxOR;   //!
   TBranch        *b_L1_SingleS1JetC32_NotBptxOR_Prescl;   //!
   TBranch        *b_L1_SingleTrack12_BptxAND;   //!
   TBranch        *b_L1_SingleTrack12_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack12_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleTrack12_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack16_BptxAND;   //!
   TBranch        *b_L1_SingleTrack16_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack16_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleTrack16_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack20_BptxAND;   //!
   TBranch        *b_L1_SingleTrack20_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack20_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleTrack20_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack24_BptxAND;   //!
   TBranch        *b_L1_SingleTrack24_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack24_Centrality_ext30_100_BptxAND;   //!
   TBranch        *b_L1_SingleTrack24_Centrality_ext30_100_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleTrack28_BptxAND;   //!
   TBranch        *b_L1_SingleTrack28_BptxAND_Prescl;   //!
   TBranch        *b_L1_TOTEM_1;   //!
   TBranch        *b_L1_TOTEM_1_Prescl;   //!
   TBranch        *b_L1_TOTEM_2;   //!
   TBranch        *b_L1_TOTEM_2_Prescl;   //!
   TBranch        *b_L1_ZdcOR_BptxAND;   //!
   TBranch        *b_L1_ZdcOR_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcXOR_BptxAND;   //!
   TBranch        *b_L1_ZdcXOR_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZeroBias;   //!
   TBranch        *b_L1_ZeroBias_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_PreBPTX_v0;   //!
   TBranch        *b_L1Tech_BPTX_PreBPTX_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit28;   //!
   TBranch        *b_L1Tech_BRIL_bit28_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit29;   //!
   TBranch        *b_L1Tech_BRIL_bit29_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit30;   //!
   TBranch        *b_L1Tech_BRIL_bit30_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit31;   //!
   TBranch        *b_L1Tech_BRIL_bit31_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit32;   //!
   TBranch        *b_L1Tech_BRIL_bit32_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit33;   //!
   TBranch        *b_L1Tech_BRIL_bit33_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit34;   //!
   TBranch        *b_L1Tech_BRIL_bit34_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit35;   //!
   TBranch        *b_L1Tech_BRIL_bit35_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit36;   //!
   TBranch        *b_L1Tech_BRIL_bit36_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit37;   //!
   TBranch        *b_L1Tech_BRIL_bit37_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit38;   //!
   TBranch        *b_L1Tech_BRIL_bit38_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit39;   //!
   TBranch        *b_L1Tech_BRIL_bit39_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit40;   //!
   TBranch        *b_L1Tech_BRIL_bit40_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit41;   //!
   TBranch        *b_L1Tech_BRIL_bit41_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit42;   //!
   TBranch        *b_L1Tech_BRIL_bit42_Prescl;   //!
   TBranch        *b_L1Tech_BRIL_bit43;   //!
   TBranch        *b_L1Tech_BRIL_bit43_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_Gap_v0;   //!
   TBranch        *b_L1Tech_CASTOR_Gap_v0_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_HighJet_v0;   //!
   TBranch        *b_L1Tech_CASTOR_HighJet_v0_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_MediumJet_v0;   //!
   TBranch        *b_L1Tech_CASTOR_MediumJet_v0_Prescl;   //!
   TBranch        *b_L1Tech_DT_GlobalOR_v0;   //!
   TBranch        *b_L1Tech_DT_GlobalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_MMP_or_MPP_v1;   //!
   TBranch        *b_L1Tech_HCAL_HF_MMP_or_MPP_v1_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_coincidence_PM_v2;   //!
   TBranch        *b_L1Tech_HCAL_HF_coincidence_PM_v2_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_single_channel_v0;   //!
   TBranch        *b_L1Tech_HCAL_HF_single_channel_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HO_totalOR_v0;   //!
   TBranch        *b_L1Tech_HCAL_HO_totalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_TOTEM_0;   //!
   TBranch        *b_L1Tech_TOTEM_0_Prescl;   //!
   TBranch        *b_L1Tech_TOTEM_1;   //!
   TBranch        *b_L1Tech_TOTEM_1_Prescl;   //!
   TBranch        *b_L1Tech_TOTEM_2;   //!
   TBranch        *b_L1Tech_TOTEM_2_Prescl;   //!
   TBranch        *b_L1Tech_TOTEM_3;   //!
   TBranch        *b_L1Tech_TOTEM_3_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_minus;   //!
   TBranch        *b_L1Tech_ZDC_minus_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_plus;   //!
   TBranch        *b_L1Tech_ZDC_plus_Prescl;   //!

   hltTreeReader(TTree *tree=0);
   virtual ~hltTreeReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef hltTreeReader_cxx
hltTreeReader::hltTreeReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/phys_diffraction/diphoton/qed_ee/hiforest_noptcut_3-53_invmass_more_var3/0002/hiForest_qedee_4.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/phys_diffraction/diphoton/qed_ee/hiforest_noptcut_3-53_invmass_more_var3/0002/hiForest_qedee_4.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/phys_diffraction/diphoton/qed_ee/hiforest_noptcut_3-53_invmass_more_var3/0002/hiForest_qedee_4.root:/hltanalysis");
      dir->GetObject("HltTree",tree);

   }
   Init(tree);
}

hltTreeReader::~hltTreeReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hltTreeReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hltTreeReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void hltTreeReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("NL1IsolEm", &NL1IsolEm, &b_NL1IsolEm);
   fChain->SetBranchAddress("L1IsolEmEt", L1IsolEmEt, &b_L1IsolEmEt);
   fChain->SetBranchAddress("L1IsolEmE", L1IsolEmE, &b_L1IsolEmE);
   fChain->SetBranchAddress("L1IsolEmEta", L1IsolEmEta, &b_L1IsolEmEta);
   fChain->SetBranchAddress("L1IsolEmPhi", L1IsolEmPhi, &b_L1IsolEmPhi);
   fChain->SetBranchAddress("NL1NIsolEm", &NL1NIsolEm, &b_NL1NIsolEm);
   fChain->SetBranchAddress("L1NIsolEmEt", L1NIsolEmEt, &b_L1NIsolEmEt);
   fChain->SetBranchAddress("L1NIsolEmE", L1NIsolEmE, &b_L1NIsolEmE);
   fChain->SetBranchAddress("L1NIsolEmEta", L1NIsolEmEta, &b_L1NIsolEmEta);
   fChain->SetBranchAddress("L1NIsolEmPhi", L1NIsolEmPhi, &b_L1NIsolEmPhi);
   fChain->SetBranchAddress("NL1Mu", &NL1Mu, &b_NL1Mu);
   fChain->SetBranchAddress("L1MuPt", L1MuPt, &b_L1MuPt);
   fChain->SetBranchAddress("L1MuE", L1MuE, &b_L1MuE);
   fChain->SetBranchAddress("L1MuEta", L1MuEta, &b_L1MuEta);
   fChain->SetBranchAddress("L1MuPhi", L1MuPhi, &b_L1MuPhi);
   fChain->SetBranchAddress("L1MuIsol", L1MuIsol, &b_L1MuIsol);
   fChain->SetBranchAddress("L1MuMip", L1MuMip, &b_L1MuMip);
   fChain->SetBranchAddress("L1MuFor", L1MuFor, &b_L1MuFor);
   fChain->SetBranchAddress("L1MuRPC", L1MuRPC, &b_L1MuRPC);
   fChain->SetBranchAddress("L1MuQal", L1MuQal, &b_L1MuQal);
   fChain->SetBranchAddress("L1MuChg", L1MuChg, &b_L1MuChg);
   fChain->SetBranchAddress("NL1CenJet", &NL1CenJet, &b_NL1CenJet);
   fChain->SetBranchAddress("L1CenJetEt", L1CenJetEt, &b_L1CenJetEt);
   fChain->SetBranchAddress("L1CenJetE", L1CenJetE, &b_L1CenJetE);
   fChain->SetBranchAddress("L1CenJetEta", L1CenJetEta, &b_L1CenJetEta);
   fChain->SetBranchAddress("L1CenJetPhi", L1CenJetPhi, &b_L1CenJetPhi);
   fChain->SetBranchAddress("NL1ForJet", &NL1ForJet, &b_NL1ForJet);
   fChain->SetBranchAddress("L1ForJetEt", L1ForJetEt, &b_L1ForJetEt);
   fChain->SetBranchAddress("L1ForJetE", L1ForJetE, &b_L1ForJetE);
   fChain->SetBranchAddress("L1ForJetEta", L1ForJetEta, &b_L1ForJetEta);
   fChain->SetBranchAddress("L1ForJetPhi", L1ForJetPhi, &b_L1ForJetPhi);
   fChain->SetBranchAddress("NL1Tau", &NL1Tau, &b_NL1Tau);
   fChain->SetBranchAddress("L1TauEt", L1TauEt, &b_L1TauEt);
   fChain->SetBranchAddress("L1TauE", L1TauE, &b_L1TauE);
   fChain->SetBranchAddress("L1TauEta", L1TauEta, &b_L1TauEta);
   fChain->SetBranchAddress("L1TauPhi", L1TauPhi, &b_L1TauPhi);
   fChain->SetBranchAddress("L1Met", &L1Met, &b_L1Met);
   fChain->SetBranchAddress("L1MetPhi", &L1MetPhi, &b_L1MetPhi);
   fChain->SetBranchAddress("L1EtTot", &L1EtTot, &b_L1EtTot);
   fChain->SetBranchAddress("L1Mht", &L1Mht, &b_L1Mht);
   fChain->SetBranchAddress("L1MhtPhi", &L1MhtPhi, &b_L1MhtPhi);
   fChain->SetBranchAddress("L1EtHad", &L1EtHad, &b_L1EtHad);
   fChain->SetBranchAddress("L1HfRing1EtSumPositiveEta", &L1HfRing1EtSumPositiveEta, &b_L1HfRing1EtSumPositiveEta);
   fChain->SetBranchAddress("L1HfRing2EtSumPositiveEta", &L1HfRing2EtSumPositiveEta, &b_L1HfRing2EtSumPositiveEta);
   fChain->SetBranchAddress("L1HfRing1EtSumNegativeEta", &L1HfRing1EtSumNegativeEta, &b_L1HfRing1EtSumNegativeEta);
   fChain->SetBranchAddress("L1HfRing2EtSumNegativeEta", &L1HfRing2EtSumNegativeEta, &b_L1HfRing2EtSumNegativeEta);
   fChain->SetBranchAddress("L1HfTowerCountPositiveEtaRing1", &L1HfTowerCountPositiveEtaRing1, &b_L1HfTowerCountPositiveEtaRing1);
   fChain->SetBranchAddress("L1HfTowerCountNegativeEtaRing1", &L1HfTowerCountNegativeEtaRing1, &b_L1HfTowerCountNegativeEtaRing1);
   fChain->SetBranchAddress("L1HfTowerCountPositiveEtaRing2", &L1HfTowerCountPositiveEtaRing2, &b_L1HfTowerCountPositiveEtaRing2);
   fChain->SetBranchAddress("L1HfTowerCountNegativeEtaRing2", &L1HfTowerCountNegativeEtaRing2, &b_L1HfTowerCountNegativeEtaRing2);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Bx", &Bx, &b_Bx);
   fChain->SetBranchAddress("Orbit", &Orbit, &b_Orbit);
   fChain->SetBranchAddress("AvgInstDelLumi", &AvgInstDelLumi, &b_AvgInstDelLumi);
   fChain->SetBranchAddress("digitisation_step", &digitisation_step, &b_digitisation_step);
   fChain->SetBranchAddress("digitisation_step_Prescl", &digitisation_step_Prescl, &b_digitisation_step_Prescl);
   fChain->SetBranchAddress("L1simulation_step", &L1simulation_step, &b_L1simulation_step);
   fChain->SetBranchAddress("L1simulation_step_Prescl", &L1simulation_step_Prescl, &b_L1simulation_step_Prescl);
   fChain->SetBranchAddress("digi2raw_step", &digi2raw_step, &b_digi2raw_step);
   fChain->SetBranchAddress("digi2raw_step_Prescl", &digi2raw_step_Prescl, &b_digi2raw_step_Prescl);
   fChain->SetBranchAddress("HLTriggerFirstPath", &HLTriggerFirstPath, &b_HLTriggerFirstPath);
   fChain->SetBranchAddress("HLTriggerFirstPath_Prescl", &HLTriggerFirstPath_Prescl, &b_HLTriggerFirstPath_Prescl);
   fChain->SetBranchAddress("DST_Physics_v1", &DST_Physics_v1, &b_DST_Physics_v1);
   fChain->SetBranchAddress("DST_Physics_v1_Prescl", &DST_Physics_v1_Prescl, &b_DST_Physics_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v2", &HLT_HIPuAK4CaloJet40_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet40_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v2", &HLT_HIPuAK4CaloJet60_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet60_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v2", &HLT_HIPuAK4CaloJet80_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet80_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v2", &HLT_HIPuAK4CaloJet100_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet100_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet110_Eta5p1_v2", &HLT_HIPuAK4CaloJet110_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet110_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet110_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet110_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet110_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120_Eta5p1_v2", &HLT_HIPuAK4CaloJet120_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet120_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet120_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet120_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet150_Eta5p1_v2", &HLT_HIPuAK4CaloJet150_Eta5p1_v2, &b_HLT_HIPuAK4CaloJet150_Eta5p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet150_Eta5p1_v2_Prescl", &HLT_HIPuAK4CaloJet150_Eta5p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet150_Eta5p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2", &HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2_Prescl", &HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2", &HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2_Prescl", &HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2", &HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2_Prescl", &HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2", &HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2_Prescl", &HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2_Prescl, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2", &HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2, &b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet60_Eta2p1_v2", &HLT_HIPuAK4CaloDJet60_Eta2p1_v2, &b_HLT_HIPuAK4CaloDJet60_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet60_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloDJet60_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloDJet60_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet80_Eta2p1_v2", &HLT_HIPuAK4CaloDJet80_Eta2p1_v2, &b_HLT_HIPuAK4CaloDJet80_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet80_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloDJet80_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloDJet80_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2", &HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2, &b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2", &HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2, &b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2", &HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2, &b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2", &HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2, &b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2_Prescl", &HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2_Prescl, &b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_v2", &HLT_HIDmesonHITrackingGlobal_Dpt20_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_v2", &HLT_HIDmesonHITrackingGlobal_Dpt30_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_v2", &HLT_HIDmesonHITrackingGlobal_Dpt40_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt50_v2", &HLT_HIDmesonHITrackingGlobal_Dpt50_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt50_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt50_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt50_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt50_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_v2", &HLT_HIDmesonHITrackingGlobal_Dpt60_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt70_v2", &HLT_HIDmesonHITrackingGlobal_Dpt70_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt70_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt70_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt70_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt70_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_v2", &HLT_HISinglePhoton10_Eta1p5_v2, &b_HLT_HISinglePhoton10_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_v2_Prescl", &HLT_HISinglePhoton10_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_v2", &HLT_HISinglePhoton15_Eta1p5_v2, &b_HLT_HISinglePhoton15_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_v2_Prescl", &HLT_HISinglePhoton15_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_v2", &HLT_HISinglePhoton20_Eta1p5_v2, &b_HLT_HISinglePhoton20_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_v2_Prescl", &HLT_HISinglePhoton20_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_v2", &HLT_HISinglePhoton30_Eta1p5_v2, &b_HLT_HISinglePhoton30_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_v2_Prescl", &HLT_HISinglePhoton30_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v2", &HLT_HISinglePhoton40_Eta1p5_v2, &b_HLT_HISinglePhoton40_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v2_Prescl", &HLT_HISinglePhoton40_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta1p5_v2", &HLT_HISinglePhoton50_Eta1p5_v2, &b_HLT_HISinglePhoton50_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta1p5_v2_Prescl", &HLT_HISinglePhoton50_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton50_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta1p5_v2", &HLT_HISinglePhoton60_Eta1p5_v2, &b_HLT_HISinglePhoton60_Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta1p5_v2_Prescl", &HLT_HISinglePhoton60_Eta1p5_v2_Prescl, &b_HLT_HISinglePhoton60_Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2", &HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2, &b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2_Prescl", &HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2", &HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2, &b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2_Prescl", &HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2", &HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2, &b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2_Prescl", &HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2", &HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2, &b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2_Prescl", &HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2", &HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2, &b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2_Prescl", &HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2", &HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2, &b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2_Prescl", &HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2", &HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2, &b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2_Prescl", &HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2", &HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2, &b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2_Prescl", &HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2", &HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2, &b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2_Prescl", &HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2", &HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2, &b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2_Prescl", &HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta2p1_v2", &HLT_HISinglePhoton40_Eta2p1_v2, &b_HLT_HISinglePhoton40_Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta2p1_v2_Prescl", &HLT_HISinglePhoton40_Eta2p1_v2_Prescl, &b_HLT_HISinglePhoton40_Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_v2", &HLT_HISinglePhoton10_Eta3p1_v2, &b_HLT_HISinglePhoton10_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_v2_Prescl", &HLT_HISinglePhoton10_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_v2", &HLT_HISinglePhoton15_Eta3p1_v2, &b_HLT_HISinglePhoton15_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_v2_Prescl", &HLT_HISinglePhoton15_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_v2", &HLT_HISinglePhoton20_Eta3p1_v2, &b_HLT_HISinglePhoton20_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_v2_Prescl", &HLT_HISinglePhoton20_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_v2", &HLT_HISinglePhoton30_Eta3p1_v2, &b_HLT_HISinglePhoton30_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_v2_Prescl", &HLT_HISinglePhoton30_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_v2", &HLT_HISinglePhoton40_Eta3p1_v2, &b_HLT_HISinglePhoton40_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_v2_Prescl", &HLT_HISinglePhoton40_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta3p1_v2", &HLT_HISinglePhoton50_Eta3p1_v2, &b_HLT_HISinglePhoton50_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta3p1_v2_Prescl", &HLT_HISinglePhoton50_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton50_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta3p1_v2", &HLT_HISinglePhoton60_Eta3p1_v2, &b_HLT_HISinglePhoton60_Eta3p1_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta3p1_v2_Prescl", &HLT_HISinglePhoton60_Eta3p1_v2_Prescl, &b_HLT_HISinglePhoton60_Eta3p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2", &HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2, &b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2_Prescl", &HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2", &HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2, &b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2_Prescl", &HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2", &HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2, &b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2_Prescl", &HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2", &HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2, &b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2_Prescl", &HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2", &HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2, &b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2_Prescl", &HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2", &HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2, &b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2_Prescl", &HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2", &HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2, &b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2_Prescl", &HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2", &HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2, &b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2_Prescl", &HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2", &HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2, &b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2_Prescl", &HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2", &HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2, &b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2_Prescl", &HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2_Prescl", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2_Prescl, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2_Prescl", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2_Prescl, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2", &HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2, &b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2_Prescl", &HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2_Prescl, &b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2", &HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2, &b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2_Prescl", &HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2_Prescl, &b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2", &HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2, &b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2", &HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2, &b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2", &HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2, &b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2", &HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2, &b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2", &HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2, &b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC100_v2", &HLT_HIUCC100_v2, &b_HLT_HIUCC100_v2);
   fChain->SetBranchAddress("HLT_HIUCC100_v2_Prescl", &HLT_HIUCC100_v2_Prescl, &b_HLT_HIUCC100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC020_v2", &HLT_HIUCC020_v2, &b_HLT_HIUCC020_v2);
   fChain->SetBranchAddress("HLT_HIUCC020_v2_Prescl", &HLT_HIUCC020_v2_Prescl, &b_HLT_HIUCC020_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v2", &HLT_HIQ2Bottom005_Centrality1030_v2, &b_HLT_HIQ2Bottom005_Centrality1030_v2);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v2_Prescl", &HLT_HIQ2Bottom005_Centrality1030_v2_Prescl, &b_HLT_HIQ2Bottom005_Centrality1030_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v2", &HLT_HIQ2Top005_Centrality1030_v2, &b_HLT_HIQ2Top005_Centrality1030_v2);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v2_Prescl", &HLT_HIQ2Top005_Centrality1030_v2_Prescl, &b_HLT_HIQ2Top005_Centrality1030_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v2", &HLT_HIQ2Bottom005_Centrality3050_v2, &b_HLT_HIQ2Bottom005_Centrality3050_v2);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v2_Prescl", &HLT_HIQ2Bottom005_Centrality3050_v2_Prescl, &b_HLT_HIQ2Bottom005_Centrality3050_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v2", &HLT_HIQ2Top005_Centrality3050_v2, &b_HLT_HIQ2Top005_Centrality3050_v2);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v2_Prescl", &HLT_HIQ2Top005_Centrality3050_v2_Prescl, &b_HLT_HIQ2Top005_Centrality3050_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v2", &HLT_HIQ2Bottom005_Centrality5070_v2, &b_HLT_HIQ2Bottom005_Centrality5070_v2);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v2_Prescl", &HLT_HIQ2Bottom005_Centrality5070_v2_Prescl, &b_HLT_HIQ2Bottom005_Centrality5070_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v2", &HLT_HIQ2Top005_Centrality5070_v2, &b_HLT_HIQ2Top005_Centrality5070_v2);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v2_Prescl", &HLT_HIQ2Top005_Centrality5070_v2_Prescl, &b_HLT_HIQ2Top005_Centrality5070_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2", &HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2, &b_HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2_Prescl", &HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2_Prescl, &b_HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality010_v2", &HLT_HIFullTrack12_L1Centrality010_v2, &b_HLT_HIFullTrack12_L1Centrality010_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality010_v2_Prescl", &HLT_HIFullTrack12_L1Centrality010_v2_Prescl, &b_HLT_HIFullTrack12_L1Centrality010_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality30100_v2", &HLT_HIFullTrack12_L1Centrality30100_v2, &b_HLT_HIFullTrack12_L1Centrality30100_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality30100_v2_Prescl", &HLT_HIFullTrack12_L1Centrality30100_v2_Prescl, &b_HLT_HIFullTrack12_L1Centrality30100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2", &HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2, &b_HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2_Prescl", &HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2_Prescl, &b_HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality010_v2", &HLT_HIFullTrack18_L1Centrality010_v2, &b_HLT_HIFullTrack18_L1Centrality010_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality010_v2_Prescl", &HLT_HIFullTrack18_L1Centrality010_v2_Prescl, &b_HLT_HIFullTrack18_L1Centrality010_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality30100_v2", &HLT_HIFullTrack18_L1Centrality30100_v2, &b_HLT_HIFullTrack18_L1Centrality30100_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality30100_v2_Prescl", &HLT_HIFullTrack18_L1Centrality30100_v2_Prescl, &b_HLT_HIFullTrack18_L1Centrality30100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack24_v2", &HLT_HIFullTrack24_v2, &b_HLT_HIFullTrack24_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack24_v2_Prescl", &HLT_HIFullTrack24_v2_Prescl, &b_HLT_HIFullTrack24_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack24_L1Centrality30100_v2", &HLT_HIFullTrack24_L1Centrality30100_v2, &b_HLT_HIFullTrack24_L1Centrality30100_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack24_L1Centrality30100_v2_Prescl", &HLT_HIFullTrack24_L1Centrality30100_v2_Prescl, &b_HLT_HIFullTrack24_L1Centrality30100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack34_v2", &HLT_HIFullTrack34_v2, &b_HLT_HIFullTrack34_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack34_v2_Prescl", &HLT_HIFullTrack34_v2_Prescl, &b_HLT_HIFullTrack34_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack34_L1Centrality30100_v2", &HLT_HIFullTrack34_L1Centrality30100_v2, &b_HLT_HIFullTrack34_L1Centrality30100_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack34_L1Centrality30100_v2_Prescl", &HLT_HIFullTrack34_L1Centrality30100_v2_Prescl, &b_HLT_HIFullTrack34_L1Centrality30100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack45_v2", &HLT_HIFullTrack45_v2, &b_HLT_HIFullTrack45_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack45_v2_Prescl", &HLT_HIFullTrack45_v2_Prescl, &b_HLT_HIFullTrack45_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack45_L1Centrality30100_v2", &HLT_HIFullTrack45_L1Centrality30100_v2, &b_HLT_HIFullTrack45_L1Centrality30100_v2);
   fChain->SetBranchAddress("HLT_HIFullTrack45_L1Centrality30100_v2_Prescl", &HLT_HIFullTrack45_L1Centrality30100_v2_Prescl, &b_HLT_HIFullTrack45_L1Centrality30100_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_v1", &HLT_HIL1DoubleMu0_v1, &b_HLT_HIL1DoubleMu0_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_v1_Prescl", &HLT_HIL1DoubleMu0_v1_Prescl, &b_HLT_HIL1DoubleMu0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF_v1", &HLT_HIL1DoubleMu0_2HF_v1, &b_HLT_HIL1DoubleMu0_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF_v1_Prescl", &HLT_HIL1DoubleMu0_2HF_v1_Prescl, &b_HLT_HIL1DoubleMu0_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF0_v1", &HLT_HIL1DoubleMu0_2HF0_v1, &b_HLT_HIL1DoubleMu0_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF0_v1_Prescl", &HLT_HIL1DoubleMu0_2HF0_v1_Prescl, &b_HLT_HIL1DoubleMu0_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu10_v1", &HLT_HIL1DoubleMu10_v1, &b_HLT_HIL1DoubleMu10_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu10_v1_Prescl", &HLT_HIL1DoubleMu10_v1_Prescl, &b_HLT_HIL1DoubleMu10_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v2", &HLT_HIL2DoubleMu0_NHitQ_v2, &b_HLT_HIL2DoubleMu0_NHitQ_v2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v2_Prescl", &HLT_HIL2DoubleMu0_NHitQ_v2_Prescl, &b_HLT_HIL2DoubleMu0_NHitQ_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_2HF_v1", &HLT_HIL2DoubleMu0_NHitQ_2HF_v1, &b_HLT_HIL2DoubleMu0_NHitQ_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_2HF_v1_Prescl", &HLT_HIL2DoubleMu0_NHitQ_2HF_v1_Prescl, &b_HLT_HIL2DoubleMu0_NHitQ_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_2HF0_v1", &HLT_HIL2DoubleMu0_NHitQ_2HF0_v1, &b_HLT_HIL2DoubleMu0_NHitQ_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_2HF0_v1_Prescl", &HLT_HIL2DoubleMu0_NHitQ_2HF0_v1_Prescl, &b_HLT_HIL2DoubleMu0_NHitQ_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3_NHitQ10_2HF_v1", &HLT_HIL2Mu3_NHitQ10_2HF_v1, &b_HLT_HIL2Mu3_NHitQ10_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3_NHitQ10_2HF_v1_Prescl", &HLT_HIL2Mu3_NHitQ10_2HF_v1_Prescl, &b_HLT_HIL2Mu3_NHitQ10_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3_NHitQ10_2HF0_v1", &HLT_HIL2Mu3_NHitQ10_2HF0_v1, &b_HLT_HIL2Mu3_NHitQ10_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3_NHitQ10_2HF0_v1_Prescl", &HLT_HIL2Mu3_NHitQ10_2HF0_v1_Prescl, &b_HLT_HIL2Mu3_NHitQ10_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu3_NHitQ15_2HF_v1", &HLT_HIL3Mu3_NHitQ15_2HF_v1, &b_HLT_HIL3Mu3_NHitQ15_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3_NHitQ15_2HF_v1_Prescl", &HLT_HIL3Mu3_NHitQ15_2HF_v1_Prescl, &b_HLT_HIL3Mu3_NHitQ15_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu3_NHitQ15_2HF0_v1", &HLT_HIL3Mu3_NHitQ15_2HF0_v1, &b_HLT_HIL3Mu3_NHitQ15_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3_NHitQ15_2HF0_v1_Prescl", &HLT_HIL3Mu3_NHitQ15_2HF0_v1_Prescl, &b_HLT_HIL3Mu3_NHitQ15_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu5_NHitQ10_2HF_v1", &HLT_HIL2Mu5_NHitQ10_2HF_v1, &b_HLT_HIL2Mu5_NHitQ10_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu5_NHitQ10_2HF_v1_Prescl", &HLT_HIL2Mu5_NHitQ10_2HF_v1_Prescl, &b_HLT_HIL2Mu5_NHitQ10_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu5_NHitQ10_2HF0_v1", &HLT_HIL2Mu5_NHitQ10_2HF0_v1, &b_HLT_HIL2Mu5_NHitQ10_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu5_NHitQ10_2HF0_v1_Prescl", &HLT_HIL2Mu5_NHitQ10_2HF0_v1_Prescl, &b_HLT_HIL2Mu5_NHitQ10_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu5_NHitQ15_2HF_v1", &HLT_HIL3Mu5_NHitQ15_2HF_v1, &b_HLT_HIL3Mu5_NHitQ15_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu5_NHitQ15_2HF_v1_Prescl", &HLT_HIL3Mu5_NHitQ15_2HF_v1_Prescl, &b_HLT_HIL3Mu5_NHitQ15_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu5_NHitQ15_2HF0_v1", &HLT_HIL3Mu5_NHitQ15_2HF0_v1, &b_HLT_HIL3Mu5_NHitQ15_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu5_NHitQ15_2HF0_v1_Prescl", &HLT_HIL3Mu5_NHitQ15_2HF0_v1_Prescl, &b_HLT_HIL3Mu5_NHitQ15_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu7_NHitQ10_2HF_v1", &HLT_HIL2Mu7_NHitQ10_2HF_v1, &b_HLT_HIL2Mu7_NHitQ10_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu7_NHitQ10_2HF_v1_Prescl", &HLT_HIL2Mu7_NHitQ10_2HF_v1_Prescl, &b_HLT_HIL2Mu7_NHitQ10_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu7_NHitQ10_2HF0_v1", &HLT_HIL2Mu7_NHitQ10_2HF0_v1, &b_HLT_HIL2Mu7_NHitQ10_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu7_NHitQ10_2HF0_v1_Prescl", &HLT_HIL2Mu7_NHitQ10_2HF0_v1_Prescl, &b_HLT_HIL2Mu7_NHitQ10_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu7_NHitQ15_2HF_v1", &HLT_HIL3Mu7_NHitQ15_2HF_v1, &b_HLT_HIL3Mu7_NHitQ15_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu7_NHitQ15_2HF_v1_Prescl", &HLT_HIL3Mu7_NHitQ15_2HF_v1_Prescl, &b_HLT_HIL3Mu7_NHitQ15_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu7_NHitQ15_2HF0_v1", &HLT_HIL3Mu7_NHitQ15_2HF0_v1, &b_HLT_HIL3Mu7_NHitQ15_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu7_NHitQ15_2HF0_v1_Prescl", &HLT_HIL3Mu7_NHitQ15_2HF0_v1_Prescl, &b_HLT_HIL3Mu7_NHitQ15_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v2", &HLT_HIL2Mu15_v2, &b_HLT_HIL2Mu15_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v2_Prescl", &HLT_HIL2Mu15_v2_Prescl, &b_HLT_HIL2Mu15_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu15_2HF_v1", &HLT_HIL2Mu15_2HF_v1, &b_HLT_HIL2Mu15_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu15_2HF_v1_Prescl", &HLT_HIL2Mu15_2HF_v1_Prescl, &b_HLT_HIL2Mu15_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu15_2HF0_v1", &HLT_HIL2Mu15_2HF0_v1, &b_HLT_HIL2Mu15_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu15_2HF0_v1_Prescl", &HLT_HIL2Mu15_2HF0_v1_Prescl, &b_HLT_HIL2Mu15_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu15_v1", &HLT_HIL3Mu15_v1, &b_HLT_HIL3Mu15_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu15_v1_Prescl", &HLT_HIL3Mu15_v1_Prescl, &b_HLT_HIL3Mu15_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu15_2HF_v1", &HLT_HIL3Mu15_2HF_v1, &b_HLT_HIL3Mu15_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu15_2HF_v1_Prescl", &HLT_HIL3Mu15_2HF_v1_Prescl, &b_HLT_HIL3Mu15_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu15_2HF0_v1", &HLT_HIL3Mu15_2HF0_v1, &b_HLT_HIL3Mu15_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu15_2HF0_v1_Prescl", &HLT_HIL3Mu15_2HF0_v1_Prescl, &b_HLT_HIL3Mu15_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu20_v1", &HLT_HIL2Mu20_v1, &b_HLT_HIL2Mu20_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu20_v1_Prescl", &HLT_HIL2Mu20_v1_Prescl, &b_HLT_HIL2Mu20_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu20_2HF_v1", &HLT_HIL2Mu20_2HF_v1, &b_HLT_HIL2Mu20_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu20_2HF_v1_Prescl", &HLT_HIL2Mu20_2HF_v1_Prescl, &b_HLT_HIL2Mu20_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu20_2HF0_v1", &HLT_HIL2Mu20_2HF0_v1, &b_HLT_HIL2Mu20_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu20_2HF0_v1_Prescl", &HLT_HIL2Mu20_2HF0_v1_Prescl, &b_HLT_HIL2Mu20_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu20_v1", &HLT_HIL3Mu20_v1, &b_HLT_HIL3Mu20_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu20_v1_Prescl", &HLT_HIL3Mu20_v1_Prescl, &b_HLT_HIL3Mu20_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu20_2HF_v1", &HLT_HIL3Mu20_2HF_v1, &b_HLT_HIL3Mu20_2HF_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu20_2HF_v1_Prescl", &HLT_HIL3Mu20_2HF_v1_Prescl, &b_HLT_HIL3Mu20_2HF_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu20_2HF0_v1", &HLT_HIL3Mu20_2HF0_v1, &b_HLT_HIL3Mu20_2HF0_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu20_2HF0_v1_Prescl", &HLT_HIL3Mu20_2HF0_v1_Prescl, &b_HLT_HIL3Mu20_2HF0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF_Cent30100_v1", &HLT_HIL1DoubleMu0_2HF_Cent30100_v1, &b_HLT_HIL1DoubleMu0_2HF_Cent30100_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF_Cent30100_v1_Prescl", &HLT_HIL1DoubleMu0_2HF_Cent30100_v1_Prescl, &b_HLT_HIL1DoubleMu0_2HF_Cent30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF0_Cent30100_v1", &HLT_HIL1DoubleMu0_2HF0_Cent30100_v1, &b_HLT_HIL1DoubleMu0_2HF0_Cent30100_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_2HF0_Cent30100_v1_Prescl", &HLT_HIL1DoubleMu0_2HF0_Cent30100_v1_Prescl, &b_HLT_HIL1DoubleMu0_2HF0_Cent30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1", &HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1, &b_HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1_Prescl", &HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1_Prescl, &b_HLT_HIL2DoubleMu0_2HF_Cent30100_NHitQ_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_Cent30_v1", &HLT_HIL1DoubleMu0_Cent30_v1, &b_HLT_HIL1DoubleMu0_Cent30_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_Cent30_v1_Prescl", &HLT_HIL1DoubleMu0_Cent30_v1_Prescl, &b_HLT_HIL1DoubleMu0_Cent30_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1", &HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1, &b_HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1_Prescl", &HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1_Prescl, &b_HLT_HIL2DoubleMu0_2HF0_Cent30100_NHitQ_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1", &HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1, &b_HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1_Prescl", &HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1_Prescl, &b_HLT_HIL2DoubleMu0_Cent30_OS_NHitQ_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_Cent30_NHitQ_v1", &HLT_HIL2DoubleMu0_Cent30_NHitQ_v1, &b_HLT_HIL2DoubleMu0_Cent30_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_Cent30_NHitQ_v1_Prescl", &HLT_HIL2DoubleMu0_Cent30_NHitQ_v1_Prescl, &b_HLT_HIL2DoubleMu0_Cent30_NHitQ_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_v1", &HLT_HIL3DoubleMu0_Cent30_v1, &b_HLT_HIL3DoubleMu0_Cent30_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_v1_Prescl", &HLT_HIL3DoubleMu0_Cent30_v1_Prescl, &b_HLT_HIL3DoubleMu0_Cent30_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1", &HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1, &b_HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1_Prescl", &HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1_Prescl, &b_HLT_HIL3DoubleMu0_Cent30_OS_m2p5to4p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1", &HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1, &b_HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1_Prescl", &HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1_Prescl, &b_HLT_HIL3DoubleMu0_Cent30_OS_m7to14_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1", &HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1, &b_HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1_Prescl", &HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1_Prescl, &b_HLT_HIL3DoubleMu0_OS_m2p5to4p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_OS_m7to14_v1", &HLT_HIL3DoubleMu0_OS_m7to14_v1, &b_HLT_HIL3DoubleMu0_OS_m7to14_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMu0_OS_m7to14_v1_Prescl", &HLT_HIL3DoubleMu0_OS_m7to14_v1_Prescl, &b_HLT_HIL3DoubleMu0_OS_m7to14_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleMuOpenNotHF2_v1", &HLT_HIUPCL1SingleMuOpenNotHF2_v1, &b_HLT_HIUPCL1SingleMuOpenNotHF2_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleMuOpenNotHF2_v1_Prescl", &HLT_HIUPCL1SingleMuOpenNotHF2_v1_Prescl, &b_HLT_HIUPCL1SingleMuOpenNotHF2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1", &HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1, &b_HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCSingleMuNotHF2Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHF2_v1", &HLT_HIUPCL1DoubleMuOpenNotHF2_v1, &b_HLT_HIUPCL1DoubleMuOpenNotHF2_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHF2_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHF2_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHF2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1", &HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1, &b_HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCDoubleMuNotHF2Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleEG2NotHF2_v1", &HLT_HIUPCL1SingleEG2NotHF2_v1, &b_HLT_HIUPCL1SingleEG2NotHF2_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleEG2NotHF2_v1_Prescl", &HLT_HIUPCL1SingleEG2NotHF2_v1_Prescl, &b_HLT_HIUPCL1SingleEG2NotHF2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1", &HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1, &b_HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCSingleEG2NotHF2Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotHF2_v1", &HLT_HIUPCL1DoubleEG2NotHF2_v1, &b_HLT_HIUPCL1DoubleEG2NotHF2_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotHF2_v1_Prescl", &HLT_HIUPCL1DoubleEG2NotHF2_v1_Prescl, &b_HLT_HIUPCL1DoubleEG2NotHF2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1", &HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1, &b_HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCDoubleEG2NotHF2Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleEG5NotHF2_v1", &HLT_HIUPCL1SingleEG5NotHF2_v1, &b_HLT_HIUPCL1SingleEG5NotHF2_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1SingleEG5NotHF2_v1_Prescl", &HLT_HIUPCL1SingleEG5NotHF2_v1_Prescl, &b_HLT_HIUPCL1SingleEG5NotHF2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1", &HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1, &b_HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHF1_v1", &HLT_HIUPCL1DoubleMuOpenNotHF1_v1, &b_HLT_HIUPCL1DoubleMuOpenNotHF1_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHF1_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHF1_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHF1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1", &HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1, &b_HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCDoubleMuNotHF1Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotZDCAND_v1", &HLT_HIUPCL1DoubleEG2NotZDCAND_v1, &b_HLT_HIUPCL1DoubleEG2NotZDCAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotZDCAND_v1_Prescl", &HLT_HIUPCL1DoubleEG2NotZDCAND_v1_Prescl, &b_HLT_HIUPCL1DoubleEG2NotZDCAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1", &HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1DoubleEG2NotZDCANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1", &HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1, &b_HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotZDCAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1", &HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotZDCANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1EG2NotZDCAND_v1", &HLT_HIUPCL1EG2NotZDCAND_v1, &b_HLT_HIUPCL1EG2NotZDCAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1EG2NotZDCAND_v1_Prescl", &HLT_HIUPCL1EG2NotZDCAND_v1_Prescl, &b_HLT_HIUPCL1EG2NotZDCAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1", &HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1, &b_HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCEG2NotZDCANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1MuOpenNotZDCAND_v1", &HLT_HIUPCL1MuOpenNotZDCAND_v1, &b_HLT_HIUPCL1MuOpenNotZDCAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1MuOpenNotZDCAND_v1_Prescl", &HLT_HIUPCL1MuOpenNotZDCAND_v1_Prescl, &b_HLT_HIUPCL1MuOpenNotZDCAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1", &HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1MuOpenNotZDCANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1", &HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1, &b_HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1_Prescl", &HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1_Prescl, &b_HLT_HIUPCL1NotHFplusANDminusTH0BptxAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1", &HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1NotHFplusANDminusTH0BptxANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2_Prescl", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2_Prescl, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJet_v1", &HLT_HIL1CastorMediumJet_v1, &b_HLT_HIL1CastorMediumJet_v1);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJet_v1_Prescl", &HLT_HIL1CastorMediumJet_v1_Prescl, &b_HLT_HIL1CastorMediumJet_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJetAK4CaloJet20_v2", &HLT_HIL1CastorMediumJetAK4CaloJet20_v2, &b_HLT_HIL1CastorMediumJetAK4CaloJet20_v2);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJetAK4CaloJet20_v2_Prescl", &HLT_HIL1CastorMediumJetAK4CaloJet20_v2_Prescl, &b_HLT_HIL1CastorMediumJetAK4CaloJet20_v2_Prescl);
   fChain->SetBranchAddress("HLT_HICastorMediumJetPixel_SingleTrack_v1", &HLT_HICastorMediumJetPixel_SingleTrack_v1, &b_HLT_HICastorMediumJetPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HICastorMediumJetPixel_SingleTrack_v1_Prescl", &HLT_HICastorMediumJetPixel_SingleTrack_v1_Prescl, &b_HLT_HICastorMediumJetPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotMinimumBiasHF2_AND_v1", &HLT_HIUPCL1NotMinimumBiasHF2_AND_v1, &b_HLT_HIUPCL1NotMinimumBiasHF2_AND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotMinimumBiasHF2_AND_v1_Prescl", &HLT_HIUPCL1NotMinimumBiasHF2_AND_v1_Prescl, &b_HLT_HIUPCL1NotMinimumBiasHF2_AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1", &HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1NotMinimumBiasHF2_ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcOR_BptxAND_v1", &HLT_HIUPCL1ZdcOR_BptxAND_v1, &b_HLT_HIUPCL1ZdcOR_BptxAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcOR_BptxAND_v1_Prescl", &HLT_HIUPCL1ZdcOR_BptxAND_v1_Prescl, &b_HLT_HIUPCL1ZdcOR_BptxAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1", &HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1ZdcOR_BptxANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcXOR_BptxAND_v1", &HLT_HIUPCL1ZdcXOR_BptxAND_v1, &b_HLT_HIUPCL1ZdcXOR_BptxAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcXOR_BptxAND_v1_Prescl", &HLT_HIUPCL1ZdcXOR_BptxAND_v1_Prescl, &b_HLT_HIUPCL1ZdcXOR_BptxAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1", &HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1ZdcXOR_BptxANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotZdcOR_BptxAND_v1", &HLT_HIUPCL1NotZdcOR_BptxAND_v1, &b_HLT_HIUPCL1NotZdcOR_BptxAND_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotZdcOR_BptxAND_v1_Prescl", &HLT_HIUPCL1NotZdcOR_BptxAND_v1_Prescl, &b_HLT_HIUPCL1NotZdcOR_BptxAND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1", &HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1, &b_HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1NotZdcOR_BptxANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIZeroBias_v1", &HLT_HIZeroBias_v1, &b_HLT_HIZeroBias_v1);
   fChain->SetBranchAddress("HLT_HIZeroBias_v1_Prescl", &HLT_HIZeroBias_v1_Prescl, &b_HLT_HIZeroBias_v1_Prescl);
   fChain->SetBranchAddress("HLT_HICentralityVeto_v1", &HLT_HICentralityVeto_v1, &b_HLT_HICentralityVeto_v1);
   fChain->SetBranchAddress("HLT_HICentralityVeto_v1_Prescl", &HLT_HICentralityVeto_v1_Prescl, &b_HLT_HICentralityVeto_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Tech5_BPTX_PlusOnly_v1", &HLT_HIL1Tech5_BPTX_PlusOnly_v1, &b_HLT_HIL1Tech5_BPTX_PlusOnly_v1);
   fChain->SetBranchAddress("HLT_HIL1Tech5_BPTX_PlusOnly_v1_Prescl", &HLT_HIL1Tech5_BPTX_PlusOnly_v1_Prescl, &b_HLT_HIL1Tech5_BPTX_PlusOnly_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Tech6_BPTX_MinusOnly_v1", &HLT_HIL1Tech6_BPTX_MinusOnly_v1, &b_HLT_HIL1Tech6_BPTX_MinusOnly_v1);
   fChain->SetBranchAddress("HLT_HIL1Tech6_BPTX_MinusOnly_v1_Prescl", &HLT_HIL1Tech6_BPTX_MinusOnly_v1_Prescl, &b_HLT_HIL1Tech6_BPTX_MinusOnly_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Tech7_NoBPTX_v1", &HLT_HIL1Tech7_NoBPTX_v1, &b_HLT_HIL1Tech7_NoBPTX_v1);
   fChain->SetBranchAddress("HLT_HIL1Tech7_NoBPTX_v1_Prescl", &HLT_HIL1Tech7_NoBPTX_v1_Prescl, &b_HLT_HIL1Tech7_NoBPTX_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1OR_v1", &HLT_HIL1MinimumBiasHF1OR_v1, &b_HLT_HIL1MinimumBiasHF1OR_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1OR_v1_Prescl", &HLT_HIL1MinimumBiasHF1OR_v1_Prescl, &b_HLT_HIL1MinimumBiasHF1OR_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2OR_v1", &HLT_HIL1MinimumBiasHF2OR_v1, &b_HLT_HIL1MinimumBiasHF2OR_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2OR_v1_Prescl", &HLT_HIL1MinimumBiasHF2OR_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2OR_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1AND_v1", &HLT_HIL1MinimumBiasHF1AND_v1, &b_HLT_HIL1MinimumBiasHF1AND_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1AND_v1_Prescl", &HLT_HIL1MinimumBiasHF1AND_v1_Prescl, &b_HLT_HIL1MinimumBiasHF1AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_v1", &HLT_HIL1MinimumBiasHF2AND_v1, &b_HLT_HIL1MinimumBiasHF2AND_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1", &HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1, &b_HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1_Prescl", &HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIZeroBiasPixel_SingleTrack_v1", &HLT_HIZeroBiasPixel_SingleTrack_v1, &b_HLT_HIZeroBiasPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIZeroBiasPixel_SingleTrack_v1_Prescl", &HLT_HIZeroBiasPixel_SingleTrack_v1_Prescl, &b_HLT_HIZeroBiasPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1", &HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1, &b_HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1_Prescl", &HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1_Prescl, &b_HLT_HIL1Centralityext70100MinimumumBiasHF1AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1", &HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1, &b_HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl", &HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIL1Centralityext70100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1", &HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1, &b_HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1_Prescl", &HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1_Prescl, &b_HLT_HIL1Centralityext50100MinimumumBiasHF1AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1", &HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1, &b_HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl", &HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIL1Centralityext50100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF1AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF1ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPhysics_v1", &HLT_HIPhysics_v1, &b_HLT_HIPhysics_v1);
   fChain->SetBranchAddress("HLT_HIPhysics_v1_Prescl", &HLT_HIPhysics_v1_Prescl, &b_HLT_HIPhysics_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIRandom_v1", &HLT_HIRandom_v1, &b_HLT_HIRandom_v1);
   fChain->SetBranchAddress("HLT_HIRandom_v1_Prescl", &HLT_HIRandom_v1_Prescl, &b_HLT_HIRandom_v1_Prescl);
   fChain->SetBranchAddress("HLT_EcalCalibration_v2", &HLT_EcalCalibration_v2, &b_HLT_EcalCalibration_v2);
   fChain->SetBranchAddress("HLT_EcalCalibration_v2_Prescl", &HLT_EcalCalibration_v2_Prescl, &b_HLT_EcalCalibration_v2_Prescl);
   fChain->SetBranchAddress("HLT_HcalCalibration_v1", &HLT_HcalCalibration_v1, &b_HLT_HcalCalibration_v1);
   fChain->SetBranchAddress("HLT_HcalCalibration_v1_Prescl", &HLT_HcalCalibration_v1_Prescl, &b_HLT_HcalCalibration_v1_Prescl);
   fChain->SetBranchAddress("AlCa_EcalPhiSymForHI_v2", &AlCa_EcalPhiSymForHI_v2, &b_AlCa_EcalPhiSymForHI_v2);
   fChain->SetBranchAddress("AlCa_EcalPhiSymForHI_v2_Prescl", &AlCa_EcalPhiSymForHI_v2_Prescl, &b_AlCa_EcalPhiSymForHI_v2_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNoTriggersForHI_v1", &AlCa_RPCMuonNoTriggersForHI_v1, &b_AlCa_RPCMuonNoTriggersForHI_v1);
   fChain->SetBranchAddress("AlCa_RPCMuonNoTriggersForHI_v1_Prescl", &AlCa_RPCMuonNoTriggersForHI_v1_Prescl, &b_AlCa_RPCMuonNoTriggersForHI_v1_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNoHitsForHI_v1", &AlCa_RPCMuonNoHitsForHI_v1, &b_AlCa_RPCMuonNoHitsForHI_v1);
   fChain->SetBranchAddress("AlCa_RPCMuonNoHitsForHI_v1_Prescl", &AlCa_RPCMuonNoHitsForHI_v1_Prescl, &b_AlCa_RPCMuonNoHitsForHI_v1_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNormalisationForHI_v1", &AlCa_RPCMuonNormalisationForHI_v1, &b_AlCa_RPCMuonNormalisationForHI_v1);
   fChain->SetBranchAddress("AlCa_RPCMuonNormalisationForHI_v1_Prescl", &AlCa_RPCMuonNormalisationForHI_v1_Prescl, &b_AlCa_RPCMuonNormalisationForHI_v1_Prescl);
   fChain->SetBranchAddress("AlCa_LumiPixels_Random_v1", &AlCa_LumiPixels_Random_v1, &b_AlCa_LumiPixels_Random_v1);
   fChain->SetBranchAddress("AlCa_LumiPixels_Random_v1_Prescl", &AlCa_LumiPixels_Random_v1_Prescl, &b_AlCa_LumiPixels_Random_v1_Prescl);
   fChain->SetBranchAddress("AlCa_LumiPixels_ZeroBias_v2", &AlCa_LumiPixels_ZeroBias_v2, &b_AlCa_LumiPixels_ZeroBias_v2);
   fChain->SetBranchAddress("AlCa_LumiPixels_ZeroBias_v2_Prescl", &AlCa_LumiPixels_ZeroBias_v2_Prescl, &b_AlCa_LumiPixels_ZeroBias_v2_Prescl);
   fChain->SetBranchAddress("HLTriggerFinalPath", &HLTriggerFinalPath, &b_HLTriggerFinalPath);
   fChain->SetBranchAddress("HLTriggerFinalPath_Prescl", &HLTriggerFinalPath_Prescl, &b_HLTriggerFinalPath_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v1", &HLT_HIPuAK4CaloJet40_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet40_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v1", &HLT_HIPuAK4CaloJet60_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet60_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v1", &HLT_HIPuAK4CaloJet80_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet80_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1", &HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1, &b_HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1ForZS_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v1", &HLT_HIPuAK4CaloJet100_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet100_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet110_Eta5p1_v1", &HLT_HIPuAK4CaloJet110_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet110_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet110_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet110_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet110_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120_Eta5p1_v1", &HLT_HIPuAK4CaloJet120_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet120_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet120_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet120_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet150_Eta5p1_v1", &HLT_HIPuAK4CaloJet150_Eta5p1_v1, &b_HLT_HIPuAK4CaloJet150_Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet150_Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet150_Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet150_Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1_Prescl", &HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet40_Eta5p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1_Prescl", &HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet60_Eta5p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1_Prescl", &HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Eta5p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1_Prescl", &HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1_Prescl, &b_HLT_HIPuAK4CaloJet100_Eta5p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1", &HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1_Prescl", &HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta1p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1", &HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1_Prescl", &HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_Jet35_Eta0p7_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1", &HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1_Prescl", &HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta1p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1", &HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1_Prescl", &HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1_Prescl, &b_HLT_HIPuAK4CaloJet100_Jet35_Eta0p7_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1", &HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1, &b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet60_Eta2p1_v1", &HLT_HIPuAK4CaloDJet60_Eta2p1_v1, &b_HLT_HIPuAK4CaloDJet60_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet60_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloDJet60_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloDJet60_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet80_Eta2p1_v1", &HLT_HIPuAK4CaloDJet80_Eta2p1_v1, &b_HLT_HIPuAK4CaloDJet80_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloDJet80_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloDJet80_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloDJet80_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1", &HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1, &b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloBJetCSV60_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1", &HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1, &b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloBJetCSV80_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1", &HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1, &b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloBJetSSV60_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1", &HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1, &b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1_Prescl", &HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1_Prescl, &b_HLT_HIPuAK4CaloBJetSSV80_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_v1", &HLT_HIDmesonHITrackingGlobal_Dpt20_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_v1", &HLT_HIDmesonHITrackingGlobal_Dpt30_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_v1", &HLT_HIDmesonHITrackingGlobal_Dpt40_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt50_v1", &HLT_HIDmesonHITrackingGlobal_Dpt50_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt50_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt50_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt50_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt50_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_v1", &HLT_HIDmesonHITrackingGlobal_Dpt60_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt70_v1", &HLT_HIDmesonHITrackingGlobal_Dpt70_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt70_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt70_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt70_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt70_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1_Prescl", &HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1_Prescl, &b_HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_v1", &HLT_HISinglePhoton10_Eta1p5_v1, &b_HLT_HISinglePhoton10_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_v1_Prescl", &HLT_HISinglePhoton10_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_v1", &HLT_HISinglePhoton15_Eta1p5_v1, &b_HLT_HISinglePhoton15_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_v1_Prescl", &HLT_HISinglePhoton15_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_v1", &HLT_HISinglePhoton20_Eta1p5_v1, &b_HLT_HISinglePhoton20_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_v1_Prescl", &HLT_HISinglePhoton20_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_v1", &HLT_HISinglePhoton30_Eta1p5_v1, &b_HLT_HISinglePhoton30_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_v1_Prescl", &HLT_HISinglePhoton30_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v1", &HLT_HISinglePhoton40_Eta1p5_v1, &b_HLT_HISinglePhoton40_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v1_Prescl", &HLT_HISinglePhoton40_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta1p5_v1", &HLT_HISinglePhoton50_Eta1p5_v1, &b_HLT_HISinglePhoton50_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta1p5_v1_Prescl", &HLT_HISinglePhoton50_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton50_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta1p5_v1", &HLT_HISinglePhoton60_Eta1p5_v1, &b_HLT_HISinglePhoton60_Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta1p5_v1_Prescl", &HLT_HISinglePhoton60_Eta1p5_v1_Prescl, &b_HLT_HISinglePhoton60_Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1", &HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1, &b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1_Prescl", &HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1", &HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1, &b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1_Prescl", &HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1", &HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1, &b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1_Prescl", &HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1", &HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1, &b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1_Prescl", &HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1", &HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1, &b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1_Prescl", &HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1", &HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1, &b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1_Prescl", &HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton10_Eta1p5_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1", &HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1, &b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1_Prescl", &HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton15_Eta1p5_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1", &HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1, &b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1_Prescl", &HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton20_Eta1p5_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1", &HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1, &b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1_Prescl", &HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton30_Eta1p5_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1", &HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1, &b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1_Prescl", &HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton40_Eta1p5_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta2p1_v1", &HLT_HISinglePhoton40_Eta2p1_v1, &b_HLT_HISinglePhoton40_Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta2p1_v1_Prescl", &HLT_HISinglePhoton40_Eta2p1_v1_Prescl, &b_HLT_HISinglePhoton40_Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_v1", &HLT_HISinglePhoton10_Eta3p1_v1, &b_HLT_HISinglePhoton10_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_v1_Prescl", &HLT_HISinglePhoton10_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_v1", &HLT_HISinglePhoton15_Eta3p1_v1, &b_HLT_HISinglePhoton15_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_v1_Prescl", &HLT_HISinglePhoton15_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_v1", &HLT_HISinglePhoton20_Eta3p1_v1, &b_HLT_HISinglePhoton20_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_v1_Prescl", &HLT_HISinglePhoton20_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_v1", &HLT_HISinglePhoton30_Eta3p1_v1, &b_HLT_HISinglePhoton30_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_v1_Prescl", &HLT_HISinglePhoton30_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_v1", &HLT_HISinglePhoton40_Eta3p1_v1, &b_HLT_HISinglePhoton40_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_v1_Prescl", &HLT_HISinglePhoton40_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta3p1_v1", &HLT_HISinglePhoton50_Eta3p1_v1, &b_HLT_HISinglePhoton50_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton50_Eta3p1_v1_Prescl", &HLT_HISinglePhoton50_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton50_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta3p1_v1", &HLT_HISinglePhoton60_Eta3p1_v1, &b_HLT_HISinglePhoton60_Eta3p1_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton60_Eta3p1_v1_Prescl", &HLT_HISinglePhoton60_Eta3p1_v1_Prescl, &b_HLT_HISinglePhoton60_Eta3p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1", &HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1, &b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1_Prescl", &HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1", &HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1, &b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1_Prescl", &HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1", &HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1, &b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1_Prescl", &HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1", &HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1, &b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1_Prescl", &HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1", &HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1, &b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1_Prescl", &HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_Cent50_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1", &HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1, &b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1_Prescl", &HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton10_Eta3p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1", &HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1, &b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1_Prescl", &HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton15_Eta3p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1", &HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1, &b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1_Prescl", &HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton20_Eta3p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1", &HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1, &b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1_Prescl", &HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton30_Eta3p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1", &HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1, &b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1);
   fChain->SetBranchAddress("HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1_Prescl", &HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1_Prescl, &b_HLT_HISinglePhoton40_Eta3p1_Cent30_100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1_Prescl", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1_Prescl, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1_Prescl", &HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1_Prescl, &b_HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1", &HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1, &b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1_Prescl", &HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1_Prescl, &b_HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1", &HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1, &b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1);
   fChain->SetBranchAddress("HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1_Prescl", &HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1_Prescl, &b_HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl", &HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1", &HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1, &b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton10Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1", &HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1, &b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton15Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1", &HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1, &b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton20Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1", &HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1, &b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton30Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1", &HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1, &b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1_Prescl", &HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1_Prescl, &b_HLT_HIL2Mu3Eta2p5_HIPhoton40Eta1p5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC100_v1", &HLT_HIUCC100_v1, &b_HLT_HIUCC100_v1);
   fChain->SetBranchAddress("HLT_HIUCC100_v1_Prescl", &HLT_HIUCC100_v1_Prescl, &b_HLT_HIUCC100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC100_v3", &HLT_HIUCC100_v3, &b_HLT_HIUCC100_v3);
   fChain->SetBranchAddress("HLT_HIUCC100_v3_Prescl", &HLT_HIUCC100_v3_Prescl, &b_HLT_HIUCC100_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC020_v1", &HLT_HIUCC020_v1, &b_HLT_HIUCC020_v1);
   fChain->SetBranchAddress("HLT_HIUCC020_v1_Prescl", &HLT_HIUCC020_v1_Prescl, &b_HLT_HIUCC020_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUCC020_v3", &HLT_HIUCC020_v3, &b_HLT_HIUCC020_v3);
   fChain->SetBranchAddress("HLT_HIUCC020_v3_Prescl", &HLT_HIUCC020_v3_Prescl, &b_HLT_HIUCC020_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v1", &HLT_HIQ2Bottom005_Centrality1030_v1, &b_HLT_HIQ2Bottom005_Centrality1030_v1);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v1_Prescl", &HLT_HIQ2Bottom005_Centrality1030_v1_Prescl, &b_HLT_HIQ2Bottom005_Centrality1030_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v3", &HLT_HIQ2Bottom005_Centrality1030_v3, &b_HLT_HIQ2Bottom005_Centrality1030_v3);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality1030_v3_Prescl", &HLT_HIQ2Bottom005_Centrality1030_v3_Prescl, &b_HLT_HIQ2Bottom005_Centrality1030_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v1", &HLT_HIQ2Top005_Centrality1030_v1, &b_HLT_HIQ2Top005_Centrality1030_v1);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v1_Prescl", &HLT_HIQ2Top005_Centrality1030_v1_Prescl, &b_HLT_HIQ2Top005_Centrality1030_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v3", &HLT_HIQ2Top005_Centrality1030_v3, &b_HLT_HIQ2Top005_Centrality1030_v3);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality1030_v3_Prescl", &HLT_HIQ2Top005_Centrality1030_v3_Prescl, &b_HLT_HIQ2Top005_Centrality1030_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v1", &HLT_HIQ2Bottom005_Centrality3050_v1, &b_HLT_HIQ2Bottom005_Centrality3050_v1);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v1_Prescl", &HLT_HIQ2Bottom005_Centrality3050_v1_Prescl, &b_HLT_HIQ2Bottom005_Centrality3050_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v3", &HLT_HIQ2Bottom005_Centrality3050_v3, &b_HLT_HIQ2Bottom005_Centrality3050_v3);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality3050_v3_Prescl", &HLT_HIQ2Bottom005_Centrality3050_v3_Prescl, &b_HLT_HIQ2Bottom005_Centrality3050_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v1", &HLT_HIQ2Top005_Centrality3050_v1, &b_HLT_HIQ2Top005_Centrality3050_v1);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v1_Prescl", &HLT_HIQ2Top005_Centrality3050_v1_Prescl, &b_HLT_HIQ2Top005_Centrality3050_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v3", &HLT_HIQ2Top005_Centrality3050_v3, &b_HLT_HIQ2Top005_Centrality3050_v3);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality3050_v3_Prescl", &HLT_HIQ2Top005_Centrality3050_v3_Prescl, &b_HLT_HIQ2Top005_Centrality3050_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v1", &HLT_HIQ2Bottom005_Centrality5070_v1, &b_HLT_HIQ2Bottom005_Centrality5070_v1);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v1_Prescl", &HLT_HIQ2Bottom005_Centrality5070_v1_Prescl, &b_HLT_HIQ2Bottom005_Centrality5070_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v3", &HLT_HIQ2Bottom005_Centrality5070_v3, &b_HLT_HIQ2Bottom005_Centrality5070_v3);
   fChain->SetBranchAddress("HLT_HIQ2Bottom005_Centrality5070_v3_Prescl", &HLT_HIQ2Bottom005_Centrality5070_v3_Prescl, &b_HLT_HIQ2Bottom005_Centrality5070_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v1", &HLT_HIQ2Top005_Centrality5070_v1, &b_HLT_HIQ2Top005_Centrality5070_v1);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v1_Prescl", &HLT_HIQ2Top005_Centrality5070_v1_Prescl, &b_HLT_HIQ2Top005_Centrality5070_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v3", &HLT_HIQ2Top005_Centrality5070_v3, &b_HLT_HIQ2Top005_Centrality5070_v3);
   fChain->SetBranchAddress("HLT_HIQ2Top005_Centrality5070_v3_Prescl", &HLT_HIQ2Top005_Centrality5070_v3_Prescl, &b_HLT_HIQ2Top005_Centrality5070_v3_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1", &HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1, &b_HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1_Prescl", &HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1_Prescl, &b_HLT_HIFullTrack12_L1MinimumBiasHF2_AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality010_v1", &HLT_HIFullTrack12_L1Centrality010_v1, &b_HLT_HIFullTrack12_L1Centrality010_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality010_v1_Prescl", &HLT_HIFullTrack12_L1Centrality010_v1_Prescl, &b_HLT_HIFullTrack12_L1Centrality010_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality30100_v1", &HLT_HIFullTrack12_L1Centrality30100_v1, &b_HLT_HIFullTrack12_L1Centrality30100_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack12_L1Centrality30100_v1_Prescl", &HLT_HIFullTrack12_L1Centrality30100_v1_Prescl, &b_HLT_HIFullTrack12_L1Centrality30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1", &HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1, &b_HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1_Prescl", &HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1_Prescl, &b_HLT_HIFullTrack18_L1MinimumBiasHF2_AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality010_v1", &HLT_HIFullTrack18_L1Centrality010_v1, &b_HLT_HIFullTrack18_L1Centrality010_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality010_v1_Prescl", &HLT_HIFullTrack18_L1Centrality010_v1_Prescl, &b_HLT_HIFullTrack18_L1Centrality010_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality30100_v1", &HLT_HIFullTrack18_L1Centrality30100_v1, &b_HLT_HIFullTrack18_L1Centrality30100_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack18_L1Centrality30100_v1_Prescl", &HLT_HIFullTrack18_L1Centrality30100_v1_Prescl, &b_HLT_HIFullTrack18_L1Centrality30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack24_v1", &HLT_HIFullTrack24_v1, &b_HLT_HIFullTrack24_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack24_v1_Prescl", &HLT_HIFullTrack24_v1_Prescl, &b_HLT_HIFullTrack24_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack24_L1Centrality30100_v1", &HLT_HIFullTrack24_L1Centrality30100_v1, &b_HLT_HIFullTrack24_L1Centrality30100_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack24_L1Centrality30100_v1_Prescl", &HLT_HIFullTrack24_L1Centrality30100_v1_Prescl, &b_HLT_HIFullTrack24_L1Centrality30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack34_v1", &HLT_HIFullTrack34_v1, &b_HLT_HIFullTrack34_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack34_v1_Prescl", &HLT_HIFullTrack34_v1_Prescl, &b_HLT_HIFullTrack34_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack34_L1Centrality30100_v1", &HLT_HIFullTrack34_L1Centrality30100_v1, &b_HLT_HIFullTrack34_L1Centrality30100_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack34_L1Centrality30100_v1_Prescl", &HLT_HIFullTrack34_L1Centrality30100_v1_Prescl, &b_HLT_HIFullTrack34_L1Centrality30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack45_v1", &HLT_HIFullTrack45_v1, &b_HLT_HIFullTrack45_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack45_v1_Prescl", &HLT_HIFullTrack45_v1_Prescl, &b_HLT_HIFullTrack45_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIFullTrack45_L1Centrality30100_v1", &HLT_HIFullTrack45_L1Centrality30100_v1, &b_HLT_HIFullTrack45_L1Centrality30100_v1);
   fChain->SetBranchAddress("HLT_HIFullTrack45_L1Centrality30100_v1_Prescl", &HLT_HIFullTrack45_L1Centrality30100_v1_Prescl, &b_HLT_HIFullTrack45_L1Centrality30100_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part1_v1", &HLT_HIL1DoubleMu0_part1_v1, &b_HLT_HIL1DoubleMu0_part1_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part1_v1_Prescl", &HLT_HIL1DoubleMu0_part1_v1_Prescl, &b_HLT_HIL1DoubleMu0_part1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part2_v1", &HLT_HIL1DoubleMu0_part2_v1, &b_HLT_HIL1DoubleMu0_part2_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part2_v1_Prescl", &HLT_HIL1DoubleMu0_part2_v1_Prescl, &b_HLT_HIL1DoubleMu0_part2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part3_v1", &HLT_HIL1DoubleMu0_part3_v1, &b_HLT_HIL1DoubleMu0_part3_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_part3_v1_Prescl", &HLT_HIL1DoubleMu0_part3_v1_Prescl, &b_HLT_HIL1DoubleMu0_part3_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v1", &HLT_HIL2DoubleMu0_NHitQ_v1, &b_HLT_HIL2DoubleMu0_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v1_Prescl", &HLT_HIL2DoubleMu0_NHitQ_v1_Prescl, &b_HLT_HIL2DoubleMu0_NHitQ_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v1", &HLT_HIL2Mu15_v1, &b_HLT_HIL2Mu15_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v1_Prescl", &HLT_HIL2Mu15_v1_Prescl, &b_HLT_HIL2Mu15_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1_Prescl", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1_Prescl, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1NotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl", &HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl, &b_HLT_HIUPCL1DoubleMuOpenNotHFMinimumbiasHFplusANDminustTH0Pixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJetAK4CaloJet20_v1", &HLT_HIL1CastorMediumJetAK4CaloJet20_v1, &b_HLT_HIL1CastorMediumJetAK4CaloJet20_v1);
   fChain->SetBranchAddress("HLT_HIL1CastorMediumJetAK4CaloJet20_v1_Prescl", &HLT_HIL1CastorMediumJetAK4CaloJet20_v1_Prescl, &b_HLT_HIL1CastorMediumJetAK4CaloJet20_v1_Prescl);
   fChain->SetBranchAddress("HLT_HICastorMediumJetPixel_SingleTrack_v2", &HLT_HICastorMediumJetPixel_SingleTrack_v2, &b_HLT_HICastorMediumJetPixel_SingleTrack_v2);
   fChain->SetBranchAddress("HLT_HICastorMediumJetPixel_SingleTrack_v2_Prescl", &HLT_HICastorMediumJetPixel_SingleTrack_v2_Prescl, &b_HLT_HICastorMediumJetPixel_SingleTrack_v2_Prescl);
   fChain->SetBranchAddress("HLT_HICentralityVeto_v2", &HLT_HICentralityVeto_v2, &b_HLT_HICentralityVeto_v2);
   fChain->SetBranchAddress("HLT_HICentralityVeto_v2_Prescl", &HLT_HICentralityVeto_v2_Prescl, &b_HLT_HICentralityVeto_v2_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1ANDExpress_v1", &HLT_HIL1MinimumBiasHF1ANDExpress_v1, &b_HLT_HIL1MinimumBiasHF1ANDExpress_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF1ANDExpress_v1_Prescl", &HLT_HIL1MinimumBiasHF1ANDExpress_v1_Prescl, &b_HLT_HIL1MinimumBiasHF1ANDExpress_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part1_v1", &HLT_HIL1MinimumBiasHF2AND_part1_v1, &b_HLT_HIL1MinimumBiasHF2AND_part1_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part1_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part1_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part2_v1", &HLT_HIL1MinimumBiasHF2AND_part2_v1, &b_HLT_HIL1MinimumBiasHF2AND_part2_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part2_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part2_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part3_v1", &HLT_HIL1MinimumBiasHF2AND_part3_v1, &b_HLT_HIL1MinimumBiasHF2AND_part3_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part3_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part3_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part3_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part4_v1", &HLT_HIL1MinimumBiasHF2AND_part4_v1, &b_HLT_HIL1MinimumBiasHF2AND_part4_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part4_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part4_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part4_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part5_v1", &HLT_HIL1MinimumBiasHF2AND_part5_v1, &b_HLT_HIL1MinimumBiasHF2AND_part5_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part5_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part5_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part5_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part6_v1", &HLT_HIL1MinimumBiasHF2AND_part6_v1, &b_HLT_HIL1MinimumBiasHF2AND_part6_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part6_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part6_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part6_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part7_v1", &HLT_HIL1MinimumBiasHF2AND_part7_v1, &b_HLT_HIL1MinimumBiasHF2AND_part7_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part7_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part7_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part7_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part8_v1", &HLT_HIL1MinimumBiasHF2AND_part8_v1, &b_HLT_HIL1MinimumBiasHF2AND_part8_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part8_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part8_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part8_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part9_v1", &HLT_HIL1MinimumBiasHF2AND_part9_v1, &b_HLT_HIL1MinimumBiasHF2AND_part9_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part9_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part9_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part9_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part10_v1", &HLT_HIL1MinimumBiasHF2AND_part10_v1, &b_HLT_HIL1MinimumBiasHF2AND_part10_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part10_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part10_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part10_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part11_v1", &HLT_HIL1MinimumBiasHF2AND_part11_v1, &b_HLT_HIL1MinimumBiasHF2AND_part11_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part11_v1_Prescl", &HLT_HIL1MinimumBiasHF2AND_part11_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2AND_part11_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2ANDExpress_v1", &HLT_HIL1MinimumBiasHF2ANDExpress_v1, &b_HLT_HIL1MinimumBiasHF2ANDExpress_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2ANDExpress_v1_Prescl", &HLT_HIL1MinimumBiasHF2ANDExpress_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2ANDExpress_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1HFplusANDminusTH0Express_v1", &HLT_HIL1HFplusANDminusTH0Express_v1, &b_HLT_HIL1HFplusANDminusTH0Express_v1);
   fChain->SetBranchAddress("HLT_HIL1HFplusANDminusTH0Express_v1_Prescl", &HLT_HIL1HFplusANDminusTH0Express_v1_Prescl, &b_HLT_HIL1HFplusANDminusTH0Express_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1", &HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1, &b_HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1_Prescl", &HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1_Prescl, &b_HLT_HIL1MinimumBiasHF2ANDPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part2_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_part3_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1", &HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1, &b_HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1_Prescl", &HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1_Prescl, &b_HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1", &HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1, &b_HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1_Prescl", &HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1_Prescl, &b_HLT_HIL1Centralityext010MinimumumBiasHF1ANDForZS_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPhysicsForZS_v1", &HLT_HIPhysicsForZS_v1, &b_HLT_HIPhysicsForZS_v1);
   fChain->SetBranchAddress("HLT_HIPhysicsForZS_v1_Prescl", &HLT_HIPhysicsForZS_v1_Prescl, &b_HLT_HIPhysicsForZS_v1_Prescl);
   fChain->SetBranchAddress("HLT_EcalCalibration_v1", &HLT_EcalCalibration_v1, &b_HLT_EcalCalibration_v1);
   fChain->SetBranchAddress("HLT_EcalCalibration_v1_Prescl", &HLT_EcalCalibration_v1_Prescl, &b_HLT_EcalCalibration_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPhysicsNoZS_v1", &HLT_HIPhysicsNoZS_v1, &b_HLT_HIPhysicsNoZS_v1);
   fChain->SetBranchAddress("HLT_HIPhysicsNoZS_v1_Prescl", &HLT_HIPhysicsNoZS_v1_Prescl, &b_HLT_HIPhysicsNoZS_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1_Prescl", &HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1_Prescl, &b_HLT_HIL1Centralityext30100MinimumumBiasHF2AND_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100HFplusANDminusTH0_v1", &HLT_HIL1Centralityext30100HFplusANDminusTH0_v1, &b_HLT_HIL1Centralityext30100HFplusANDminusTH0_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext30100HFplusANDminusTH0_v1_Prescl", &HLT_HIL1Centralityext30100HFplusANDminusTH0_v1_Prescl, &b_HLT_HIL1Centralityext30100HFplusANDminusTH0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100HFplusANDminusTH0_v1", &HLT_HIL1Centralityext50100HFplusANDminusTH0_v1, &b_HLT_HIL1Centralityext50100HFplusANDminusTH0_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext50100HFplusANDminusTH0_v1_Prescl", &HLT_HIL1Centralityext50100HFplusANDminusTH0_v1_Prescl, &b_HLT_HIL1Centralityext50100HFplusANDminusTH0_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100HFplusANDminusTH0_v1", &HLT_HIL1Centralityext70100HFplusANDminusTH0_v1, &b_HLT_HIL1Centralityext70100HFplusANDminusTH0_v1);
   fChain->SetBranchAddress("HLT_HIL1Centralityext70100HFplusANDminusTH0_v1_Prescl", &HLT_HIL1Centralityext70100HFplusANDminusTH0_v1_Prescl, &b_HLT_HIL1Centralityext70100HFplusANDminusTH0_v1_Prescl);
   fChain->SetBranchAddress("L1_BptxMinus_NotBptxPlus", &L1_BptxMinus_NotBptxPlus, &b_L1_BptxMinus_NotBptxPlus);
   fChain->SetBranchAddress("L1_BptxMinus_NotBptxPlus_Prescl", &L1_BptxMinus_NotBptxPlus_Prescl, &b_L1_BptxMinus_NotBptxPlus_Prescl);
   fChain->SetBranchAddress("L1_BptxPlusORMinus", &L1_BptxPlusORMinus, &b_L1_BptxPlusORMinus);
   fChain->SetBranchAddress("L1_BptxPlusORMinus_Prescl", &L1_BptxPlusORMinus_Prescl, &b_L1_BptxPlusORMinus_Prescl);
   fChain->SetBranchAddress("L1_BptxPlus_NotBptxMinus", &L1_BptxPlus_NotBptxMinus, &b_L1_BptxPlus_NotBptxMinus);
   fChain->SetBranchAddress("L1_BptxPlus_NotBptxMinus_Prescl", &L1_BptxPlus_NotBptxMinus_Prescl, &b_L1_BptxPlus_NotBptxMinus_Prescl);
   fChain->SetBranchAddress("L1_CastorHighJet_BptxAND", &L1_CastorHighJet_BptxAND, &b_L1_CastorHighJet_BptxAND);
   fChain->SetBranchAddress("L1_CastorHighJet_BptxAND_Prescl", &L1_CastorHighJet_BptxAND_Prescl, &b_L1_CastorHighJet_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_CastorMediumJet_BptxAND", &L1_CastorMediumJet_BptxAND, &b_L1_CastorMediumJet_BptxAND);
   fChain->SetBranchAddress("L1_CastorMediumJet_BptxAND_Prescl", &L1_CastorMediumJet_BptxAND_Prescl, &b_L1_CastorMediumJet_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_CastorMuon_BptxAND", &L1_CastorMuon_BptxAND, &b_L1_CastorMuon_BptxAND);
   fChain->SetBranchAddress("L1_CastorMuon_BptxAND_Prescl", &L1_CastorMuon_BptxAND_Prescl, &b_L1_CastorMuon_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext0_100_HFplusORminusTH0", &L1_Centrality_ext0_100_HFplusORminusTH0, &b_L1_Centrality_ext0_100_HFplusORminusTH0);
   fChain->SetBranchAddress("L1_Centrality_ext0_100_HFplusORminusTH0_Prescl", &L1_Centrality_ext0_100_HFplusORminusTH0_Prescl, &b_L1_Centrality_ext0_100_HFplusORminusTH0_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext0_100_MinimumumBiasHF1_AND", &L1_Centrality_ext0_100_MinimumumBiasHF1_AND, &b_L1_Centrality_ext0_100_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext0_100_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext0_100_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext0_100_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext0_10_MinimumumBiasHF1_AND", &L1_Centrality_ext0_10_MinimumumBiasHF1_AND, &b_L1_Centrality_ext0_10_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext0_10_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext0_10_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext0_10_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext0_5_MinimumumBiasHF1_AND", &L1_Centrality_ext0_5_MinimumumBiasHF1_AND, &b_L1_Centrality_ext0_5_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext0_5_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext0_5_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext0_5_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext30_100_MinimumumBiasHF1_AND", &L1_Centrality_ext30_100_MinimumumBiasHF1_AND, &b_L1_Centrality_ext30_100_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext30_100_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext30_100_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext30_100_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext30_50_MinimumumBiasHF1_AND", &L1_Centrality_ext30_50_MinimumumBiasHF1_AND, &b_L1_Centrality_ext30_50_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext30_50_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext30_50_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext30_50_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext50_100_MinimumumBiasHF1_AND", &L1_Centrality_ext50_100_MinimumumBiasHF1_AND, &b_L1_Centrality_ext50_100_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext50_100_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext50_100_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext50_100_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_Centrality_ext70_100_MinimumumBiasHF1_AND", &L1_Centrality_ext70_100_MinimumumBiasHF1_AND, &b_L1_Centrality_ext70_100_MinimumumBiasHF1_AND);
   fChain->SetBranchAddress("L1_Centrality_ext70_100_MinimumumBiasHF1_AND_Prescl", &L1_Centrality_ext70_100_MinimumumBiasHF1_AND_Prescl, &b_L1_Centrality_ext70_100_MinimumumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG10", &L1_DoubleEG10, &b_L1_DoubleEG10);
   fChain->SetBranchAddress("L1_DoubleEG10_Prescl", &L1_DoubleEG10_Prescl, &b_L1_DoubleEG10_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG2_BptxAND", &L1_DoubleEG2_BptxAND, &b_L1_DoubleEG2_BptxAND);
   fChain->SetBranchAddress("L1_DoubleEG2_BptxAND_Prescl", &L1_DoubleEG2_BptxAND_Prescl, &b_L1_DoubleEG2_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG2_NotMinimumBiasHF2_AND", &L1_DoubleEG2_NotMinimumBiasHF2_AND, &b_L1_DoubleEG2_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_DoubleEG2_NotMinimumBiasHF2_AND_Prescl", &L1_DoubleEG2_NotMinimumBiasHF2_AND_Prescl, &b_L1_DoubleEG2_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG2_NotZdc_AND_BptxAND", &L1_DoubleEG2_NotZdc_AND_BptxAND, &b_L1_DoubleEG2_NotZdc_AND_BptxAND);
   fChain->SetBranchAddress("L1_DoubleEG2_NotZdc_AND_BptxAND_Prescl", &L1_DoubleEG2_NotZdc_AND_BptxAND_Prescl, &b_L1_DoubleEG2_NotZdc_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG5_BptxAND", &L1_DoubleEG5_BptxAND, &b_L1_DoubleEG5_BptxAND);
   fChain->SetBranchAddress("L1_DoubleEG5_BptxAND_Prescl", &L1_DoubleEG5_BptxAND_Prescl, &b_L1_DoubleEG5_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG8_BptxAND", &L1_DoubleEG8_BptxAND, &b_L1_DoubleEG8_BptxAND);
   fChain->SetBranchAddress("L1_DoubleEG8_BptxAND_Prescl", &L1_DoubleEG8_BptxAND_Prescl, &b_L1_DoubleEG8_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG_13_7", &L1_DoubleEG_13_7, &b_L1_DoubleEG_13_7);
   fChain->SetBranchAddress("L1_DoubleEG_13_7_Prescl", &L1_DoubleEG_13_7_Prescl, &b_L1_DoubleEG_13_7_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_BptxAND", &L1_DoubleMu0_BptxAND, &b_L1_DoubleMu0_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu0_BptxAND_Prescl", &L1_DoubleMu0_BptxAND_Prescl, &b_L1_DoubleMu0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_HFplusANDminusTH0_BptxAND", &L1_DoubleMu0_HFplusANDminusTH0_BptxAND, &b_L1_DoubleMu0_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu0_HFplusANDminusTH0_BptxAND_Prescl", &L1_DoubleMu0_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_DoubleMu0_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND", &L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND, &b_L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND_Prescl", &L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND_Prescl, &b_L1_DoubleMu0_HFplusANDminusTH0_Centrliatiy_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND", &L1_DoubleMu0_MinimumBiasHF1_AND, &b_L1_DoubleMu0_MinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND_Prescl", &L1_DoubleMu0_MinimumBiasHF1_AND_Prescl, &b_L1_DoubleMu0_MinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND", &L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND, &b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND_Prescl", &L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND_Prescl, &b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext0_30_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND", &L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND, &b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND_Prescl", &L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND_Prescl, &b_L1_DoubleMu0_MinimumBiasHF1_AND_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu10_BptxAND", &L1_DoubleMu10_BptxAND, &b_L1_DoubleMu10_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMu10_BptxAND_Prescl", &L1_DoubleMu10_BptxAND_Prescl, &b_L1_DoubleMu10_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND", &L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND, &b_L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND_Prescl", &L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND_Prescl, &b_L1_DoubleMuOpenNotHFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMuOpen_BptxAND", &L1_DoubleMuOpen_BptxAND, &b_L1_DoubleMuOpen_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMuOpen_BptxAND_Prescl", &L1_DoubleMuOpen_BptxAND_Prescl, &b_L1_DoubleMuOpen_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotMinimumBiasHF1_AND", &L1_DoubleMuOpen_NotMinimumBiasHF1_AND, &b_L1_DoubleMuOpen_NotMinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotMinimumBiasHF1_AND_Prescl", &L1_DoubleMuOpen_NotMinimumBiasHF1_AND_Prescl, &b_L1_DoubleMuOpen_NotMinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotMinimumBiasHF2_AND", &L1_DoubleMuOpen_NotMinimumBiasHF2_AND, &b_L1_DoubleMuOpen_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotMinimumBiasHF2_AND_Prescl", &L1_DoubleMuOpen_NotMinimumBiasHF2_AND_Prescl, &b_L1_DoubleMuOpen_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotZdc_AND_BptxAND", &L1_DoubleMuOpen_NotZdc_AND_BptxAND, &b_L1_DoubleMuOpen_NotZdc_AND_BptxAND);
   fChain->SetBranchAddress("L1_DoubleMuOpen_NotZdc_AND_BptxAND_Prescl", &L1_DoubleMuOpen_NotZdc_AND_BptxAND_Prescl, &b_L1_DoubleMuOpen_NotZdc_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_EG2_NotMinimumBiasHF2_AND", &L1_EG2_NotMinimumBiasHF2_AND, &b_L1_EG2_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_EG2_NotMinimumBiasHF2_AND_Prescl", &L1_EG2_NotMinimumBiasHF2_AND_Prescl, &b_L1_EG2_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_EG5_NotMinimumBiasHF2_AND", &L1_EG5_NotMinimumBiasHF2_AND, &b_L1_EG5_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_EG5_NotMinimumBiasHF2_AND_Prescl", &L1_EG5_NotMinimumBiasHF2_AND_Prescl, &b_L1_EG5_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_HF_2reg_plusANDminusTH0", &L1_HF_2reg_plusANDminusTH0, &b_L1_HF_2reg_plusANDminusTH0);
   fChain->SetBranchAddress("L1_HF_2reg_plusANDminusTH0_Prescl", &L1_HF_2reg_plusANDminusTH0_Prescl, &b_L1_HF_2reg_plusANDminusTH0_Prescl);
   fChain->SetBranchAddress("L1_HF_2reg_plusANDminusTH1", &L1_HF_2reg_plusANDminusTH1, &b_L1_HF_2reg_plusANDminusTH1);
   fChain->SetBranchAddress("L1_HF_2reg_plusANDminusTH1_Prescl", &L1_HF_2reg_plusANDminusTH1_Prescl, &b_L1_HF_2reg_plusANDminusTH1_Prescl);
   fChain->SetBranchAddress("L1_HFplusANDminusTH0", &L1_HFplusANDminusTH0, &b_L1_HFplusANDminusTH0);
   fChain->SetBranchAddress("L1_HFplusANDminusTH0_Prescl", &L1_HFplusANDminusTH0_Prescl, &b_L1_HFplusANDminusTH0_Prescl);
   fChain->SetBranchAddress("L1_HFplusANDminusTH1", &L1_HFplusANDminusTH1, &b_L1_HFplusANDminusTH1);
   fChain->SetBranchAddress("L1_HFplusANDminusTH1_Prescl", &L1_HFplusANDminusTH1_Prescl, &b_L1_HFplusANDminusTH1_Prescl);
   fChain->SetBranchAddress("L1_HFplusORminusTH0", &L1_HFplusORminusTH0, &b_L1_HFplusORminusTH0);
   fChain->SetBranchAddress("L1_HFplusORminusTH0_Prescl", &L1_HFplusORminusTH0_Prescl, &b_L1_HFplusORminusTH0_Prescl);
   fChain->SetBranchAddress("L1_HFplusORminusTH1", &L1_HFplusORminusTH1, &b_L1_HFplusORminusTH1);
   fChain->SetBranchAddress("L1_HFplusORminusTH1_Prescl", &L1_HFplusORminusTH1_Prescl, &b_L1_HFplusORminusTH1_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_AND", &L1_MinimumBiasHF1_AND, &b_L1_MinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_AND_Prescl", &L1_MinimumBiasHF1_AND_Prescl, &b_L1_MinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_OR", &L1_MinimumBiasHF1_OR, &b_L1_MinimumBiasHF1_OR);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_OR_Prescl", &L1_MinimumBiasHF1_OR_Prescl, &b_L1_MinimumBiasHF1_OR_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_OR_NotInUse", &L1_MinimumBiasHF1_OR_NotInUse, &b_L1_MinimumBiasHF1_OR_NotInUse);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_OR_NotInUse_Prescl", &L1_MinimumBiasHF1_OR_NotInUse_Prescl, &b_L1_MinimumBiasHF1_OR_NotInUse_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_XOR", &L1_MinimumBiasHF1_XOR, &b_L1_MinimumBiasHF1_XOR);
   fChain->SetBranchAddress("L1_MinimumBiasHF1_XOR_Prescl", &L1_MinimumBiasHF1_XOR_Prescl, &b_L1_MinimumBiasHF1_XOR_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF2_AND", &L1_MinimumBiasHF2_AND, &b_L1_MinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_MinimumBiasHF2_AND_Prescl", &L1_MinimumBiasHF2_AND_Prescl, &b_L1_MinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_MinimumBiasHF2_OR", &L1_MinimumBiasHF2_OR, &b_L1_MinimumBiasHF2_OR);
   fChain->SetBranchAddress("L1_MinimumBiasHF2_OR_Prescl", &L1_MinimumBiasHF2_OR_Prescl, &b_L1_MinimumBiasHF2_OR_Prescl);
   fChain->SetBranchAddress("L1_MuOpen_NotMinimumBiasHF1_AND", &L1_MuOpen_NotMinimumBiasHF1_AND, &b_L1_MuOpen_NotMinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_MuOpen_NotMinimumBiasHF1_AND_Prescl", &L1_MuOpen_NotMinimumBiasHF1_AND_Prescl, &b_L1_MuOpen_NotMinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_MuOpen_NotMinimumBiasHF2_AND", &L1_MuOpen_NotMinimumBiasHF2_AND, &b_L1_MuOpen_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_MuOpen_NotMinimumBiasHF2_AND_Prescl", &L1_MuOpen_NotMinimumBiasHF2_AND_Prescl, &b_L1_MuOpen_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_MuOpen_NotZdc_AND_BptxAND", &L1_MuOpen_NotZdc_AND_BptxAND, &b_L1_MuOpen_NotZdc_AND_BptxAND);
   fChain->SetBranchAddress("L1_MuOpen_NotZdc_AND_BptxAND_Prescl", &L1_MuOpen_NotZdc_AND_BptxAND_Prescl, &b_L1_MuOpen_NotZdc_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_NotHFplusANDminusTH0_BptxAND", &L1_NotHFplusANDminusTH0_BptxAND, &b_L1_NotHFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_NotHFplusANDminusTH0_BptxAND_Prescl", &L1_NotHFplusANDminusTH0_BptxAND_Prescl, &b_L1_NotHFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_NotMinimumBiasHF1_OR", &L1_NotMinimumBiasHF1_OR, &b_L1_NotMinimumBiasHF1_OR);
   fChain->SetBranchAddress("L1_NotMinimumBiasHF1_OR_Prescl", &L1_NotMinimumBiasHF1_OR_Prescl, &b_L1_NotMinimumBiasHF1_OR_Prescl);
   fChain->SetBranchAddress("L1_NotMinimumBiasHF2_AND", &L1_NotMinimumBiasHF2_AND, &b_L1_NotMinimumBiasHF2_AND);
   fChain->SetBranchAddress("L1_NotMinimumBiasHF2_AND_Prescl", &L1_NotMinimumBiasHF2_AND_Prescl, &b_L1_NotMinimumBiasHF2_AND_Prescl);
   fChain->SetBranchAddress("L1_NotZdcOR_BptxAND", &L1_NotZdcOR_BptxAND, &b_L1_NotZdcOR_BptxAND);
   fChain->SetBranchAddress("L1_NotZdcOR_BptxAND_Prescl", &L1_NotZdcOR_BptxAND_Prescl, &b_L1_NotZdcOR_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG12_BptxAND", &L1_SingleEG12_BptxAND, &b_L1_SingleEG12_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG12_BptxAND_Prescl", &L1_SingleEG12_BptxAND_Prescl, &b_L1_SingleEG12_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG15_BptxAND", &L1_SingleEG15_BptxAND, &b_L1_SingleEG15_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG15_BptxAND_Prescl", &L1_SingleEG15_BptxAND_Prescl, &b_L1_SingleEG15_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG21_BptxAND", &L1_SingleEG21_BptxAND, &b_L1_SingleEG21_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG21_BptxAND_Prescl", &L1_SingleEG21_BptxAND_Prescl, &b_L1_SingleEG21_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG21_Centrality_ext30_100_BptxAND", &L1_SingleEG21_Centrality_ext30_100_BptxAND, &b_L1_SingleEG21_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG21_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleEG21_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleEG21_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG21_Centrality_ext50_100_BptxAND", &L1_SingleEG21_Centrality_ext50_100_BptxAND, &b_L1_SingleEG21_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG21_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleEG21_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleEG21_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG2_NotZDC_AND_BptxAND", &L1_SingleEG2_NotZDC_AND_BptxAND, &b_L1_SingleEG2_NotZDC_AND_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG2_NotZDC_AND_BptxAND_Prescl", &L1_SingleEG2_NotZDC_AND_BptxAND_Prescl, &b_L1_SingleEG2_NotZDC_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG30_BptxAND", &L1_SingleEG30_BptxAND, &b_L1_SingleEG30_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG30_BptxAND_Prescl", &L1_SingleEG30_BptxAND_Prescl, &b_L1_SingleEG30_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG3_BptxAND", &L1_SingleEG3_BptxAND, &b_L1_SingleEG3_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG3_BptxAND_Prescl", &L1_SingleEG3_BptxAND_Prescl, &b_L1_SingleEG3_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG3_Centrality_ext30_100_BptxAND", &L1_SingleEG3_Centrality_ext30_100_BptxAND, &b_L1_SingleEG3_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG3_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleEG3_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleEG3_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG3_Centrality_ext50_100_BptxAND", &L1_SingleEG3_Centrality_ext50_100_BptxAND, &b_L1_SingleEG3_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG3_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleEG3_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleEG3_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG5", &L1_SingleEG5, &b_L1_SingleEG5);
   fChain->SetBranchAddress("L1_SingleEG5_Prescl", &L1_SingleEG5_Prescl, &b_L1_SingleEG5_Prescl);
   fChain->SetBranchAddress("L1_SingleEG5_BptxAND", &L1_SingleEG5_BptxAND, &b_L1_SingleEG5_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG5_BptxAND_Prescl", &L1_SingleEG5_BptxAND_Prescl, &b_L1_SingleEG5_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG5_NotZdc_AND_BptxAND", &L1_SingleEG5_NotZdc_AND_BptxAND, &b_L1_SingleEG5_NotZdc_AND_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG5_NotZdc_AND_BptxAND_Prescl", &L1_SingleEG5_NotZdc_AND_BptxAND_Prescl, &b_L1_SingleEG5_NotZdc_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG7_BptxAND", &L1_SingleEG7_BptxAND, &b_L1_SingleEG7_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG7_BptxAND_Prescl", &L1_SingleEG7_BptxAND_Prescl, &b_L1_SingleEG7_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG7_Centrality_ext30_100_BptxAND", &L1_SingleEG7_Centrality_ext30_100_BptxAND, &b_L1_SingleEG7_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG7_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleEG7_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleEG7_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleEG7_Centrality_ext50_100_BptxAND", &L1_SingleEG7_Centrality_ext50_100_BptxAND, &b_L1_SingleEG7_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleEG7_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleEG7_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleEG7_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleIsoEG3_BptxAND", &L1_SingleIsoEG3_BptxAND, &b_L1_SingleIsoEG3_BptxAND);
   fChain->SetBranchAddress("L1_SingleIsoEG3_BptxAND_Prescl", &L1_SingleIsoEG3_BptxAND_Prescl, &b_L1_SingleIsoEG3_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleIsoEG7_BptxAND", &L1_SingleIsoEG7_BptxAND, &b_L1_SingleIsoEG7_BptxAND);
   fChain->SetBranchAddress("L1_SingleIsoEG7_BptxAND_Prescl", &L1_SingleIsoEG7_BptxAND_Prescl, &b_L1_SingleIsoEG7_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12_BptxAND", &L1_SingleMu12_BptxAND, &b_L1_SingleMu12_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu12_BptxAND_Prescl", &L1_SingleMu12_BptxAND_Prescl, &b_L1_SingleMu12_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12_HFplusANDminusTH0_BptxAND", &L1_SingleMu12_HFplusANDminusTH0_BptxAND, &b_L1_SingleMu12_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu12_HFplusANDminusTH0_BptxAND_Prescl", &L1_SingleMu12_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_SingleMu12_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12_MinimumBiasHF1_AND_BptxAND", &L1_SingleMu12_MinimumBiasHF1_AND_BptxAND, &b_L1_SingleMu12_MinimumBiasHF1_AND_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu12_MinimumBiasHF1_AND_BptxAND_Prescl", &L1_SingleMu12_MinimumBiasHF1_AND_BptxAND_Prescl, &b_L1_SingleMu12_MinimumBiasHF1_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12_SingleEG7", &L1_SingleMu12_SingleEG7, &b_L1_SingleMu12_SingleEG7);
   fChain->SetBranchAddress("L1_SingleMu12_SingleEG7_Prescl", &L1_SingleMu12_SingleEG7_Prescl, &b_L1_SingleMu12_SingleEG7_Prescl);
   fChain->SetBranchAddress("L1_SingleMu16_BptxAND", &L1_SingleMu16_BptxAND, &b_L1_SingleMu16_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu16_BptxAND_Prescl", &L1_SingleMu16_BptxAND_Prescl, &b_L1_SingleMu16_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu16_HFplusANDminusTH0_BptxAND", &L1_SingleMu16_HFplusANDminusTH0_BptxAND, &b_L1_SingleMu16_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu16_HFplusANDminusTH0_BptxAND_Prescl", &L1_SingleMu16_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_SingleMu16_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu16_MinimumBiasHF1_AND_BptxAND", &L1_SingleMu16_MinimumBiasHF1_AND_BptxAND, &b_L1_SingleMu16_MinimumBiasHF1_AND_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu16_MinimumBiasHF1_AND_BptxAND_Prescl", &L1_SingleMu16_MinimumBiasHF1_AND_BptxAND_Prescl, &b_L1_SingleMu16_MinimumBiasHF1_AND_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_HFplusANDminusTH0_BptxAND", &L1_SingleMu3_HFplusANDminusTH0_BptxAND, &b_L1_SingleMu3_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu3_HFplusANDminusTH0_BptxAND_Prescl", &L1_SingleMu3_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_SingleMu3_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_MinimumBiasHF1_AND", &L1_SingleMu3_MinimumBiasHF1_AND, &b_L1_SingleMu3_MinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_SingleMu3_MinimumBiasHF1_AND_Prescl", &L1_SingleMu3_MinimumBiasHF1_AND_Prescl, &b_L1_SingleMu3_MinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet28", &L1_SingleMu3_SingleCenJet28, &b_L1_SingleMu3_SingleCenJet28);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet28_Prescl", &L1_SingleMu3_SingleCenJet28_Prescl, &b_L1_SingleMu3_SingleCenJet28_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet32", &L1_SingleMu3_SingleCenJet32, &b_L1_SingleMu3_SingleCenJet32);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet32_Prescl", &L1_SingleMu3_SingleCenJet32_Prescl, &b_L1_SingleMu3_SingleCenJet32_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet40", &L1_SingleMu3_SingleCenJet40, &b_L1_SingleMu3_SingleCenJet40);
   fChain->SetBranchAddress("L1_SingleMu3_SingleCenJet40_Prescl", &L1_SingleMu3_SingleCenJet40_Prescl, &b_L1_SingleMu3_SingleCenJet40_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_SingleEG12", &L1_SingleMu3_SingleEG12, &b_L1_SingleMu3_SingleEG12);
   fChain->SetBranchAddress("L1_SingleMu3_SingleEG12_Prescl", &L1_SingleMu3_SingleEG12_Prescl, &b_L1_SingleMu3_SingleEG12_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3_SingleEG20", &L1_SingleMu3_SingleEG20, &b_L1_SingleMu3_SingleEG20);
   fChain->SetBranchAddress("L1_SingleMu3_SingleEG20_Prescl", &L1_SingleMu3_SingleEG20_Prescl, &b_L1_SingleMu3_SingleEG20_Prescl);
   fChain->SetBranchAddress("L1_SingleMu5_HFplusANDminusTH0_BptxAND", &L1_SingleMu5_HFplusANDminusTH0_BptxAND, &b_L1_SingleMu5_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu5_HFplusANDminusTH0_BptxAND_Prescl", &L1_SingleMu5_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_SingleMu5_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu5_MinimumBiasHF1_AND", &L1_SingleMu5_MinimumBiasHF1_AND, &b_L1_SingleMu5_MinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_SingleMu5_MinimumBiasHF1_AND_Prescl", &L1_SingleMu5_MinimumBiasHF1_AND_Prescl, &b_L1_SingleMu5_MinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu5_SingleEG20", &L1_SingleMu5_SingleEG20, &b_L1_SingleMu5_SingleEG20);
   fChain->SetBranchAddress("L1_SingleMu5_SingleEG20_Prescl", &L1_SingleMu5_SingleEG20_Prescl, &b_L1_SingleMu5_SingleEG20_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7_HFplusANDminusTH0_BptxAND", &L1_SingleMu7_HFplusANDminusTH0_BptxAND, &b_L1_SingleMu7_HFplusANDminusTH0_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu7_HFplusANDminusTH0_BptxAND_Prescl", &L1_SingleMu7_HFplusANDminusTH0_BptxAND_Prescl, &b_L1_SingleMu7_HFplusANDminusTH0_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7_MinimumBiasHF1_AND", &L1_SingleMu7_MinimumBiasHF1_AND, &b_L1_SingleMu7_MinimumBiasHF1_AND);
   fChain->SetBranchAddress("L1_SingleMu7_MinimumBiasHF1_AND_Prescl", &L1_SingleMu7_MinimumBiasHF1_AND_Prescl, &b_L1_SingleMu7_MinimumBiasHF1_AND_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7_SingleEG12", &L1_SingleMu7_SingleEG12, &b_L1_SingleMu7_SingleEG12);
   fChain->SetBranchAddress("L1_SingleMu7_SingleEG12_Prescl", &L1_SingleMu7_SingleEG12_Prescl, &b_L1_SingleMu7_SingleEG12_Prescl);
   fChain->SetBranchAddress("L1_SingleMuOpen", &L1_SingleMuOpen, &b_L1_SingleMuOpen);
   fChain->SetBranchAddress("L1_SingleMuOpen_Prescl", &L1_SingleMuOpen_Prescl, &b_L1_SingleMuOpen_Prescl);
   fChain->SetBranchAddress("L1_SingleMuOpen_BptxAND", &L1_SingleMuOpen_BptxAND, &b_L1_SingleMuOpen_BptxAND);
   fChain->SetBranchAddress("L1_SingleMuOpen_BptxAND_Prescl", &L1_SingleMuOpen_BptxAND_Prescl, &b_L1_SingleMuOpen_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet16_BptxAND", &L1_SingleS1Jet16_BptxAND, &b_L1_SingleS1Jet16_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet16_BptxAND_Prescl", &L1_SingleS1Jet16_BptxAND_Prescl, &b_L1_SingleS1Jet16_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet16_Centrality_ext30_100_BptxAND", &L1_SingleS1Jet16_Centrality_ext30_100_BptxAND, &b_L1_SingleS1Jet16_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet16_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleS1Jet16_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleS1Jet16_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet16_Centrality_ext50_100_BptxAND", &L1_SingleS1Jet16_Centrality_ext50_100_BptxAND, &b_L1_SingleS1Jet16_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet16_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleS1Jet16_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleS1Jet16_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet28_BptxAND", &L1_SingleS1Jet28_BptxAND, &b_L1_SingleS1Jet28_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet28_BptxAND_Prescl", &L1_SingleS1Jet28_BptxAND_Prescl, &b_L1_SingleS1Jet28_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet28_Centrality_ext30_100_BptxAND", &L1_SingleS1Jet28_Centrality_ext30_100_BptxAND, &b_L1_SingleS1Jet28_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet28_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleS1Jet28_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleS1Jet28_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet28_Centrality_ext50_100_BptxAND", &L1_SingleS1Jet28_Centrality_ext50_100_BptxAND, &b_L1_SingleS1Jet28_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet28_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleS1Jet28_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleS1Jet28_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet32_BptxAND", &L1_SingleS1Jet32_BptxAND, &b_L1_SingleS1Jet32_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet32_BptxAND_Prescl", &L1_SingleS1Jet32_BptxAND_Prescl, &b_L1_SingleS1Jet32_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet32_Centrality_ext30_100_BptxAND", &L1_SingleS1Jet32_Centrality_ext30_100_BptxAND, &b_L1_SingleS1Jet32_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet32_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleS1Jet32_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleS1Jet32_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet32_Centrality_ext50_100_BptxAND", &L1_SingleS1Jet32_Centrality_ext50_100_BptxAND, &b_L1_SingleS1Jet32_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet32_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleS1Jet32_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleS1Jet32_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet36_BptxAND", &L1_SingleS1Jet36_BptxAND, &b_L1_SingleS1Jet36_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet36_BptxAND_Prescl", &L1_SingleS1Jet36_BptxAND_Prescl, &b_L1_SingleS1Jet36_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet40_BptxAND", &L1_SingleS1Jet40_BptxAND, &b_L1_SingleS1Jet40_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet40_BptxAND_Prescl", &L1_SingleS1Jet40_BptxAND_Prescl, &b_L1_SingleS1Jet40_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleJet44_BptxAND", &L1_SingleJet44_BptxAND, &b_L1_SingleJet44_BptxAND);
   fChain->SetBranchAddress("L1_SingleJet44_BptxAND_Prescl", &L1_SingleJet44_BptxAND_Prescl, &b_L1_SingleJet44_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet44_Centrality_ext30_100_BptxAND", &L1_SingleS1Jet44_Centrality_ext30_100_BptxAND, &b_L1_SingleS1Jet44_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet44_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleS1Jet44_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleS1Jet44_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet44_Centrality_ext50_100_BptxAND", &L1_SingleS1Jet44_Centrality_ext50_100_BptxAND, &b_L1_SingleS1Jet44_Centrality_ext50_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet44_Centrality_ext50_100_BptxAND_Prescl", &L1_SingleS1Jet44_Centrality_ext50_100_BptxAND_Prescl, &b_L1_SingleS1Jet44_Centrality_ext50_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet48_BptxAND", &L1_SingleS1Jet48_BptxAND, &b_L1_SingleS1Jet48_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet48_BptxAND_Prescl", &L1_SingleS1Jet48_BptxAND_Prescl, &b_L1_SingleS1Jet48_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet52_BptxAND", &L1_SingleS1Jet52_BptxAND, &b_L1_SingleS1Jet52_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet52_BptxAND_Prescl", &L1_SingleS1Jet52_BptxAND_Prescl, &b_L1_SingleS1Jet52_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet56_BptxAND", &L1_SingleS1Jet56_BptxAND, &b_L1_SingleS1Jet56_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet56_BptxAND_Prescl", &L1_SingleS1Jet56_BptxAND_Prescl, &b_L1_SingleS1Jet56_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1Jet64_BptxAND", &L1_SingleS1Jet64_BptxAND, &b_L1_SingleS1Jet64_BptxAND);
   fChain->SetBranchAddress("L1_SingleS1Jet64_BptxAND_Prescl", &L1_SingleS1Jet64_BptxAND_Prescl, &b_L1_SingleS1Jet64_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleS1JetC20_NotBptxOR", &L1_SingleS1JetC20_NotBptxOR, &b_L1_SingleS1JetC20_NotBptxOR);
   fChain->SetBranchAddress("L1_SingleS1JetC20_NotBptxOR_Prescl", &L1_SingleS1JetC20_NotBptxOR_Prescl, &b_L1_SingleS1JetC20_NotBptxOR_Prescl);
   fChain->SetBranchAddress("L1_SingleS1JetC32_NotBptxOR", &L1_SingleS1JetC32_NotBptxOR, &b_L1_SingleS1JetC32_NotBptxOR);
   fChain->SetBranchAddress("L1_SingleS1JetC32_NotBptxOR_Prescl", &L1_SingleS1JetC32_NotBptxOR_Prescl, &b_L1_SingleS1JetC32_NotBptxOR_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack12_BptxAND", &L1_SingleTrack12_BptxAND, &b_L1_SingleTrack12_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack12_BptxAND_Prescl", &L1_SingleTrack12_BptxAND_Prescl, &b_L1_SingleTrack12_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack12_Centrality_ext30_100_BptxAND", &L1_SingleTrack12_Centrality_ext30_100_BptxAND, &b_L1_SingleTrack12_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack12_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleTrack12_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleTrack12_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack16_BptxAND", &L1_SingleTrack16_BptxAND, &b_L1_SingleTrack16_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack16_BptxAND_Prescl", &L1_SingleTrack16_BptxAND_Prescl, &b_L1_SingleTrack16_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack16_Centrality_ext30_100_BptxAND", &L1_SingleTrack16_Centrality_ext30_100_BptxAND, &b_L1_SingleTrack16_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack16_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleTrack16_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleTrack16_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack20_BptxAND", &L1_SingleTrack20_BptxAND, &b_L1_SingleTrack20_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack20_BptxAND_Prescl", &L1_SingleTrack20_BptxAND_Prescl, &b_L1_SingleTrack20_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack20_Centrality_ext30_100_BptxAND", &L1_SingleTrack20_Centrality_ext30_100_BptxAND, &b_L1_SingleTrack20_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack20_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleTrack20_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleTrack20_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack24_BptxAND", &L1_SingleTrack24_BptxAND, &b_L1_SingleTrack24_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack24_BptxAND_Prescl", &L1_SingleTrack24_BptxAND_Prescl, &b_L1_SingleTrack24_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack24_Centrality_ext30_100_BptxAND", &L1_SingleTrack24_Centrality_ext30_100_BptxAND, &b_L1_SingleTrack24_Centrality_ext30_100_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack24_Centrality_ext30_100_BptxAND_Prescl", &L1_SingleTrack24_Centrality_ext30_100_BptxAND_Prescl, &b_L1_SingleTrack24_Centrality_ext30_100_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_SingleTrack28_BptxAND", &L1_SingleTrack28_BptxAND, &b_L1_SingleTrack28_BptxAND);
   fChain->SetBranchAddress("L1_SingleTrack28_BptxAND_Prescl", &L1_SingleTrack28_BptxAND_Prescl, &b_L1_SingleTrack28_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_TOTEM_1", &L1_TOTEM_1, &b_L1_TOTEM_1);
   fChain->SetBranchAddress("L1_TOTEM_1_Prescl", &L1_TOTEM_1_Prescl, &b_L1_TOTEM_1_Prescl);
   fChain->SetBranchAddress("L1_TOTEM_2", &L1_TOTEM_2, &b_L1_TOTEM_2);
   fChain->SetBranchAddress("L1_TOTEM_2_Prescl", &L1_TOTEM_2_Prescl, &b_L1_TOTEM_2_Prescl);
   fChain->SetBranchAddress("L1_ZdcOR_BptxAND", &L1_ZdcOR_BptxAND, &b_L1_ZdcOR_BptxAND);
   fChain->SetBranchAddress("L1_ZdcOR_BptxAND_Prescl", &L1_ZdcOR_BptxAND_Prescl, &b_L1_ZdcOR_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_ZdcXOR_BptxAND", &L1_ZdcXOR_BptxAND, &b_L1_ZdcXOR_BptxAND);
   fChain->SetBranchAddress("L1_ZdcXOR_BptxAND_Prescl", &L1_ZdcXOR_BptxAND_Prescl, &b_L1_ZdcXOR_BptxAND_Prescl);
   fChain->SetBranchAddress("L1_ZeroBias", &L1_ZeroBias, &b_L1_ZeroBias);
   fChain->SetBranchAddress("L1_ZeroBias_Prescl", &L1_ZeroBias_Prescl, &b_L1_ZeroBias_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_PreBPTX.v0", &L1Tech_BPTX_PreBPTX_v0, &b_L1Tech_BPTX_PreBPTX_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_PreBPTX.v0_Prescl", &L1Tech_BPTX_PreBPTX_v0_Prescl, &b_L1Tech_BPTX_PreBPTX_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_minus.v0", &L1Tech_BPTX_minus_v0, &b_L1Tech_BPTX_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_minus.v0_Prescl", &L1Tech_BPTX_minus_v0_Prescl, &b_L1Tech_BPTX_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0", &L1Tech_BPTX_minus_AND_not_plus_v0, &b_L1Tech_BPTX_minus_AND_not_plus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_Prescl", &L1Tech_BPTX_minus_AND_not_plus_v0_Prescl, &b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus.v0", &L1Tech_BPTX_plus_v0, &b_L1Tech_BPTX_plus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus.v0_Prescl", &L1Tech_BPTX_plus_v0_Prescl, &b_L1Tech_BPTX_plus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0", &L1Tech_BPTX_plus_AND_NOT_minus_v0, &b_L1Tech_BPTX_plus_AND_NOT_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_Prescl", &L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl, &b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0", &L1Tech_BPTX_plus_AND_minus_v0, &b_L1Tech_BPTX_plus_AND_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_Prescl", &L1Tech_BPTX_plus_AND_minus_v0_Prescl, &b_L1Tech_BPTX_plus_AND_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0", &L1Tech_BPTX_plus_AND_minus_instance1_v0, &b_L1Tech_BPTX_plus_AND_minus_instance1_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_Prescl", &L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl, &b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0", &L1Tech_BPTX_plus_OR_minus_v0, &b_L1Tech_BPTX_plus_OR_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_Prescl", &L1Tech_BPTX_plus_OR_minus_v0_Prescl, &b_L1Tech_BPTX_plus_OR_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_quiet.v0", &L1Tech_BPTX_quiet_v0, &b_L1Tech_BPTX_quiet_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_quiet.v0_Prescl", &L1Tech_BPTX_quiet_v0_Prescl, &b_L1Tech_BPTX_quiet_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit28", &L1Tech_BRIL_bit28, &b_L1Tech_BRIL_bit28);
   fChain->SetBranchAddress("L1Tech_BRIL_bit28_Prescl", &L1Tech_BRIL_bit28_Prescl, &b_L1Tech_BRIL_bit28_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit29", &L1Tech_BRIL_bit29, &b_L1Tech_BRIL_bit29);
   fChain->SetBranchAddress("L1Tech_BRIL_bit29_Prescl", &L1Tech_BRIL_bit29_Prescl, &b_L1Tech_BRIL_bit29_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit30", &L1Tech_BRIL_bit30, &b_L1Tech_BRIL_bit30);
   fChain->SetBranchAddress("L1Tech_BRIL_bit30_Prescl", &L1Tech_BRIL_bit30_Prescl, &b_L1Tech_BRIL_bit30_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit31", &L1Tech_BRIL_bit31, &b_L1Tech_BRIL_bit31);
   fChain->SetBranchAddress("L1Tech_BRIL_bit31_Prescl", &L1Tech_BRIL_bit31_Prescl, &b_L1Tech_BRIL_bit31_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit32", &L1Tech_BRIL_bit32, &b_L1Tech_BRIL_bit32);
   fChain->SetBranchAddress("L1Tech_BRIL_bit32_Prescl", &L1Tech_BRIL_bit32_Prescl, &b_L1Tech_BRIL_bit32_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit33", &L1Tech_BRIL_bit33, &b_L1Tech_BRIL_bit33);
   fChain->SetBranchAddress("L1Tech_BRIL_bit33_Prescl", &L1Tech_BRIL_bit33_Prescl, &b_L1Tech_BRIL_bit33_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit34", &L1Tech_BRIL_bit34, &b_L1Tech_BRIL_bit34);
   fChain->SetBranchAddress("L1Tech_BRIL_bit34_Prescl", &L1Tech_BRIL_bit34_Prescl, &b_L1Tech_BRIL_bit34_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit35", &L1Tech_BRIL_bit35, &b_L1Tech_BRIL_bit35);
   fChain->SetBranchAddress("L1Tech_BRIL_bit35_Prescl", &L1Tech_BRIL_bit35_Prescl, &b_L1Tech_BRIL_bit35_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit36", &L1Tech_BRIL_bit36, &b_L1Tech_BRIL_bit36);
   fChain->SetBranchAddress("L1Tech_BRIL_bit36_Prescl", &L1Tech_BRIL_bit36_Prescl, &b_L1Tech_BRIL_bit36_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit37", &L1Tech_BRIL_bit37, &b_L1Tech_BRIL_bit37);
   fChain->SetBranchAddress("L1Tech_BRIL_bit37_Prescl", &L1Tech_BRIL_bit37_Prescl, &b_L1Tech_BRIL_bit37_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit38", &L1Tech_BRIL_bit38, &b_L1Tech_BRIL_bit38);
   fChain->SetBranchAddress("L1Tech_BRIL_bit38_Prescl", &L1Tech_BRIL_bit38_Prescl, &b_L1Tech_BRIL_bit38_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit39", &L1Tech_BRIL_bit39, &b_L1Tech_BRIL_bit39);
   fChain->SetBranchAddress("L1Tech_BRIL_bit39_Prescl", &L1Tech_BRIL_bit39_Prescl, &b_L1Tech_BRIL_bit39_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit40", &L1Tech_BRIL_bit40, &b_L1Tech_BRIL_bit40);
   fChain->SetBranchAddress("L1Tech_BRIL_bit40_Prescl", &L1Tech_BRIL_bit40_Prescl, &b_L1Tech_BRIL_bit40_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit41", &L1Tech_BRIL_bit41, &b_L1Tech_BRIL_bit41);
   fChain->SetBranchAddress("L1Tech_BRIL_bit41_Prescl", &L1Tech_BRIL_bit41_Prescl, &b_L1Tech_BRIL_bit41_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit42", &L1Tech_BRIL_bit42, &b_L1Tech_BRIL_bit42);
   fChain->SetBranchAddress("L1Tech_BRIL_bit42_Prescl", &L1Tech_BRIL_bit42_Prescl, &b_L1Tech_BRIL_bit42_Prescl);
   fChain->SetBranchAddress("L1Tech_BRIL_bit43", &L1Tech_BRIL_bit43, &b_L1Tech_BRIL_bit43);
   fChain->SetBranchAddress("L1Tech_BRIL_bit43_Prescl", &L1Tech_BRIL_bit43_Prescl, &b_L1Tech_BRIL_bit43_Prescl);
   fChain->SetBranchAddress("L1Tech_CASTOR_Gap.v0", &L1Tech_CASTOR_Gap_v0, &b_L1Tech_CASTOR_Gap_v0);
   fChain->SetBranchAddress("L1Tech_CASTOR_Gap.v0_Prescl", &L1Tech_CASTOR_Gap_v0_Prescl, &b_L1Tech_CASTOR_Gap_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0", &L1Tech_CASTOR_HaloMuon_v0, &b_L1Tech_CASTOR_HaloMuon_v0);
   fChain->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_Prescl", &L1Tech_CASTOR_HaloMuon_v0_Prescl, &b_L1Tech_CASTOR_HaloMuon_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_CASTOR_HighJet.v0", &L1Tech_CASTOR_HighJet_v0, &b_L1Tech_CASTOR_HighJet_v0);
   fChain->SetBranchAddress("L1Tech_CASTOR_HighJet.v0_Prescl", &L1Tech_CASTOR_HighJet_v0_Prescl, &b_L1Tech_CASTOR_HighJet_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_CASTOR_MediumJet.v0", &L1Tech_CASTOR_MediumJet_v0, &b_L1Tech_CASTOR_MediumJet_v0);
   fChain->SetBranchAddress("L1Tech_CASTOR_MediumJet.v0_Prescl", &L1Tech_CASTOR_MediumJet_v0_Prescl, &b_L1Tech_CASTOR_MediumJet_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_DT_GlobalOR.v0", &L1Tech_DT_GlobalOR_v0, &b_L1Tech_DT_GlobalOR_v0);
   fChain->SetBranchAddress("L1Tech_DT_GlobalOR.v0_Prescl", &L1Tech_DT_GlobalOR_v0_Prescl, &b_L1Tech_DT_GlobalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0", &L1Tech_HCAL_HBHE_totalOR_v0, &b_L1Tech_HCAL_HBHE_totalOR_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_Prescl", &L1Tech_HCAL_HBHE_totalOR_v0_Prescl, &b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MMP_or_MPP.v1", &L1Tech_HCAL_HF_MMP_or_MPP_v1, &b_L1Tech_HCAL_HF_MMP_or_MPP_v1);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MMP_or_MPP.v1_Prescl", &L1Tech_HCAL_HF_MMP_or_MPP_v1_Prescl, &b_L1Tech_HCAL_HF_MMP_or_MPP_v1_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_coincidence_PM.v2", &L1Tech_HCAL_HF_coincidence_PM_v2, &b_L1Tech_HCAL_HF_coincidence_PM_v2);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_coincidence_PM.v2_Prescl", &L1Tech_HCAL_HF_coincidence_PM_v2_Prescl, &b_L1Tech_HCAL_HF_coincidence_PM_v2_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_single_channel.v0", &L1Tech_HCAL_HF_single_channel_v0, &b_L1Tech_HCAL_HF_single_channel_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_single_channel.v0_Prescl", &L1Tech_HCAL_HF_single_channel_v0_Prescl, &b_L1Tech_HCAL_HF_single_channel_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HO_totalOR.v0", &L1Tech_HCAL_HO_totalOR_v0, &b_L1Tech_HCAL_HO_totalOR_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HO_totalOR.v0_Prescl", &L1Tech_HCAL_HO_totalOR_v0_Prescl, &b_L1Tech_HCAL_HO_totalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0", &L1Tech_RPC_TTU_RBplus1_Cosmics_v0, &b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0", &L1Tech_RPC_TTU_RBplus2_Cosmics_v0, &b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0", &L1Tech_RPC_TTU_barrel_Cosmics_v0, &b_L1Tech_RPC_TTU_barrel_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0", &L1Tech_RPC_TTU_pointing_Cosmics_v0, &b_L1Tech_RPC_TTU_pointing_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_TOTEM_0", &L1Tech_TOTEM_0, &b_L1Tech_TOTEM_0);
   fChain->SetBranchAddress("L1Tech_TOTEM_0_Prescl", &L1Tech_TOTEM_0_Prescl, &b_L1Tech_TOTEM_0_Prescl);
   fChain->SetBranchAddress("L1Tech_TOTEM_1", &L1Tech_TOTEM_1, &b_L1Tech_TOTEM_1);
   fChain->SetBranchAddress("L1Tech_TOTEM_1_Prescl", &L1Tech_TOTEM_1_Prescl, &b_L1Tech_TOTEM_1_Prescl);
   fChain->SetBranchAddress("L1Tech_TOTEM_2", &L1Tech_TOTEM_2, &b_L1Tech_TOTEM_2);
   fChain->SetBranchAddress("L1Tech_TOTEM_2_Prescl", &L1Tech_TOTEM_2_Prescl, &b_L1Tech_TOTEM_2_Prescl);
   fChain->SetBranchAddress("L1Tech_TOTEM_3", &L1Tech_TOTEM_3, &b_L1Tech_TOTEM_3);
   fChain->SetBranchAddress("L1Tech_TOTEM_3_Prescl", &L1Tech_TOTEM_3_Prescl, &b_L1Tech_TOTEM_3_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_minus", &L1Tech_ZDC_minus, &b_L1Tech_ZDC_minus);
   fChain->SetBranchAddress("L1Tech_ZDC_minus_Prescl", &L1Tech_ZDC_minus_Prescl, &b_L1Tech_ZDC_minus_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_plus", &L1Tech_ZDC_plus, &b_L1Tech_ZDC_plus);
   fChain->SetBranchAddress("L1Tech_ZDC_plus_Prescl", &L1Tech_ZDC_plus_Prescl, &b_L1Tech_ZDC_plus_Prescl);
   Notify();
}

Bool_t hltTreeReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hltTreeReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hltTreeReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef hltTreeReader_cxx
