#!/bin/bash

echo "Starting runEventList"

# ./runEventList.sh fileNumber sampleType configType

configPath=""
suffix=""
basepath=/afs/cern.ch/work/e/echapon/private/LightByLight_2018PbPb

# for the data:
inputPath=""
outputPath=""
sampleName=""

# basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
basePath="/eos/cms/store/group/phys_heavyions/echapon/LightByLight2018"

if [ $2 -eq 0 ]
then
  sampleName="Data" # last chunk number: 7440, merged into 80 files
    inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/merged_ntuples_${1}.root"
  
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 95, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
elif [ $2 -eq 2 ]
then
  sampleName="CEP" # last chunk numer: 410, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2/merged_ntuples.root"
elif [ $2 -eq 3 ]
then
  sampleName="LbL" # last chunk numer: 375, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2/merged_ntuples.root"
elif [ $2 -eq 4 ]
then
  sampleName="QED_SL"
fi


echo "Input: ${inputPath}"

echo $basepath/LightByLight2018/analysis/runEventList $inputPath 
$basepath/LightByLight2018/analysis/runEventList $inputPath
