#!/bin/bash

basePath="/eos/cms/store/group/phys_diffraction/lbyl_2018"

# for the data:
sampleName=""
inputPath=""
secondaryInputPath=""
outputPath=""

if [ $2 -eq 0 ] # data
then
  sampleName="Data"
  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/merged_ntuples_${1}.root"
#  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2/merged/merged_ntuples_${1}.root"
  secondaryInputPath="${basePath}/pixel_ntuples/ntuples_pixel_data.root"
  outputPath="${basePath}/skimmed_ntuples/data_doubleEG2_trackerAndPixelBranches/ntuples_${1}.root"
  
fi

mkdir -p $outputPath

echo "Input path: ${inputPath}"
echo "Secondary input path: ${inputPath}"
echo "Output path: ${outputPath}"

/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/addPixelTrackInfo $inputPath $secondaryInputPath $outputPath $sampleName
