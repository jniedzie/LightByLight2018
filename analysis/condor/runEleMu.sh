#!/bin/bash

userBasePath="/afs/cern.ch/user/p/pjana/private/CMSSW_10_3_5/src"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholds.md"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_HFVeto_withEleIsolatioNewThresholds.md"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_HFVeto_withEleIsolatioNewThresholdsEta2p2.md"
configPath="${userBasePath}/LightByLight2018/analysis/configs/applySelections.md"

inputPath=""
outputPath=""
sampleName=""

#inbasePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
basePath="/eos/user/p/pjana/Other/Data"

suffix="_EleMu_15thJune_noEG5_AT3"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/data${suffix}"

fi


mkdir -p $outputPath
output="${outputPath}/EleMu_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  ${userBasePath}/LightByLight2018/analysis/EleMu $configPath $inputPath $output $sampleName
fi
