#!/bin/bash

# Set those variables:
config_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/MC_reconstruction/gen_sim/1ststep_GEN_SIM.py
input_path=/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/MC_reconstruction/gen_sim/input_filelist.txt
cmssw_path=/afs/cern.ch/work/j/jniedzie/private/CMSSW_10_3_2/src
output_path=/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/gen_sim/superchic_gensim/


#----------------------------------------------------------------------------
export XRD_NETWORKSTACK=IPv4
export CMSSWVER="CMSSW_10_3_2"
export SCRAM_ARCH="slc6_amd64_gcc700"

cd $cmssw_path
cmsenv

source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`
edmPluginRefresh -p ../lib/$SCRAM_ARCH

echo "Job running"
echo "awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}"

infilename=`awk -v awklinefrom=$((${1}+1)) -v awklineto=$((${1}+1)) 'NR==awklinefrom,NR==awklineto' ${input_path}`
echo "Input files: ${infilename}"
outfilename="QED_gensim_${1}.root"
echo "Executing command:cmsRun $config_path outputFile=$outfilename inputFiles=$infilename"

cmsRun $config_path outputFile=$outfilename inputFiles=$infilename
xrdcp -N -v $outfilename root://eoscms.cern.ch/$output_path
rm $outfilename
