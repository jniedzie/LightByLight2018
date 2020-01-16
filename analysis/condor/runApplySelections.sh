#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/data_all_withSingleEG3/ntuples/data_HiForestAOD_withSingleEG3_${1}.root"

output="/eos/cms/store/group/phys_diffraction/lbyl_2018/data_forRecoEff/data_HiForestAOD_forRecoEff_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $output
