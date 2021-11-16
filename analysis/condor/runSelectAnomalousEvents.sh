#!/bin/bash

configPath="/afs/cern.ch/work/o/osuranyi/public/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholds.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
#basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
suffix="_03Oct_newThresholds"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  #inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_full_lumi_complete/merged/merged_ntuples_${1}.root"
  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_full_lumi/merged/merged_ntuples_${1}.root"
  #inputPath=`sed "${1}q;d" /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
  #inputPath="${basePath}/mc_qed/ntuples_sc_full_lumi/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/200807_100412/0000/mc_HiForestAOD_${1}.root"
  #inputPath="${basePath}/mc_qed/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/210417_081453/0000/mc_HiForestAOD_${1}.root"
  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 253
  #inputPath="${basePath}/mc_qed/ntuples_sl_full_lumi_v5/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi_v5/200929_094304/0000/mc_HiForestAOD_${1}.root"
  #inputPath="${basePath}/mc_qed/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi/210417_080949/0000/mc_HiForestAOD_${1}.root"
  inputPath="${basePath}/skimmed_ntuples/mc_qed_sl_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_qed_sl${suffix}"
elif [ $2 -eq 3 ]
then
  sampleName="LbL" # 3 files only
  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_lbl_sc${suffix}"
elif [ $2 -eq 4 ]
then
  sampleName="CEP" # 3 files only
  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2_full_lumi/ntuples_loose_selections_${1}.root"
  outputPath="${basePath}/analysis_ruchi/anomalous_plots/mc_cep_sc${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/data_plots_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/selectAnomalousEvents $configPath $inputPath $output $sampleName
fi
