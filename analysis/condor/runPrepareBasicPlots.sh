#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

# for the data:
inputPath=""
outputPath=""

# data
if [ $2 -eq 0 ]
then
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/basicPlots_data_etaDepNEE"
else
 # MC
  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/basicPlots_mc_etaDepNEE"
fi

mkdir -p $outputPath

output="${outputPath}/basicPlots_${1}.root"

isMC=$2

echo "Config: ${configPath}"
echo "Input: ${inputPath}"
echo "Output: ${output}"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/prepareBasicPlots $configPath $inputPath $output $isMC
