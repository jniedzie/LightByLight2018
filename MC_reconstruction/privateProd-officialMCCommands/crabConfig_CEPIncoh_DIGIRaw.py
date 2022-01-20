from CRABClient.UserUtilities import config
config = config()

#config.section_('General')
config.General.requestName = 'DigiRaw_cep_SC_incoh'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_DIGI_L1_DIGI2RAW_HLT.py'
config.JobType.maxMemoryMB = 4000
config.Data.inputDBS = 'phys03'
config.Data.inputDataset ='/gen_sim_cep_SC_incoh/rchudasa-gen_sim_cep_SC_incoh-3c7cab1e0f7d901400af378f9c9dad6b/USER'

#config.Data.outputPrimaryDataset = 'DigiRaw_cep_SC_incoh'
#config.Data.userInputFiles = open('input.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#NJOBS = 2000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS

#config.section_('Data')
config.Data.outLFNDirBase = '/store/group/phys_heavyions/rchudasa/lbyl_2018/mc_cep'
config.Data.allowNonValidInputDataset = True
config.Data.publication = True
config.Data.outputDatasetTag = 'DigiRaw_cep_SC_incoh'
config.Site.storageSite = 'T2_CH_CERN'
