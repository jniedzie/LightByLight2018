import FWCore.ParameterSet.Config as cms

interestingEgammaIsoESDetId = cms.EDProducer("EgammaIsoESDetIdCollectionProducer",
                                             eeClusToESMapLabel=cms.InputTag("particleFlowClusterECALRemade"),
                                             ecalPFClustersLabel=cms.InputTag("particleFlowClusterECALRemade"),
                                             elesLabel=cms.InputTag("gedGsfElectrons"),
                                             phosLabel=cms.InputTag("gedPhotons"),
                                             superClustersLabel=cms.InputTag("particleFlowEGamma"),
                                             minSCEt=cms.double(1),
                                             minEleEt=cms.double(1),
                                             minPhoEt=cms.double(1),
                                             maxDR=cms.double(0.4),
                                             interestingDetIdCollection=cms.string("")
                                             )
                                                
