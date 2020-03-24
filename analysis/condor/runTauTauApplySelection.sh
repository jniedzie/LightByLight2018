#!/bin/bash
for i in {10..10}
do
  python /afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/MakeInputFile.py "$i" "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/tmp_runfile_$i.txt"
  /afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/applySelections "TauTau" "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/input_files/tmp_runfile_$i.txt" "Data"
done
