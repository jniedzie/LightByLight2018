//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 21 18:04:24 2017 by ROOT version 6.04/02
// from TTree EventTree/Event data
// found on file: /eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root
//////////////////////////////////////////////////////////

#ifndef eventTreeReaderData_h
#define eventTreeReaderData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class eventTreeReaderData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   ULong64_t       event;
   UInt_t          lumis;
   Bool_t          isData;
   Int_t           nVtx;
   vector<int>     *isFakeVtx;
   vector<float>   *xVtx;
   vector<float>   *yVtx;
   vector<float>   *zVtx;
   Int_t           nEle;
   vector<int>     *eleCharge;
   vector<int>     *eleChargeConsistent;
   vector<int>     *eleSCPixCharge;
   vector<int>     *eleCtfCharge;
   vector<float>   *eleEn;
   vector<float>   *eleD0;
   vector<float>   *eleDz;
   vector<float>   *eleD0Err;
   vector<float>   *eleDzErr;
   vector<float>   *eleTrkPt;
   vector<float>   *eleTrkEta;
   vector<float>   *eleTrkPhi;
   vector<int>     *eleTrkCharge;
   vector<float>   *eleTrkChi2;
   vector<float>   *eleTrkNdof;
   vector<float>   *eleTrkNormalizedChi2;
   vector<int>     *eleTrkValidHits;
   vector<int>     *eleTrkLayers;
   vector<float>   *eleP;
   vector<float>   *elePt;
   vector<float>   *eleEta;
   vector<float>   *elePhi;
   vector<float>   *eleSCx;
   vector<float>   *eleSCy;
   vector<float>   *eleSCz;
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
   vector<float>   *eleBrem;
   vector<float>   *eledEtaAtVtx;
   vector<float>   *eledPhiAtVtx;
   vector<float>   *eledEtaSeedAtVtx;
   vector<float>   *eleSigmaIEtaIEta;
   vector<float>   *eleSigmaIEtaIEta_2012;
   vector<float>   *eleSigmaIPhiIPhi;
   vector<int>     *eleMissHits;
   vector<float>   *eleTrackIso;
   vector<float>   *eleECalIso;
   vector<float>   *eleHCalIso;
   vector<float>   *eleECalDriven;
   vector<float>   *eleESEffSigmaRR;
   vector<float>   *elePFChIso;
   vector<float>   *elePFPhoIso;
   vector<float>   *elePFNeuIso;
   vector<float>   *elePFPUIso;
   vector<float>   *elePFChIso03;
   vector<float>   *elePFPhoIso03;
   vector<float>   *elePFNeuIso03;
   vector<float>   *elePFChIso04;
   vector<float>   *elePFPhoIso04;
   vector<float>   *elePFNeuIso04;
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
   vector<int>     *eleIDVeto;
   vector<int>     *eleIDLoose;
   vector<int>     *eleIDMedium;
   vector<int>     *eleIDTight;
   vector<int>     *elepassConversionVeto;
   vector<float>   *eleEffAreaTimesRho;
   Int_t           nConv;
   vector<int>     *conv_eleind;
   vector<int>     *conv_phoind;
   vector<float>   *conv_vtxprob;
   vector<float>   *conv_lxy;
   vector<int>     *conv_nhits_bvtx;
   Int_t           nPho;
   vector<float>   *phoE;
   vector<float>   *phoEt;
   vector<float>   *phoEta;
   vector<float>   *phoPhi;
   vector<float>   *phoSCE;
   vector<float>   *phoSCEt;
   vector<float>   *phoSCRawE;
   vector<float>   *phoSCRawEt;
   vector<float>   *phoESEn;
   vector<float>   *phoSCEta;
   vector<float>   *phoSCPhi;
   vector<float>   *phoSCx;
   vector<float>   *phoSCy;
   vector<float>   *phoSCz;
   vector<float>   *phoSCEtaWidth;
   vector<float>   *phoSCPhiWidth;
   vector<float>   *phoSCBrem;
   vector<int>     *phohasPixelSeed;
   vector<int>     *phopassConversionVeto;
   vector<float>   *phoR9;
   vector<float>   *phoHadTowerOverEm;
   vector<float>   *phoHoverE;
   vector<float>   *phoSigmaIEtaIEta;
   vector<float>   *phoE1x3;
   vector<float>   *phoE2x2;
   vector<float>   *phoE3x3;
   vector<float>   *phoE2x5Max;
   vector<float>   *phoE1x5;
   vector<float>   *phoE2x5;
   vector<float>   *phoE5x5;
   vector<float>   *phoMaxEnergyXtal;
   vector<float>   *phoSigmaEtaEta;
   vector<float>   *phoR1x5;
   vector<float>   *phoR2x5;
   vector<float>   *phoESEffSigmaRR;
   vector<float>   *phoSigmaIEtaIEta_2012;
   vector<float>   *phoSigmaIEtaIPhi_2012;
   vector<float>   *phoSigmaIPhiIPhi_2012;
   vector<float>   *phoE1x3_2012;
   vector<float>   *phoE2x2_2012;
   vector<float>   *phoE3x3_2012;
   vector<float>   *phoE2x5Max_2012;
   vector<float>   *phoE5x5_2012;
   vector<float>   *phoBC1E;
   vector<float>   *phoBC1Eta;
   vector<float>   *phoBC2E;
   vector<float>   *phoBC2Eta;
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
   vector<int>     *phoIsConv;
   vector<int>     *phoNConv;
   vector<float>   *phoConvInvMass;
   vector<float>   *phoConvCotTheta;
   vector<float>   *phoConvEoverP;
   vector<float>   *phoConvZofPVfromTrks;
   vector<float>   *phoConvMinDist;
   vector<float>   *phoConvdPhiAtVtx;
   vector<float>   *phoConvdPhiAtCalo;
   vector<float>   *phoConvdEtaAtCalo;
   vector<float>   *phoConvTrkd0_x;
   vector<float>   *phoConvTrkd0_y;
   vector<float>   *phoConvTrkPin_x;
   vector<float>   *phoConvTrkPin_y;
   vector<float>   *phoConvTrkPout_x;
   vector<float>   *phoConvTrkPout_y;
   vector<float>   *phoConvTrkdz_x;
   vector<float>   *phoConvTrkdz_y;
   vector<float>   *phoConvTrkdzErr_x;
   vector<float>   *phoConvTrkdzErr_y;
   vector<float>   *phoConvChi2;
   vector<float>   *phoConvChi2Prob;
   vector<int>     *phoConvNTrks;
   vector<float>   *phoConvCharge1;
   vector<float>   *phoConvCharge2;
   vector<int>     *phoConvValidVtx;
   vector<float>   *phoConvLikeLihood;
   vector<float>   *phoConvP4_0;
   vector<float>   *phoConvP4_1;
   vector<float>   *phoConvP4_2;
   vector<float>   *phoConvP4_3;
   vector<float>   *phoConvVtx_x;
   vector<float>   *phoConvVtx_y;
   vector<float>   *phoConvVtx_z;
   vector<float>   *phoConvVtxErr_x;
   vector<float>   *phoConvVtxErr_y;
   vector<float>   *phoConvVtxErr_z;
   vector<float>   *phoConvPairMomentum_x;
   vector<float>   *phoConvPairMomentum_y;
   vector<float>   *phoConvPairMomentum_z;
   vector<float>   *phoConvRefittedMomentum_x;
   vector<float>   *phoConvRefittedMomentum_y;
   vector<float>   *phoConvRefittedMomentum_z;
   vector<int>     *SingleLegConv;
   Int_t           nMu;
   vector<float>   *muPt;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<int>     *muCharge;
   vector<int>     *muType;
   vector<int>     *muIsGood;
   vector<float>   *muD0;
   vector<float>   *muDz;
   vector<float>   *muChi2NDF;
   vector<float>   *muInnerD0;
   vector<float>   *muInnerDz;
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
   Int_t           nTower;
   vector<float>   *CaloTower_hadE;
   vector<float>   *CaloTower_emE;
   vector<float>   *CaloTower_e;
   vector<float>   *CaloTower_et;
   vector<float>   *CaloTower_eta;
   vector<float>   *CaloTower_phi;
   Int_t           nHyPho;
   vector<float>   *hyphoE;
   vector<float>   *hyphoEt;
   vector<float>   *hyphoEta;
   vector<float>   *hyphoPhi;
   vector<float>   *hyphoSCE;
   vector<float>   *hyphoSCEt;
   vector<float>   *hyphoSCRawE;
   vector<float>   *hyphoSCRawEt;
   vector<float>   *hyphoESEn;
   vector<float>   *hyphoSCEta;
   vector<float>   *hyphoSCPhi;
   vector<float>   *hyphoSCx;
   vector<float>   *hyphoSCy;
   vector<float>   *hyphoSCz;
   vector<float>   *hyphoSCEtaWidth;
   vector<float>   *hyphoSCPhiWidth;
   vector<float>   *hyphoSCBrem;
   vector<int>     *hyphohasPixelSeed;
   vector<int>     *hyphopassConversionVeto;
   vector<float>   *hyphoR9;
   vector<float>   *hyphoHadTowerOverEm;
   vector<float>   *hyphoHoverE;
   vector<float>   *hyphoSigmaIEtaIEta;
   vector<float>   *hyphoE1x3;
   vector<float>   *hyphoE2x2;
   vector<float>   *hyphoE3x3;
   vector<float>   *hyphoE2x5Max;
   vector<float>   *hyphoE1x5;
   vector<float>   *hyphoE2x5;
   vector<float>   *hyphoE5x5;
   vector<float>   *hyphoMaxEnergyXtal;
   vector<float>   *hyphoSigmaEtaEta;
   vector<float>   *hyphoR1x5;
   vector<float>   *hyphoR2x5;
   vector<float>   *hyphoESEffSigmaRR;
   vector<float>   *hyphoSigmaIEtaIEta_2012;
   vector<float>   *hyphoSigmaIEtaIPhi_2012;
   vector<float>   *hyphoSigmaIPhiIPhi_2012;
   vector<float>   *hyphoE1x3_2012;
   vector<float>   *hyphoE2x2_2012;
   vector<float>   *hyphoE3x3_2012;
   vector<float>   *hyphoE2x5Max_2012;
   vector<float>   *hyphoE5x5_2012;
   vector<float>   *hyphoBC1E;
   vector<float>   *hyphoBC1Eta;
   vector<float>   *hyphoBC2E;
   vector<float>   *hyphoBC2Eta;
   vector<float>   *hypho_ecalClusterIsoR2;
   vector<float>   *hypho_ecalClusterIsoR3;
   vector<float>   *hypho_ecalClusterIsoR4;
   vector<float>   *hypho_ecalClusterIsoR5;
   vector<float>   *hypho_hcalRechitIsoR1;
   vector<float>   *hypho_hcalRechitIsoR2;
   vector<float>   *hypho_hcalRechitIsoR3;
   vector<float>   *hypho_hcalRechitIsoR4;
   vector<float>   *hypho_hcalRechitIsoR5;
   vector<float>   *hypho_trackIsoR1PtCut20;
   vector<float>   *hypho_trackIsoR2PtCut20;
   vector<float>   *hypho_trackIsoR3PtCut20;
   vector<float>   *hypho_trackIsoR4PtCut20;
   vector<float>   *hypho_trackIsoR5PtCut20;
   vector<float>   *hypho_swissCrx;
   vector<float>   *hypho_seedTime;
   Int_t           ngsfEle;
   vector<float>   *elegsfTrkPt;
   vector<float>   *elegsfTrkP;
   vector<float>   *elegsfTrkEta;
   vector<float>   *elegsfTrkPhi;
   vector<int>     *elegsfTrkCharge;
   vector<float>   *elegsfTrkChi2;
   vector<float>   *elegsfTrkNdof;
   vector<float>   *elegsfTrkNormalizedChi2;
   vector<int>     *elegsfTrkValidHits;
   vector<int>     *elegsfTrkMissHits;
   vector<int>     *elegsfTrkLayers;
   vector<float>   *elegsfD0;
   vector<float>   *elegsfDz;
   vector<float>   *elegsfD0Err;
   vector<float>   *elegsfDzErr;
   Int_t           ngenTrk;
   vector<float>   *gentrkPt;
   vector<float>   *gentrkP;
   vector<float>   *gentrkEta;
   vector<float>   *gentrkPhi;
   vector<int>     *gentrkcharge;
   vector<float>   *gentrkvx;
   vector<float>   *gentrkvy;
   vector<float>   *gentrkvz;
   vector<float>   *gentrknormchi2;
   vector<float>   *gentrkchi2;
   vector<float>   *gentrkd0;
   vector<float>   *gentrkdxy;
   vector<float>   *gentrkdz;
   vector<float>   *gentrkdxyError;
   vector<float>   *gentrkdzError;
   vector<int>     *gentrkValidHits;
   vector<int>     *gentrkMissHits;
   vector<int>     *gentrkPurity;
   Int_t           nsc_hybrid;
   vector<float>   *sc_hybrid_E;
   vector<float>   *sc_hybrid_Et;
   vector<float>   *sc_hybrid_Eta;
   vector<float>   *sc_hybrid_Phi;
   vector<float>   *sc_hybrid_x;
   vector<float>   *sc_hybrid_y;
   vector<float>   *sc_hybrid_z;
   vector<float>   *sc_hybrid_EtaWidth;
   vector<float>   *sc_hybrid_PhiWidth;
   vector<float>   *sc_hybrid_RawE;
   vector<float>   *sc_hybrid_RawEt;
   Int_t           nsc_mult55;
   vector<float>   *sc_mult55_E;
   vector<float>   *sc_mult55_Et;
   vector<float>   *sc_mult55_Eta;
   vector<float>   *sc_mult55_Phi;
   vector<float>   *sc_mult55_x;
   vector<float>   *sc_mult55_y;
   vector<float>   *sc_mult55_z;
   vector<float>   *sc_mult55_EtaWidth;
   vector<float>   *sc_mult55_PhiWidth;
   vector<float>   *sc_mult55_RawE;
   vector<float>   *sc_mult55_RawEt;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_isFakeVtx;   //!
   TBranch        *b_xVtx;   //!
   TBranch        *b_yVtx;   //!
   TBranch        *b_zVtx;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleChargeConsistent;   //!
   TBranch        *b_eleSCPixCharge;   //!
   TBranch        *b_eleCtfCharge;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleD0Err;   //!
   TBranch        *b_eleDzErr;   //!
   TBranch        *b_eleTrkPt;   //!
   TBranch        *b_eleTrkEta;   //!
   TBranch        *b_eleTrkPhi;   //!
   TBranch        *b_eleTrkCharge;   //!
   TBranch        *b_eleTrkChi2;   //!
   TBranch        *b_eleTrkNdof;   //!
   TBranch        *b_eleTrkNormalizedChi2;   //!
   TBranch        *b_eleTrkValidHits;   //!
   TBranch        *b_eleTrkLayers;   //!
   TBranch        *b_eleP;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleSCx;   //!
   TBranch        *b_eleSCy;   //!
   TBranch        *b_eleSCz;   //!
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
   TBranch        *b_eleBrem;   //!
   TBranch        *b_eledEtaAtVtx;   //!
   TBranch        *b_eledPhiAtVtx;   //!
   TBranch        *b_eledEtaSeedAtVtx;   //!
   TBranch        *b_eleSigmaIEtaIEta;   //!
   TBranch        *b_eleSigmaIEtaIEta_2012;   //!
   TBranch        *b_eleSigmaIPhiIPhi;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_eleTrackIso;   //!
   TBranch        *b_eleECalIso;   //!
   TBranch        *b_eleHCalIso;   //!
   TBranch        *b_eleECalDriven;   //!
   TBranch        *b_eleESEffSigmaRR;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_elePFPUIso;   //!
   TBranch        *b_elePFChIso03;   //!
   TBranch        *b_elePFPhoIso03;   //!
   TBranch        *b_elePFNeuIso03;   //!
   TBranch        *b_elePFChIso04;   //!
   TBranch        *b_elePFPhoIso04;   //!
   TBranch        *b_elePFNeuIso04;   //!
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
   TBranch        *b_eleIDVeto;   //!
   TBranch        *b_eleIDLoose;   //!
   TBranch        *b_eleIDMedium;   //!
   TBranch        *b_eleIDTight;   //!
   TBranch        *b_elepassConversionVeto;   //!
   TBranch        *b_eleEffAreaTimesRho;   //!
   TBranch        *b_nConv;   //!
   TBranch        *b_conv_eleind;   //!
   TBranch        *b_conv_phoind;   //!
   TBranch        *b_conv_vtxprob;   //!
   TBranch        *b_conv_lxy;   //!
   TBranch        *b_conv_nhits_bvtx;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCEt;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoSCRawEt;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCx;   //!
   TBranch        *b_phoSCy;   //!
   TBranch        *b_phoSCz;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_phopassConversionVeto;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoHadTowerOverEm;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoSigmaIEtaIEta;   //!
   TBranch        *b_phoE1x3;   //!
   TBranch        *b_phoE2x2;   //!
   TBranch        *b_phoE3x3;   //!
   TBranch        *b_phoE2x5Max;   //!
   TBranch        *b_phoE1x5;   //!
   TBranch        *b_phoE2x5;   //!
   TBranch        *b_phoE5x5;   //!
   TBranch        *b_phoMaxEnergyXtal;   //!
   TBranch        *b_phoSigmaEtaEta;   //!
   TBranch        *b_phoR1x5;   //!
   TBranch        *b_phoR2x5;   //!
   TBranch        *b_phoESEffSigmaRR;   //!
   TBranch        *b_phoSigmaIEtaIEta_2012;   //!
   TBranch        *b_phoSigmaIEtaIPhi_2012;   //!
   TBranch        *b_phoSigmaIPhiIPhi_2012;   //!
   TBranch        *b_phoE1x3_2012;   //!
   TBranch        *b_phoE2x2_2012;   //!
   TBranch        *b_phoE3x3_2012;   //!
   TBranch        *b_phoE2x5Max_2012;   //!
   TBranch        *b_phoE5x5_2012;   //!
   TBranch        *b_phoBC1E;   //!
   TBranch        *b_phoBC1Eta;   //!
   TBranch        *b_phoBC2E;   //!
   TBranch        *b_phoBC2Eta;   //!
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
   TBranch        *b_phoIsConv;   //!
   TBranch        *b_phoNConv;   //!
   TBranch        *b_phoConvInvMass;   //!
   TBranch        *b_phoConvCotTheta;   //!
   TBranch        *b_phoConvEoverP;   //!
   TBranch        *b_phoConvZofPVfromTrks;   //!
   TBranch        *b_phoConvMinDist;   //!
   TBranch        *b_phoConvdPhiAtVtx;   //!
   TBranch        *b_phoConvdPhiAtCalo;   //!
   TBranch        *b_phoConvdEtaAtCalo;   //!
   TBranch        *b_phoConvTrkd0_x;   //!
   TBranch        *b_phoConvTrkd0_y;   //!
   TBranch        *b_phoConvTrkPin_x;   //!
   TBranch        *b_phoConvTrkPin_y;   //!
   TBranch        *b_phoConvTrkPout_x;   //!
   TBranch        *b_phoConvTrkPout_y;   //!
   TBranch        *b_phoConvTrkdz_x;   //!
   TBranch        *b_phoConvTrkdz_y;   //!
   TBranch        *b_phoConvTrkdzErr_x;   //!
   TBranch        *b_phoConvTrkdzErr_y;   //!
   TBranch        *b_phoConvChi2;   //!
   TBranch        *b_phoConvChi2Prob;   //!
   TBranch        *b_phoConvNTrks;   //!
   TBranch        *b_phoConvCharge1;   //!
   TBranch        *b_phoConvCharge2;   //!
   TBranch        *b_phoConvValidVtx;   //!
   TBranch        *b_phoConvLikeLihood;   //!
   TBranch        *b_phoConvP4_0;   //!
   TBranch        *b_phoConvP4_1;   //!
   TBranch        *b_phoConvP4_2;   //!
   TBranch        *b_phoConvP4_3;   //!
   TBranch        *b_phoConvVtx_x;   //!
   TBranch        *b_phoConvVtx_y;   //!
   TBranch        *b_phoConvVtx_z;   //!
   TBranch        *b_phoConvVtxErr_x;   //!
   TBranch        *b_phoConvVtxErr_y;   //!
   TBranch        *b_phoConvVtxErr_z;   //!
   TBranch        *b_phoConvPairMomentum_x;   //!
   TBranch        *b_phoConvPairMomentum_y;   //!
   TBranch        *b_phoConvPairMomentum_z;   //!
   TBranch        *b_phoConvRefittedMomentum_x;   //!
   TBranch        *b_phoConvRefittedMomentum_y;   //!
   TBranch        *b_phoConvRefittedMomentum_z;   //!
   TBranch        *b_SingleLegConv;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muIsGood;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muChi2NDF;   //!
   TBranch        *b_muInnerD0;   //!
   TBranch        *b_muInnerDz;   //!
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
   TBranch        *b_nTower;   //!
   TBranch        *b_CaloTower_hadE;   //!
   TBranch        *b_CaloTower_emE;   //!
   TBranch        *b_CaloTower_e;   //!
   TBranch        *b_CaloTower_et;   //!
   TBranch        *b_CaloTower_eta;   //!
   TBranch        *b_CaloTower_phi;   //!
   TBranch        *b_nHyPho;   //!
   TBranch        *b_hyphoE;   //!
   TBranch        *b_hyphoEt;   //!
   TBranch        *b_hyphoEta;   //!
   TBranch        *b_hyphoPhi;   //!
   TBranch        *b_hyphoSCE;   //!
   TBranch        *b_hyphoSCEt;   //!
   TBranch        *b_hyphoSCRawE;   //!
   TBranch        *b_hyphoSCRawEt;   //!
   TBranch        *b_hyphoESEn;   //!
   TBranch        *b_hyphoSCEta;   //!
   TBranch        *b_hyphoSCPhi;   //!
   TBranch        *b_hyphoSCx;   //!
   TBranch        *b_hyphoSCy;   //!
   TBranch        *b_hyphoSCz;   //!
   TBranch        *b_hyphoSCEtaWidth;   //!
   TBranch        *b_hyphoSCPhiWidth;   //!
   TBranch        *b_hyphoSCBrem;   //!
   TBranch        *b_hyphohasPixelSeed;   //!
   TBranch        *b_hyphopassConversionVeto;   //!
   TBranch        *b_hyphoR9;   //!
   TBranch        *b_hyphoHadTowerOverEm;   //!
   TBranch        *b_hyphoHoverE;   //!
   TBranch        *b_hyphoSigmaIEtaIEta;   //!
   TBranch        *b_hyphoE1x3;   //!
   TBranch        *b_hyphoE2x2;   //!
   TBranch        *b_hyphoE3x3;   //!
   TBranch        *b_hyphoE2x5Max;   //!
   TBranch        *b_hyphoE1x5;   //!
   TBranch        *b_hyphoE2x5;   //!
   TBranch        *b_hyphoE5x5;   //!
   TBranch        *b_hyphoMaxEnergyXtal;   //!
   TBranch        *b_hyphoSigmaEtaEta;   //!
   TBranch        *b_hyphoR1x5;   //!
   TBranch        *b_hyphoR2x5;   //!
   TBranch        *b_hyphoESEffSigmaRR;   //!
   TBranch        *b_hyphoSigmaIEtaIEta_2012;   //!
   TBranch        *b_hyphoSigmaIEtaIPhi_2012;   //!
   TBranch        *b_hyphoSigmaIPhiIPhi_2012;   //!
   TBranch        *b_hyphoE1x3_2012;   //!
   TBranch        *b_hyphoE2x2_2012;   //!
   TBranch        *b_hyphoE3x3_2012;   //!
   TBranch        *b_hyphoE2x5Max_2012;   //!
   TBranch        *b_hyphoE5x5_2012;   //!
   TBranch        *b_hyphoBC1E;   //!
   TBranch        *b_hyphoBC1Eta;   //!
   TBranch        *b_hyphoBC2E;   //!
   TBranch        *b_hyphoBC2Eta;   //!
   TBranch        *b_hypho_ecalClusterIsoR2;   //!
   TBranch        *b_hypho_ecalClusterIsoR3;   //!
   TBranch        *b_hypho_ecalClusterIsoR4;   //!
   TBranch        *b_hypho_ecalClusterIsoR5;   //!
   TBranch        *b_hypho_hcalRechitIsoR1;   //!
   TBranch        *b_hypho_hcalRechitIsoR2;   //!
   TBranch        *b_hypho_hcalRechitIsoR3;   //!
   TBranch        *b_hypho_hcalRechitIsoR4;   //!
   TBranch        *b_hypho_hcalRechitIsoR5;   //!
   TBranch        *b_hypho_trackIsoR1PtCut20;   //!
   TBranch        *b_hypho_trackIsoR2PtCut20;   //!
   TBranch        *b_hypho_trackIsoR3PtCut20;   //!
   TBranch        *b_hypho_trackIsoR4PtCut20;   //!
   TBranch        *b_hypho_trackIsoR5PtCut20;   //!
   TBranch        *b_hypho_swissCrx;   //!
   TBranch        *b_hypho_seedTime;   //!
   TBranch        *b_ngsfEle;   //!
   TBranch        *b_elegsfTrkPt;   //!
   TBranch        *b_elegsfTrkP;   //!
   TBranch        *b_elegsfTrkEta;   //!
   TBranch        *b_elegsfTrkPhi;   //!
   TBranch        *b_elegsfTrkCharge;   //!
   TBranch        *b_elegsfTrkChi2;   //!
   TBranch        *b_elegsfTrkNdof;   //!
   TBranch        *b_elegsfTrkNormalizedChi2;   //!
   TBranch        *b_elegsfTrkValidHits;   //!
   TBranch        *b_elegsfTrkMissHits;   //!
   TBranch        *b_elegsfTrkLayers;   //!
   TBranch        *b_elegsfD0;   //!
   TBranch        *b_elegsfDz;   //!
   TBranch        *b_elegsfD0Err;   //!
   TBranch        *b_elegsfDzErr;   //!
   TBranch        *b_ngenTrk;   //!
   TBranch        *b_gentrkPt;   //!
   TBranch        *b_gentrkP;   //!
   TBranch        *b_gentrkEta;   //!
   TBranch        *b_gentrkPhi;   //!
   TBranch        *b_gentrkcharge;   //!
   TBranch        *b_gentrkvx;   //!
   TBranch        *b_gentrkvy;   //!
   TBranch        *b_gentrkvz;   //!
   TBranch        *b_gentrknormchi2;   //!
   TBranch        *b_gentrkchi2;   //!
   TBranch        *b_gentrkd0;   //!
   TBranch        *b_gentrkdxy;   //!
   TBranch        *b_gentrkdz;   //!
   TBranch        *b_gentrkdxyError;   //!
   TBranch        *b_gentrkdzError;   //!
   TBranch        *b_gentrkValidHits;   //!
   TBranch        *b_gentrkMissHits;   //!
   TBranch        *b_gentrkPurity;   //!
   TBranch        *b_nsc_hybrid;   //!
   TBranch        *b_sc_hybrid_E;   //!
   TBranch        *b_sc_hybrid_Et;   //!
   TBranch        *b_sc_hybrid_Eta;   //!
   TBranch        *b_sc_hybrid_Phi;   //!
   TBranch        *b_sc_hybrid_x;   //!
   TBranch        *b_sc_hybrid_y;   //!
   TBranch        *b_sc_hybrid_z;   //!
   TBranch        *b_sc_hybrid_EtaWidth;   //!
   TBranch        *b_sc_hybrid_PhiWidth;   //!
   TBranch        *b_sc_hybrid_RawE;   //!
   TBranch        *b_sc_hybrid_RawEt;   //!
   TBranch        *b_nsc_mult55;   //!
   TBranch        *b_sc_mult55_E;   //!
   TBranch        *b_sc_mult55_Et;   //!
   TBranch        *b_sc_mult55_Eta;   //!
   TBranch        *b_sc_mult55_Phi;   //!
   TBranch        *b_sc_mult55_x;   //!
   TBranch        *b_sc_mult55_y;   //!
   TBranch        *b_sc_mult55_z;   //!
   TBranch        *b_sc_mult55_EtaWidth;   //!
   TBranch        *b_sc_mult55_PhiWidth;   //!
   TBranch        *b_sc_mult55_RawE;   //!
   TBranch        *b_sc_mult55_RawEt;   //!

   eventTreeReaderData(TTree *tree=0);
   virtual ~eventTreeReaderData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef eventTreeReaderData_cxx
