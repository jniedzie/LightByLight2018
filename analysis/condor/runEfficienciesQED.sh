#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

#inputPathData="/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_lbl/ntuples_data_lbl/190723_062214/0000/HiForestAOD_AOD_${1}.root"
inputPathData="/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_l1_branches/ntuples_data_l1_branches/191008_125700/0000/HiForestAOD_${1}.root"

#inputPathQED_SC="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sc/reco_mc_qed_sc/reco_mc_qed_sc/190723_061308/0000/HiForestAOD_mc_${1}.root"
inputPathQED_SC="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"

inputPathQED_SL="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sl/reco_mc_qed_sl/reco_mc_qed_sl/190731_115947/0000/HiForestAOD_mc_${1}.root"

output="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/efficienciesQED/efficienciesQED_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/getEfficienciesQED $configPath $inputPathData $inputPathQED_SC $inputPathQED_SL $output
