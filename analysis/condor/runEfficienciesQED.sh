#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 5646 files
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/analysis/efficienciesQED/efficienciesQED_data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 96
#inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/efficienciesQED/efficienciesQED_mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 74
  inputPath="${basePath}/mc_qed/ntuples_sl/reco_mc_qed_sl/reco_mc_qed_sl/190731_115947/0000/HiForestAOD_mc_${1}.root"
  outputPath="${basePath}/analysis/efficienciesQED/efficienciesQED_mc_qed_sl${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/efficienciesQED_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/getEfficienciesQED $configPath $inputPath $output $sampleName
