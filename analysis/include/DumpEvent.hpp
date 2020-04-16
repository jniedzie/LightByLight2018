//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 30 11:50:23 2020 by ROOT version 6.16/00
// from TTree EventTree/Event data
// found on file: merged_ntuples_4.root
//////////////////////////////////////////////////////////

#ifndef DumpEvent_h
#define DumpEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "map"
#include "algorithm"
#include "fstream"

using namespace std;

// PARAMETER
const double aco_cut = 0.01;

class DumpEvent {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // set of interesting events
   map<vector<int>, float> goodevents;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   ULong64_t       event;
   UInt_t          lumis;
   Bool_t          isData;
   Float_t         rho;
   Int_t           nSC;
   vector<float>   *scE;
   vector<float>   *scRawE;
   vector<float>   *scEta;
   vector<float>   *scPhi;
   Int_t           nEle;
   vector<int>     *eleCharge;
   vector<int>     *eleChargeConsistent;
   vector<int>     *eleSCPixCharge;
   vector<int>     *eleCtfCharge;
   vector<float>   *eleEn;
   vector<float>   *eleD0;
   vector<float>   *eleDz;
   vector<float>   *eleIP3D;
   vector<float>   *eleD0Err;
   vector<float>   *eleDzErr;
   vector<float>   *eleIP3DErr;
   vector<float>   *eleTrkPt;
   vector<float>   *eleTrkEta;
   vector<float>   *eleTrkPhi;
   vector<int>     *eleTrkCharge;
   vector<float>   *eleTrkPtErr;
   vector<float>   *eleTrkChi2;
   vector<float>   *eleTrkNdof;
   vector<float>   *eleTrkNormalizedChi2;
   vector<int>     *eleTrkValidHits;
   vector<int>     *eleTrkLayers;
   vector<float>   *elePt;
   vector<float>   *eleEta;
   vector<float>   *elePhi;
   vector<float>   *eleSCEn;
   vector<float>   *eleESEn;
   vector<float>   *eleSCEta;
   vector<float>   *eleSCPhi;
   vector<float>   *eleSCRawEn;
   vector<float>   *eleSCEtaWidth;
   vector<float>   *eleSCPhiWidth;
   vector<float>   *eleHoverE;
   vector<float>   *eleHoverEBc;
   vector<float>   *eleEoverP;
   vector<float>   *eleEoverPInv;
   vector<float>   *eleEcalE;
   vector<float>   *elePAtVtx;
   vector<float>   *elePAtSC;
   vector<float>   *elePAtCluster;
   vector<float>   *elePAtSeed;
   vector<float>   *eleBrem;
   vector<float>   *eledEtaAtVtx;
   vector<float>   *eledPhiAtVtx;
   vector<float>   *eledEtaSeedAtVtx;
   vector<float>   *eleSigmaIEtaIEta;
   vector<float>   *eleSigmaIEtaIEta_2012;
   vector<float>   *eleSigmaIPhiIPhi;
   vector<int>     *eleConvVeto;
   vector<int>     *eleMissHits;
   vector<float>   *eleESEffSigmaRR;
   vector<float>   *elePFChIso;
   vector<float>   *elePFPhoIso;
   vector<float>   *elePFNeuIso;
   vector<float>   *elePFPUIso;
   vector<float>   *elePFRelIsoWithEA;
   vector<float>   *elePFRelIsoWithDBeta;
   vector<float>   *eleEffAreaTimesRho;
   vector<float>   *eleR9;
   vector<float>   *eleE3x3;
   vector<float>   *eleE5x5;
   vector<float>   *eleR9Full5x5;
   vector<float>   *eleE3x3Full5x5;
   vector<float>   *eleE5x5Full5x5;
   vector<int>     *NClusters;
   vector<int>     *NEcalClusters;
   vector<float>   *eleSeedEn;
   vector<float>   *eleSeedEta;
   vector<float>   *eleSeedPhi;
   vector<float>   *eleSeedCryEta;
   vector<float>   *eleSeedCryPhi;
   vector<float>   *eleSeedCryIeta;
   vector<float>   *eleSeedCryIphi;
   vector<float>   *eleBC1E;
   vector<float>   *eleBC1Eta;
   vector<float>   *eleBC2E;
   vector<float>   *eleBC2Eta;
   Int_t           nPho;
   vector<float>   *phoE;
   vector<float>   *phoEt;
   vector<float>   *phoEta;
   vector<float>   *phoPhi;
   vector<float>   *phoEcorrStdEcal;
   vector<float>   *phoEcorrPhoEcal;
   vector<float>   *phoEcorrRegr1;
   vector<float>   *phoEcorrRegr2;
   vector<float>   *phoEcorrErrStdEcal;
   vector<float>   *phoEcorrErrPhoEcal;
   vector<float>   *phoEcorrErrRegr1;
   vector<float>   *phoEcorrErrRegr2;
   vector<float>   *phoSCE;
   vector<float>   *phoSCEt;
   vector<float>   *phoSCRawE;
   vector<float>   *phoSCEta;
   vector<float>   *phoSCPhi;
   vector<float>   *phoSCEtaWidth;
   vector<float>   *phoSCPhiWidth;
   vector<float>   *phoSCBrem;
   vector<int>     *phoSCnHits;
   vector<unsigned int> *phoSCflags;
   vector<int>     *phoSCinClean;
   vector<int>     *phoSCinUnClean;
   vector<int>     *phoSCnBC;
   vector<float>   *phoESEn;
   vector<float>   *phoPSCE;
   vector<float>   *phoPSCRawE;
   vector<float>   *phoPSCEta;
   vector<float>   *phoPSCPhi;
   vector<float>   *phoPSCEtaWidth;
   vector<float>   *phoPSCPhiWidth;
   vector<float>   *phoPSCBrem;
   vector<int>     *phoPSCnHits;
   vector<unsigned int> *phoPSCflags;
   vector<int>     *phoPSCinClean;
   vector<int>     *phoPSCinUnClean;
   vector<int>     *phoPSCnBC;
   vector<float>   *phoPESEn;
   vector<int>     *phoIsPFPhoton;
   vector<int>     *phoIsStandardPhoton;
   vector<int>     *phoHasPixelSeed;
   vector<int>     *phoHasConversionTracks;
   vector<float>   *phoHadTowerOverEm;
   vector<float>   *phoHoverE;
   vector<int>     *phoHoverEValid;
   vector<float>   *phoSigmaIEtaIEta;
   vector<float>   *phoR9;
   vector<float>   *phoE1x5;
   vector<float>   *phoE2x5;
   vector<float>   *phoE3x3;
   vector<float>   *phoE5x5;
   vector<float>   *phoMaxEnergyXtal;
   vector<float>   *phoSigmaEtaEta;
   vector<float>   *phoSigmaIEtaIEta_2012;
   vector<float>   *phoR9_2012;
   vector<float>   *phoE1x5_2012;
   vector<float>   *phoE2x5_2012;
   vector<float>   *phoE3x3_2012;
   vector<float>   *phoE5x5_2012;
   vector<float>   *phoMaxEnergyXtal_2012;
   vector<float>   *phoSigmaEtaEta_2012;
   vector<float>   *phoHadTowerOverEm1;
   vector<float>   *phoHadTowerOverEm2;
   vector<float>   *phoHoverE1;
   vector<float>   *phoHoverE2;
   vector<float>   *phoSigmaIEtaIPhi;
   vector<float>   *phoSigmaIPhiIPhi;
   vector<float>   *phoR1x5;
   vector<float>   *phoR2x5;
   vector<float>   *phoE2nd;
   vector<float>   *phoETop;
   vector<float>   *phoEBottom;
   vector<float>   *phoELeft;
   vector<float>   *phoERight;
   vector<float>   *phoE1x3;
   vector<float>   *phoE2x2;
   vector<float>   *phoE2x5Max;
   vector<float>   *phoE2x5Top;
   vector<float>   *phoE2x5Bottom;
   vector<float>   *phoE2x5Left;
   vector<float>   *phoE2x5Right;
   vector<float>   *phoSigmaIEtaIPhi_2012;
   vector<float>   *phoSigmaIPhiIPhi_2012;
   vector<float>   *phoR1x5_2012;
   vector<float>   *phoR2x5_2012;
   vector<float>   *phoE2nd_2012;
   vector<float>   *phoETop_2012;
   vector<float>   *phoEBottom_2012;
   vector<float>   *phoELeft_2012;
   vector<float>   *phoERight_2012;
   vector<float>   *phoE1x3_2012;
   vector<float>   *phoE2x2_2012;
   vector<float>   *phoE2x5Max_2012;
   vector<float>   *phoE2x5Top_2012;
   vector<float>   *phoE2x5Bottom_2012;
   vector<float>   *phoE2x5Left_2012;
   vector<float>   *phoE2x5Right_2012;
   vector<float>   *phoBC1E;
   vector<float>   *phoBC1Ecorr;
   vector<float>   *phoBC1Eta;
   vector<float>   *phoBC1Phi;
   vector<int>     *phoBC1size;
   vector<unsigned int> *phoBC1flags;
   vector<int>     *phoBC1inClean;
   vector<int>     *phoBC1inUnClean;
   vector<unsigned int> *phoBC1rawID;
   vector<float>   *pho_ecalClusterIsoR2;
   vector<float>   *pho_ecalClusterIsoR3;
   vector<float>   *pho_ecalClusterIsoR4;
   vector<float>   *pho_ecalClusterIsoR5;
   vector<float>   *pho_hcalRechitIsoR1;
   vector<float>   *pho_hcalRechitIsoR2;
   vector<float>   *pho_hcalRechitIsoR3;
   vector<float>   *pho_hcalRechitIsoR4;
   vector<float>   *pho_hcalRechitIsoR5;
   vector<float>   *pho_trackIsoR1PtCut20;
   vector<float>   *pho_trackIsoR2PtCut20;
   vector<float>   *pho_trackIsoR3PtCut20;
   vector<float>   *pho_trackIsoR4PtCut20;
   vector<float>   *pho_trackIsoR5PtCut20;
   vector<float>   *pho_swissCrx;
   vector<float>   *pho_seedTime;
   Int_t           nMu;
   vector<float>   *muPt;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<int>     *muCharge;
   vector<int>     *muType;
   vector<int>     *muIsGood;
   vector<int>     *muIsGlobal;
   vector<int>     *muIsTracker;
   vector<int>     *muIsPF;
   vector<int>     *muIsSTA;
   vector<float>   *muD0;
   vector<float>   *muDz;
   vector<float>   *muIP3D;
   vector<float>   *muD0Err;
   vector<float>   *muDzErr;
   vector<float>   *muIP3DErr;
   vector<float>   *muChi2NDF;
   vector<float>   *muInnerD0;
   vector<float>   *muInnerDz;
   vector<float>   *muInnerD0Err;
   vector<float>   *muInnerDzErr;
   vector<float>   *muInnerPt;
   vector<float>   *muInnerPtErr;
   vector<float>   *muInnerEta;
   vector<int>     *muTrkLayers;
   vector<int>     *muPixelLayers;
   vector<int>     *muPixelHits;
   vector<int>     *muMuonHits;
   vector<int>     *muTrkQuality;
   vector<int>     *muStations;
   vector<float>   *muIsoTrk;
   vector<float>   *muPFChIso;
   vector<float>   *muPFPhoIso;
   vector<float>   *muPFNeuIso;
   vector<float>   *muPFPUIso;
   vector<int>     *muIDSoft;
   vector<int>     *muIDLoose;
   vector<int>     *muIDMedium;
   vector<int>     *muIDMediumPrompt;
   vector<int>     *muIDTight;
   vector<int>     *muIDGlobalHighPt;
   vector<int>     *muIDTrkHighPt;
   vector<int>     *muIDInTime;
   Int_t           nTrk;
   vector<float>   *trkPt;
   vector<float>   *trkP;
   vector<float>   *trkEta;
   vector<float>   *trkPhi;
   vector<int>     *trkcharge;
   vector<float>   *trkvx;
   vector<float>   *trkvy;
   vector<float>   *trkvz;
   vector<float>   *trknormchi2;
   vector<float>   *trkchi2;
   vector<float>   *trkd0;
   vector<float>   *trkdxy;
   vector<float>   *trkdz;
   vector<float>   *trkdxyBS;
   vector<float>   *trkdzBS;
   vector<float>   *trkdxyError;
   vector<float>   *trkdzError;
   vector<int>     *trkValidHits;
   vector<int>     *trkMissHits;
   vector<int>     *trkPurity;
   Int_t           nTower;
   vector<float>   *CaloTower_hadE;
   vector<float>   *CaloTower_emE;
   vector<float>   *CaloTower_e;
   vector<float>   *CaloTower_et;
   vector<float>   *CaloTower_eta;
   vector<float>   *CaloTower_phi;
   Int_t           nTrackerHits;
   Int_t           nPixelClusters;
   Int_t           nPixelRecHits;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_nSC;   //!
   TBranch        *b_scE;   //!
   TBranch        *b_scRawE;   //!
   TBranch        *b_scEta;   //!
   TBranch        *b_scPhi;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleChargeConsistent;   //!
   TBranch        *b_eleSCPixCharge;   //!
   TBranch        *b_eleCtfCharge;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleIP3D;   //!
   TBranch        *b_eleD0Err;   //!
   TBranch        *b_eleDzErr;   //!
   TBranch        *b_eleIP3DErr;   //!
   TBranch        *b_eleTrkPt;   //!
   TBranch        *b_eleTrkEta;   //!
   TBranch        *b_eleTrkPhi;   //!
   TBranch        *b_eleTrkCharge;   //!
   TBranch        *b_eleTrkPtErr;   //!
   TBranch        *b_eleTrkChi2;   //!
   TBranch        *b_eleTrkNdof;   //!
   TBranch        *b_eleTrkNormalizedChi2;   //!
   TBranch        *b_eleTrkValidHits;   //!
   TBranch        *b_eleTrkLayers;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleESEn;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleSCRawEn;   //!
   TBranch        *b_eleSCEtaWidth;   //!
   TBranch        *b_eleSCPhiWidth;   //!
   TBranch        *b_eleHoverE;   //!
   TBranch        *b_eleHoverEBc;   //!
   TBranch        *b_eleEoverP;   //!
   TBranch        *b_eleEoverPInv;   //!
   TBranch        *b_eleEcalE;   //!
   TBranch        *b_elePAtVtx;   //!
   TBranch        *b_elePAtSC;   //!
   TBranch        *b_elePAtCluster;   //!
   TBranch        *b_elePAtSeed;   //!
   TBranch        *b_eleBrem;   //!
   TBranch        *b_eledEtaAtVtx;   //!
   TBranch        *b_eledPhiAtVtx;   //!
   TBranch        *b_eledEtaSeedAtVtx;   //!
   TBranch        *b_eleSigmaIEtaIEta;   //!
   TBranch        *b_eleSigmaIEtaIEta_2012;   //!
   TBranch        *b_eleSigmaIPhiIPhi;   //!
   TBranch        *b_eleConvVeto;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_eleESEffSigmaRR;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_elePFPUIso;   //!
   TBranch        *b_elePFRelIsoWithEA;   //!
   TBranch        *b_elePFRelIsoWithDBeta;   //!
   TBranch        *b_eleEffAreaTimesRho;   //!
   TBranch        *b_eleR9;   //!
   TBranch        *b_eleE3x3;   //!
   TBranch        *b_eleE5x5;   //!
   TBranch        *b_eleR9Full5x5;   //!
   TBranch        *b_eleE3x3Full5x5;   //!
   TBranch        *b_eleE5x5Full5x5;   //!
   TBranch        *b_NClusters;   //!
   TBranch        *b_NEcalClusters;   //!
   TBranch        *b_eleSeedEn;   //!
   TBranch        *b_eleSeedEta;   //!
   TBranch        *b_eleSeedPhi;   //!
   TBranch        *b_eleSeedCryEta;   //!
   TBranch        *b_eleSeedCryPhi;   //!
   TBranch        *b_eleSeedCryIeta;   //!
   TBranch        *b_eleSeedCryIphi;   //!
   TBranch        *b_eleBC1E;   //!
   TBranch        *b_eleBC1Eta;   //!
   TBranch        *b_eleBC2E;   //!
   TBranch        *b_eleBC2Eta;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoEcorrStdEcal;   //!
   TBranch        *b_phoEcorrPhoEcal;   //!
   TBranch        *b_phoEcorrRegr1;   //!
   TBranch        *b_phoEcorrRegr2;   //!
   TBranch        *b_phoEcorrErrStdEcal;   //!
   TBranch        *b_phoEcorrErrPhoEcal;   //!
   TBranch        *b_phoEcorrErrRegr1;   //!
   TBranch        *b_phoEcorrErrRegr2;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCEt;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phoSCnHits;   //!
   TBranch        *b_phoSCflags;   //!
   TBranch        *b_phoSCinClean;   //!
   TBranch        *b_phoSCinUnClean;   //!
   TBranch        *b_phoSCnBC;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoPSCE;   //!
   TBranch        *b_phoPSCRawE;   //!
   TBranch        *b_phoPSCEta;   //!
   TBranch        *b_phoPSCPhi;   //!
   TBranch        *b_phoPSCEtaWidth;   //!
   TBranch        *b_phoPSCPhiWidth;   //!
   TBranch        *b_phoPSCBrem;   //!
   TBranch        *b_phoPSCnHits;   //!
   TBranch        *b_phoPSCflags;   //!
   TBranch        *b_phoPSCinClean;   //!
   TBranch        *b_phoPSCinUnClean;   //!
   TBranch        *b_phoPSCnBC;   //!
   TBranch        *b_phoPESEn;   //!
   TBranch        *b_phoIsPFPhoton;   //!
   TBranch        *b_phoIsStandardPhoton;   //!
   TBranch        *b_phoHasPixelSeed;   //!
   TBranch        *b_phoHasConversionTracks;   //!
   TBranch        *b_phoHadTowerOverEm;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoHoverEValid;   //!
   TBranch        *b_phoSigmaIEtaIEta;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoE1x5;   //!
   TBranch        *b_phoE2x5;   //!
   TBranch        *b_phoE3x3;   //!
   TBranch        *b_phoE5x5;   //!
   TBranch        *b_phoMaxEnergyXtal;   //!
   TBranch        *b_phoSigmaEtaEta;   //!
   TBranch        *b_phoSigmaIEtaIEta_2012;   //!
   TBranch        *b_phoR9_2012;   //!
   TBranch        *b_phoE1x5_2012;   //!
   TBranch        *b_phoE2x5_2012;   //!
   TBranch        *b_phoE3x3_2012;   //!
   TBranch        *b_phoE5x5_2012;   //!
   TBranch        *b_phoMaxEnergyXtal_2012;   //!
   TBranch        *b_phoSigmaEtaEta_2012;   //!
   TBranch        *b_phoHadTowerOverEm1;   //!
   TBranch        *b_phoHadTowerOverEm2;   //!
   TBranch        *b_phoHoverE1;   //!
   TBranch        *b_phoHoverE2;   //!
   TBranch        *b_phoSigmaIEtaIPhi;   //!
   TBranch        *b_phoSigmaIPhiIPhi;   //!
   TBranch        *b_phoR1x5;   //!
   TBranch        *b_phoR2x5;   //!
   TBranch        *b_phoE2nd;   //!
   TBranch        *b_phoETop;   //!
   TBranch        *b_phoEBottom;   //!
   TBranch        *b_phoELeft;   //!
   TBranch        *b_phoERight;   //!
   TBranch        *b_phoE1x3;   //!
   TBranch        *b_phoE2x2;   //!
   TBranch        *b_phoE2x5Max;   //!
   TBranch        *b_phoE2x5Top;   //!
   TBranch        *b_phoE2x5Bottom;   //!
   TBranch        *b_phoE2x5Left;   //!
   TBranch        *b_phoE2x5Right;   //!
   TBranch        *b_phoSigmaIEtaIPhi_2012;   //!
   TBranch        *b_phoSigmaIPhiIPhi_2012;   //!
   TBranch        *b_phoR1x5_2012;   //!
   TBranch        *b_phoR2x5_2012;   //!
   TBranch        *b_phoE2nd_2012;   //!
   TBranch        *b_phoETop_2012;   //!
   TBranch        *b_phoEBottom_2012;   //!
   TBranch        *b_phoELeft_2012;   //!
   TBranch        *b_phoERight_2012;   //!
   TBranch        *b_phoE1x3_2012;   //!
   TBranch        *b_phoE2x2_2012;   //!
   TBranch        *b_phoE2x5Max_2012;   //!
   TBranch        *b_phoE2x5Top_2012;   //!
   TBranch        *b_phoE2x5Bottom_2012;   //!
   TBranch        *b_phoE2x5Left_2012;   //!
   TBranch        *b_phoE2x5Right_2012;   //!
   TBranch        *b_phoBC1E;   //!
   TBranch        *b_phoBC1Ecorr;   //!
   TBranch        *b_phoBC1Eta;   //!
   TBranch        *b_phoBC1Phi;   //!
   TBranch        *b_phoBC1size;   //!
   TBranch        *b_phoBC1flags;   //!
   TBranch        *b_phoBC1inClean;   //!
   TBranch        *b_phoBC1inUnClean;   //!
   TBranch        *b_phoBC1rawID;   //!
   TBranch        *b_pho_ecalClusterIsoR2;   //!
   TBranch        *b_pho_ecalClusterIsoR3;   //!
   TBranch        *b_pho_ecalClusterIsoR4;   //!
   TBranch        *b_pho_ecalClusterIsoR5;   //!
   TBranch        *b_pho_hcalRechitIsoR1;   //!
   TBranch        *b_pho_hcalRechitIsoR2;   //!
   TBranch        *b_pho_hcalRechitIsoR3;   //!
   TBranch        *b_pho_hcalRechitIsoR4;   //!
   TBranch        *b_pho_hcalRechitIsoR5;   //!
   TBranch        *b_pho_trackIsoR1PtCut20;   //!
   TBranch        *b_pho_trackIsoR2PtCut20;   //!
   TBranch        *b_pho_trackIsoR3PtCut20;   //!
   TBranch        *b_pho_trackIsoR4PtCut20;   //!
   TBranch        *b_pho_trackIsoR5PtCut20;   //!
   TBranch        *b_pho_swissCrx;   //!
   TBranch        *b_pho_seedTime;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muIsGood;   //!
   TBranch        *b_muIsGlobal;   //!
   TBranch        *b_muIsTracker;   //!
   TBranch        *b_muIsPF;   //!
   TBranch        *b_muIsSTA;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muIP3D;   //!
   TBranch        *b_muD0Err;   //!
   TBranch        *b_muDzErr;   //!
   TBranch        *b_muIP3DErr;   //!
   TBranch        *b_muChi2NDF;   //!
   TBranch        *b_muInnerD0;   //!
   TBranch        *b_muInnerDz;   //!
   TBranch        *b_muInnerD0Err;   //!
   TBranch        *b_muInnerDzErr;   //!
   TBranch        *b_muInnerPt;   //!
   TBranch        *b_muInnerPtErr;   //!
   TBranch        *b_muInnerEta;   //!
   TBranch        *b_muTrkLayers;   //!
   TBranch        *b_muPixelLayers;   //!
   TBranch        *b_muPixelHits;   //!
   TBranch        *b_muMuonHits;   //!
   TBranch        *b_muTrkQuality;   //!
   TBranch        *b_muStations;   //!
   TBranch        *b_muIsoTrk;   //!
   TBranch        *b_muPFChIso;   //!
   TBranch        *b_muPFPhoIso;   //!
   TBranch        *b_muPFNeuIso;   //!
   TBranch        *b_muPFPUIso;   //!
   TBranch        *b_muIDSoft;   //!
   TBranch        *b_muIDLoose;   //!
   TBranch        *b_muIDMedium;   //!
   TBranch        *b_muIDMediumPrompt;   //!
   TBranch        *b_muIDTight;   //!
   TBranch        *b_muIDGlobalHighPt;   //!
   TBranch        *b_muIDTrkHighPt;   //!
   TBranch        *b_muIDInTime;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkP;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_trkcharge;   //!
   TBranch        *b_trkvx;   //!
   TBranch        *b_trkvy;   //!
   TBranch        *b_trkvz;   //!
   TBranch        *b_trknormchi2;   //!
   TBranch        *b_trkchi2;   //!
   TBranch        *b_trkd0;   //!
   TBranch        *b_trkdxy;   //!
   TBranch        *b_trkdz;   //!
   TBranch        *b_trkdxyBS;   //!
   TBranch        *b_trkdzBS;   //!
   TBranch        *b_trkdxyError;   //!
   TBranch        *b_trkdzError;   //!
   TBranch        *b_trkValidHits;   //!
   TBranch        *b_trkMissHits;   //!
   TBranch        *b_trkPurity;   //!
   TBranch        *b_nTower;   //!
   TBranch        *b_CaloTower_hadE;   //!
   TBranch        *b_CaloTower_emE;   //!
   TBranch        *b_CaloTower_e;   //!
   TBranch        *b_CaloTower_et;   //!
   TBranch        *b_CaloTower_eta;   //!
   TBranch        *b_CaloTower_phi;   //!
   TBranch        *b_nTrackerHits;   //!
   TBranch        *b_nPixelClusters;   //!
   TBranch        *b_nPixelRecHits;   //!

