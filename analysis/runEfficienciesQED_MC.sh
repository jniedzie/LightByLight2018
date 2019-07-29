#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sc/reco_mc_qed_sc/reco_mc_qed_sc/190723_061308/0000/HiForestAOD_mc_${1}.root"

output="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/efficiency_sc/efficienciesQED_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/getEfficienciesQED $configPath $inputPath $output
