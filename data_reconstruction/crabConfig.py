from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.section_('General')
config.General.requestName = 'pbpb_forward_2018'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3_RAW2DIGI_L1Reco_RECO.py'
config.JobType.maxMemoryMB = 4000

#config.section_('Data')
config.Data.inputDataset ='/HIForward/HIRun2018A-v1/RAW'  
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt"
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1 

config.Data.runRange = '326381-327564'
config.Data.outLFNDirBase = '/store/group/phys_diffraction/lbyl_2018/HIForward_Reco'
config.Data.allowNonValidInputDataset = True

config.Data.outputDatasetTag = config.General.requestName
#config.Site.whitelist = ["T2_US_Vanderbilt"]
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
