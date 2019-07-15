source /cvmfs/cms.cern.ch/crab3/crab.sh
#source /afs/cern.ch/cms/ccs/wm/scripts/Crab/CRAB3/crab.sh
cd $CMSSW_BASE
cmsenv
cd -
voms-proxy-init --voms cms --valid 168:00
voms-proxy-info --all
