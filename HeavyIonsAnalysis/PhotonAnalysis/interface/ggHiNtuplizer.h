#ifndef ggHiNtuplizer_h
#define ggHiNtuplizer_h

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/HIPhotonIsolation.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include <TTree.h>
//LbyL addition
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterFunctionFactory.h" 

class ggHiNtuplizer : public edm::EDAnalyzer {

 public:

   ggHiNtuplizer(const edm::ParameterSet&);
   virtual ~ggHiNtuplizer() {};

 private:

   virtual void analyze(const edm::Event&, const edm::EventSetup&);

   void fillGenParticles (const edm::Event&);
   void fillGenPileupInfo(const edm::Event&);
   void fillElectrons    (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillPhotons      (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillMuons        (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);

   void fillHMPhotons    (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillGSFElectrons (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillGeneralTracks(const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillHMSuperCluster(const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);
   void fillCaloTower    (const edm::Event&, const edm::EventSetup&, math::XYZPoint& pv);


   // Et and pT sums
   float getGenCalIso(edm::Handle<std::vector<reco::GenParticle> >&, reco::GenParticleCollection::const_iterator, float dRMax, bool removeMu, bool removeNu);
   float getGenTrkIso(edm::Handle<std::vector<reco::GenParticle> >&, reco::GenParticleCollection::const_iterator, float dRMax);

   // switches
   bool doGenParticles_;
   bool doElectrons_;
   bool doPhotons_;
   bool doMuons_;
   bool runOnParticleGun_;
   bool useValMapIso_;
   bool doPfIso_;
   bool doVID_;
   bool doRecHitsEB_;
   bool doRecHitsEE_;

   // LbyL addition
   bool doHMPhotons_;
   bool doGSFElectrons_;
   bool doGeneralTracks_;
   bool doHMSuperCluster_;
   bool doCaloTower_;


   // handles to collections of objects
   edm::EDGetTokenT<std::vector<PileupSummaryInfo> >    genPileupCollection_;
   edm::EDGetTokenT<std::vector<reco::GenParticle> >    genParticlesCollection_;
   edm::EDGetTokenT<edm::View<reco::GsfElectron> > gsfElectronsCollection_;
   edm::EDGetTokenT<edm::ValueMap<bool> > eleVetoIdMapToken_;
   edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseIdMapToken_;
   edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumIdMapToken_;
   edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken_;
   edm::EDGetTokenT<edm::View<reco::Photon> >      recoPhotonsCollection_;
   edm::EDGetTokenT<edm::ValueMap<reco::HIPhotonIsolation> > recoPhotonsHiIso_;
   edm::EDGetTokenT<edm::View<reco::Muon> >        recoMuonsCollection_;
   edm::EDGetTokenT<std::vector<reco::Vertex> >         vtxCollection_;
   edm::EDGetTokenT<double> rhoToken_;
   edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
   edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;
   edm::EDGetTokenT<edm::View<reco::PFCandidate> >    pfCollection_;

   edm::EDGetTokenT<EcalRecHitCollection> recHitsEB_;
   edm::EDGetTokenT<EcalRecHitCollection> recHitsEE_;

  
   // LbyL addition
   edm::EDGetTokenT<edm::View<reco::Photon> >      recoHMPhotonsCollection_;
   edm::EDGetTokenT<edm::ValueMap<reco::HIPhotonIsolation> > recoHMPhotonsHiIso_;
   edm::EDGetTokenT<reco::GsfTrackCollection>  gsfTracks_;
   edm::EDGetTokenT<reco::TrackCollection>    genTracks_;
   edm::EDGetTokenT<reco::SuperClusterCollection>      hybridsc_;
   edm::EDGetTokenT<reco::SuperClusterCollection>      mult55sc_;
   edm::EDGetTokenT<edm::SortedCollection<CaloTower>>        CaloTowerCollection_;



   const CaloGeometry *geo;

   EffectiveAreas effectiveAreas_;

   TTree*         tree_;

   // variables associated with tree branches
   UInt_t         run_;
   ULong64_t      event_;
   UInt_t         lumis_;
   Bool_t         isData_;

   // PileupSummaryInfo
   Int_t          nPUInfo_;
   std::vector<int>    nPU_;
   std::vector<int>    puBX_;
   std::vector<float>  puTrue_;

   // reco::GenParticle
   Int_t          nMC_;
   std::vector<int>    mcPID_;
   std::vector<int>    mcStatus_;
   std::vector<float>  mcVtx_x_;
   std::vector<float>  mcVtx_y_;
   std::vector<float>  mcVtx_z_;
   std::vector<float>  mcPt_;
   std::vector<float>  mcEta_;
   std::vector<float>  mcPhi_;
   std::vector<float>  mcE_;
   std::vector<float>  mcEt_;
   std::vector<float>  mcMass_;
   std::vector<int>    mcParentage_;
   std::vector<int>    mcMomPID_;
   std::vector<float>  mcMomPt_;
   std::vector<float>  mcMomEta_;
   std::vector<float>  mcMomPhi_;
   std::vector<float>  mcMomMass_;
   std::vector<int>    mcGMomPID_;
   std::vector<int>    mcIndex_;
   std::vector<float>  mcCalIsoDR03_;
   std::vector<float>  mcCalIsoDR04_;
   std::vector<float>  mcTrkIsoDR03_;
   std::vector<float>  mcTrkIsoDR04_;

   // reco::GsfElectron
   Int_t          nEle_;
   std::vector<int>    eleCharge_;
   std::vector<int>    eleChargeConsistent_;
   std::vector<int>    eleSCPixCharge_;
   std::vector<int>    eleCtfCharge_;
   std::vector<float>  eleEn_;
   std::vector<float>  eleD0_;
   std::vector<float>  eleDz_;
   std::vector<float>  eleD0Err_;
   std::vector<float>  eleDzErr_;
   std::vector<float>  eleTrkPt_;
   std::vector<float>  eleTrkEta_;
   std::vector<float>  eleTrkPhi_;
   std::vector<int>    eleTrkCharge_;
   std::vector<float>  eleTrkChi2_;
   std::vector<float>  eleTrkNdof_;
   std::vector<float>  eleTrkNormalizedChi2_;
   std::vector<int>    eleTrkValidHits_;
   std::vector<int>    eleTrkLayers_;
   std::vector<float>  elePt_;
   std::vector<float>  eleEta_;
   std::vector<float>  elePhi_;
   std::vector<float>  eleSCEn_;
   std::vector<float>  eleESEn_;
   std::vector<float>  eleSCEta_;
   std::vector<float>  eleSCPhi_;
   std::vector<float>  eleSCRawEn_;
   std::vector<float>  eleSCEtaWidth_;
   std::vector<float>  eleSCPhiWidth_;
   std::vector<float>  eleHoverE_;
   std::vector<float>  eleHoverEBc_;
   std::vector<float>  eleEoverP_;
   std::vector<float>  eleEoverPInv_;
   std::vector<float>  eleBrem_;
   std::vector<float>  eledEtaAtVtx_;
   std::vector<float>  eledPhiAtVtx_;
   std::vector<float>  eleSigmaIEtaIEta_;
   std::vector<float>  eleSigmaIEtaIEta_2012_;
   std::vector<float>  eleSigmaIPhiIPhi_;
// std::vector<int>    eleConvVeto_;     // TODO: not available in reco::
   std::vector<int>    eleMissHits_;
   std::vector<float>  eleESEffSigmaRR_;
   std::vector<float>  elePFChIso_;
   std::vector<float>  elePFPhoIso_;
   std::vector<float>  elePFNeuIso_;
   std::vector<float>  elePFPUIso_;
   std::vector<float>  elePFChIso03_;
   std::vector<float>  elePFPhoIso03_;
   std::vector<float>  elePFNeuIso03_;
   std::vector<float>  elePFChIso04_;
   std::vector<float>  elePFPhoIso04_;
   std::vector<float>  elePFNeuIso04_;
   std::vector<float>  elePFRelIsoWithEA_;
   std::vector<float>  elePFRelIsoWithDBeta_;
   std::vector<float>  eleR9_;
   std::vector<float>  eleE3x3_;
   std::vector<float>  eleE5x5_;
   std::vector<float>  eleR9Full5x5_;
   std::vector<float>  eleE3x3Full5x5_;
   std::vector<float>  eleE5x5Full5x5_;
   std::vector<int>    NClusters_;
   std::vector<int>    NEcalClusters_;
   std::vector<float>  eleSeedEn_;
   std::vector<float>  eleSeedEta_;
   std::vector<float>  eleSeedPhi_;
   std::vector<float>  eleSeedCryEta_;
   std::vector<float>  eleSeedCryPhi_;
   std::vector<float>  eleSeedCryIeta_;
   std::vector<float>  eleSeedCryIphi_;
   std::vector<float>  eleBC1E_;
   std::vector<float>  eleBC1Eta_;
   std::vector<float>  eleBC2E_;
   std::vector<float>  eleBC2Eta_;
   std::vector<int>    eleIDVeto_; //50nsV1 is depreacated; updated in 76X
   std::vector<int>    eleIDLoose_;
   std::vector<int>    eleIDMedium_;
   std::vector<int>    eleIDTight_;
   std::vector<int>    elepassConversionVeto_;
   std::vector<float>  eleEffAreaTimesRho_;

   // reco:: GED Photon
   Int_t          nPho_;
   std::vector<float>  phoE_;
   std::vector<float>  phoEt_;
   std::vector<float>  phoEta_;
   std::vector<float>  phoPhi_;

   std::vector<float>  phoEcorrStdEcal_;
   std::vector<float>  phoEcorrPhoEcal_;
   std::vector<float>  phoEcorrRegr1_;
   std::vector<float>  phoEcorrRegr2_;
   std::vector<float>  phoEcorrErrStdEcal_;
   std::vector<float>  phoEcorrErrPhoEcal_;
   std::vector<float>  phoEcorrErrRegr1_;
   std::vector<float>  phoEcorrErrRegr2_;

   std::vector<float>  phoSCE_;
   std::vector<float>  phoSCEt_;
   std::vector<float>  phoSCRawE_;
   std::vector<float>  phoSCEta_;
   std::vector<float>  phoSCPhi_;
   std::vector<float>  phoSCEtaWidth_;
   std::vector<float>  phoSCPhiWidth_;
   std::vector<float>  phoSCBrem_;
   std::vector<int>    phoSCnHits_;
   std::vector<uint32_t> phoSCflags_;
   std::vector<int>    phoSCinClean_;
   std::vector<int>    phoSCinUnClean_;
   std::vector<int>    phoSCnBC_;
   std::vector<float>  phoESEn_;

   std::vector<float>  phoPSCE_;
   std::vector<float>  phoPSCRawE_;
   std::vector<float>  phoPSCEta_;
   std::vector<float>  phoPSCPhi_;
   std::vector<float>  phoPSCEtaWidth_;
   std::vector<float>  phoPSCPhiWidth_;
   std::vector<float>  phoPSCBrem_;
   std::vector<int>    phoPSCnHits_;
   std::vector<uint32_t> phoPSCflags_;
   std::vector<int>    phoPSCinClean_;
   std::vector<int>    phoPSCinUnClean_;
   std::vector<int>    phoPSCnBC_;
   std::vector<float>  phoPESEn_;

   std::vector<int>    phoIsPFPhoton_;
   std::vector<int>    phoIsStandardPhoton_;
   std::vector<int>    phoHasPixelSeed_;
   std::vector<int>    phoHasConversionTracks_;
// std::vector<int>    phoEleVeto_;         // TODO: not available in reco::
   std::vector<float>  phoR9_;
   std::vector<float>  phoHadTowerOverEm_;
   std::vector<float>  phoHoverE_;
   std::vector<float>  phoSigmaIEtaIEta_;
// std::vector<float>  phoSigmaIEtaIPhi_;   // TODO: not available in reco::
// std::vector<float>  phoSigmaIPhiIPhi_;   // TODO: not available in reco::
   std::vector<float>  phoE1x5_;
   std::vector<float>  phoE2x5_;
   std::vector<float>  phoE3x3_;
   std::vector<float>  phoE5x5_;
   std::vector<float>  phoMaxEnergyXtal_;
   std::vector<float>  phoSigmaEtaEta_;
   std::vector<float>  phoR1x5_;
   std::vector<float>  phoR2x5_;
   std::vector<float>  phoR9_2012_;
   std::vector<float>  phoSigmaIEtaIEta_2012_;
   std::vector<float>  phoE1x5_2012_;
   std::vector<float>  phoE2x5_2012_;
   std::vector<float>  phoE3x3_2012_;
   std::vector<float>  phoE5x5_2012_;
   std::vector<float>  phoMaxEnergyXtal_2012_;
   std::vector<float>  phoSigmaEtaEta_2012_;
   std::vector<float>  phoR1x5_2012_;
   std::vector<float>  phoR2x5_2012_;
   std::vector<float>  phoBC1E_;
   std::vector<float>  phoBC1Ecorr_;
   std::vector<float>  phoBC1Eta_;
   std::vector<float>  phoBC1Phi_;
   std::vector<int>    phoBC1size_;
   std::vector<uint32_t> phoBC1flags_;
   std::vector<int>    phoBC1inClean_;
   std::vector<int>    phoBC1inUnClean_;
   std::vector<uint32_t> phoBC1rawID_;

   /* std::vector<float>  phoBC2E_; */
   /* std::vector<float>  phoBC2Eta_; */
   /* std::vector<float>  phoBC2Phi_; */
   std::vector<float>  pho_ecalClusterIsoR2_;
   std::vector<float>  pho_ecalClusterIsoR3_;
   std::vector<float>  pho_ecalClusterIsoR4_;
   std::vector<float>  pho_ecalClusterIsoR5_;
   std::vector<float>  pho_hcalRechitIsoR1_;
   std::vector<float>  pho_hcalRechitIsoR2_;
   std::vector<float>  pho_hcalRechitIsoR3_;
   std::vector<float>  pho_hcalRechitIsoR4_;
   std::vector<float>  pho_hcalRechitIsoR5_;
   std::vector<float>  pho_trackIsoR1PtCut20_;
   std::vector<float>  pho_trackIsoR2PtCut20_;
   std::vector<float>  pho_trackIsoR3PtCut20_;
   std::vector<float>  pho_trackIsoR4PtCut20_;
   std::vector<float>  pho_trackIsoR5PtCut20_;
   std::vector<float>  pho_swissCrx_;
   std::vector<float>  pho_seedTime_;
   std::vector<int>    pho_genMatchedIndex_;

   // rechit info
   int nRH_;
   std::vector<uint32_t> rhRawId_;
   std::vector<int> rhieta_;
   std::vector<int> rhiphi_;
   std::vector<int> rhix_;
   std::vector<int> rhiy_;
   std::vector<float> rhE_;
   std::vector<float> rhEt_;
   std::vector<float> rhEta_;
   std::vector<float> rhPhi_;
   std::vector<float> rhChi2_;
   std::vector<float> rhEerror_;
   std::vector<uint32_t> rhFlags_;
   std::vector<int> rhPhoIdx_;   // index of the photon this rechit belongs to
   std::vector<int> rhBCIdx_;    // index of this rechit's BC in the SC

   // photon pf isolation stuff
   std::vector<float> pfcIso1;
   std::vector<float> pfcIso2;
   std::vector<float> pfcIso3;
   std::vector<float> pfcIso4;
   std::vector<float> pfcIso5;

   std::vector<float> pfpIso1;
   std::vector<float> pfpIso2;
   std::vector<float> pfpIso3;
   std::vector<float> pfpIso4;
   std::vector<float> pfpIso5;

   std::vector<float> pfnIso1;
   std::vector<float> pfnIso2;
   std::vector<float> pfnIso3;
   std::vector<float> pfnIso4;
   std::vector<float> pfnIso5;

   // reco::Muon
   Int_t          nMu_;
   std::vector<float>  muPt_;
   std::vector<float>  muEta_;
   std::vector<float>  muPhi_;
   std::vector<int>    muCharge_;
   std::vector<int>    muType_;
   std::vector<int>    muIsGood_;
   std::vector<float>  muD0_;
   std::vector<float>  muDz_;
   std::vector<float>  muChi2NDF_;
   std::vector<float>  muInnerD0_;
   std::vector<float>  muInnerDz_;
   std::vector<int>    muTrkLayers_;
   std::vector<int>    muPixelLayers_;
   std::vector<int>    muPixelHits_;
   std::vector<int>    muMuonHits_;
   std::vector<int>    muTrkQuality_;
   std::vector<int>    muStations_;
   std::vector<float>  muIsoTrk_;
   std::vector<float>  muPFChIso_;
   std::vector<float>  muPFPhoIso_;
   std::vector<float>  muPFNeuIso_;
   std::vector<float>  muPFPUIso_;


   // LbyL addition
   // reco:: HM Photon
   Int_t          nHMPho_;
   std::vector<float>  HMphoE_;
   std::vector<float>  HMphoEt_;
   std::vector<float>  HMphoEta_;
   std::vector<float>  HMphoPhi_;

   std::vector<float>  HMphoEcorrStdEcal_;
   std::vector<float>  HMphoEcorrPhoEcal_;
   std::vector<float>  HMphoEcorrRegr1_;
   std::vector<float>  HMphoEcorrRegr2_;
   std::vector<float>  HMphoEcorrErrStdEcal_;
   std::vector<float>  HMphoEcorrErrPhoEcal_;
   std::vector<float>  HMphoEcorrErrRegr1_;
   std::vector<float>  HMphoEcorrErrRegr2_;

   std::vector<float>  HMphoSCE_;
   std::vector<float>  HMphoSCEt_;
   std::vector<float>  HMphoSCRawE_;
   std::vector<float>  HMphoSCEta_;
   std::vector<float>  HMphoSCPhi_;
   std::vector<float>  HMphoSCEtaWidth_;
   std::vector<float>  HMphoSCPhiWidth_;
   std::vector<float>  HMphoSCBrem_;
   std::vector<int>    HMphoSCnHits_;
   std::vector<uint32_t> HMphoSCflags_;
   std::vector<int>    HMphoSCinClean_;
   std::vector<int>    HMphoSCinUnClean_;
   std::vector<int>    HMphoSCnBC_;
   std::vector<float>  HMphoESEn_;

   std::vector<float>  HMphoPSCE_;
   std::vector<float>  HMphoPSCRawE_;
   std::vector<float>  HMphoPSCEta_;
   std::vector<float>  HMphoPSCPhi_;
   std::vector<float>  HMphoPSCEtaWidth_;
   std::vector<float>  HMphoPSCPhiWidth_;
   std::vector<float>  HMphoPSCBrem_;
   std::vector<int>    HMphoPSCnHits_;
   std::vector<uint32_t> HMphoPSCflags_;
   std::vector<int>    HMphoPSCinClean_;
   std::vector<int>    HMphoPSCinUnClean_;
   std::vector<int>    HMphoPSCnBC_;
   std::vector<float>  HMphoPESEn_;

   std::vector<int>    HMphoIsPFPhoton_;
   std::vector<int>    HMphoIsStandardPhoton_;
   std::vector<int>    HMphoHasPixelSeed_;
   std::vector<int>    HMphoHasConversionTracks_;
// std::vector<int>    HMphoEleVeto_;         // TODO: not available in reco::
   std::vector<float>  HMphoR9_;
   std::vector<float>  HMphoHadTowerOverEm_;
   std::vector<float>  HMphoHoverE_;
   std::vector<float>  HMphoSigmaIEtaIEta_;
// std::vector<float>  HMphoSigmaIEtaIPhi_;   // TODO: not available in reco::
// std::vector<float>  HMphoSigmaIPhiIPhi_;   // TODO: not available in reco::
   std::vector<float>  HMphoE1x5_;
   std::vector<float>  HMphoE2x5_;
   std::vector<float>  HMphoE3x3_;
   std::vector<float>  HMphoE5x5_;
   std::vector<float>  HMphoMaxEnergyXtal_;
   std::vector<float>  HMphoSigmaEtaEta_;
   std::vector<float>  HMphoR1x5_;
   std::vector<float>  HMphoR2x5_;
   std::vector<float>  HMphoR9_2012_;
   std::vector<float>  HMphoSigmaIEtaIEta_2012_;
   std::vector<float>  HMphoE1x5_2012_;
   std::vector<float>  HMphoE2x5_2012_;
   std::vector<float>  HMphoE3x3_2012_;
   std::vector<float>  HMphoE5x5_2012_;
   std::vector<float>  HMphoMaxEnergyXtal_2012_;
   std::vector<float>  HMphoSigmaEtaEta_2012_;
   std::vector<float>  HMphoR1x5_2012_;
   std::vector<float>  HMphoR2x5_2012_;
   std::vector<float>  HMphoBC1E_;
   std::vector<float>  HMphoBC1Ecorr_;
   std::vector<float>  HMphoBC1Eta_;
   std::vector<float>  HMphoBC1Phi_;
   std::vector<int>    HMphoBC1size_;
   std::vector<uint32_t> HMphoBC1flags_;
   std::vector<int>    HMphoBC1inClean_;
   std::vector<int>    HMphoBC1inUnClean_;
   std::vector<uint32_t> HMphoBC1rawID_;

   /* std::vector<float>  HMphoBC2E_; */
   /* std::vector<float>  HMphoBC2Eta_; */
   /* std::vector<float>  HMphoBC2Phi_; */
   std::vector<float>  HMpho_ecalClusterIsoR2_;
   std::vector<float>  HMpho_ecalClusterIsoR3_;
   std::vector<float>  HMpho_ecalClusterIsoR4_;
   std::vector<float>  HMpho_ecalClusterIsoR5_;
   std::vector<float>  HMpho_hcalRechitIsoR1_;
   std::vector<float>  HMpho_hcalRechitIsoR2_;
   std::vector<float>  HMpho_hcalRechitIsoR3_;
   std::vector<float>  HMpho_hcalRechitIsoR4_;
   std::vector<float>  HMpho_hcalRechitIsoR5_;
   std::vector<float>  HMpho_trackIsoR1PtCut20_;
   std::vector<float>  HMpho_trackIsoR2PtCut20_;
   std::vector<float>  HMpho_trackIsoR3PtCut20_;
   std::vector<float>  HMpho_trackIsoR4PtCut20_;
   std::vector<float>  HMpho_trackIsoR5PtCut20_;
   std::vector<float>  HMpho_swissCrx_;
   std::vector<float>  HMpho_seedTime_;
   std::vector<int>    HMpho_genMatchedIndex_;

   // rechit info
   int nHMRH_;
   std::vector<uint32_t> HMrhRawId_;
   std::vector<int> HMrhieta_;
   std::vector<int> HMrhiphi_;
   std::vector<int> HMrhix_;
   std::vector<int> HMrhiy_;
   std::vector<float> HMrhE_;
   std::vector<float> HMrhEt_;
   std::vector<float> HMrhEta_;
   std::vector<float> HMrhPhi_;
   std::vector<float> HMrhChi2_;
   std::vector<float> HMrhEerror_;
   std::vector<uint32_t> HMrhFlags_;
   std::vector<int> HMrhPhoIdx_;   // index of the photon this rechit belongs to
   std::vector<int> HMrhBCIdx_;    // index of this rechit's BC in the SC

   // photon pf isolation stuff
   std::vector<float> HMpfcIso1;
   std::vector<float> HMpfcIso2;
   std::vector<float> HMpfcIso3;
   std::vector<float> HMpfcIso4;
   std::vector<float> HMpfcIso5;

   std::vector<float> HMpfpIso1;
   std::vector<float> HMpfpIso2;
   std::vector<float> HMpfpIso3;
   std::vector<float> HMpfpIso4;
   std::vector<float> HMpfpIso5;

   std::vector<float> HMpfnIso1;
   std::vector<float> HMpfnIso2;
   std::vector<float> HMpfnIso3;
   std::vector<float> HMpfnIso4;
   std::vector<float> HMpfnIso5;

   // reco::GsfTrack elctron tracks
    int           ngsfEle_;
    std::vector<float> elegsfTrkPt_;            
    std::vector<float> elegsfTrkP_;            
    std::vector<float> elegsfTrkEta_;           
    std::vector<float> elegsfTrkPhi_;           
    std::vector<int>   elegsfTrkCharge_;        
    std::vector<float> elegsfTrkChi2_;          
    std::vector<float> elegsfTrkNdof_;          
    std::vector<float> elegsfTrkNormalizedChi2_;
    std::vector<int>   elegsfTrkValidHits_;   
    std::vector<int>   elegsfTrkMissHits_;       
    std::vector<int>   elegsfTrkLayers_;    
    std::vector<float> elegsfD0_;
    std::vector<float> elegsfDz_;              
    std::vector<float> elegsfD0Err_;            
    std::vector<float> elegsfDzErr_;       

   // reco::general track     
    Int_t         ngenTrk_;
    std::vector<float> gentrkPt_;            
    std::vector<float> gentrkP_;            
    std::vector<float> gentrkEta_;           
    std::vector<float> gentrkPhi_;     
    std::vector<int>   gentrkcharge_; 
    std::vector<float> gentrkvx_;            
    std::vector<float> gentrkvy_;           
    std::vector<float> gentrkvz_;     
    std::vector<float> gentrknormchi2_;     
    std::vector<float> gentrkchi2_;  
    std::vector<float> gentrkd0_;                         
    std::vector<float> gentrkdxy_;                      
    std::vector<float> gentrkdz_;  
    std::vector<float> gentrkdxyError_;  
    std::vector<float> gentrkdzError_;   
    std::vector<int>   gentrkValidHits_;           
    std::vector<int>   gentrkMissHits_;   
    std::vector<int>   gentrkPurity_;     
    
    //reco::hybrid supercluster
    Int_t          nsc_hybrid_;
    std::vector<float>  sc_hybrid_E_;
    std::vector<float>  sc_hybrid_Et_;
    std::vector<float>  sc_hybrid_Eta_;
    std::vector<float>  sc_hybrid_Phi_;
    std::vector<float>  sc_hybrid_x_;
    std::vector<float>  sc_hybrid_y_;
    std::vector<float>  sc_hybrid_z_;
    std::vector<float>  sc_hybrid_EtaWidth_;
    std::vector<float>  sc_hybrid_PhiWidth_;
    std::vector<float>  sc_hybrid_RawE_;
    std::vector<float>  sc_hybrid_RawEt_;
    
    //reco::mult55 supercluster
    Int_t          nsc_mult55_;
    std::vector<float>  sc_mult55_E_;
    std::vector<float>  sc_mult55_Et_;
    std::vector<float>  sc_mult55_Eta_;
    std::vector<float>  sc_mult55_Phi_;
    std::vector<float>  sc_mult55_x_;
    std::vector<float>  sc_mult55_y_;
    std::vector<float>  sc_mult55_z_;
    std::vector<float>  sc_mult55_EtaWidth_;
    std::vector<float>  sc_mult55_PhiWidth_;
    std::vector<float>  sc_mult55_RawE_;
    std::vector<float>  sc_mult55_RawEt_;
    
    
   // reco::calotower
   Int_t          nTower_;
   Int_t          nTower_barrel_;
   std::vector<float> CaloTower_hadE_;
   std::vector<float> CaloTower_emE_;
   std::vector<float> CaloTower_e_;
   std::vector<float> CaloTower_et_;
   std::vector<float> CaloTower_eta_;
   std::vector<float> CaloTower_phi_;

};

#endif
