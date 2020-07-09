# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/HIN-HINPbPbAutumn18GS-00065-fragment.py --filein /store/himc/HINPbPbAutumn18pLHE/QEDGammaGamma_5p02TeV_STARlight/LHE/LbyL_103X_upgrade2018_realistic_HI_v11-v3/260000/C5F65C6F-D1B6-164B-86B6-EC184E639950.root --fileout file:HIN-HINPbPbAutumn18GS-00065.root --mc --eventcontent RAWSIM --no_exec --datatier GEN-SIM --conditions 103X_upgrade2018_realistic_HI_v11 --beamspot RealisticPbPbCollision2018 --step GEN,SIM --scenario HeavyIons --geometry DB:Extended --era Run2_2018_pp_on_AA --python_filename HIN-HINPbPbAutumn18GS-00065_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring
# combining with DIGI, RECO, ntuplizer
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2018_pp_on_AA)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealisticPbPbCollision2018_cfi')
process.load('Configuration.StandardSequences.GeneratorHI_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register ('skipEvents',
      0,
      VarParsing.multiplicity.singleton,
      VarParsing.varType.int,
      "number of events to skip")
options.register ('eventsToProcess',
      '',
      VarParsing.multiplicity.list,
      VarParsing.varType.string,
      "Events to process")
options.parseArguments()

###############################################################################
# HiForest labelling info
###############################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
# version = subprocess.check_output(['git',
#     '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
# if version == '':
version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    # fileNames = cms.untracked.vstring('/store/himc/HINPbPbAutumn18pLHE/QEDGammaGamma_5p02TeV_STARlight/LHE/LbyL_103X_upgrade2018_realistic_HI_v11-v3/260000/C5F65C6F-D1B6-164B-86B6-EC184E639950.root'),
    fileNames = cms.untracked.vstring(options.inputFiles),
    skipEvents = cms.untracked.uint32(options.skipEvents),
    inputCommands = cms.untracked.vstring(
        'keep *', 
        'drop LHEXMLStringProduct_*_*_*'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

if options.eventsToProcess:
   process.source.eventsToProcess = cms.untracked.VEventRange (options.eventsToProcess)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Configuration/GenProduction/python/HIN-HINPbPbAutumn18GS-00065-fragment.py nevts:1'),
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
    fileName = cms.untracked.string('file:HIN-HINPbPbAutumn18DR-00187.root'),
    outputCommands = process.AODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
process.XMLFromDBSource.label = cms.string("Extended")
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_upgrade2018_realistic_HI_v13', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")

process.generator = cms.EDFilter("Pythia8HadronizerFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('skip_hadronization'),
        skip_hadronization = cms.vstring(
            'ProcessLevel:all = off', 
            'Check:event = off'
        )
    ),
    comEnergy = cms.double(5020.0),
    filterEfficiency = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(1)
)

###############################################################################
# Define tree output
###############################################################################

process.TFileService = cms.Service("TFileService",
    #fileName = cms.string("data_HiForestAOD_wohlt_eta2p3_norechit.root"))
    fileName = cms.string(options.outputFile))

###############################################################################
# Additional Reconstruction and Analysis: Main Body
###############################################################################

#############################
# Jets
#############################
# jet reco sequence
# process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pponAA_data_cff')

# process.load('HeavyIonsAnalysis.JetAnalysis.hiFJRhoAnalyzer_cff')
# process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
# process.pfcandAnalyzer.doTrackMatching  = cms.bool(True)

# from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_DATA_PbPb5020_2018
# process = overrideJEC_DATA_PbPb5020_2018(process)

###############################################################################

############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_data
process.hltobject.triggerNames = trigger_list_data

###############################################################################

#########################
# Track Analyzer
#########################
process.load('HeavyIonsAnalysis.TrackAnalysis.ExtraTrackReco_cff')
process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_cff')

# Use this instead for track corrections
# process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_Corr_cff')

###############################################################################

