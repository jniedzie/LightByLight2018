#!/bin/bash

# Set those variables:
config_path=/afs/cern.ch/work/r/rchudasa/private/ruchi_reco_2018/CMSSW_10_3_2/src/Configuration/Generator/python/digi_raw/step2_DIGI_L1_DIGI2RAW_HLT.py
input_path=/afs/cern.ch/work/r/rchudasa/private/ruchi_reco_2018/CMSSW_10_3_2/src/Configuration/Generator/python/digi_raw/input_filelist.txt
cmssw_path=/afs/cern.ch/work/r/rchudasa/private/ruchi_reco_2018/CMSSW_10_3_2
output_path=/eos/yourpath/
outfilename="flatpt_photon_digi_raw_${1}.root"

#----------------------------------------------------------------------------
export XRD_NETWORKSTACK=IPv4
export SCRAM_ARCH="slc6_amd64_gcc700"
CMSSWVER=CMSSW_10_3_2
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 project CMSSW ${CMSSWVER}`
cd ${CMSSWVER}/
rm -rf ./*
cp -r -d ${cmssw_path}/* ./
cd src
eval `scramv1 runtime -sh`
edmPluginRefresh -p ../lib/$SCRAM_ARCH


echo "Job running"
echo "awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}"

infilename=`awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}`
echo "Input files: ${infilename}"
echo "Executing command:cmsRun $config_path outputFile=$outfilename inputFiles=$infilename"
cmsRun $config_path outputFile=$outfilename inputFiles=$infilename
xrdcp -N -v $outfilename root://eoscms.cern.ch/$output_path
rm $outfilename