   DumpEvent(TTree *tree=0);
   virtual ~DumpEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString histfilename, bool dolowaco);
   virtual void     Loop_evtlist();
   virtual void     dump(Long64_t entry);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     FillGoodEvents(TString filename);
};

#endif

#ifdef DumpEvent_cxx
DumpEvent::DumpEvent(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("merged_ntuples_4.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("merged_ntuples_4.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("merged_ntuples_4.root:/ggHiNtuplizer");
      dir->GetObject("EventTree",tree);

   }
   Init(tree);
   FillGoodEvents("/afs/cern.ch/user/e/echapon/workspace/private/LightByLight_2018PbPb/LightByLight2018/analysis/condor/PASSING.list");
}

DumpEvent::~DumpEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DumpEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DumpEvent::LoadTree(Long64_t entry)
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

void DumpEvent::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   scE = 0;
   scRawE = 0;
   scEta = 0;
   scPhi = 0;
   eleCharge = 0;
   eleChargeConsistent = 0;
   eleSCPixCharge = 0;
   eleCtfCharge = 0;
   eleEn = 0;
   eleD0 = 0;
   eleDz = 0;
   eleIP3D = 0;
   eleD0Err = 0;
   eleDzErr = 0;
   eleIP3DErr = 0;
   eleTrkPt = 0;
   eleTrkEta = 0;
   eleTrkPhi = 0;
   eleTrkCharge = 0;
   eleTrkPtErr = 0;
   eleTrkChi2 = 0;
   eleTrkNdof = 0;
   eleTrkNormalizedChi2 = 0;
   eleTrkValidHits = 0;
   eleTrkLayers = 0;
   elePt = 0;
   eleEta = 0;
   elePhi = 0;
   eleSCEn = 0;
   eleESEn = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleSCRawEn = 0;
   eleSCEtaWidth = 0;
   eleSCPhiWidth = 0;
   eleHoverE = 0;
   eleHoverEBc = 0;
   eleEoverP = 0;
   eleEoverPInv = 0;
   eleEcalE = 0;
   elePAtVtx = 0;
   elePAtSC = 0;
   elePAtCluster = 0;
   elePAtSeed = 0;
   eleBrem = 0;
   eledEtaAtVtx = 0;
   eledPhiAtVtx = 0;
   eledEtaSeedAtVtx = 0;
   eleSigmaIEtaIEta = 0;
   eleSigmaIEtaIEta_2012 = 0;
   eleSigmaIPhiIPhi = 0;
   eleConvVeto = 0;
   eleMissHits = 0;
   eleESEffSigmaRR = 0;
   elePFChIso = 0;
   elePFPhoIso = 0;
   elePFNeuIso = 0;
   elePFPUIso = 0;
   elePFRelIsoWithEA = 0;
   elePFRelIsoWithDBeta = 0;
   eleEffAreaTimesRho = 0;
   eleR9 = 0;
   eleE3x3 = 0;
   eleE5x5 = 0;
   eleR9Full5x5 = 0;
   eleE3x3Full5x5 = 0;
   eleE5x5Full5x5 = 0;
   NClusters = 0;
   NEcalClusters = 0;
   eleSeedEn = 0;
   eleSeedEta = 0;
   eleSeedPhi = 0;
   eleSeedCryEta = 0;
   eleSeedCryPhi = 0;
   eleSeedCryIeta = 0;
   eleSeedCryIphi = 0;
   eleBC1E = 0;
   eleBC1Eta = 0;
   eleBC2E = 0;
   eleBC2Eta = 0;
   phoE = 0;
   phoEt = 0;
   phoEta = 0;
   phoPhi = 0;
   phoEcorrStdEcal = 0;
   phoEcorrPhoEcal = 0;
   phoEcorrRegr1 = 0;
   phoEcorrRegr2 = 0;
   phoEcorrErrStdEcal = 0;
   phoEcorrErrPhoEcal = 0;
   phoEcorrErrRegr1 = 0;
   phoEcorrErrRegr2 = 0;
   phoSCE = 0;
   phoSCEt = 0;
   phoSCRawE = 0;
   phoSCEta = 0;
   phoSCPhi = 0;
   phoSCEtaWidth = 0;
   phoSCPhiWidth = 0;
   phoSCBrem = 0;
   phoSCnHits = 0;
   phoSCflags = 0;
   phoSCinClean = 0;
   phoSCinUnClean = 0;
   phoSCnBC = 0;
   phoESEn = 0;
   phoPSCE = 0;
   phoPSCRawE = 0;
   phoPSCEta = 0;
   phoPSCPhi = 0;
   phoPSCEtaWidth = 0;
   phoPSCPhiWidth = 0;
   phoPSCBrem = 0;
   phoPSCnHits = 0;
   phoPSCflags = 0;
   phoPSCinClean = 0;
   phoPSCinUnClean = 0;
   phoPSCnBC = 0;
   phoPESEn = 0;
   phoIsPFPhoton = 0;
   phoIsStandardPhoton = 0;
   phoHasPixelSeed = 0;
   phoHasConversionTracks = 0;
   phoHadTowerOverEm = 0;
   phoHoverE = 0;
   phoHoverEValid = 0;
   phoSigmaIEtaIEta = 0;
   phoR9 = 0;
   phoE1x5 = 0;
   phoE2x5 = 0;
   phoE3x3 = 0;
   phoE5x5 = 0;
   phoMaxEnergyXtal = 0;
   phoSigmaEtaEta = 0;
   phoSigmaIEtaIEta_2012 = 0;
   phoR9_2012 = 0;
   phoE1x5_2012 = 0;
   phoE2x5_2012 = 0;
   phoE3x3_2012 = 0;
   phoE5x5_2012 = 0;
   phoMaxEnergyXtal_2012 = 0;
   phoSigmaEtaEta_2012 = 0;
   phoHadTowerOverEm1 = 0;
   phoHadTowerOverEm2 = 0;
   phoHoverE1 = 0;
   phoHoverE2 = 0;
   phoSigmaIEtaIPhi = 0;
   phoSigmaIPhiIPhi = 0;
   phoR1x5 = 0;
   phoR2x5 = 0;
   phoE2nd = 0;
   phoETop = 0;
   phoEBottom = 0;
   phoELeft = 0;
   phoERight = 0;
   phoE1x3 = 0;
   phoE2x2 = 0;
   phoE2x5Max = 0;
   phoE2x5Top = 0;
   phoE2x5Bottom = 0;
   phoE2x5Left = 0;
   phoE2x5Right = 0;
   phoSigmaIEtaIPhi_2012 = 0;
   phoSigmaIPhiIPhi_2012 = 0;
   phoR1x5_2012 = 0;
   phoR2x5_2012 = 0;
   phoE2nd_2012 = 0;
   phoETop_2012 = 0;
   phoEBottom_2012 = 0;
   phoELeft_2012 = 0;
   phoERight_2012 = 0;
   phoE1x3_2012 = 0;
   phoE2x2_2012 = 0;
   phoE2x5Max_2012 = 0;
   phoE2x5Top_2012 = 0;
   phoE2x5Bottom_2012 = 0;
   phoE2x5Left_2012 = 0;
   phoE2x5Right_2012 = 0;
   phoBC1E = 0;
   phoBC1Ecorr = 0;
   phoBC1Eta = 0;
   phoBC1Phi = 0;
   phoBC1size = 0;
   phoBC1flags = 0;
   phoBC1inClean = 0;
   phoBC1inUnClean = 0;
   phoBC1rawID = 0;
   pho_ecalClusterIsoR2 = 0;
   pho_ecalClusterIsoR3 = 0;
   pho_ecalClusterIsoR4 = 0;
   pho_ecalClusterIsoR5 = 0;
   pho_hcalRechitIsoR1 = 0;
   pho_hcalRechitIsoR2 = 0;
   pho_hcalRechitIsoR3 = 0;
   pho_hcalRechitIsoR4 = 0;
   pho_hcalRechitIsoR5 = 0;
   pho_trackIsoR1PtCut20 = 0;
   pho_trackIsoR2PtCut20 = 0;
   pho_trackIsoR3PtCut20 = 0;
   pho_trackIsoR4PtCut20 = 0;
   pho_trackIsoR5PtCut20 = 0;
   pho_swissCrx = 0;
   pho_seedTime = 0;
   muPt = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIsGood = 0;
   muIsGlobal = 0;
   muIsTracker = 0;
   muIsPF = 0;
   muIsSTA = 0;
   muD0 = 0;
   muDz = 0;
   muIP3D = 0;
   muD0Err = 0;
   muDzErr = 0;
   muIP3DErr = 0;
   muChi2NDF = 0;
   muInnerD0 = 0;
   muInnerDz = 0;
   muInnerD0Err = 0;
   muInnerDzErr = 0;
   muInnerPt = 0;
   muInnerPtErr = 0;
   muInnerEta = 0;
   muTrkLayers = 0;
   muPixelLayers = 0;
   muPixelHits = 0;
   muMuonHits = 0;
   muTrkQuality = 0;
   muStations = 0;
   muIsoTrk = 0;
   muPFChIso = 0;
   muPFPhoIso = 0;
   muPFNeuIso = 0;
   muPFPUIso = 0;
   muIDSoft = 0;
   muIDLoose = 0;
   muIDMedium = 0;
   muIDMediumPrompt = 0;
   muIDTight = 0;
   muIDGlobalHighPt = 0;
   muIDTrkHighPt = 0;
   muIDInTime = 0;
   trkPt = 0;
   trkP = 0;
   trkEta = 0;
   trkPhi = 0;
   trkcharge = 0;
   trkvx = 0;
   trkvy = 0;
   trkvz = 0;
   trknormchi2 = 0;
   trkchi2 = 0;
   trkd0 = 0;
   trkdxy = 0;
   trkdz = 0;
   trkdxyBS = 0;
   trkdzBS = 0;
   trkdxyError = 0;
   trkdzError = 0;
   trkValidHits = 0;
   trkMissHits = 0;
   trkPurity = 0;
   CaloTower_hadE = 0;
   CaloTower_emE = 0;
   CaloTower_e = 0;
   CaloTower_et = 0;
   CaloTower_eta = 0;
   CaloTower_phi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nSC", &nSC, &b_nSC);
   fChain->SetBranchAddress("scE", &scE, &b_scE);
   fChain->SetBranchAddress("scRawE", &scRawE, &b_scRawE);
   fChain->SetBranchAddress("scEta", &scEta, &b_scEta);
   fChain->SetBranchAddress("scPhi", &scPhi, &b_scPhi);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleSCPixCharge", &eleSCPixCharge, &b_eleSCPixCharge);
   fChain->SetBranchAddress("eleCtfCharge", &eleCtfCharge, &b_eleCtfCharge);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleIP3D", &eleIP3D, &b_eleIP3D);
   fChain->SetBranchAddress("eleD0Err", &eleD0Err, &b_eleD0Err);
   fChain->SetBranchAddress("eleDzErr", &eleDzErr, &b_eleDzErr);
   fChain->SetBranchAddress("eleIP3DErr", &eleIP3DErr, &b_eleIP3DErr);
   fChain->SetBranchAddress("eleTrkPt", &eleTrkPt, &b_eleTrkPt);
   fChain->SetBranchAddress("eleTrkEta", &eleTrkEta, &b_eleTrkEta);
   fChain->SetBranchAddress("eleTrkPhi", &eleTrkPhi, &b_eleTrkPhi);
   fChain->SetBranchAddress("eleTrkCharge", &eleTrkCharge, &b_eleTrkCharge);
   fChain->SetBranchAddress("eleTrkPtErr", &eleTrkPtErr, &b_eleTrkPtErr);
   fChain->SetBranchAddress("eleTrkChi2", &eleTrkChi2, &b_eleTrkChi2);
   fChain->SetBranchAddress("eleTrkNdof", &eleTrkNdof, &b_eleTrkNdof);
   fChain->SetBranchAddress("eleTrkNormalizedChi2", &eleTrkNormalizedChi2, &b_eleTrkNormalizedChi2);
   fChain->SetBranchAddress("eleTrkValidHits", &eleTrkValidHits, &b_eleTrkValidHits);
   fChain->SetBranchAddress("eleTrkLayers", &eleTrkLayers, &b_eleTrkLayers);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleESEn", &eleESEn, &b_eleESEn);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
   fChain->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
   fChain->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
   fChain->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
   fChain->SetBranchAddress("eleHoverEBc", &eleHoverEBc, &b_eleHoverEBc);
   fChain->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
   fChain->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
   fChain->SetBranchAddress("eleEcalE", &eleEcalE, &b_eleEcalE);
   fChain->SetBranchAddress("elePAtVtx", &elePAtVtx, &b_elePAtVtx);
   fChain->SetBranchAddress("elePAtSC", &elePAtSC, &b_elePAtSC);
   fChain->SetBranchAddress("elePAtCluster", &elePAtCluster, &b_elePAtCluster);
   fChain->SetBranchAddress("elePAtSeed", &elePAtSeed, &b_elePAtSeed);
   fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
   fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
   fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
   fChain->SetBranchAddress("eledEtaSeedAtVtx", &eledEtaSeedAtVtx, &b_eledEtaSeedAtVtx);
   fChain->SetBranchAddress("eleSigmaIEtaIEta", &eleSigmaIEtaIEta, &b_eleSigmaIEtaIEta);
   fChain->SetBranchAddress("eleSigmaIEtaIEta_2012", &eleSigmaIEtaIEta_2012, &b_eleSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("eleSigmaIPhiIPhi", &eleSigmaIPhiIPhi, &b_eleSigmaIPhiIPhi);
   fChain->SetBranchAddress("eleConvVeto", &eleConvVeto, &b_eleConvVeto);
   fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
   fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
   fChain->SetBranchAddress("elePFRelIsoWithEA", &elePFRelIsoWithEA, &b_elePFRelIsoWithEA);
   fChain->SetBranchAddress("elePFRelIsoWithDBeta", &elePFRelIsoWithDBeta, &b_elePFRelIsoWithDBeta);
   fChain->SetBranchAddress("eleEffAreaTimesRho", &eleEffAreaTimesRho, &b_eleEffAreaTimesRho);
   fChain->SetBranchAddress("eleR9", &eleR9, &b_eleR9);
   fChain->SetBranchAddress("eleE3x3", &eleE3x3, &b_eleE3x3);
   fChain->SetBranchAddress("eleE5x5", &eleE5x5, &b_eleE5x5);
   fChain->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
   fChain->SetBranchAddress("eleE3x3Full5x5", &eleE3x3Full5x5, &b_eleE3x3Full5x5);
   fChain->SetBranchAddress("eleE5x5Full5x5", &eleE5x5Full5x5, &b_eleE5x5Full5x5);
   fChain->SetBranchAddress("NClusters", &NClusters, &b_NClusters);
   fChain->SetBranchAddress("NEcalClusters", &NEcalClusters, &b_NEcalClusters);
   fChain->SetBranchAddress("eleSeedEn", &eleSeedEn, &b_eleSeedEn);
   fChain->SetBranchAddress("eleSeedEta", &eleSeedEta, &b_eleSeedEta);
   fChain->SetBranchAddress("eleSeedPhi", &eleSeedPhi, &b_eleSeedPhi);
   fChain->SetBranchAddress("eleSeedCryEta", &eleSeedCryEta, &b_eleSeedCryEta);
   fChain->SetBranchAddress("eleSeedCryPhi", &eleSeedCryPhi, &b_eleSeedCryPhi);
   fChain->SetBranchAddress("eleSeedCryIeta", &eleSeedCryIeta, &b_eleSeedCryIeta);
   fChain->SetBranchAddress("eleSeedCryIphi", &eleSeedCryIphi, &b_eleSeedCryIphi);
   fChain->SetBranchAddress("eleBC1E", &eleBC1E, &b_eleBC1E);
   fChain->SetBranchAddress("eleBC1Eta", &eleBC1Eta, &b_eleBC1Eta);
   fChain->SetBranchAddress("eleBC2E", &eleBC2E, &b_eleBC2E);
   fChain->SetBranchAddress("eleBC2Eta", &eleBC2Eta, &b_eleBC2Eta);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoEcorrStdEcal", &phoEcorrStdEcal, &b_phoEcorrStdEcal);
   fChain->SetBranchAddress("phoEcorrPhoEcal", &phoEcorrPhoEcal, &b_phoEcorrPhoEcal);
   fChain->SetBranchAddress("phoEcorrRegr1", &phoEcorrRegr1, &b_phoEcorrRegr1);
   fChain->SetBranchAddress("phoEcorrRegr2", &phoEcorrRegr2, &b_phoEcorrRegr2);
   fChain->SetBranchAddress("phoEcorrErrStdEcal", &phoEcorrErrStdEcal, &b_phoEcorrErrStdEcal);
   fChain->SetBranchAddress("phoEcorrErrPhoEcal", &phoEcorrErrPhoEcal, &b_phoEcorrErrPhoEcal);
   fChain->SetBranchAddress("phoEcorrErrRegr1", &phoEcorrErrRegr1, &b_phoEcorrErrRegr1);
   fChain->SetBranchAddress("phoEcorrErrRegr2", &phoEcorrErrRegr2, &b_phoEcorrErrRegr2);
   fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
   fChain->SetBranchAddress("phoSCEt", &phoSCEt, &b_phoSCEt);
   fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
   fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
   fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
   fChain->SetBranchAddress("phoSCBrem", &phoSCBrem, &b_phoSCBrem);
   fChain->SetBranchAddress("phoSCnHits", &phoSCnHits, &b_phoSCnHits);
   fChain->SetBranchAddress("phoSCflags", &phoSCflags, &b_phoSCflags);
   fChain->SetBranchAddress("phoSCinClean", &phoSCinClean, &b_phoSCinClean);
   fChain->SetBranchAddress("phoSCinUnClean", &phoSCinUnClean, &b_phoSCinUnClean);
   fChain->SetBranchAddress("phoSCnBC", &phoSCnBC, &b_phoSCnBC);
   fChain->SetBranchAddress("phoESEn", &phoESEn, &b_phoESEn);
   fChain->SetBranchAddress("phoPSCE", &phoPSCE, &b_phoPSCE);
   fChain->SetBranchAddress("phoPSCRawE", &phoPSCRawE, &b_phoPSCRawE);
   fChain->SetBranchAddress("phoPSCEta", &phoPSCEta, &b_phoPSCEta);
   fChain->SetBranchAddress("phoPSCPhi", &phoPSCPhi, &b_phoPSCPhi);
   fChain->SetBranchAddress("phoPSCEtaWidth", &phoPSCEtaWidth, &b_phoPSCEtaWidth);
   fChain->SetBranchAddress("phoPSCPhiWidth", &phoPSCPhiWidth, &b_phoPSCPhiWidth);
   fChain->SetBranchAddress("phoPSCBrem", &phoPSCBrem, &b_phoPSCBrem);
   fChain->SetBranchAddress("phoPSCnHits", &phoPSCnHits, &b_phoPSCnHits);
   fChain->SetBranchAddress("phoPSCflags", &phoPSCflags, &b_phoPSCflags);
   fChain->SetBranchAddress("phoPSCinClean", &phoPSCinClean, &b_phoPSCinClean);
   fChain->SetBranchAddress("phoPSCinUnClean", &phoPSCinUnClean, &b_phoPSCinUnClean);
   fChain->SetBranchAddress("phoPSCnBC", &phoPSCnBC, &b_phoPSCnBC);
   fChain->SetBranchAddress("phoPESEn", &phoPESEn, &b_phoPESEn);
   fChain->SetBranchAddress("phoIsPFPhoton", &phoIsPFPhoton, &b_phoIsPFPhoton);
   fChain->SetBranchAddress("phoIsStandardPhoton", &phoIsStandardPhoton, &b_phoIsStandardPhoton);
   fChain->SetBranchAddress("phoHasPixelSeed", &phoHasPixelSeed, &b_phoHasPixelSeed);
   fChain->SetBranchAddress("phoHasConversionTracks", &phoHasConversionTracks, &b_phoHasConversionTracks);
   fChain->SetBranchAddress("phoHadTowerOverEm", &phoHadTowerOverEm, &b_phoHadTowerOverEm);
   fChain->SetBranchAddress("phoHoverE", &phoHoverE, &b_phoHoverE);
   fChain->SetBranchAddress("phoHoverEValid", &phoHoverEValid, &b_phoHoverEValid);
   fChain->SetBranchAddress("phoSigmaIEtaIEta", &phoSigmaIEtaIEta, &b_phoSigmaIEtaIEta);
   fChain->SetBranchAddress("phoR9", &phoR9, &b_phoR9);
   fChain->SetBranchAddress("phoE1x5", &phoE1x5, &b_phoE1x5);
   fChain->SetBranchAddress("phoE2x5", &phoE2x5, &b_phoE2x5);
   fChain->SetBranchAddress("phoE3x3", &phoE3x3, &b_phoE3x3);
   fChain->SetBranchAddress("phoE5x5", &phoE5x5, &b_phoE5x5);
   fChain->SetBranchAddress("phoMaxEnergyXtal", &phoMaxEnergyXtal, &b_phoMaxEnergyXtal);
   fChain->SetBranchAddress("phoSigmaEtaEta", &phoSigmaEtaEta, &b_phoSigmaEtaEta);
   fChain->SetBranchAddress("phoSigmaIEtaIEta_2012", &phoSigmaIEtaIEta_2012, &b_phoSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("phoR9_2012", &phoR9_2012, &b_phoR9_2012);
   fChain->SetBranchAddress("phoE1x5_2012", &phoE1x5_2012, &b_phoE1x5_2012);
   fChain->SetBranchAddress("phoE2x5_2012", &phoE2x5_2012, &b_phoE2x5_2012);
   fChain->SetBranchAddress("phoE3x3_2012", &phoE3x3_2012, &b_phoE3x3_2012);
   fChain->SetBranchAddress("phoE5x5_2012", &phoE5x5_2012, &b_phoE5x5_2012);
   fChain->SetBranchAddress("phoMaxEnergyXtal_2012", &phoMaxEnergyXtal_2012, &b_phoMaxEnergyXtal_2012);
   fChain->SetBranchAddress("phoSigmaEtaEta_2012", &phoSigmaEtaEta_2012, &b_phoSigmaEtaEta_2012);
   fChain->SetBranchAddress("phoHadTowerOverEm1", &phoHadTowerOverEm1, &b_phoHadTowerOverEm1);
   fChain->SetBranchAddress("phoHadTowerOverEm2", &phoHadTowerOverEm2, &b_phoHadTowerOverEm2);
   fChain->SetBranchAddress("phoHoverE1", &phoHoverE1, &b_phoHoverE1);
   fChain->SetBranchAddress("phoHoverE2", &phoHoverE2, &b_phoHoverE2);
   fChain->SetBranchAddress("phoSigmaIEtaIPhi", &phoSigmaIEtaIPhi, &b_phoSigmaIEtaIPhi);
   fChain->SetBranchAddress("phoSigmaIPhiIPhi", &phoSigmaIPhiIPhi, &b_phoSigmaIPhiIPhi);
   fChain->SetBranchAddress("phoR1x5", &phoR1x5, &b_phoR1x5);
   fChain->SetBranchAddress("phoR2x5", &phoR2x5, &b_phoR2x5);
   fChain->SetBranchAddress("phoE2nd", &phoE2nd, &b_phoE2nd);
   fChain->SetBranchAddress("phoETop", &phoETop, &b_phoETop);
   fChain->SetBranchAddress("phoEBottom", &phoEBottom, &b_phoEBottom);
   fChain->SetBranchAddress("phoELeft", &phoELeft, &b_phoELeft);
   fChain->SetBranchAddress("phoERight", &phoERight, &b_phoERight);
   fChain->SetBranchAddress("phoE1x3", &phoE1x3, &b_phoE1x3);
   fChain->SetBranchAddress("phoE2x2", &phoE2x2, &b_phoE2x2);
   fChain->SetBranchAddress("phoE2x5Max", &phoE2x5Max, &b_phoE2x5Max);
   fChain->SetBranchAddress("phoE2x5Top", &phoE2x5Top, &b_phoE2x5Top);
   fChain->SetBranchAddress("phoE2x5Bottom", &phoE2x5Bottom, &b_phoE2x5Bottom);
   fChain->SetBranchAddress("phoE2x5Left", &phoE2x5Left, &b_phoE2x5Left);
   fChain->SetBranchAddress("phoE2x5Right", &phoE2x5Right, &b_phoE2x5Right);
   fChain->SetBranchAddress("phoSigmaIEtaIPhi_2012", &phoSigmaIEtaIPhi_2012, &b_phoSigmaIEtaIPhi_2012);
   fChain->SetBranchAddress("phoSigmaIPhiIPhi_2012", &phoSigmaIPhiIPhi_2012, &b_phoSigmaIPhiIPhi_2012);
   fChain->SetBranchAddress("phoR1x5_2012", &phoR1x5_2012, &b_phoR1x5_2012);
   fChain->SetBranchAddress("phoR2x5_2012", &phoR2x5_2012, &b_phoR2x5_2012);
   fChain->SetBranchAddress("phoE2nd_2012", &phoE2nd_2012, &b_phoE2nd_2012);
   fChain->SetBranchAddress("phoETop_2012", &phoETop_2012, &b_phoETop_2012);
   fChain->SetBranchAddress("phoEBottom_2012", &phoEBottom_2012, &b_phoEBottom_2012);
   fChain->SetBranchAddress("phoELeft_2012", &phoELeft_2012, &b_phoELeft_2012);
   fChain->SetBranchAddress("phoERight_2012", &phoERight_2012, &b_phoERight_2012);
   fChain->SetBranchAddress("phoE1x3_2012", &phoE1x3_2012, &b_phoE1x3_2012);
   fChain->SetBranchAddress("phoE2x2_2012", &phoE2x2_2012, &b_phoE2x2_2012);
   fChain->SetBranchAddress("phoE2x5Max_2012", &phoE2x5Max_2012, &b_phoE2x5Max_2012);
   fChain->SetBranchAddress("phoE2x5Top_2012", &phoE2x5Top_2012, &b_phoE2x5Top_2012);
   fChain->SetBranchAddress("phoE2x5Bottom_2012", &phoE2x5Bottom_2012, &b_phoE2x5Bottom_2012);
   fChain->SetBranchAddress("phoE2x5Left_2012", &phoE2x5Left_2012, &b_phoE2x5Left_2012);
   fChain->SetBranchAddress("phoE2x5Right_2012", &phoE2x5Right_2012, &b_phoE2x5Right_2012);
   fChain->SetBranchAddress("phoBC1E", &phoBC1E, &b_phoBC1E);
   fChain->SetBranchAddress("phoBC1Ecorr", &phoBC1Ecorr, &b_phoBC1Ecorr);
   fChain->SetBranchAddress("phoBC1Eta", &phoBC1Eta, &b_phoBC1Eta);
   fChain->SetBranchAddress("phoBC1Phi", &phoBC1Phi, &b_phoBC1Phi);
   fChain->SetBranchAddress("phoBC1size", &phoBC1size, &b_phoBC1size);
   fChain->SetBranchAddress("phoBC1flags", &phoBC1flags, &b_phoBC1flags);
   fChain->SetBranchAddress("phoBC1inClean", &phoBC1inClean, &b_phoBC1inClean);
   fChain->SetBranchAddress("phoBC1inUnClean", &phoBC1inUnClean, &b_phoBC1inUnClean);
   fChain->SetBranchAddress("phoBC1rawID", &phoBC1rawID, &b_phoBC1rawID);
   fChain->SetBranchAddress("pho_ecalClusterIsoR2", &pho_ecalClusterIsoR2, &b_pho_ecalClusterIsoR2);
   fChain->SetBranchAddress("pho_ecalClusterIsoR3", &pho_ecalClusterIsoR3, &b_pho_ecalClusterIsoR3);
   fChain->SetBranchAddress("pho_ecalClusterIsoR4", &pho_ecalClusterIsoR4, &b_pho_ecalClusterIsoR4);
   fChain->SetBranchAddress("pho_ecalClusterIsoR5", &pho_ecalClusterIsoR5, &b_pho_ecalClusterIsoR5);
   fChain->SetBranchAddress("pho_hcalRechitIsoR1", &pho_hcalRechitIsoR1, &b_pho_hcalRechitIsoR1);
   fChain->SetBranchAddress("pho_hcalRechitIsoR2", &pho_hcalRechitIsoR2, &b_pho_hcalRechitIsoR2);
   fChain->SetBranchAddress("pho_hcalRechitIsoR3", &pho_hcalRechitIsoR3, &b_pho_hcalRechitIsoR3);
   fChain->SetBranchAddress("pho_hcalRechitIsoR4", &pho_hcalRechitIsoR4, &b_pho_hcalRechitIsoR4);
   fChain->SetBranchAddress("pho_hcalRechitIsoR5", &pho_hcalRechitIsoR5, &b_pho_hcalRechitIsoR5);
   fChain->SetBranchAddress("pho_trackIsoR1PtCut20", &pho_trackIsoR1PtCut20, &b_pho_trackIsoR1PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR2PtCut20", &pho_trackIsoR2PtCut20, &b_pho_trackIsoR2PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR3PtCut20", &pho_trackIsoR3PtCut20, &b_pho_trackIsoR3PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR4PtCut20", &pho_trackIsoR4PtCut20, &b_pho_trackIsoR4PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR5PtCut20", &pho_trackIsoR5PtCut20, &b_pho_trackIsoR5PtCut20);
   fChain->SetBranchAddress("pho_swissCrx", &pho_swissCrx, &b_pho_swissCrx);
   fChain->SetBranchAddress("pho_seedTime", &pho_seedTime, &b_pho_seedTime);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muIsGood", &muIsGood, &b_muIsGood);
   fChain->SetBranchAddress("muIsGlobal", &muIsGlobal, &b_muIsGlobal);
   fChain->SetBranchAddress("muIsTracker", &muIsTracker, &b_muIsTracker);
   fChain->SetBranchAddress("muIsPF", &muIsPF, &b_muIsPF);
   fChain->SetBranchAddress("muIsSTA", &muIsSTA, &b_muIsSTA);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muIP3D", &muIP3D, &b_muIP3D);
   fChain->SetBranchAddress("muD0Err", &muD0Err, &b_muD0Err);
   fChain->SetBranchAddress("muDzErr", &muDzErr, &b_muDzErr);
   fChain->SetBranchAddress("muIP3DErr", &muIP3DErr, &b_muIP3DErr);
   fChain->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
   fChain->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
   fChain->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
   fChain->SetBranchAddress("muInnerD0Err", &muInnerD0Err, &b_muInnerD0Err);
   fChain->SetBranchAddress("muInnerDzErr", &muInnerDzErr, &b_muInnerDzErr);
   fChain->SetBranchAddress("muInnerPt", &muInnerPt, &b_muInnerPt);
   fChain->SetBranchAddress("muInnerPtErr", &muInnerPtErr, &b_muInnerPtErr);
   fChain->SetBranchAddress("muInnerEta", &muInnerEta, &b_muInnerEta);
   fChain->SetBranchAddress("muTrkLayers", &muTrkLayers, &b_muTrkLayers);
   fChain->SetBranchAddress("muPixelLayers", &muPixelLayers, &b_muPixelLayers);
   fChain->SetBranchAddress("muPixelHits", &muPixelHits, &b_muPixelHits);
   fChain->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
   fChain->SetBranchAddress("muTrkQuality", &muTrkQuality, &b_muTrkQuality);
   fChain->SetBranchAddress("muStations", &muStations, &b_muStations);
   fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
   fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
   fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
   fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
   fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
   fChain->SetBranchAddress("muIDSoft", &muIDSoft, &b_muIDSoft);
   fChain->SetBranchAddress("muIDLoose", &muIDLoose, &b_muIDLoose);
   fChain->SetBranchAddress("muIDMedium", &muIDMedium, &b_muIDMedium);
   fChain->SetBranchAddress("muIDMediumPrompt", &muIDMediumPrompt, &b_muIDMediumPrompt);
   fChain->SetBranchAddress("muIDTight", &muIDTight, &b_muIDTight);
   fChain->SetBranchAddress("muIDGlobalHighPt", &muIDGlobalHighPt, &b_muIDGlobalHighPt);
   fChain->SetBranchAddress("muIDTrkHighPt", &muIDTrkHighPt, &b_muIDTrkHighPt);
   fChain->SetBranchAddress("muIDInTime", &muIDInTime, &b_muIDInTime);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("trkPt", &trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkP", &trkP, &b_trkP);
   fChain->SetBranchAddress("trkEta", &trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", &trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkcharge", &trkcharge, &b_trkcharge);
   fChain->SetBranchAddress("trkvx", &trkvx, &b_trkvx);
   fChain->SetBranchAddress("trkvy", &trkvy, &b_trkvy);
   fChain->SetBranchAddress("trkvz", &trkvz, &b_trkvz);
   fChain->SetBranchAddress("trknormchi2", &trknormchi2, &b_trknormchi2);
   fChain->SetBranchAddress("trkchi2", &trkchi2, &b_trkchi2);
   fChain->SetBranchAddress("trkd0", &trkd0, &b_trkd0);
   fChain->SetBranchAddress("trkdxy", &trkdxy, &b_trkdxy);
   fChain->SetBranchAddress("trkdz", &trkdz, &b_trkdz);
   fChain->SetBranchAddress("trkdxyBS", &trkdxyBS, &b_trkdxyBS);
   fChain->SetBranchAddress("trkdzBS", &trkdzBS, &b_trkdzBS);
   fChain->SetBranchAddress("trkdxyError", &trkdxyError, &b_trkdxyError);
   fChain->SetBranchAddress("trkdzError", &trkdzError, &b_trkdzError);
   fChain->SetBranchAddress("trkValidHits", &trkValidHits, &b_trkValidHits);
   fChain->SetBranchAddress("trkMissHits", &trkMissHits, &b_trkMissHits);
   fChain->SetBranchAddress("trkPurity", &trkPurity, &b_trkPurity);
   fChain->SetBranchAddress("nTower", &nTower, &b_nTower);
   fChain->SetBranchAddress("CaloTower_hadE", &CaloTower_hadE, &b_CaloTower_hadE);
   fChain->SetBranchAddress("CaloTower_emE", &CaloTower_emE, &b_CaloTower_emE);
   fChain->SetBranchAddress("CaloTower_e", &CaloTower_e, &b_CaloTower_e);
   fChain->SetBranchAddress("CaloTower_et", &CaloTower_et, &b_CaloTower_et);
   fChain->SetBranchAddress("CaloTower_eta", &CaloTower_eta, &b_CaloTower_eta);
   fChain->SetBranchAddress("CaloTower_phi", &CaloTower_phi, &b_CaloTower_phi);
   fChain->SetBranchAddress("nTrackerHits", &nTrackerHits, &b_nTrackerHits);
   fChain->SetBranchAddress("nPixelClusters", &nPixelClusters, &b_nPixelClusters);
   fChain->SetBranchAddress("nPixelRecHits", &nPixelRecHits, &b_nPixelRecHits);
   Notify();
}

Bool_t DumpEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DumpEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DumpEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void DumpEvent::FillGoodEvents(TString filename)
{
   // fill list of good events
   ifstream ifs(filename.Data());
   char theline[1024];

   while (ifs.is_open()) {
      ifs.getline(theline,1024);
      TString thelineT(theline);

      if (thelineT=="") break;

      vector<int> v;
      TString tok;
      Ssiz_t from = 0;
      unsigned int cnt=0;
      while (thelineT.Tokenize(tok, from, "[,]")) {
         if (cnt==0) {cnt++; continue;}
         if (cnt<4) {v.push_back(atoi(tok));}
         else {goodevents[v] = atof(tok);}
         cnt++;
      }
   }
}
#endif // #ifdef DumpEvent_cxx
