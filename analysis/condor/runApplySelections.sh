#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/applySelections.md"
basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
sampleName=""

# for the data:
inputPath=""
outputPathReco=""
outputPathTrigger=""
outputPathHFveto=""
outputPathExclusivity=""
outputPathLbLsignal=""
outputPathQEDsignal=""
outputPathLowAco=""
outputPathHighAco=""
outputPath=""


if [ $2 -eq 0 ] # data
then
  sampleName="Data"
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPathReco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forRecoEff_tmp"
  outputPathTrigger="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forTriggerEff_tmp"
  outputPathHFveto="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forHFvetoEff_tmp"
  outputPathExclusivity="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forExclusivityEff_tmp"
  outputPathLbLsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forLbLsignal_CHE_500MeV"
  outputPathQEDsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forQEDsignal_tmp"
  mkdir -p $outputPathReco
  mkdir -p $outputPathTrigger
  mkdir -p $outputPathHFveto
  mkdir -p $outputPathExclusivity
  mkdir -p $outputPathLbLsignal
  mkdir -p $outputPathQEDsignal
elif [ $2 -eq 1 ] # MC
then
  # QED
#   sampleName="QED_SC"
#  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  
  # LbL
#  sampleName="LbL"
#  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  
  # CEP
  sampleName="CEP" inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  
  outputPathReco="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forRecoEff"
  outputPathTrigger="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forTriggerEff"
  outputPathHFveto="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forHFvetoEff"
  outputPathExclusivity="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forExclusivityEff"
  outputPathLbLsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forLbLsignal"
  outputPathQEDsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forQEDsignal"
  mkdir -p $outputPathReco
  mkdir -p $outputPathTrigger
  mkdir -p $outputPathHFveto
  mkdir -p $outputPathExclusivity
  mkdir -p $outputPathLbLsignal
  mkdir -p $outputPathQEDsignal
elif [ $2 -eq 2 ] # Data passing LbL selections
then
  sampleName="Data"
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPathLowAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_lowAco"
  outputPathHighAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_highAco"
  mkdir -p $outputPathLowAco
  mkdir -p $outputPathHighAco
elif [ $2 -eq 3 ] # Loose selections
then
  if [ $3 -eq 0 ] # data, 8500 chunks
  then
    sampleName="Data"
    inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
    outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_noPixelTracks_full"
  elif [ $3 -eq 1 ] # QED SC, 96 chunks, max chunk number: 96
  then
    sampleName="QED_SC" inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
    outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_qed_sc_doubleEG2"
  elif [ $3 -eq 2 ] # CEP SC, 408 chunks, max chunk number: 411
  then
    sampleName="CEP" inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
    outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_cep_sc_doubleEG2"
  elif [ $3 -eq 3 ] # LbL SC, 362 chunks, max chunk number: 376
  then
    sampleName="LbL"    inputPath="${basePath}/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
    outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_lbl_sc_doubleEG2"
  fi
  mkdir -p $outputPath
fi

outputReco="${outputPathReco}/ntuples_forRecoEff_${1}.root"
outputTrigger="${outputPathTrigger}/ntuples_forTriggerEff_${1}.root"
outputHFveto="${outputPathHFveto}/ntuples_forHFvetoEff_${1}.root"
outputExclusivity="${outputPathExclusivity}/ntuples_forExclusivityEff_${1}.root"
outputLbLsignal="${outputPathLbLsignal}/ntuples_forLbLsignal_${1}.root"
outputQEDsignal="${outputPathQEDsignal}/ntuples_forQEDsignal_${1}.root"
outputLowAco="${outputPathLowAco}/ntuples_passingLbL_lowAco_${1}.root"
outputHighAco="${outputPathHighAco}/ntuples_passingLbL_highAco_${1}.root"
output="${outputPath}/ntuples_loose_selections_${1}.root"

echo "Config: ${configPath}"
echo "Input: ${inputPath}"
echo "Output reco: ${outputReco}"
echo "Output trigger: ${outputTrigger}"
echo "Output HF veto: ${outputHFveto}"
echo "Output exclusivity: ${outputExclusivity}"
echo "Output LbL signal: ${outputLbLsignal}"
echo "Output QED signal: ${outputQEDsignal}"
echo "Output low aco: ${outputLowAco}"
echo "Output high aco: ${outputHighAco}"
echo "Output: ${output}"

if [ $2 -eq 0 ] # data
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal $sampleName
elif [ $2 -eq 1 ] # MC
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal $sampleName
elif [ $2 -eq 2 ] # Data passing LbL selections
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $outputLowAco $outputHighAco $sampleName
elif [ $2 -eq 3 ] # Data passing loose selections
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $output $sampleName
fi
