from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.section_('General')
config.General.requestName = 'gen_sim_qed_starlight_with_cuts'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '1ststep_GEN_SIM.py'
config.JobType.maxMemoryMB = 4000
config.Data.outputPrimaryDataset = 'gen_sim_qed_starlight_with_cuts'
config.Data.userInputFiles = open('input.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#NJOBS = 2000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS

#config.section_('Data')
config.Data.outLFNDirBase = '/store/group/phys_diffraction/lbyl_2018/mc_qed/gen_sim_qed_starlight_with_cuts'
config.Data.allowNonValidInputDataset = True
config.Data.publication = True
config.Data.outputDatasetTag = 'gen_sim_qed_superchic_with_cuts'
config.Site.storageSite = 'T2_CH_CERN'
