#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

inputPathData=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`

inputPathLbL="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"

inputPathQED_SC="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"

inputPathQED_SL="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sl/reco_mc_qed_sl/reco_mc_qed_sl/190731_115947/0000/HiForestAOD_mc_${1}.root"

inputPathCEP="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"


outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/photonIDplots_new"

mkdir -p $outputPath

output="${outputPath}/photonID_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/preparePhotonIDplots $configPath $inputPathData $inputPathLbL $inputPathQED_SC $inputPathQED_SL $inputPathCEP $output
