from CRABClient.UserUtilities import config
config = config()

#config.section_('General')
config.General.requestName = 'Reco_cep_SC_incoh'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3_RAW2DIGI_L1Reco_RECO.py'
config.JobType.maxMemoryMB = 4000
config.Data.inputDBS = 'phys03'
config.Data.inputDataset ='/gen_sim_cep_SC_incoh/rchudasa-DigiRaw_cep_SC_incoh-68827332deeb199e3021a78c21279fab/USER'

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
config.Data.outputDatasetTag = 'Reco_cep_SC_incoh'
config.Site.storageSite = 'T2_CH_CERN'
