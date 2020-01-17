#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

ls /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt

inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
echo "Input path: ${inputPath}"

outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/data_forTriggerEff"
mkdir -p $outputPath

output="${outputPath}/data_HiForestAOD_forTriggerEff_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $output
