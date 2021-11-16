#!/bin/bash

configPath="/afs/cern.ch/work/o/osuranyi/public/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation_newThresholds.md "
#configPath="/afs/cern.ch/work/r/rchudasa/private/LightByLight2018/analysis/configs/efficiencies_eleNoIsolation.md"

inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_heavyions/osuranyi"
basePathMC="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"

suffix="_swissCrossFixed_8Nov21"

if [ $2 -eq 0 ]
then
  sampleName="Data" # 10400 files
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/o/osuranyi/public/LightByLight2018/analysis/input_list.txt`
  outputPath="${basePath}/lbyl_2018/efficienciesQED/photonEfficienciesQED_data${suffix}"
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 255
#inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  inputPath="${basePathMC}/mc_qed/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/210417_081453/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/lbyl_2018/efficienciesQED/photonEfficienciesQED_mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="QED_SL" # last chunk numer: 253
  inputPath="${basePathMC}/mc_qed/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi/210417_080949/0000/mc_HiForestAOD_${1}.root"
  outputPath="${basePath}/lbyl_2018/efficienciesQED/photonEfficienciesQED_mc_qed_sl${suffix}"
fi


mkdir -p $outputPath
output="${outputPath}/efficienciesQED_${1}.root"

if [ -s ${output} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  /afs/cern.ch/work/o/osuranyi/public/LightByLight2018/analysis/getPhotonRecoIDEfficiencies $configPath $inputPath $output $sampleName
fi
