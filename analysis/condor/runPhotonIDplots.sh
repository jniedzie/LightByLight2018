#!/bin/bash

configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
#basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
suffix="_23April21"

if [ $2 -eq 0 ]
then
  sampleName="Data" # last chunk number: 7440, merged into 60 files
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
#  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_complete/merged/merged_ntuples_${1}.root"
  outputPath="${basePath}/analysis/photonIDplots/photonIDplots_data_new"
  
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 95, merged into 1 file
#  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/ntuples_loose_selections_${1}.root"
 inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/photonIDplots/photonIDplots_mc_qed_sc_new"
elif [ $2 -eq 2 ]
then
  sampleName="CEP" # last chunk numer: 410, merged into 1 file
#  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2/ntuples_loose_selections_${1}.root"
  inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  outputPath="${basePath}/analysis/photonIDplots/photonIDplots_mc_cep_sc_new"
elif [ $2 -eq 3 ]
then
  sampleName="LbL" # last chunk numer: 375, merged into 1 file
#  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2/ntuples_loose_selections_${1}.root"
  inputPath="${basePath}/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  outputPath="${basePath}/analysis/photonIDplots/photonIDplots_mc_lbl_sc_new"
elif [ $2 -eq 4 ] # last chunk numer: 96
then
  sampleName="QED_SL"
  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/photonIDplots/photonIDplots_mc_qed_sl_new"
fi


mkdir -p $outputPath
output="${outputPath}/photonID_plots_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/preparePhotonIDplots $configPath $sampleName $inputPath $output 
fi
