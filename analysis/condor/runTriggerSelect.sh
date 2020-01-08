#!/bin/bash

cd /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/
fileNumber=$1
echo "Executing command: root -l -b -q \"triggerSelect.C($fileNumber)\""
root -l -b -q "triggerSelect.C($fileNumber)"