#####################
# Photons
#####################
SSHIRun2018A = "HeavyIonsAnalysis/PhotonAnalysis/data/SSHIRun2018A.dat"
process.load('HeavyIonsAnalysis.PhotonAnalysis.correctedElectronProducer_cfi')
process.correctedElectrons.correctionFile = SSHIRun2018A

process.load('HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi')
process.ggHiNtuplizer_pixelOnly = process.ggHiNtuplizer.clone()
process.ggHiNtuplizer_pixelOnly.doGenParticles = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doPixelTracks = cms.bool(True)
process.ggHiNtuplizer_pixelOnly.doSuperClusters = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doElectrons        = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doPhotons          = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doMuons            = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.runOnParticleGun   = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.useValMapIso       = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doElectronVID      = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doEleERegression   = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doEffectiveAreas   = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doPhoERegression   = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doRecHitsEB        = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doRecHitsEE        = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doGeneralTracks    = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doTrackerHits      = cms.bool(False)
process.ggHiNtuplizer_pixelOnly.doCaloTower        = cms.bool(False)
#process.ggHiNtuplizer_pixelOnlyGED.doGenParticles = False
#process.ggHiNtuplizer_pixelOnlyGED.gsfElectronLabel = "correctedElectrons"

###############################################################################

# #######################
# # B-tagging
# ######################
# # replace pp CSVv2 with PbPb CSVv2 (positive and negative taggers unchanged!)
# process.load('RecoBTag.CSVscikit.csvscikitTagJetTags_cfi')
# process.load('RecoBTag.CSVscikit.csvscikitTaggerProducer_cfi')
# process.akPu4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
# process.akPu4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
#     cms.InputTag("akPu4PFImpactParameterTagInfos"),
#     cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
# process.akCs4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
# process.akCs4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
#     cms.InputTag("akCs4PFImpactParameterTagInfos"),
#     cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
# process.akPu4CaloCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
# process.akPu4CaloCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
#     cms.InputTag("akPu4CaloImpactParameterTagInfos"),
#     cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))

# # trained on CS jets
# process.CSVscikitTags.weightFile = cms.FileInPath(
#     'HeavyIonsAnalysis/JetAnalysis/data/TMVA_Btag_CsJets_PbPb2018_BDTG.weights.xml')

###############################################################################

#########################
# RecHits & pfTowers (HF, Castor & ZDC)
#########################
# ZDC RecHit Producer
process.load('RecoHI.ZDCRecHit.QWZDC2018Producer_cfi')
process.load('RecoHI.ZDCRecHit.QWZDC2018RecHit_cfi')

process.load('HeavyIonsAnalysis.JetAnalysis.rechitanalyzer_cfi')
process.rechitanalyzerpp.doZDCRecHit = True
process.rechitanalyzerpp.zdcRecHitSrc = cms.InputTag("QWzdcreco")
#process.pfTowerspp.doHF = False

###############################################################################
#Recover peripheral primary vertices
#https://twiki.cern.ch/twiki/bin/view/CMS/HITracking2018PbPb#Peripheral%20Vertex%20Recovery
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")

# # clean bad PF candidates
# if cleanJets:
#     process.load("RecoHI.HiJetAlgos.HiBadParticleFilter_cfi")
#     process.pfBadCandAnalyzer = process.pfcandAnalyzer.clone(pfCandidateLabel = cms.InputTag("filteredParticleFlow","cleaned"))
#     process.pfFilter = cms.Path(process.filteredParticleFlow + process.pfBadCandAnalyzer)

### FILTERS ###
# Trigger Filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
process.hltFilter = hltHighLevel.clone(
      HLTPaths =  [
         'HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1',
         'HLT_HIUPC_DoubleEG2_NotMBHF2AND_SinglePixelTrack_v1',
         'HLT_HIUPC_DoubleEG2_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1',
         'HLT_HIUPC_DoubleEG5_NotMBHF2AND_v1',
         'HLT_HIUPC_DoubleEG5_NotMBHF2AND_SinglePixelTrack_v1',
         'HLT_HIUPC_DoubleEG5_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1'
         ] , 
      TriggerResultsTag = cms.InputTag("TriggerResults","","HLT") , 
      throw = False , andOr = True , eventSetupPathsKey = cms.string( '' ) 
      )
