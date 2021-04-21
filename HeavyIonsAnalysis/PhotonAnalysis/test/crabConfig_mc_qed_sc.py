from CRABClient.UserUtilities import config
config = config()

#config.section_('General')
config.General.requestName = 'ntuples_mc_qed_sc_full_lumi'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_MC_103X.py'
config.JobType.maxMemoryMB = 4000

config.Data.inputDataset ='/QEDGammaGamma_5p02TeV_SuperChic/HINPbPbAutumn18DR-NoPUlowPtPhotonReg_LbyL_103X_upgrade2018_realistic_HI_LowPtPhotonReg_v2-v4/AODSIM'
# config.Data.userInputFiles = open('input_mc_qed_sl.txt').readlines()

config.JobType.allowUndistributedCMSSW = True

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

#config.Data.outLFNDirBase = '/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sc'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/rchudasa/lbyl_2018/mc_qed'
config.Data.allowNonValidInputDataset = True
config.Data.publication = False
config.Data.outputDatasetTag = 'reco_mc_qed_sc_full_lumi'
config.Site.storageSite = 'T2_CH_CERN'
