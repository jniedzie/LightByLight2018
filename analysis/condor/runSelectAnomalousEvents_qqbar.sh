#!/bin/bash

configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
#basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
suffix="_26April21"

if [ $2 -eq 0 ]
then
  sampleName="LbL" # 10400 files
  inputPath="${basePath}/mc_ccbar/ggCCbar_TuneCP5_5p02TeV_MG5_aMCatNLO_pythia8/reco_mc_ccbar/210424_130914/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_ccbar${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
  inputPath="${basePath}/mc_bbbar/ggBBbar_4f_TuneCP5_5p02TeV_MG5_aMCatNLO_pythia8/reco_mc_bbbar/210424_131218/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_bbbar${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/data_plots_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/selectAnomalousEvents $configPath $inputPath $output $sampleName
fi
