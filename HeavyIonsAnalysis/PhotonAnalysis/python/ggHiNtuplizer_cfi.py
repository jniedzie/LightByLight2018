import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.PhotonAnalysis.ElectronVID_cff import *

ggHiNtuplizer = cms.EDAnalyzer("ggHiNtuplizer",
    doGenParticles     = cms.bool(True),
    doElectrons        = cms.bool(True),
    doPhotons          = cms.bool(True),
    doMuons            = cms.bool(False),
    runOnParticleGun   = cms.bool(False),
    useValMapIso       = cms.bool(False),
    doElectronVID      = cms.bool(False),
    doRecHitsEB        = cms.bool(False),
    doRecHitsEE        = cms.bool(False),
    recHitsEB          = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEB"),
    recHitsEE          = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEE"),
    pileupCollection   = cms.InputTag("addPileupInfo"),
    genParticleSrc     = cms.InputTag("genParticles"),
    gsfElectronLabel   = cms.InputTag("gedGsfElectrons"),
    recoPhotonSrc      = cms.InputTag("gedPhotons"),
    electronVetoID     = electronVetoID25nsV1,
    electronLooseID    = electronLooseID25nsV1,
    electronMediumID   = electronMediumID25nsV1,
    electronTightID    = electronTightID25nsV1,
    recoPhotonHiIsolationMap = cms.InputTag("photonIsolationHIProducerppGED"),
    recoMuonSrc        = cms.InputTag("muons"),
    VtxLabel           = cms.InputTag("offlinePrimaryVertices"),
    rho                = cms.InputTag("fixedGridRhoFastjetAll"),
    beamSpot           = cms.InputTag('offlineBeamSpot'),
    conversions        = cms.InputTag('allConversions'),
    effAreasConfigFile = cms.FileInPath('HeavyIonsAnalysis/PhotonAnalysis/data/EffectiveAreas_94X_v0'),
    doPfIso            = cms.bool(True),
    particleFlowCollection = cms.InputTag("particleFlow"),


    doHMPhotons        = cms.bool(True),
    doGSFElectrons     = cms.bool(True),
    doGeneralTracks    = cms.bool(True),
    doHMSuperCluster   = cms.bool(True),
    doCaloTower        = cms.bool(True),
    recoHMPhotonSrc    = cms.InputTag("photons"),
    eletrk             = cms.InputTag("electronGsfTracks"),
    gentrk             = cms.InputTag("generalTracks"),
    hybridsc           = cms.InputTag("correctedHybridSuperClusters"),
    mult55sc           = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
    recoCaloTower      = cms.InputTag("towerMaker"),
    recoHMPhotonHiIsolationMap = cms.InputTag("photonIsolationHIProducerpp"),
)

#ggHiNtuplizerGED = ggHiNtuplizer.clone(
#    doElectrons              = True,
#    doMuons                  = True,
#    recoPhotonSrc            = 'gedPhotons',
#    recoPhotonHiIsolationMap = 'photonIsolationHIProducerppGED'
#)
