#!/bin/bash

userBasePath="/afs/cern.ch/work/r/rchudasa/private"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"
#configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholds.md"
configPath="${userBasePath}/LightByLight2018/analysis/configs/efficiencies_HFVeto_withEleIsolatioNewThresholds.md"

inputPath=""
outputPath=""
sampleName=""

inbasePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

suffix=""
#suffix="_noElectronIDcuts"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/analysis_ruchi/efficienciesQED/efficienciesQED_data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
  inputPath="${basePath}/mc_qed/ntuples_sc_full_lumi/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/200807_100412/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis/efficienciesQED/efficienciesQED_mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 253
  #inputPath="${basePath}/mc_qed/ntuples_sl_full_lumi_v5/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi_v5/200929_094304/0000/mc_HiForestAOD_${1}.root"
  inputPath="${inbasePath}/mcForests/mc_qed/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_CastorInfo/210906_102343/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/analysis_ruchi/efficienciesQED/mc_qed_sl${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/efficienciesQED_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  ${userBasePath}/LightByLight2018/analysis/getEfficienciesQED $configPath $inputPath $output $sampleName
fi