eventTreeReaderData::eventTreeReaderData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root:/ggHiNtuplizer");
      dir->GetObject("EventTree",tree);

   }
   Init(tree);
}

eventTreeReaderData::~eventTreeReaderData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t eventTreeReaderData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t eventTreeReaderData::LoadTree(Long64_t entry)
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

void eventTreeReaderData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   isFakeVtx = 0;
   xVtx = 0;
   yVtx = 0;
   zVtx = 0;
   eleCharge = 0;
   eleChargeConsistent = 0;
   eleSCPixCharge = 0;
   eleCtfCharge = 0;
   eleEn = 0;
   eleD0 = 0;
   eleDz = 0;
   eleD0Err = 0;
   eleDzErr = 0;
   eleTrkPt = 0;
   eleTrkEta = 0;
   eleTrkPhi = 0;
   eleTrkCharge = 0;
   eleTrkChi2 = 0;
   eleTrkNdof = 0;
   eleTrkNormalizedChi2 = 0;
   eleTrkValidHits = 0;
   eleTrkLayers = 0;
   eleP = 0;
   elePt = 0;
   eleEta = 0;
   elePhi = 0;
   eleSCx = 0;
   eleSCy = 0;
   eleSCz = 0;
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
   eleBrem = 0;
   eledEtaAtVtx = 0;
   eledPhiAtVtx = 0;
   eledEtaSeedAtVtx = 0;
   eleSigmaIEtaIEta = 0;
   eleSigmaIEtaIEta_2012 = 0;
   eleSigmaIPhiIPhi = 0;
   eleMissHits = 0;
   eleTrackIso = 0;
   eleECalIso = 0;
   eleHCalIso = 0;
   eleECalDriven = 0;
   eleESEffSigmaRR = 0;
   elePFChIso = 0;
   elePFPhoIso = 0;
   elePFNeuIso = 0;
   elePFPUIso = 0;
   elePFChIso03 = 0;
   elePFPhoIso03 = 0;
   elePFNeuIso03 = 0;
   elePFChIso04 = 0;
   elePFPhoIso04 = 0;
   elePFNeuIso04 = 0;
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
   eleIDVeto = 0;
   eleIDLoose = 0;
   eleIDMedium = 0;
   eleIDTight = 0;
   elepassConversionVeto = 0;
   eleEffAreaTimesRho = 0;
   conv_eleind = 0;
   conv_phoind = 0;
   conv_vtxprob = 0;
   conv_lxy = 0;
   conv_nhits_bvtx = 0;
   phoE = 0;
   phoEt = 0;
   phoEta = 0;
   phoPhi = 0;
   phoSCE = 0;
   phoSCEt = 0;
   phoSCRawE = 0;
   phoSCRawEt = 0;
   phoESEn = 0;
   phoSCEta = 0;
   phoSCPhi = 0;
   phoSCx = 0;
   phoSCy = 0;
   phoSCz = 0;
   phoSCEtaWidth = 0;
   phoSCPhiWidth = 0;
   phoSCBrem = 0;
   phohasPixelSeed = 0;
   phopassConversionVeto = 0;
   phoR9 = 0;
   phoHadTowerOverEm = 0;
   phoHoverE = 0;
   phoSigmaIEtaIEta = 0;
   phoE1x3 = 0;
   phoE2x2 = 0;
   phoE3x3 = 0;
   phoE2x5Max = 0;
   phoE1x5 = 0;
   phoE2x5 = 0;
   phoE5x5 = 0;
   phoMaxEnergyXtal = 0;
   phoSigmaEtaEta = 0;
   phoR1x5 = 0;
   phoR2x5 = 0;
   phoESEffSigmaRR = 0;
   phoSigmaIEtaIEta_2012 = 0;
   phoSigmaIEtaIPhi_2012 = 0;
   phoSigmaIPhiIPhi_2012 = 0;
   phoE1x3_2012 = 0;
   phoE2x2_2012 = 0;
   phoE3x3_2012 = 0;
   phoE2x5Max_2012 = 0;
   phoE5x5_2012 = 0;
   phoBC1E = 0;
   phoBC1Eta = 0;
   phoBC2E = 0;
   phoBC2Eta = 0;
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
   phoIsConv = 0;
   phoNConv = 0;
   phoConvInvMass = 0;
   phoConvCotTheta = 0;
   phoConvEoverP = 0;
   phoConvZofPVfromTrks = 0;
   phoConvMinDist = 0;
   phoConvdPhiAtVtx = 0;
   phoConvdPhiAtCalo = 0;
   phoConvdEtaAtCalo = 0;
   phoConvTrkd0_x = 0;
   phoConvTrkd0_y = 0;
   phoConvTrkPin_x = 0;
   phoConvTrkPin_y = 0;
   phoConvTrkPout_x = 0;
   phoConvTrkPout_y = 0;
   phoConvTrkdz_x = 0;
   phoConvTrkdz_y = 0;
   phoConvTrkdzErr_x = 0;
   phoConvTrkdzErr_y = 0;
   phoConvChi2 = 0;
   phoConvChi2Prob = 0;
   phoConvNTrks = 0;
   phoConvCharge1 = 0;
   phoConvCharge2 = 0;
   phoConvValidVtx = 0;
   phoConvLikeLihood = 0;
   phoConvP4_0 = 0;
   phoConvP4_1 = 0;
   phoConvP4_2 = 0;
   phoConvP4_3 = 0;
   phoConvVtx_x = 0;
   phoConvVtx_y = 0;
   phoConvVtx_z = 0;
   phoConvVtxErr_x = 0;
   phoConvVtxErr_y = 0;
   phoConvVtxErr_z = 0;
   phoConvPairMomentum_x = 0;
   phoConvPairMomentum_y = 0;
   phoConvPairMomentum_z = 0;
   phoConvRefittedMomentum_x = 0;
   phoConvRefittedMomentum_y = 0;
   phoConvRefittedMomentum_z = 0;
   SingleLegConv = 0;
   muPt = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIsGood = 0;
   muD0 = 0;
   muDz = 0;
   muChi2NDF = 0;
   muInnerD0 = 0;
   muInnerDz = 0;
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
   CaloTower_hadE = 0;
   CaloTower_emE = 0;
   CaloTower_e = 0;
   CaloTower_et = 0;
   CaloTower_eta = 0;
   CaloTower_phi = 0;
   hyphoE = 0;
   hyphoEt = 0;
   hyphoEta = 0;
   hyphoPhi = 0;
   hyphoSCE = 0;
   hyphoSCEt = 0;
   hyphoSCRawE = 0;
   hyphoSCRawEt = 0;
   hyphoESEn = 0;
   hyphoSCEta = 0;
   hyphoSCPhi = 0;
   hyphoSCx = 0;
   hyphoSCy = 0;
   hyphoSCz = 0;
   hyphoSCEtaWidth = 0;
   hyphoSCPhiWidth = 0;
   hyphoSCBrem = 0;
   hyphohasPixelSeed = 0;
   hyphopassConversionVeto = 0;
   hyphoR9 = 0;
   hyphoHadTowerOverEm = 0;
   hyphoHoverE = 0;
   hyphoSigmaIEtaIEta = 0;
   hyphoE1x3 = 0;
   hyphoE2x2 = 0;
   hyphoE3x3 = 0;
   hyphoE2x5Max = 0;
   hyphoE1x5 = 0;
   hyphoE2x5 = 0;
   hyphoE5x5 = 0;
   hyphoMaxEnergyXtal = 0;
   hyphoSigmaEtaEta = 0;
   hyphoR1x5 = 0;
   hyphoR2x5 = 0;
   hyphoESEffSigmaRR = 0;
   hyphoSigmaIEtaIEta_2012 = 0;
   hyphoSigmaIEtaIPhi_2012 = 0;
   hyphoSigmaIPhiIPhi_2012 = 0;
   hyphoE1x3_2012 = 0;
   hyphoE2x2_2012 = 0;
   hyphoE3x3_2012 = 0;
   hyphoE2x5Max_2012 = 0;
   hyphoE5x5_2012 = 0;
   hyphoBC1E = 0;
   hyphoBC1Eta = 0;
   hyphoBC2E = 0;
   hyphoBC2Eta = 0;
   hypho_ecalClusterIsoR2 = 0;
   hypho_ecalClusterIsoR3 = 0;
   hypho_ecalClusterIsoR4 = 0;
   hypho_ecalClusterIsoR5 = 0;
   hypho_hcalRechitIsoR1 = 0;
   hypho_hcalRechitIsoR2 = 0;
   hypho_hcalRechitIsoR3 = 0;
   hypho_hcalRechitIsoR4 = 0;
   hypho_hcalRechitIsoR5 = 0;
   hypho_trackIsoR1PtCut20 = 0;
   hypho_trackIsoR2PtCut20 = 0;
   hypho_trackIsoR3PtCut20 = 0;
   hypho_trackIsoR4PtCut20 = 0;
   hypho_trackIsoR5PtCut20 = 0;
   hypho_swissCrx = 0;
   hypho_seedTime = 0;
   elegsfTrkPt = 0;
   elegsfTrkP = 0;
   elegsfTrkEta = 0;
   elegsfTrkPhi = 0;
   elegsfTrkCharge = 0;
   elegsfTrkChi2 = 0;
   elegsfTrkNdof = 0;
   elegsfTrkNormalizedChi2 = 0;
   elegsfTrkValidHits = 0;
   elegsfTrkMissHits = 0;
   elegsfTrkLayers = 0;
   elegsfD0 = 0;
   elegsfDz = 0;
   elegsfD0Err = 0;
   elegsfDzErr = 0;
   gentrkPt = 0;
   gentrkP = 0;
   gentrkEta = 0;
   gentrkPhi = 0;
   gentrkcharge = 0;
   gentrkvx = 0;
   gentrkvy = 0;
   gentrkvz = 0;
   gentrknormchi2 = 0;
   gentrkchi2 = 0;
   gentrkd0 = 0;
   gentrkdxy = 0;
   gentrkdz = 0;
   gentrkdxyError = 0;
   gentrkdzError = 0;
   gentrkValidHits = 0;
   gentrkMissHits = 0;
   gentrkPurity = 0;
   sc_hybrid_E = 0;
   sc_hybrid_Et = 0;
   sc_hybrid_Eta = 0;
   sc_hybrid_Phi = 0;
   sc_hybrid_x = 0;
   sc_hybrid_y = 0;
   sc_hybrid_z = 0;
   sc_hybrid_EtaWidth = 0;
   sc_hybrid_PhiWidth = 0;
   sc_hybrid_RawE = 0;
   sc_hybrid_RawEt = 0;
   sc_mult55_E = 0;
   sc_mult55_Et = 0;
   sc_mult55_Eta = 0;
   sc_mult55_Phi = 0;
   sc_mult55_x = 0;
   sc_mult55_y = 0;
   sc_mult55_z = 0;
   sc_mult55_EtaWidth = 0;
   sc_mult55_PhiWidth = 0;
   sc_mult55_RawE = 0;
   sc_mult55_RawEt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("isFakeVtx", &isFakeVtx, &b_isFakeVtx);
   fChain->SetBranchAddress("xVtx", &xVtx, &b_xVtx);
   fChain->SetBranchAddress("yVtx", &yVtx, &b_yVtx);
   fChain->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleSCPixCharge", &eleSCPixCharge, &b_eleSCPixCharge);
   fChain->SetBranchAddress("eleCtfCharge", &eleCtfCharge, &b_eleCtfCharge);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleD0Err", &eleD0Err, &b_eleD0Err);
   fChain->SetBranchAddress("eleDzErr", &eleDzErr, &b_eleDzErr);
   fChain->SetBranchAddress("eleTrkPt", &eleTrkPt, &b_eleTrkPt);
   fChain->SetBranchAddress("eleTrkEta", &eleTrkEta, &b_eleTrkEta);
   fChain->SetBranchAddress("eleTrkPhi", &eleTrkPhi, &b_eleTrkPhi);
   fChain->SetBranchAddress("eleTrkCharge", &eleTrkCharge, &b_eleTrkCharge);
   fChain->SetBranchAddress("eleTrkChi2", &eleTrkChi2, &b_eleTrkChi2);
   fChain->SetBranchAddress("eleTrkNdof", &eleTrkNdof, &b_eleTrkNdof);
   fChain->SetBranchAddress("eleTrkNormalizedChi2", &eleTrkNormalizedChi2, &b_eleTrkNormalizedChi2);
   fChain->SetBranchAddress("eleTrkValidHits", &eleTrkValidHits, &b_eleTrkValidHits);
   fChain->SetBranchAddress("eleTrkLayers", &eleTrkLayers, &b_eleTrkLayers);
   fChain->SetBranchAddress("eleP", &eleP, &b_eleP);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleSCx", &eleSCx, &b_eleSCx);
   fChain->SetBranchAddress("eleSCy", &eleSCy, &b_eleSCy);
   fChain->SetBranchAddress("eleSCz", &eleSCz, &b_eleSCz);
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
   fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
   fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
   fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
   fChain->SetBranchAddress("eledEtaSeedAtVtx", &eledEtaSeedAtVtx, &b_eledEtaSeedAtVtx);
   fChain->SetBranchAddress("eleSigmaIEtaIEta", &eleSigmaIEtaIEta, &b_eleSigmaIEtaIEta);
   fChain->SetBranchAddress("eleSigmaIEtaIEta_2012", &eleSigmaIEtaIEta_2012, &b_eleSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("eleSigmaIPhiIPhi", &eleSigmaIPhiIPhi, &b_eleSigmaIPhiIPhi);
   fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("eleTrackIso", &eleTrackIso, &b_eleTrackIso);
   fChain->SetBranchAddress("eleECalIso", &eleECalIso, &b_eleECalIso);
   fChain->SetBranchAddress("eleHCalIso", &eleHCalIso, &b_eleHCalIso);
   fChain->SetBranchAddress("eleECalDriven", &eleECalDriven, &b_eleECalDriven);
   fChain->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
   fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
   fChain->SetBranchAddress("elePFChIso03", &elePFChIso03, &b_elePFChIso03);
   fChain->SetBranchAddress("elePFPhoIso03", &elePFPhoIso03, &b_elePFPhoIso03);
   fChain->SetBranchAddress("elePFNeuIso03", &elePFNeuIso03, &b_elePFNeuIso03);
   fChain->SetBranchAddress("elePFChIso04", &elePFChIso04, &b_elePFChIso04);
   fChain->SetBranchAddress("elePFPhoIso04", &elePFPhoIso04, &b_elePFPhoIso04);
   fChain->SetBranchAddress("elePFNeuIso04", &elePFNeuIso04, &b_elePFNeuIso04);
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
   fChain->SetBranchAddress("eleIDVeto", &eleIDVeto, &b_eleIDVeto);
   fChain->SetBranchAddress("eleIDLoose", &eleIDLoose, &b_eleIDLoose);
   fChain->SetBranchAddress("eleIDMedium", &eleIDMedium, &b_eleIDMedium);
   fChain->SetBranchAddress("eleIDTight", &eleIDTight, &b_eleIDTight);
   fChain->SetBranchAddress("elepassConversionVeto", &elepassConversionVeto, &b_elepassConversionVeto);
   fChain->SetBranchAddress("eleEffAreaTimesRho", &eleEffAreaTimesRho, &b_eleEffAreaTimesRho);
   fChain->SetBranchAddress("nConv", &nConv, &b_nConv);
   fChain->SetBranchAddress("conv_eleind", &conv_eleind, &b_conv_eleind);
   fChain->SetBranchAddress("conv_phoind", &conv_phoind, &b_conv_phoind);
   fChain->SetBranchAddress("conv_vtxprob", &conv_vtxprob, &b_conv_vtxprob);
   fChain->SetBranchAddress("conv_lxy", &conv_lxy, &b_conv_lxy);
   fChain->SetBranchAddress("conv_nhits_bvtx", &conv_nhits_bvtx, &b_conv_nhits_bvtx);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
   fChain->SetBranchAddress("phoSCEt", &phoSCEt, &b_phoSCEt);
   fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
   fChain->SetBranchAddress("phoSCRawEt", &phoSCRawEt, &b_phoSCRawEt);
   fChain->SetBranchAddress("phoESEn", &phoESEn, &b_phoESEn);
   fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoSCx", &phoSCx, &b_phoSCx);
   fChain->SetBranchAddress("phoSCy", &phoSCy, &b_phoSCy);
   fChain->SetBranchAddress("phoSCz", &phoSCz, &b_phoSCz);
   fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
   fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
   fChain->SetBranchAddress("phoSCBrem", &phoSCBrem, &b_phoSCBrem);
   fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
   fChain->SetBranchAddress("phopassConversionVeto", &phopassConversionVeto, &b_phopassConversionVeto);
   fChain->SetBranchAddress("phoR9", &phoR9, &b_phoR9);
   fChain->SetBranchAddress("phoHadTowerOverEm", &phoHadTowerOverEm, &b_phoHadTowerOverEm);
   fChain->SetBranchAddress("phoHoverE", &phoHoverE, &b_phoHoverE);
   fChain->SetBranchAddress("phoSigmaIEtaIEta", &phoSigmaIEtaIEta, &b_phoSigmaIEtaIEta);
   fChain->SetBranchAddress("phoE1x3", &phoE1x3, &b_phoE1x3);
   fChain->SetBranchAddress("phoE2x2", &phoE2x2, &b_phoE2x2);
   fChain->SetBranchAddress("phoE3x3", &phoE3x3, &b_phoE3x3);
   fChain->SetBranchAddress("phoE2x5Max", &phoE2x5Max, &b_phoE2x5Max);
   fChain->SetBranchAddress("phoE1x5", &phoE1x5, &b_phoE1x5);
   fChain->SetBranchAddress("phoE2x5", &phoE2x5, &b_phoE2x5);
   fChain->SetBranchAddress("phoE5x5", &phoE5x5, &b_phoE5x5);
   fChain->SetBranchAddress("phoMaxEnergyXtal", &phoMaxEnergyXtal, &b_phoMaxEnergyXtal);
   fChain->SetBranchAddress("phoSigmaEtaEta", &phoSigmaEtaEta, &b_phoSigmaEtaEta);
   fChain->SetBranchAddress("phoR1x5", &phoR1x5, &b_phoR1x5);
   fChain->SetBranchAddress("phoR2x5", &phoR2x5, &b_phoR2x5);
   fChain->SetBranchAddress("phoESEffSigmaRR", &phoESEffSigmaRR, &b_phoESEffSigmaRR);
   fChain->SetBranchAddress("phoSigmaIEtaIEta_2012", &phoSigmaIEtaIEta_2012, &b_phoSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("phoSigmaIEtaIPhi_2012", &phoSigmaIEtaIPhi_2012, &b_phoSigmaIEtaIPhi_2012);
   fChain->SetBranchAddress("phoSigmaIPhiIPhi_2012", &phoSigmaIPhiIPhi_2012, &b_phoSigmaIPhiIPhi_2012);
   fChain->SetBranchAddress("phoE1x3_2012", &phoE1x3_2012, &b_phoE1x3_2012);
   fChain->SetBranchAddress("phoE2x2_2012", &phoE2x2_2012, &b_phoE2x2_2012);
   fChain->SetBranchAddress("phoE3x3_2012", &phoE3x3_2012, &b_phoE3x3_2012);
   fChain->SetBranchAddress("phoE2x5Max_2012", &phoE2x5Max_2012, &b_phoE2x5Max_2012);
   fChain->SetBranchAddress("phoE5x5_2012", &phoE5x5_2012, &b_phoE5x5_2012);
   fChain->SetBranchAddress("phoBC1E", &phoBC1E, &b_phoBC1E);
   fChain->SetBranchAddress("phoBC1Eta", &phoBC1Eta, &b_phoBC1Eta);
   fChain->SetBranchAddress("phoBC2E", &phoBC2E, &b_phoBC2E);
   fChain->SetBranchAddress("phoBC2Eta", &phoBC2Eta, &b_phoBC2Eta);
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
   fChain->SetBranchAddress("phoIsConv", &phoIsConv, &b_phoIsConv);
   fChain->SetBranchAddress("phoNConv", &phoNConv, &b_phoNConv);
   fChain->SetBranchAddress("phoConvInvMass", &phoConvInvMass, &b_phoConvInvMass);
   fChain->SetBranchAddress("phoConvCotTheta", &phoConvCotTheta, &b_phoConvCotTheta);
   fChain->SetBranchAddress("phoConvEoverP", &phoConvEoverP, &b_phoConvEoverP);
   fChain->SetBranchAddress("phoConvZofPVfromTrks", &phoConvZofPVfromTrks, &b_phoConvZofPVfromTrks);
   fChain->SetBranchAddress("phoConvMinDist", &phoConvMinDist, &b_phoConvMinDist);
   fChain->SetBranchAddress("phoConvdPhiAtVtx", &phoConvdPhiAtVtx, &b_phoConvdPhiAtVtx);
   fChain->SetBranchAddress("phoConvdPhiAtCalo", &phoConvdPhiAtCalo, &b_phoConvdPhiAtCalo);
   fChain->SetBranchAddress("phoConvdEtaAtCalo", &phoConvdEtaAtCalo, &b_phoConvdEtaAtCalo);
   fChain->SetBranchAddress("phoConvTrkd0_x", &phoConvTrkd0_x, &b_phoConvTrkd0_x);
   fChain->SetBranchAddress("phoConvTrkd0_y", &phoConvTrkd0_y, &b_phoConvTrkd0_y);
   fChain->SetBranchAddress("phoConvTrkPin_x", &phoConvTrkPin_x, &b_phoConvTrkPin_x);
   fChain->SetBranchAddress("phoConvTrkPin_y", &phoConvTrkPin_y, &b_phoConvTrkPin_y);
   fChain->SetBranchAddress("phoConvTrkPout_x", &phoConvTrkPout_x, &b_phoConvTrkPout_x);
   fChain->SetBranchAddress("phoConvTrkPout_y", &phoConvTrkPout_y, &b_phoConvTrkPout_y);
   fChain->SetBranchAddress("phoConvTrkdz_x", &phoConvTrkdz_x, &b_phoConvTrkdz_x);
   fChain->SetBranchAddress("phoConvTrkdz_y", &phoConvTrkdz_y, &b_phoConvTrkdz_y);
   fChain->SetBranchAddress("phoConvTrkdzErr_x", &phoConvTrkdzErr_x, &b_phoConvTrkdzErr_x);
   fChain->SetBranchAddress("phoConvTrkdzErr_y", &phoConvTrkdzErr_y, &b_phoConvTrkdzErr_y);
   fChain->SetBranchAddress("phoConvChi2", &phoConvChi2, &b_phoConvChi2);
   fChain->SetBranchAddress("phoConvChi2Prob", &phoConvChi2Prob, &b_phoConvChi2Prob);
   fChain->SetBranchAddress("phoConvNTrks", &phoConvNTrks, &b_phoConvNTrks);
   fChain->SetBranchAddress("phoConvCharge1", &phoConvCharge1, &b_phoConvCharge1);
   fChain->SetBranchAddress("phoConvCharge2", &phoConvCharge2, &b_phoConvCharge2);
   fChain->SetBranchAddress("phoConvValidVtx", &phoConvValidVtx, &b_phoConvValidVtx);
   fChain->SetBranchAddress("phoConvLikeLihood", &phoConvLikeLihood, &b_phoConvLikeLihood);
   fChain->SetBranchAddress("phoConvP4_0", &phoConvP4_0, &b_phoConvP4_0);
   fChain->SetBranchAddress("phoConvP4_1", &phoConvP4_1, &b_phoConvP4_1);
   fChain->SetBranchAddress("phoConvP4_2", &phoConvP4_2, &b_phoConvP4_2);
   fChain->SetBranchAddress("phoConvP4_3", &phoConvP4_3, &b_phoConvP4_3);
   fChain->SetBranchAddress("phoConvVtx_x", &phoConvVtx_x, &b_phoConvVtx_x);
   fChain->SetBranchAddress("phoConvVtx_y", &phoConvVtx_y, &b_phoConvVtx_y);
   fChain->SetBranchAddress("phoConvVtx_z", &phoConvVtx_z, &b_phoConvVtx_z);
   fChain->SetBranchAddress("phoConvVtxErr_x", &phoConvVtxErr_x, &b_phoConvVtxErr_x);
   fChain->SetBranchAddress("phoConvVtxErr_y", &phoConvVtxErr_y, &b_phoConvVtxErr_y);
   fChain->SetBranchAddress("phoConvVtxErr_z", &phoConvVtxErr_z, &b_phoConvVtxErr_z);
   fChain->SetBranchAddress("phoConvPairMomentum_x", &phoConvPairMomentum_x, &b_phoConvPairMomentum_x);
   fChain->SetBranchAddress("phoConvPairMomentum_y", &phoConvPairMomentum_y, &b_phoConvPairMomentum_y);
   fChain->SetBranchAddress("phoConvPairMomentum_z", &phoConvPairMomentum_z, &b_phoConvPairMomentum_z);
   fChain->SetBranchAddress("phoConvRefittedMomentum_x", &phoConvRefittedMomentum_x, &b_phoConvRefittedMomentum_x);
   fChain->SetBranchAddress("phoConvRefittedMomentum_y", &phoConvRefittedMomentum_y, &b_phoConvRefittedMomentum_y);
   fChain->SetBranchAddress("phoConvRefittedMomentum_z", &phoConvRefittedMomentum_z, &b_phoConvRefittedMomentum_z);
   fChain->SetBranchAddress("SingleLegConv", &SingleLegConv, &b_SingleLegConv);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muIsGood", &muIsGood, &b_muIsGood);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
   fChain->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
   fChain->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
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
   fChain->SetBranchAddress("nTower", &nTower, &b_nTower);
   fChain->SetBranchAddress("CaloTower_hadE", &CaloTower_hadE, &b_CaloTower_hadE);
   fChain->SetBranchAddress("CaloTower_emE", &CaloTower_emE, &b_CaloTower_emE);
   fChain->SetBranchAddress("CaloTower_e", &CaloTower_e, &b_CaloTower_e);
   fChain->SetBranchAddress("CaloTower_et", &CaloTower_et, &b_CaloTower_et);
   fChain->SetBranchAddress("CaloTower_eta", &CaloTower_eta, &b_CaloTower_eta);
   fChain->SetBranchAddress("CaloTower_phi", &CaloTower_phi, &b_CaloTower_phi);
   fChain->SetBranchAddress("nHyPho", &nHyPho, &b_nHyPho);
   fChain->SetBranchAddress("hyphoE", &hyphoE, &b_hyphoE);
   fChain->SetBranchAddress("hyphoEt", &hyphoEt, &b_hyphoEt);
   fChain->SetBranchAddress("hyphoEta", &hyphoEta, &b_hyphoEta);
   fChain->SetBranchAddress("hyphoPhi", &hyphoPhi, &b_hyphoPhi);
   fChain->SetBranchAddress("hyphoSCE", &hyphoSCE, &b_hyphoSCE);
   fChain->SetBranchAddress("hyphoSCEt", &hyphoSCEt, &b_hyphoSCEt);
   fChain->SetBranchAddress("hyphoSCRawE", &hyphoSCRawE, &b_hyphoSCRawE);
   fChain->SetBranchAddress("hyphoSCRawEt", &hyphoSCRawEt, &b_hyphoSCRawEt);
   fChain->SetBranchAddress("hyphoESEn", &hyphoESEn, &b_hyphoESEn);
   fChain->SetBranchAddress("hyphoSCEta", &hyphoSCEta, &b_hyphoSCEta);
   fChain->SetBranchAddress("hyphoSCPhi", &hyphoSCPhi, &b_hyphoSCPhi);
   fChain->SetBranchAddress("hyphoSCx", &hyphoSCx, &b_hyphoSCx);
   fChain->SetBranchAddress("hyphoSCy", &hyphoSCy, &b_hyphoSCy);
   fChain->SetBranchAddress("hyphoSCz", &hyphoSCz, &b_hyphoSCz);
   fChain->SetBranchAddress("hyphoSCEtaWidth", &hyphoSCEtaWidth, &b_hyphoSCEtaWidth);
   fChain->SetBranchAddress("hyphoSCPhiWidth", &hyphoSCPhiWidth, &b_hyphoSCPhiWidth);
   fChain->SetBranchAddress("hyphoSCBrem", &hyphoSCBrem, &b_hyphoSCBrem);
   fChain->SetBranchAddress("hyphohasPixelSeed", &hyphohasPixelSeed, &b_hyphohasPixelSeed);
   fChain->SetBranchAddress("hyphopassConversionVeto", &hyphopassConversionVeto, &b_hyphopassConversionVeto);
   fChain->SetBranchAddress("hyphoR9", &hyphoR9, &b_hyphoR9);
   fChain->SetBranchAddress("hyphoHadTowerOverEm", &hyphoHadTowerOverEm, &b_hyphoHadTowerOverEm);
   fChain->SetBranchAddress("hyphoHoverE", &hyphoHoverE, &b_hyphoHoverE);
   fChain->SetBranchAddress("hyphoSigmaIEtaIEta", &hyphoSigmaIEtaIEta, &b_hyphoSigmaIEtaIEta);
   fChain->SetBranchAddress("hyphoE1x3", &hyphoE1x3, &b_hyphoE1x3);
   fChain->SetBranchAddress("hyphoE2x2", &hyphoE2x2, &b_hyphoE2x2);
   fChain->SetBranchAddress("hyphoE3x3", &hyphoE3x3, &b_hyphoE3x3);
   fChain->SetBranchAddress("hyphoE2x5Max", &hyphoE2x5Max, &b_hyphoE2x5Max);
   fChain->SetBranchAddress("hyphoE1x5", &hyphoE1x5, &b_hyphoE1x5);
   fChain->SetBranchAddress("hyphoE2x5", &hyphoE2x5, &b_hyphoE2x5);
   fChain->SetBranchAddress("hyphoE5x5", &hyphoE5x5, &b_hyphoE5x5);
   fChain->SetBranchAddress("hyphoMaxEnergyXtal", &hyphoMaxEnergyXtal, &b_hyphoMaxEnergyXtal);
   fChain->SetBranchAddress("hyphoSigmaEtaEta", &hyphoSigmaEtaEta, &b_hyphoSigmaEtaEta);
   fChain->SetBranchAddress("hyphoR1x5", &hyphoR1x5, &b_hyphoR1x5);
   fChain->SetBranchAddress("hyphoR2x5", &hyphoR2x5, &b_hyphoR2x5);
   fChain->SetBranchAddress("hyphoESEffSigmaRR", &hyphoESEffSigmaRR, &b_hyphoESEffSigmaRR);
   fChain->SetBranchAddress("hyphoSigmaIEtaIEta_2012", &hyphoSigmaIEtaIEta_2012, &b_hyphoSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("hyphoSigmaIEtaIPhi_2012", &hyphoSigmaIEtaIPhi_2012, &b_hyphoSigmaIEtaIPhi_2012);
   fChain->SetBranchAddress("hyphoSigmaIPhiIPhi_2012", &hyphoSigmaIPhiIPhi_2012, &b_hyphoSigmaIPhiIPhi_2012);
   fChain->SetBranchAddress("hyphoE1x3_2012", &hyphoE1x3_2012, &b_hyphoE1x3_2012);
   fChain->SetBranchAddress("hyphoE2x2_2012", &hyphoE2x2_2012, &b_hyphoE2x2_2012);
   fChain->SetBranchAddress("hyphoE3x3_2012", &hyphoE3x3_2012, &b_hyphoE3x3_2012);
   fChain->SetBranchAddress("hyphoE2x5Max_2012", &hyphoE2x5Max_2012, &b_hyphoE2x5Max_2012);
   fChain->SetBranchAddress("hyphoE5x5_2012", &hyphoE5x5_2012, &b_hyphoE5x5_2012);
   fChain->SetBranchAddress("hyphoBC1E", &hyphoBC1E, &b_hyphoBC1E);
   fChain->SetBranchAddress("hyphoBC1Eta", &hyphoBC1Eta, &b_hyphoBC1Eta);
   fChain->SetBranchAddress("hyphoBC2E", &hyphoBC2E, &b_hyphoBC2E);
   fChain->SetBranchAddress("hyphoBC2Eta", &hyphoBC2Eta, &b_hyphoBC2Eta);
   fChain->SetBranchAddress("hypho_ecalClusterIsoR2", &hypho_ecalClusterIsoR2, &b_hypho_ecalClusterIsoR2);
   fChain->SetBranchAddress("hypho_ecalClusterIsoR3", &hypho_ecalClusterIsoR3, &b_hypho_ecalClusterIsoR3);
   fChain->SetBranchAddress("hypho_ecalClusterIsoR4", &hypho_ecalClusterIsoR4, &b_hypho_ecalClusterIsoR4);
   fChain->SetBranchAddress("hypho_ecalClusterIsoR5", &hypho_ecalClusterIsoR5, &b_hypho_ecalClusterIsoR5);
   fChain->SetBranchAddress("hypho_hcalRechitIsoR1", &hypho_hcalRechitIsoR1, &b_hypho_hcalRechitIsoR1);
   fChain->SetBranchAddress("hypho_hcalRechitIsoR2", &hypho_hcalRechitIsoR2, &b_hypho_hcalRechitIsoR2);
   fChain->SetBranchAddress("hypho_hcalRechitIsoR3", &hypho_hcalRechitIsoR3, &b_hypho_hcalRechitIsoR3);
   fChain->SetBranchAddress("hypho_hcalRechitIsoR4", &hypho_hcalRechitIsoR4, &b_hypho_hcalRechitIsoR4);
   fChain->SetBranchAddress("hypho_hcalRechitIsoR5", &hypho_hcalRechitIsoR5, &b_hypho_hcalRechitIsoR5);
   fChain->SetBranchAddress("hypho_trackIsoR1PtCut20", &hypho_trackIsoR1PtCut20, &b_hypho_trackIsoR1PtCut20);
   fChain->SetBranchAddress("hypho_trackIsoR2PtCut20", &hypho_trackIsoR2PtCut20, &b_hypho_trackIsoR2PtCut20);
   fChain->SetBranchAddress("hypho_trackIsoR3PtCut20", &hypho_trackIsoR3PtCut20, &b_hypho_trackIsoR3PtCut20);
   fChain->SetBranchAddress("hypho_trackIsoR4PtCut20", &hypho_trackIsoR4PtCut20, &b_hypho_trackIsoR4PtCut20);
   fChain->SetBranchAddress("hypho_trackIsoR5PtCut20", &hypho_trackIsoR5PtCut20, &b_hypho_trackIsoR5PtCut20);
   fChain->SetBranchAddress("hypho_swissCrx", &hypho_swissCrx, &b_hypho_swissCrx);
   fChain->SetBranchAddress("hypho_seedTime", &hypho_seedTime, &b_hypho_seedTime);
   fChain->SetBranchAddress("ngsfEle", &ngsfEle, &b_ngsfEle);
   fChain->SetBranchAddress("elegsfTrkPt", &elegsfTrkPt, &b_elegsfTrkPt);
   fChain->SetBranchAddress("elegsfTrkP", &elegsfTrkP, &b_elegsfTrkP);
   fChain->SetBranchAddress("elegsfTrkEta", &elegsfTrkEta, &b_elegsfTrkEta);
   fChain->SetBranchAddress("elegsfTrkPhi", &elegsfTrkPhi, &b_elegsfTrkPhi);
   fChain->SetBranchAddress("elegsfTrkCharge", &elegsfTrkCharge, &b_elegsfTrkCharge);
   fChain->SetBranchAddress("elegsfTrkChi2", &elegsfTrkChi2, &b_elegsfTrkChi2);
   fChain->SetBranchAddress("elegsfTrkNdof", &elegsfTrkNdof, &b_elegsfTrkNdof);
   fChain->SetBranchAddress("elegsfTrkNormalizedChi2", &elegsfTrkNormalizedChi2, &b_elegsfTrkNormalizedChi2);
   fChain->SetBranchAddress("elegsfTrkValidHits", &elegsfTrkValidHits, &b_elegsfTrkValidHits);
   fChain->SetBranchAddress("elegsfTrkMissHits", &elegsfTrkMissHits, &b_elegsfTrkMissHits);
   fChain->SetBranchAddress("elegsfTrkLayers", &elegsfTrkLayers, &b_elegsfTrkLayers);
   fChain->SetBranchAddress("elegsfD0", &elegsfD0, &b_elegsfD0);
   fChain->SetBranchAddress("elegsfDz", &elegsfDz, &b_elegsfDz);
   fChain->SetBranchAddress("elegsfD0Err", &elegsfD0Err, &b_elegsfD0Err);
   fChain->SetBranchAddress("elegsfDzErr", &elegsfDzErr, &b_elegsfDzErr);
   fChain->SetBranchAddress("ngenTrk", &ngenTrk, &b_ngenTrk);
   fChain->SetBranchAddress("gentrkPt", &gentrkPt, &b_gentrkPt);
   fChain->SetBranchAddress("gentrkP", &gentrkP, &b_gentrkP);
   fChain->SetBranchAddress("gentrkEta", &gentrkEta, &b_gentrkEta);
   fChain->SetBranchAddress("gentrkPhi", &gentrkPhi, &b_gentrkPhi);
   fChain->SetBranchAddress("gentrkcharge", &gentrkcharge, &b_gentrkcharge);
   fChain->SetBranchAddress("gentrkvx", &gentrkvx, &b_gentrkvx);
   fChain->SetBranchAddress("gentrkvy", &gentrkvy, &b_gentrkvy);
   fChain->SetBranchAddress("gentrkvz", &gentrkvz, &b_gentrkvz);
   fChain->SetBranchAddress("gentrknormchi2", &gentrknormchi2, &b_gentrknormchi2);
   fChain->SetBranchAddress("gentrkchi2", &gentrkchi2, &b_gentrkchi2);
   fChain->SetBranchAddress("gentrkd0", &gentrkd0, &b_gentrkd0);
   fChain->SetBranchAddress("gentrkdxy", &gentrkdxy, &b_gentrkdxy);
   fChain->SetBranchAddress("gentrkdz", &gentrkdz, &b_gentrkdz);
   fChain->SetBranchAddress("gentrkdxyError", &gentrkdxyError, &b_gentrkdxyError);
   fChain->SetBranchAddress("gentrkdzError", &gentrkdzError, &b_gentrkdzError);
   fChain->SetBranchAddress("gentrkValidHits", &gentrkValidHits, &b_gentrkValidHits);
   fChain->SetBranchAddress("gentrkMissHits", &gentrkMissHits, &b_gentrkMissHits);
   fChain->SetBranchAddress("gentrkPurity", &gentrkPurity, &b_gentrkPurity);
   fChain->SetBranchAddress("nsc_hybrid", &nsc_hybrid, &b_nsc_hybrid);
   fChain->SetBranchAddress("sc_hybrid_E", &sc_hybrid_E, &b_sc_hybrid_E);
   fChain->SetBranchAddress("sc_hybrid_Et", &sc_hybrid_Et, &b_sc_hybrid_Et);
   fChain->SetBranchAddress("sc_hybrid_Eta", &sc_hybrid_Eta, &b_sc_hybrid_Eta);
   fChain->SetBranchAddress("sc_hybrid_Phi", &sc_hybrid_Phi, &b_sc_hybrid_Phi);
   fChain->SetBranchAddress("sc_hybrid_x", &sc_hybrid_x, &b_sc_hybrid_x);
   fChain->SetBranchAddress("sc_hybrid_y", &sc_hybrid_y, &b_sc_hybrid_y);
   fChain->SetBranchAddress("sc_hybrid_z", &sc_hybrid_z, &b_sc_hybrid_z);
   fChain->SetBranchAddress("sc_hybrid_EtaWidth", &sc_hybrid_EtaWidth, &b_sc_hybrid_EtaWidth);
   fChain->SetBranchAddress("sc_hybrid_PhiWidth", &sc_hybrid_PhiWidth, &b_sc_hybrid_PhiWidth);
   fChain->SetBranchAddress("sc_hybrid_RawE", &sc_hybrid_RawE, &b_sc_hybrid_RawE);
   fChain->SetBranchAddress("sc_hybrid_RawEt", &sc_hybrid_RawEt, &b_sc_hybrid_RawEt);
   fChain->SetBranchAddress("nsc_mult55", &nsc_mult55, &b_nsc_mult55);
   fChain->SetBranchAddress("sc_mult55_E", &sc_mult55_E, &b_sc_mult55_E);
   fChain->SetBranchAddress("sc_mult55_Et", &sc_mult55_Et, &b_sc_mult55_Et);
   fChain->SetBranchAddress("sc_mult55_Eta", &sc_mult55_Eta, &b_sc_mult55_Eta);
   fChain->SetBranchAddress("sc_mult55_Phi", &sc_mult55_Phi, &b_sc_mult55_Phi);
   fChain->SetBranchAddress("sc_mult55_x", &sc_mult55_x, &b_sc_mult55_x);
   fChain->SetBranchAddress("sc_mult55_y", &sc_mult55_y, &b_sc_mult55_y);
   fChain->SetBranchAddress("sc_mult55_z", &sc_mult55_z, &b_sc_mult55_z);
   fChain->SetBranchAddress("sc_mult55_EtaWidth", &sc_mult55_EtaWidth, &b_sc_mult55_EtaWidth);
   fChain->SetBranchAddress("sc_mult55_PhiWidth", &sc_mult55_PhiWidth, &b_sc_mult55_PhiWidth);
   fChain->SetBranchAddress("sc_mult55_RawE", &sc_mult55_RawE, &b_sc_mult55_RawE);
   fChain->SetBranchAddress("sc_mult55_RawEt", &sc_mult55_RawEt, &b_sc_mult55_RawEt);
   Notify();
}

Bool_t eventTreeReaderData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void eventTreeReaderData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t eventTreeReaderData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef eventTreeReaderData_cxx
