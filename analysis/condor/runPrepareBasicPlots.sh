#!/bin/bash

echo "Starting runPrepareBasicPlots"

# ./runPrepareBasicPlots.sh fileNumber sampleType configType

configPath=""
suffix=""

if [ $3 -eq 0 ]
then
# default
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_default.md"
  suffix="_default_tracker_branches"
elif [ $3 -eq 1 ]
then
# HF thresholds increased to 20 GeV
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_HF_20GeV.md"
  suffix="_HF_20GeV"
elif [ $3 -eq 2 ]
then
  # add n hits ≥ 11 requirement on tracks
    configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+nhits.md"
    suffix="_tracks+nhits"
elif [ $3 -eq 3 ]
then
  # add chi2 < 2.5 requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+chi2.md"
  suffix="_tracks+chi2"
elif [ $3 -eq 4 ]
then
  # add pt > 500 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt.md"
  suffix="_tracks+pt"
elif [ $3 -eq 5 ]
then
  # add n hits ≥ 7 requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+nhits7.md"
  suffix="_tracks+nhits7"
elif [ $3 -eq 6 ]
then
  # add n hits ≥ 3 requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+nhits3.md"
  suffix="_tracks+nhits3"
elif [ $3 -eq 7 ]
then
  # add n hits ≥ 5 requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+nhits5.md"
  suffix="_tracks+nhits5"
elif [ $3 -eq 8 ]
then
  # add pt > 700 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt700.md"
  suffix="_tracks+pt700"
elif [ $3 -eq 9 ]
then
  # add pt > 900 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt900.md"
  suffix="_tracks+pt900"
elif [ $3 -eq 10 ]
then
  # add pt > 200 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt200.md"
  suffix="_tracks+pt200"
elif [ $3 -eq 11 ]
then
  # add pt > 300 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt300.md"
  suffix="_tracks+pt300"
elif [ $3 -eq 12 ]
then
  # add pt > 400 MeV requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+pt400.md"
  suffix="_tracks+pt400"
elif [ $3 -eq 13 ]
then
  # add no conversion requirement on photons
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_pho+conversions.md"
  suffix="_pho+conversions"
elif [ $3 -eq 14 ]
then
  # add d_xy < 1 mm requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+dxy1mm.md"
  suffix="_tracks+dxy1mm"
elif [ $3 -eq 15 ]
then
  # add pt < 0.8 requirement on diphoton
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_diphoton+pt_0p8.md"
  suffix="_diphoton+pt_0p8"
elif [ $3 -eq 16 ]
then
  # add dxy_bs < 1 mm requirement on tracks
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+dxybs1mm.md"
  suffix="_tracks+dxybs1mm"
elif [ $3 -eq 17 ]
then
  # remove all track requirements
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_tracks+no_cuts.md"
  suffix="_tracks+no_cuts"
elif [ $3 -eq 18 ]
then
  # remove all track requirements
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_EEnoiseEtaDep.md"
  suffix="_EEnoiseEtaDep"
elif [ $3 -eq 19 ]
then
  # remove all track requirements
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_EEnoiseEta_2p4.md"
  suffix="_EEnoiseEta_2p4"
elif [ $3 -eq 20 ]
then
  # remove all track requirements
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_EBnoise_1p0.md"
  suffix="_EBnoise_1p0"
elif [ $3 -eq 21 ]
then
  # max 50 pixel hits
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_50hits.md"
  suffix="_50hits"
elif [ $3 -eq 22 ]
then
  # max 100 pixel hits
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_100hits.md"
  suffix="_100hits"
elif [ $3 -eq 23 ]
then
  # max 200 pixel hits
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_200hits.md"
  suffix="_200hits"
elif [ $3 -eq 24 ]
then
  # max 300 pixel hits
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_300hits.md"
  suffix="_300hits"
elif [ $3 -eq 25 ]
then
  # max 150 pixel hits
  configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/preparePlots_150hits.md"
  suffix="_150hits"
fi

# for the data:
inputPath=""
outputPath=""
sampleName=""

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

if [ $2 -eq 0 ]
then
  sampleName="Data" # last chunk number: 7440, merged into 80 files
#  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
    inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/merged_ntuples_${1}.root"
#  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2/ntuples_loose_selections_${1}.root"
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
