### HiForest Configuration
# Collisions: PbPb
# Type: Data
# Input: AOD

# keep disabled by default until fully commissioned
cleanJets = False

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')

###############################################################################
# HiForest labelling info
###############################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
version = subprocess.check_output(['git',
    '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

###############################################################################
# Input source
###############################################################################

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
        #"file:/afs/cern.ch/work/r/rbi/public/forest/HIHardProbes_HIRun2018A-PromptReco-v2_AOD.root"
        # 'file:B3B60266-96AA-A146-8658-4FE0F40F9D00.root'
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/82A92481-E129-6947-AE71-F7ED22FF47A6.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/82AF9679-492D-DE4B-8D56-0C69ED53DF0F.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/815D19EE-371A-074D-8146-2E9E6ACE7AA8.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/811FB2E8-4159-F244-B079-3F5AE4EB0C9E.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/80804F44-7F54-1A48-B3B7-9FFB80AC0ACC.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/806F77DE-A9C3-7D46-9F54-FFAB50CC9BF4.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/80316E5C-2AF8-2740-8A49-5EA8285C2DEB.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/802A2D93-8662-6A41-A648-8D7165213CEC.root',
        '/store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/280000/7F7D595B-1868-C14B-AE04-DC845AF0B721.root'
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/from_old_1034_repo/step3_RAW2DIGI_L1Reco_RECO.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/from_old_1034_repo/wo_lbyl_mod/step3_RAW2DIGI_L1Reco_RECO.root"
),
    )

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500000)
    )

###############################################################################
# Load Global Tag, Geometry, etc.
###############################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_fixEcalADCToGeV_v1', '')
# process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_LowPtPhotonReg_v1', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

print('\n\033[31m~*~ USING CENTRALITY TABLE FOR PbPb 2018 DATA ~*~\033[0m\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")

###############################################################################
# Define tree output
###############################################################################

process.TFileService = cms.Service("TFileService",
    #fileName = cms.string("data_HiForestAOD_wohlt_eta2p3_norechit.root"))
    fileName = cms.string("data_HiForestAOD_swiss_cross.root"))

###############################################################################
# Additional Reconstruction and Analysis: Main Body
###############################################################################

#############################
# Jets
#############################
# jet reco sequence
process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pponAA_data_cff')

process.load('HeavyIonsAnalysis.JetAnalysis.hiFJRhoAnalyzer_cff')
process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
process.pfcandAnalyzer.doTrackMatching  = cms.bool(True)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_DATA_PbPb5020_2018
process = overrideJEC_DATA_PbPb5020_2018(process)

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

#######################
# B-tagging
######################
# replace pp CSVv2 with PbPb CSVv2 (positive and negative taggers unchanged!)
process.load('RecoBTag.CSVscikit.csvscikitTagJetTags_cfi')
process.load('RecoBTag.CSVscikit.csvscikitTaggerProducer_cfi')
process.akPu4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4PFImpactParameterTagInfos"),
    cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
process.akCs4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akCs4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akCs4PFImpactParameterTagInfos"),
    cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
process.akPu4CaloCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4CaloCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4CaloImpactParameterTagInfos"),
    cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))

# trained on CS jets
process.CSVscikitTags.weightFile = cms.FileInPath(
    'HeavyIonsAnalysis/JetAnalysis/data/TMVA_Btag_CsJets_PbPb2018_BDTG.weights.xml')

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

# clean bad PF candidates
if cleanJets:
    process.load("RecoHI.HiJetAlgos.HiBadParticleFilter_cfi")
    process.pfBadCandAnalyzer = process.pfcandAnalyzer.clone(pfCandidateLabel = cms.InputTag("filteredParticleFlow","cleaned"))
    process.pfFilter = cms.Path(process.filteredParticleFlow + process.pfBadCandAnalyzer)

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
    process.triggerSelection + 
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

if cleanJets == True:
    from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
    process = MassReplaceInputTag(process,"particleFlow","filteredParticleFlow")                                                                                                               
    process.filteredParticleFlow.PFCandidates  = "particleFlow"

###############################################################################

# Customization
