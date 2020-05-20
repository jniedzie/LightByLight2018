#!/bin/bash
index=$(( 1 + ${1}))

inputPathData=`sed "${index}q;d" /afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/input_list.txt`

echo "${inputPathData}"

python /afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/MakeInputFile.py "${inputPathData}" "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/condor_inputfiles/tmp_runfile_${2}_${1}.txt"
/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/applySelections "TauTau" "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/condor_inputfiles/tmp_runfile_${2}_${1}.txt" "Data"
done
