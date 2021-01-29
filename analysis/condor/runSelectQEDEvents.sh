#!/bin/bash

configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
suffix="_zdcCuts_recoIDTrigSF_20012021"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_full_lumi_complete/merged/merged_ntuples_${1}.root"
  #inputPath=`sed "${1}q;d" /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/analysis_ruchi/qed_data-MC_plots/data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
#inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  inputPath="${basePath}/mc_qed/ntuples_sc_full_lumi/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/200807_100412/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis_ruchi/qed_data-MC_plots/mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 253
  inputPath="${basePath}/mc_qed/ntuples_sl_full_lumi_v5/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi_v5/200929_094304/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis_ruchi/qed_data-MC_plots/mc_qed_sl${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/data-MC_plots_QED_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/selectQEDEvents $configPath $inputPath $output $sampleName
fi
