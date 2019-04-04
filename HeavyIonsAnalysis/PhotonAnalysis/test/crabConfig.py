from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.section_('General')
config.General.requestName = 'pbpb_Emptybx_2018'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_DATA_103X.py'
config.JobType.maxMemoryMB = 4000

#config.section_('Data')
config.Data.inputDataset ='/HIEmptyBX/HIRun2018A-27Feb2019-v1/AOD'  
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt"
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 3500 

config.Data.runRange = '326381-327564'
config.Data.outLFNDirBase = '/store/group/phys_diffraction/lbyl_2018/EmptyBx_HIForest'
config.Data.allowNonValidInputDataset = True

config.Data.outputDatasetTag = config.General.requestName
#config.Site.whitelist = ["T2_US_Vanderbilt"]
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
