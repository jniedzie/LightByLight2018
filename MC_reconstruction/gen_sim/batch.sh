#!/bin/bash
export XRD_NETWORKSTACK=IPv4

arg=${1}
i=${arg}+1
curDir=/afs/cern.ch/work/r/rchudasa/private/CMSSW_10_3_2/src/mc_production/qed/gen-sim
config=1ststep_GEN_SIM.py
outputeosdir=/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/gen_sim/superchic_gensim/
outfilename=QED_gensim 

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
infilename=`awk -v awklinefrom="$i" -v awklineto="$i" 'NR==awklinefrom,NR==awklineto' input_filelist.txt`
echo $infilename
cmsRun ${curDir}/${config} outputFile=${outfilename}_${arg}.root inputFiles=${infilename}
xrdcp -N -v ${outfilename}_${arg}.root root://eoscms.cern.ch/${outputeosdir}
