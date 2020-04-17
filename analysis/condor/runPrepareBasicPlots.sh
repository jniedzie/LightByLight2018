#!/bin/bash

echo "Starting runPrepareBasicPlots"

# ./runPrepareBasicPlots.sh fileNumber sampleType configType

configPath=""
suffix=""

if [ $3 -eq 0 ]
then
# default
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_default.md"
  suffix="_default_noZDCcuts"
elif [ $3 -eq 1 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noPixelTracks.md"
  suffix="_noPixelTracks"
elif [ $3 -eq 2 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_ZDCcut.md"
  suffix="_ZDCcut_200"
elif [ $3 -eq 3 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_totalZDCcut.md"
  suffix="_totalZDCcut"
elif [ $3 -eq 4 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_newCuts.md"
  suffix="_newCuts"
elif [ $3 -eq 5 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_looserCHE.md"
  suffix="_looserCHE_noZDCcuts"
elif [ $3 -eq 6 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noCHE.md"
  suffix="_noCHE_noZDCcuts"
elif [ $3 -eq 7 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_looserPixelTracks.md"
  suffix="_looserPixelTracks_noZDCcuts"
elif [ $3 -eq 8 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noPixelTracks.md"
  suffix="_noPixelTracks_noZDCcuts"
elif [ $3 -eq 9 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_looserZDC.md"
  suffix="_looserZDC"
elif [ $3 -eq 10 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noZDC.md"
  suffix="_noZDC"
elif [ $3 -eq 11 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_looserNEE.md"
  suffix="_looserNEE_noZDCcuts"
elif [ $3 -eq 12 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noNEE.md"
  suffix="_noNEE_noZDCcuts"
elif [ $3 -eq 13 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_looserPhotonID.md"
  suffix="_looserPhotonID_noZDCcuts"
elif [ $3 -eq 14 ]
then
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_noPhotonID.md"
  suffix="_noPhotonID_noZDCcuts"
fi

# for the data:
inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

if [ $2 -eq 0 ]
then
  sampleName="Data" # last chunk number: 7440, merged into 60 files
#  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
    inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_complete/merged/merged_ntuples_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_data${suffix}"
  
elif [ $2 -eq 1 ]
then
  sampleName="QED_SC" # last chunk numer: 95, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_qed_sc_doubleEG2/ntuples_loose_selections_${1}.root"
# inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_qed_sc${suffix}"
elif [ $2 -eq 2 ]
then
  sampleName="CEP" # last chunk numer: 410, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2/ntuples_loose_selections_${1}.root"
#  inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_cep_sc${suffix}"
elif [ $2 -eq 3 ]
then
  sampleName="LbL" # last chunk numer: 375, merged into 1 file
  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2/merged_ntuples.root"
#  inputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2/ntuples_loose_selections_${1}.root"
#  inputPath="${basePath}/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_lbl_sc${suffix}"
elif [ $2 -eq 4 ]
then
  sampleName="QED_SL"
#  inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  outputPath="${basePath}/analysis/basicPlots/basicPlots_mc_qed_sl${suffix}"
fi

mkdir -p $outputPath

output="${outputPath}/basicPlots_${1}.root"

echo "Config: ${configPath}"
echo "Input: ${inputPath}"
echo "Output: ${output}"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/prepareBasicPlots $configPath $inputPath $output $sampleName

