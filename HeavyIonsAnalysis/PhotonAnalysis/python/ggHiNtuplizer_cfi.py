import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.PhotonAnalysis.ElectronVID_cff import *

ggHiNtuplizer = cms.EDAnalyzer("ggHiNtuplizer",
    doGenParticles     = cms.bool(True),
    doSuperClusters    = cms.bool(True),
    doElectrons        = cms.bool(True),
    doPhotons          = cms.bool(True),
    doMuons            = cms.bool(True),
    runOnParticleGun   = cms.bool(False),
    useValMapIso       = cms.bool(False),
    #useValMapIso       = cms.bool(True),
    doElectronVID      = cms.bool(False),
    doEleERegression   = cms.bool(False),
    doEffectiveAreas   = cms.bool(True),
    doPhoERegression   = cms.bool(True),
    doRecHitsEB        = cms.bool(True),
    doRecHitsEE        = cms.bool(True),
    doGeneralTracks    = cms.bool(True),
    doPixelTracks    = cms.bool(False),
    doTrackerHits      = cms.bool(True),
    doCaloTower        = cms.bool(True),
    doCastorTower      = cms.bool(True),
    recHitsEB          = cms.InputTag("reducedEcalRecHitsEB"),
    recHitsEE          = cms.InputTag("reducedEcalRecHitsEE"),
    recHitsES          = cms.InputTag("reducedEcalRecHitsES"),
    #recHitsEB          = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEB"),
    #recHitsEE          = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEE"),
    pileupCollection   = cms.InputTag("addPileupInfo"),
    genParticleSrc     = cms.InputTag("genParticles"),
    superClustersEB    = cms.InputTag("particleFlowSuperClusterECAL:particleFlowSuperClusterECALBarrel"),
    superClustersEE    = cms.InputTag("particleFlowSuperClusterECAL:particleFlowSuperClusterECALEndcapWithPreshower"),
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
    removePhotonPfIsoFootprint = cms.bool(False),
    particleBasedIsolationPhoton = cms.InputTag("particleBasedIsolation", "gedPhotons"),
    generalTrk         = cms.InputTag("generalTracks"),
    pixelTrk         = cms.InputTag("hiConformalPixelTracks"),
    recoCaloTower      = cms.InputTag("towerMaker"),
    recoCastorTower    = cms.InputTag("CastorTowerReco"),

)
'''
ggHiNtuplizerGED = ggHiNtuplizer.clone(
    doElectrons              = True,
    doMuons                  = True,
    recoPhotonSrc            = 'gedPhotons',
    recoPhotonHiIsolationMap = 'photonIsolationHIProducerppGED',
    doPfIso                  = True,
    removePhotonPfIsoFootprint = True,
    particleBasedIsolationPhoton = cms.InputTag("particleBasedIsolation", "gedPhotons")
)
'''
