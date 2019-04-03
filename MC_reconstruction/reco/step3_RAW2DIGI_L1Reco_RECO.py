# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --mc --eventcontent AODSIM --datatier AODSIM --conditions 103X_upgrade2018_realistic_HI_v9 --step RAW2DIGI,L1Reco,RECO --geometry DB:Extended --era Run2_2018_pp_on_AA --no_exec
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2018)
options = VarParsing.VarParsing('python')

options.inputFiles = 'file:../digi_raw/FlatGamma_pt_digi_raw.root'
options.outputFile = 'FlatGamma_pt_reco_g4simhits.root'
options.parseArguments()

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

'''
from RecoEcal.EgammaClusterProducers.particleFlowSuperClusterECAL_cfi import *
particleFlowSuperClusterECALBox.thresh_SCEt = cms.double(1.0)
particleFlowSuperClusterECALMustache.thresh_SCEt = cms.double(1.0)

from RecoEgamma.EgammaPhotonProducers.egammaForCoreTracking_cff import *
particleFlowSuperClusterECALForTrk.thresh_SCEt = cms.double(1.0)

from RecoEgamma.EgammaElectronProducers.ecalDrivenElectronSeedsParameters_cff import *
ecalDrivenElectronSeedsParameters.SCEtCut = cms.double(0.0)
ecalDrivenElectronSeedsParameters.LowPtThreshold = cms.double(1.0)

from RecoEgamma.EgammaPhotonProducers.conversionTrackCandidates_cfi import *
conversionTrackCandidates.bcEtCut = cms.double(1.0)
conversionTrackCandidates.bcECut  = cms.double(1.0)
conversionTrackCandidates.minSCEt = cms.double(1.0)


from RecoEgamma.EgammaPhotonProducers.allConversions_cfi import *
allConversions.minSCEt = cms.double(1.0)

from RecoEgamma.EgammaElectronProducers.gedGsfElectrons_cfi import *
gedGsfElectronsTmp.minSCEtBarrel  = cms.double(1.0)
gedGsfElectronsTmp.minSCEtEndcaps = cms.double(1.0)


from RecoEgamma.EgammaElectronProducers.gsfElectrons_cfi import *
ecalDrivenGsfElectrons.minSCEtBarrel  = cms.double(1.0)
ecalDrivenGsfElectrons.minSCEtEndcaps = cms.double(1.0)
gsfElectrons.minSCEtBarrel  = cms.double(1.0)
gsfElectrons.minSCEtEndcaps = cms.double(1.0)

from RecoEgamma.EgammaPhotonProducers.conversions_cfi import *
conversions.minSCEt = cms.double(1.0)

from RecoEgamma.EgammaPhotonProducers.gedPhotons_cfi import *
gedPhotons.minSCEtBarrel = cms.double(1.0)
gedPhotons.minSCEtEndcap = cms.double(1.0)

from RecoEgamma.EgammaPhotonProducers.photonCore_cfi import *
photonCore.minSCEt = cms.double(10.0)
islandPhotonCore.minSCEt = 8.0

from RecoEgamma.EgammaPhotonProducers.photons_cfi import *
photons.minSCEtBarrel = cms.double(1.0)
photons.minSCEtEndcap = cms.double(1.0)
islandPhotons.minSCEtBarrel = cms.double(1.0)
islandPhotons.minSCEtEndcap = cms.double(1.0)


from RecoParticleFlow.PFTracking.pfTrackElec_cfi import *
pfTrackElec.MinSCEnergy = cms.double(1.0) 


from RecoParticleFlow.PFTracking.particleFlowDisplacedVertex_cfi import *
particleFlowDisplacedVertex.vertexIdentifierParameters.pt_kink_min = cms.double(1.0)

from RecoParticleFlow.PFProducer.particleFlowEGamma_cfi import *
particleFlowEGamma.minPtForPostCleaning = cms.double(1.)

from RecoParticleFlow.PFProducer.particleFlow_cfi import *
particleFlowTmp.minPtForPostCleaning = cms.double(1.)
particleFlowTmp.photon_MinEt = cms.double(1.)
#particleFlowTmp.minHFCleaningPt = cms.double(5.) // not sure change or not


from RecoEgamma.EgammaIsolationAlgos.interestingEgammaIsoESDetIdModule_cff import *
interestingEgammaIsoESDetId.minSCEt=cms.double(1)
interestingEgammaIsoESDetId.minEleEt=cms.double(1)
interestingEgammaIsoESDetId.minPhoEt=cms.double(1)


from RecoEgamma.EgammaHFProducers.hfClusterShapes_cfi import *
hfEMClusters.minTowerEnergy=cms.double(1.0)
hfEMClusters.seedThresholdET=cms.double(1.0)
'''

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AODSIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(31457280),
    fileName = cms.untracked.string(options.outputFile),
    outputCommands = process.AODSIMEventContent.outputCommands
)
process.AODSIMoutput.outputCommands.extend(['keep *_towerMaker_*_*'])
process.AODSIMoutput.outputCommands.extend(['keep *_siPixelRecHits_*_*'])
process.AODSIMoutput.outputCommands.extend(['keep *_siPixelClusters_*_*'])
process.AODSIMoutput.outputCommands.extend(['keep *_g4SimHits_*_*'])

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_upgrade2018_realistic_HI_v11', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.AODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
