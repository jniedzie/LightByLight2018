#!/bin/bash

process=$1

inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_lbl/ntuples_data_lbl/190723_062214/0000/HiForestAOD_AOD_${1}.root"

output="/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/efficiency/efficienciesData_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/getEfficienciesData $inputPath $output
