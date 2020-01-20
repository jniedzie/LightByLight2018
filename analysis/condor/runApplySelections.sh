#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

#inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"

echo "Input path: ${inputPath}"

#outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/data_forTriggerEff"
outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed_sc_forTriggerEff"
mkdir -p $outputPath
#output="${outputPath}/data_HiForestAOD_forTriggerEff_${1}.root"
output="${outputPath}/mc_qed_sc_forTriggerEff_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $output
