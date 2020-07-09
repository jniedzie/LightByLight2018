#!/bin/bash

jobdir=$PWD

# Need a CMSSW_10_3_5 release including pixel ttack ntuple code
reldir=/path/to/release

cd $reldir
eval `scramv1 runtime -sh`

cd $jobdir

echo "CONFIG CHECK"
uname -a
echo $CMSSW_RELEASE_BASE
date
pwd

echo ""

configName=$1
inputFiles=$2
maxEvents=$3
skipEvents=$4
eventsToProcess_load=$5
outputFile=/path/to/output/MC_HiForestAOD_pixelOnly_nEvt${maxEvents}_skip${skipEvents}.root

skipEvents=$(( maxEvents * skipEvents ))

echo "cmsRun $configName inputFiles=$inputFiles maxEvents=$maxEvents skipEvents=$skipEvents eventsToProcess_load=$eventsToProcess_load outputFile=$outputFile"
cmsRun $configName inputFiles=$inputFiles maxEvents=$maxEvents skipEvents=$skipEvents eventsToProcess_load=$eventsToProcess_load outputFile=$outputFile
