### HiForest Configuration
# Collisions: PbPb
# Type: Minimum Bias Monte Carlo
# Input: AOD

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')

###############################################################################
# HiForest labelling info
###############################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
version = ''
# version = subprocess.check_output(['git',
#     '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

###############################################################################
# Input source
###############################################################################

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/511FD6FA-CB30-8647-A75F-62843D0C2582.root"
        "/store/himc/HINPbPbAutumn18DR/LbyLSignal_5p02TeV_SuperChic/AODSIM/NoPUlowPtPhotonReg_LbyL_103X_upgrade2018_realistic_HI_LowPtPhotonReg_v2-v3/100000/9FEE123D-3E00-3C45-9F1F-1276180C6ABD.root"
        #"/store/group/phys_diffraction/lbyl_2018/mc_flat_pt_photon/reco_lbl_modifier/flatpt_photon/reco_flat_pt_photon/190715_163552/0000/step3_RAW2DIGI_L1Reco_RECO_999.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/wo_lbyl_reco/step3_RAW2DIGI_L1Reco_RECO_qed.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/step3_RAW2DIGI_L1Reco_RECO_qed.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/wo_lbyl_reco/step3_RAW2DIGI_L1Reco_RECO_lbyl.root","file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/wo_lbyl_reco/step3_RAW2DIGI_L1Reco_RECO_lbyl_v2.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/step3_RAW2DIGI_L1Reco_RECO_lbyl.root","file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/step3_RAW2DIGI_L1Reco_RECO_lbyl_v2.root"
        #"file:/afs/cern.ch/work/r/rchudasa/private/hiforest_1034/CMSSW_10_3_4/src/mc_reco/lbyl_sample/step3_RAW2DIGI_L1Reco_RECO_lbyl.root"
        # "/store/group/phys_diffraction/lbyl_2018/mc_lbl/reco_1034/reco_1034_lbyl/reco_1034_lbyl/191110_150040/0000/step3_RAW2DIGI_L1Reco_RECO_lbyl_90.root"
        #"/store/himc/HINPbPbAutumn18DR/QEDGammaGamma_5p02TeV_STARlight/AODSIM/NoPUlowPtPhotonReg_LbyL_103X_upgrade2018_realistic_HI_LowPtPhotonReg_v2-v5/270000/00F70C94-633E-EB45-807C-2FA338E5401F.root"
        #"/eos/cms/store/himc/HINPbPbAutumn18DR/QEDGammaGamma_5p02TeV_STARlight/AODSIM/NoPUlowPtPhotonReg_LbyL_103X_upgrade2018_realistic_HI_LowPtPhotonReg_v2-v2/230000/FF0F2669-7BED-F845-8508-FE6582191483.root"
        ),
    )

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    #input = cms.untracked.int32(1000)
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
#process.GlobalTag = GlobalTag(process.GlobalTag, '103X_upgrade2018_realistic_HI_v13', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_upgrade2018_realistic_HI_LowPtPhotonReg_v2', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

print('\n\033[31m~*~ USING CENTRALITY TABLE FOR Hydjet Drum5F ~*~\033[0m\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        # tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5Ev8_v1030pre5x02_mc"),
        tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5F_v1032x01_mc"),
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
    #fileName = cms.string("HiForestAOD_flat_electron_lbyl_reco.root"))
    #fileName = cms.string("HiForestAOD_flat_gamma_def_reco.root"))
    fileName = cms.string("mc_HiForestAOD.root"))

###############################################################################
# Additional Reconstruction and Analysis: Main Body
###############################################################################

#############################
# Jets
#############################
# jet reco sequence
# process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pponAA_MB_cff')

#process.load('HeavyIonsAnalysis.JetAnalysis.hiFJRhoAnalyzer_cff')
#process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
#process.pfcandAnalyzer.doTrackMatching  = cms.bool(True)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_MC_PbPb5020_2018
#process = overrideJEC_MC_PbPb5020_2018(process)
###############################################################################

#############################
# Gen Analyzer
#############################
process.load('HeavyIonsAnalysis.EventAnalysis.runanalyzer_cfi')
process.load('HeavyIonsAnalysis.TrackAnalysis.HiGenAnalyzer_cfi')
# making cuts looser so that we can actually check dNdEta
process.HiGenParticleAna.ptMin = cms.untracked.double(0.4) # default is 5
process.HiGenParticleAna.etaMax = cms.untracked.double(5.) # default is 2

###############################################################################

############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_mc_cfi')
process.hiEvtAnalyzer.doMC = cms.bool(True) # general MC info
process.hiEvtAnalyzer.doHiMC = cms.bool(True) # HI specific MC info
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_mc
process.hltobject.triggerNames = trigger_list_mc

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
#SS2018PbPbMC = "HeavyIonsAnalysis/PhotonAnalysis/data/SS2018PbPbMC.dat"
#process.load('HeavyIonsAnalysis.PhotonAnalysis.correctedElectronProducer_cfi')
#process.correctedElectrons.correctionFile = SS2018PbPbMC

process.load('HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi')
#process.ggHiNtuplizerGED.gsfElectronLabel = "correctedElectrons"

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
process.load('RecoHI.ZDCRecHit.QWZDC2018Producer_cfi')
process.load('RecoHI.ZDCRecHit.QWZDC2018RecHit_cfi')

process.load('HeavyIonsAnalysis.JetAnalysis.rechitanalyzer_cfi')
process.rechitanalyzerpp.doZDCRecHit = False 
process.rechitanalyzerpp.zdcRecHitSrc = cms.InputTag("QWzdcreco")

###############################################################################
#Recover peripheral primary vertices
#https://twiki.cern.ch/twiki/bin/view/CMS/HITracking2018PbPb#Peripheral%20Vertex%20Recovery
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

#########################
# Main analysis list
#########################

process.ana_step = cms.Path(
    process.offlinePrimaryVerticesRecovery +
    #process.HiForest +
    #process.runAnalyzer +
    process.hltanalysis +
    #process.hltobject +
    process.l1object +
    #process.centralityBin +
    #process.hiEvtAnalyzer +
    #process.genCleanedSequence +
    #process.jetSequence +
    #process.hiPuRhoR3Analyzer + 
    #process.HiGenParticleAna +
    #process.correctedElectrons +
    process.ggHiNtuplizer +
    #process.ggHiNtuplizerGED +
    #process.hiFJRhoAnalyzer +
    #process.hiFJRhoAnalyzerFinerBins +
    #process.pfcandAnalyzer +
    #process.pfcandAnalyzerCS +
    #process.trackSequencesPP #+
    #process.zdcdigi +
    #process.QWzdcreco +
    process.rechitanalyzerpp
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

# Customization
###############################################################################
