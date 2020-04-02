#!/bin/bash

basePath=""
baseFileName=""
nFiles=0
outPath=""

if [ $1 -eq 0 ] # QED SC
then
  basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_superchic_with_cuts/"
  baseFileName="evrec_QED_p"
  nFiles=8000
#  outPath="/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/mergeLHE/merged_QED_SC.lhe"
  outPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_superchic_with_cuts/merged_QED_SC.lhe"
elif [ $1 -eq 1 ] # LbL
then
  basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/lhe_superchic/"
  baseFileName="evrec_LbL_p"
  nFiles=670
  outPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/lhe_superchic/merged_LbL_SC.lhe"
elif [ $1 -eq 2 ] # CEP
then
  basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/lhe_superchic/"
  baseFileName="evrec_CEP_p"
  nFiles=1500
  outPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/lhe_superchic/merged_CEP_SC.lhe"
elif [ $1 -eq 3 ] # QED SL
then
  basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_starlight_with_cuts/"
  baseFileName="starlight_QED_p"
  nFiles=12000
  outPath="/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_starlight_with_cuts/merged_QED_SL_fixed.lhe"
fi

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/mergeLHE/merge $basePath $baseFileName $nFiles $outPath
