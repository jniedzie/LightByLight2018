#!/bin/bash

# Set those variables:
exec_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/caloNoiseStudy/getCaloNoiseHistograms
input_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/caloNoiseStudy/input_filelist.txt
output_path=/eos/cms/store/cmst3/group/lightbylight/EmptyBx_HIForest/noiseStudyOutput/

#----------------------------------------------------------------------------
source /cvmfs/sft.cern.ch/lcg/releases/LCG_94/gcc/8.2.0/x86_64-slc6/setup.sh

echo "Job running"
echo "awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}"

infilename=`awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}`
echo "Input files: ${infilename}"
outfilename="noiseStudyOutput_${1}.root"

mkdir -p $output_path
cd $output_path
$exec_path /eos/cms/$infilename caloNoiseHists_${1}.root
