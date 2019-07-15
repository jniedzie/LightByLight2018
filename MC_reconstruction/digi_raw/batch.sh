#!/bin/bash

# Set those variables:
config_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/MC_reconstruction/digi_raw/step2_DIGI_L1_DIGI2RAW_HLT.py
input_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/MC_reconstruction/digi_raw/input_filelist.txt
cmssw_path=/afs/cern.ch/work/j/jniedzie/private/CMSSW_10_3_2
output_path=/eos/cms/store/cmst3/group/lightbylight/mc_flat_pt_electron/digi_raw
outfilename="flatpt_photon_digi_raw_${1}.root"

#----------------------------------------------------------------------------
export XRD_NETWORKSTACK=IPv4
export CMSSWVER="CMSSW_10_3_2"
export SCRAM_ARCH="slc6_amd64_gcc700"

cd $cmssw_path
cmsenv
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

mkdir -p $output_path
cd $output_path

infilename=`awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}`
echo "Input files: ${infilename}"
echo "Executing command:cmsRun $config_path outputFile=$outfilename inputFiles=$infilename"
cmsRun $config_path outputFile=$outfilename inputFiles=$infilename
