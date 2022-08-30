#!/bin/bash

#configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"
#configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholds.md"
configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholdsEta2p2.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
basePathOutput="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/analysis_ruchi/diphoton_data-MC_plots"
suffix="_30June22"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_full_lumi/merged/merged_ntuples_${1}.root"
  #inputPath=`sed "${1}q;d" /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePathOutput}/data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
  #inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  #inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_FSR_doubleEG2_full_lumi/merged/merged_ntuples_${1}.root"
  #inputPath="${basePath}/skimmed_ntuples/mc_qedMG5_FSR_doubleEG2_full_lumi/merged/merged_ntuples_${1}.root"
  inputPath="${basePath}/skimmed_ntuples/mc_qedMG5_2FSR_doubleEG2_full_lumi/merged/merged_ntuples_${1}.root"
  outputPath="${basePathOutput}/mc_qedMG5_2FSR${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 253
  #inputPath="${basePath}/mc_qed/ntuples_sl_full_lumi_v5/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi_v5/200929_094304/0000/mc_HiForestAOD_${1}.root"
  inputPath="${basePath}/skimmed_ntuples/mc_qed_sl_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePathOutput}/mc_qed_sl${suffix}"
elif [ $2 -eq 3 ]
then
  sampleName="LbL" # 3 files only
  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePathOutput}/mc_lbl_sc${suffix}"
elif [ $2 -eq 4 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePathOutput}/mc_cep_sc${suffix}"
elif [ $2 -eq 5 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-5_5p02TeV_SuperChic/mc_alps5GeV/211208_073352/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_5GeV${suffix}"
elif [ $2 -eq 6 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-6_5p02TeV_SuperChic/mc_alps6GeV/211208_081512/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_6GeV${suffix}"
elif [ $2 -eq 9 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-9_5p02TeV_SuperChic/mc_alps9GeV/211208_081631/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_9GeV${suffix}"
elif [ $2 -eq 11 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-11_5p02TeV_SuperChic/mc_alps11GeV/211208_081715/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_11GeV${suffix}"
elif [ $2 -eq 14 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-14_5p02TeV_SuperChic/mc_alps14GeV/211208_081746/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_14GeV${suffix}"
elif [ $2 -eq 16 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-16_5p02TeV_SuperChic/mc_alps16GeV/211208_081833/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_16GeV${suffix}"
elif [ $2 -eq 22 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-22_5p02TeV_SuperChic/mc_alps22GeV/211208_081937/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_22GeV${suffix}"
elif [ $2 -eq 30 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-30_5p02TeV_SuperChic/mc_alps30GeV/211208_082015/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_30GeV${suffix}"
elif [ $2 -eq 50 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-50_5p02TeV_SuperChic/mc_alps50GeV/211208_082053/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_50GeV${suffix}"
elif [ $2 -eq 90 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/mcForests/mc_alps/AxionLikeParticles_M-90_5p02TeV_SuperChic/mc_alps90GeV/211208_082354/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePathOutput}/mc_alps_90GeV${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/diphoton_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/selectDiphotonEvents $configPath $inputPath $output $sampleName
fi