process.triggerSelection = cms.Sequence( process.hltFilter )

#########################
# Main analysis list
#########################

#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltfilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltfilter.HLTPaths = ["HLT_HIUPCL1DoubleEG*","HLT_HIUPCL1SingleEG*"]
#process.hltfilter.throw = False
#process.hltfilter.andOr = True
#process.hltfilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")

process.ana_step = cms.Path(
    # process.triggerSelection + 
    process.offlinePrimaryVerticesRecovery +
    #process.HiForest +
    # process.hltanalysis +
    ##process.hltobject +
    # process.l1object +
    #process.centralityBin +
    #process.hiEvtAnalyzer +
    #process.jetSequence +
    #process.hiPuRhoR3Analyzer + 
    #process.correctedElectrons +
    process.ggHiNtuplizer_pixelOnly
    #process.ggHiNtuplizerGED +
    #process.hiFJRhoAnalyzer +
    #process.hiFJRhoAnalyzerFinerBins +
    #process.pfcandAnalyzer +
    #process.pfcandAnalyzerCS +
    #process.trackSequencesPP +
    # process.zdcdigi +
    # process.QWzdcreco +
    # process.rechitanalyzerpp
    )

# # edm output for debugging purposes
# process.output = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('HiForestEDM.root'),
#     outputCommands = cms.untracked.vstring(
#         'keep *',
#         # drop aliased products
#         'drop *_akULPu3PFJets_*_*',
#         'drop *_akULPu4PFJets_*_*',
#         )
#     )

# process.output_path = cms.EndPath(process.output)

###############################################################################

#########################
# Event Selection
#########################
'''
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.pBeamScrapingFilter = cms.Path(process.beamScrapingFilter)
process.collisionEventSelectionAOD = cms.Path(process.collisionEventSelectionAOD)
process.collisionEventSelectionAODv2 = cms.Path(process.collisionEventSelectionAODv2)

process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
process.phfCoincFilter1Th3 = cms.Path(process.hfCoincFilterTh3)
process.phfCoincFilter2Th3 = cms.Path(process.hfCoincFilter2Th3)
process.phfCoincFilter3Th3 = cms.Path(process.hfCoincFilter3Th3)
process.phfCoincFilter4Th3 = cms.Path(process.hfCoincFilter4Th3)
process.phfCoincFilter5Th3 = cms.Path(process.hfCoincFilter5Th3)
process.phfCoincFilter1Th4 = cms.Path(process.hfCoincFilterTh4)
process.phfCoincFilter2Th4 = cms.Path(process.hfCoincFilter2Th4)
process.phfCoincFilter3Th4 = cms.Path(process.hfCoincFilter3Th4)
process.phfCoincFilter4Th4 = cms.Path(process.hfCoincFilter4Th4)
process.phfCoincFilter5Th4 = cms.Path(process.hfCoincFilter5Th4)
process.phfCoincFilter1Th5 = cms.Path(process.hfCoincFilterTh5)
process.phfCoincFilter4Th2 = cms.Path(process.hfCoincFilter4Th2)

process.load("HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff")
process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)
process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)
process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)
process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)
process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)
process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)

process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
process.pHBHENoiseFilterResultProducer = cms.Path(process.HBHENoiseFilterResultProducer)
process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)
process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)
process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)
process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)
process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)

process.pAna = cms.EndPath(process.skimanalysis)
'''
from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"

# if cleanJets == True:
#     from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#     process = MassReplaceInputTag(process,"particleFlow","filteredParticleFlow")                                                                                                               
#     process.filteredParticleFlow.PFCandidates  = "particleFlow"


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.digitisation_step = cms.Path(process.pdigi_hi_nogen)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step])
# process.schedule.extend([process.endjob_step,process.AODSIMoutput_step])
process.schedule.extend([process.endjob_step,process.ana_step])
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
