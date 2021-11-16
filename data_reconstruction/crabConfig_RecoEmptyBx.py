from CRABClient.UserUtilities import config
config = config()

#config.section_('General')
config.General.requestName = 'EmptyBx_LbyLReco'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3_RAW2DIGI_L1Reco_RECO.py'
config.JobType.maxMemoryMB = 4000
config.JobType.allowUndistributedCMSSW = True


config.Data.inputDataset ='/HIEmptyBX/HIRun2018A-v1/RAW'
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt"
config.Data.splitting = 'Automatic'

config.Data.runRange = '326381-327564'

config.Data.outLFNDirBase = '/store/group/phys_heavyions/rchudasa/lbyl_2018/HIEmptyBX'
config.Data.allowNonValidInputDataset = True
config.Data.publication = True
config.Data.outputDatasetTag = 'EmptyBx_LbyLReco'
config.Site.storageSite = 'T2_CH_CERN'
