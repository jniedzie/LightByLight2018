#!/bin/bash

configPath=""
suffix=""

if [ $3 -eq 0 ]
then
# default
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_default.md"
elif [ $3 -eq 1 ]
then
# HF thresholds increased to 20 GeV
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_HF_20GeV.md"
  suffix="_HF_20GeV"
fi

# for the data:
inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

# data
if [ $2 -eq 0 ]
then
  sampleName="Data"
#  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  inputPath="${basePath}/skimmed_ntuples/data_loose_selections/ntuples_loose_selections_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_data${suffix}"
  
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC"
  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="CEP"
  inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_cep_sc${suffix}"
elif [ $2 -eq 3 ]
then
  sampleName="LbL"
  inputPath="${basePath}/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_lbl_sc${suffix}"
elif [ $2 -eq 4 ]
then
  sampleName="QED_SL"
#  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_qed_sl${suffix}"
fi

mkdir -p $outputPath

output="${outputPath}/basicPlots_${1}.root"

echo "Config: ${configPath}"
echo "Input: ${inputPath}"
echo "Output: ${output}"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/prepareBasicPlots $configPath $inputPath $output $sampleName
