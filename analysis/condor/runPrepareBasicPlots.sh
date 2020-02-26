#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

# for the data:
inputPath=""
outputPath=""
sampleName=""

# data
if [ $2 -eq 0 ]
then
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/basicPlots/basicPlots_data_new"
  sampleName="Data"
elif [ $2 -eq 1 ]
then
 # MC QED SC
  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/basicPlots/basicPlots_mc_qed_sc_new"
  sampleName="QED_SC"
elif [ $2 -eq 2 ]
then
  # MC QED SL
#  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/basicPlots/basicPlots_mc_qed_sl_new"
  sampleName="QED_SL"
elif [ $2 -eq 3 ]
then
   # MC CEP SC
  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/basicPlots/basicPlots_mc_cep_sc_new"
  sampleName="CEP"
elif [ $2 -eq 4 ]
then
    # MC LbL SC
  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/basicPlots/basicPlots_mc_lbl_sc_new"
  sampleName="LbL"
fi

mkdir -p $outputPath

output="${outputPath}/basicPlots_${1}.root"

echo "Config: ${configPath}"
echo "Input: ${inputPath}"
echo "Output: ${output}"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/prepareBasicPlots $configPath $inputPath $output $sampleName
