#!/bin/bash

userBasePath="/afs/cern.ch/work/r/rchudasa/private"
configPath="${userBasePath}/LightByLight2018/analysis/configs/applySelections.md"
#basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"
basePath="/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018"
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

echo "Params: ${1}, ${2}, ${3}"

if [ $2 -eq 0 ] # data
then
  sampleName="Data"
  inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_list.txt`
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
  inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_list.txt`
  outputPathLowAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_lowAco"
  outputPathHighAco="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_passingLbL_highAco"
  mkdir -p $outputPathLowAco
  mkdir -p $outputPathHighAco
elif [ $2 -eq 3 ] # Loose selections
then
  echo "Applying loose selections, ${3}"

  if [ ${3} -eq 0 ] # data, 10400 chunks
  then
    echo "Data"
    sampleName="Data"
    inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_list.txt`
    outputPath="${basePath}/skimmed_ntuples/data_doubleEG2_full_lumi"
  elif [ ${3} -eq 1 ] # QED SC, 255 chunks, max chunk number: 255
  then
    echo "QED SC"
    sampleName="QED_SC"
    #inputPath="${basePath}/mc_qed/ntuples_superchic_1034/ntuples_sc_1034/ntuples_sc_1034/191113_105005/0000/HiForestAOD_LbyL_full_sample_lbyl_reco_${1}.root"
    #inputPath="${basePath}/mc_qed/ntuples_sc_full_lumi/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/200807_100412/0000/mc_HiForestAOD_${1}.root"
    #inputPath="${basePath}/mc_qed/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_full_lumi/210417_081453/0000/mc_HiForestAOD_${1}.root"
    #inputPath="${basePath}/mcForests/mc_qed/QEDGammaGamma_5p02TeV_SuperChic/reco_mc_qed_sc_CastorInfo/210906_102658/0000/mc_HiForestAOD_${1}.root"
    #inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/input_qed_fsr.txt`
    inputPath=`sed "${1}q;d" ${userBasePath}/LightByLight2018/analysis/qedMG5.txt`
    #outputPath="${basePath}/skimmed_ntuples/mc_qed_sc_FSR_doubleEG2_full_lumi"
    outputPath="${basePath}/skimmed_ntuples/mc_qedMG5_FSR_doubleEG2_full_lumi"
  elif [ ${3} -eq 2 ] # CEP SC, 3 chunks, max chunk number: 3
  then
    echo "QED SL"
    sampleName="QED_SL"
    #inputPath="${basePath}/mc_qed/ntuples_sl_full_lumi/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi/200702_082621/0000/mc_HiForestAOD_${1}.root"
    #inputPath="${basePath}/mc_qed/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi/210417_080949/0000/mc_HiForestAOD_${1}.root"
    inputPath="${basePath}/mcForests/mc_qed/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_CastorInfo/210906_102343/0000/mc_HiForestAOD_${1}.root"
    outputPath="${basePath}/skimmed_ntuples/mc_qed_sl_doubleEG2_full_lumi"
  elif [ ${3} -eq 3 ] # LbL SC, 3 chunks, max chunk number: 3
  then
    echo "LbL"
    sampleName="LbL"
    #inputPath="${basePath}/mc_lbl/ntuples_1034/ntuples_lbl_1034/ntuples_lbl_1034/200207_114802/0000/HiForestAOD_LbyL_${1}.root"
    #inputPath="${basePath}/mc_lbl/LbyLSignal_5p02TeV_SuperChic/reco_mc_lbl_try2/210420_063700/0000/mc_HiForestAOD_${1}.root"
    inputPath="${basePath}/mcForests/mc_lbl/LbyLSignal_5p02TeV_SuperChic/reco_mc_lbl_CastorInfo/210906_102904/0000/mc_HiForestAOD_${1}.root"
    outputPath="${basePath}/skimmed_ntuples/mc_lbl_sc_doubleEG2_full_lumi"
  elif [ ${3} -eq 4 ] # QED SL, 253 chunks, max chunk number: 253
  then
    echo "CEP"
    sampleName="CEP"
    #inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
    #inputPath="${basePath}/mc_cep/ntuples_full_lumi/QCDDiphoton_5p02TeV_SuperChic/reco_mc_cep_full_lumi/200811_121848/0000/mc_HiForestAOD_${1}.root"
    #inputPath="${basePath}/mc_cep/QCDDiphoton_5p02TeV_SuperChic/reco_mc_cep_tryv2/210420_064351/0000/mc_HiForestAOD_${1}.root"
    inputPath="${basePath}/mcForests/mc_cep/QCDDiphoton_5p02TeV_SuperChic/reco_mc_cep_CastorInfo/210906_103054/0000/mc_HiForestAOD_${1}.root"
    outputPath="${basePath}/skimmed_ntuples/mc_cep_sc_doubleEG2_full_lumi"
  elif [ ${3} -eq 5] # CEP incoh
  then
    echo "CEPIncoh"
    sampleName="CEPIncoh"
    #inputPath="${basePath}/mc_cep/ntuples_1034/ntuples_cep_1034/ntuples_cep_1034/200211_054704/0000/HiForestAOD_cep_${1}.root"
    #inputPath="${basePath}/mc_cep/ntuples_full_lumi/QCDDiphoton_5p02TeV_SuperChic/reco_mc_cep_full_lumi/200811_121848/0000/mc_HiForestAOD_${1}.root"
    #inputPath="${basePath}/mc_cep/QCDDiphoton_5p02TeV_SuperChic/reco_mc_cep_tryv2/210420_064351/0000/mc_HiForestAOD_${1}.root"
    inputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mcForests/mc_cepIncoh/gen_sim_cep_SC_incoh/reco_mc_cepIncoh_CastorInfo/211125_053225/0000/mc_HiForestAOD_${1}.root"   
    outputPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_cepIncoh_sc_doubleEG2_full_lumi"
  else
    echo "Unknown option: ${3}"
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
  ${userBasePath}/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal $sampleName
elif [ $2 -eq 1 ] # MC
then
  ${userBasePath}/LightByLight2018/analysis/applySelections $configPath $inputPath $outputReco $outputTrigger $outputHFveto $outputExclusivity $outputLbLsignal $outputQEDsignal $sampleName
elif [ $2 -eq 2 ] # Data passing LbL selections
then
  ${userBasePath}/LightByLight2018/analysis/applySelections $configPath $inputPath $outputLowAco $outputHighAco $sampleName
elif [ $2 -eq 3 ] # Data passing loose selections
then
#  ${userBasePath}/LightByLight2018/analysis/applySelections $configPath $inputPath $output $sampleName
  if [ -s ${output} ]
  then
    echo "File already exists, skipping"
  else
    echo "File doesn't exist or is empty - running"
    ${userBasePath}/LightByLight2018/analysis/applySelections $configPath $inputPath $output $sampleName
  fi

  
  
fi


