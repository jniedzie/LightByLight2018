from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.section_('General')
config.General.requestName = 'ntuples_mc_lbl'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_MC_103X.py'
config.JobType.maxMemoryMB = 4000
config.Data.outputPrimaryDataset = 'reco_mc_lbl'
config.Data.userInputFiles = open('input_mc_lbl.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples'
config.Data.allowNonValidInputDataset = True
config.Data.publication = True
config.Data.outputDatasetTag = 'reco_mc_lbl'
config.Site.storageSite = 'T2_CH_CERN'
