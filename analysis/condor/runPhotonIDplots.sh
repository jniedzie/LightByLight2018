#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md"

inputPathData="/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_lbl/ntuples_data_lbl/190723_062214/0000/HiForestAOD_AOD_${1}.root"

inputPathLbL="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples/reco_mc_lbl/reco_mc_lbl/190719_065330/0000/HiForestAOD_mc_${1}.root"

inputPathQED_SC="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sc/reco_mc_qed_sc/reco_mc_qed_sc/190723_061308/0000/HiForestAOD_mc_${1}.root"

inputPathQED_SL="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sl/reco_mc_qed_sl/reco_mc_qed_sl/190731_115947/0000/HiForestAOD_mc_${1}.root"

inputPathCEP="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/ntuples/reco_mc_cep/reco_mc_cep/190731_074016/0000/HiForestAOD_mc_${1}.root"

output="/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis/photonIDplots/photonID_${1}.root"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/preparePhotonIDplots $configPath $inputPathData $inputPathLbL $inputPathQED_SC $inputPathQED_SL $inputPathCEP $output
