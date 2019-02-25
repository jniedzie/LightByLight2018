#!/bin/bash
export XRD_NETWORKSTACK=IPv4

arg=${1}
curDir=/afs/cern.ch/work/r/rchudasa/private/CMSSW_10_3_2/src/mc_production/lbyl/digi-raw
config=step2_DIGI_L1_DIGI2RAW_HLT.py
inputdir=/store/group/phys_diffraction/lbyl_2018/mc_lbyl/gen_sim
infilename=LbyL_gensim
outputeosdir=/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbyl/digi_raw/
outfilename=LbyL_digiraw 

CMSSWVER=CMSSW_10_3_2
CMSSWDIR=/afs/cern.ch/work/r/rchudasa/private/CMSSW_10_3_2
CMSSWARCH=slc6_amd64_gcc700

##Create Work Area
export SCRAM_ARCH=${CMSSWARCH}
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 project CMSSW ${CMSSWVER}`
cd ${CMSSWVER}/
rm -rf ./*
cp -r -d ${CMSSWDIR}/* ./
cd src
eval `scramv1 runtime -sh`
edmPluginRefresh -p ../lib/$SCRAM_ARCH

## Run the job and copy to eos

cmsRun ${curDir}/${config} outputFile=${outfilename}_${arg}.root inputFiles=${inputdir}/${infilename}_${arg}.root
xrdcp -N -v ${outfilename}_${arg}.root root://eoscms.cern.ch/${outputeosdir}
