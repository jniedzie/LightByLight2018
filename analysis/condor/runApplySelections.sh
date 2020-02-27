#!/bin/bash

configPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/applySelections.md"

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
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPathReco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forRecoEff_tmp"
  outputPathTrigger="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forTriggerEff_tmp"
  outputPathHFveto="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forHFvetoEff_tmp"
  outputPathExclusivity="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forExclusivityEff_tmp"
  outputPathLbLsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forLbLsignal_CHE_500MeV"
  outputPathQEDsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_forQEDsignal_tmp"
elif [ $2 -eq 1 ] # MC
then
  # QED
#  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
  
  # LbL
#  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
  
  # CEP
  inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
  
  outputPathReco="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forRecoEff"
  outputPathTrigger="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forTriggerEff"
  outputPathHFveto="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forHFvetoEff"
  outputPathExclusivity="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forExclusivityEff"
  outputPathLbLsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forLbLsignal"
  outputPathQEDsignal="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep_sc_forQEDsignal"
elif [ $2 -eq 2 ] # Data passing LbL selections
then
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPathLowAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_lowAco"
  outputPathHighAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_highAco"
elif [ $2 -eq 3 ] # Data passing LbL selections
then
  inputPath=`sed "${1}q;d" /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/input_list.txt`
  outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_loose_selections"
fi

mkdir -p $outputPathReco
mkdir -p $outputPathTrigger
mkdir -p $outputPathHFveto
mkdir -p $outputPathExclusivity
mkdir -p $outputPathLbLsignal
mkdir -p $outputPathQEDsignal
mkdir -p $outputPathLowAco
mkdir -p $outputPathHighAco
mkdir -p $outputPath

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
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal
elif [ $2 -eq 1 ] # MC
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal
elif [ $2 -eq 2 ] # Data passing LbL selections
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $inputPath $outputLowAco $outputHighAco
elif [ $2 -eq 3 ] # Data passing LbL selections
then
  /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/applySelections $inputPath $output
fi
