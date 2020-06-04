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
  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_noPixelTracks_full/ntuples_loose_selections_${1}.root"
#  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2_noPixelTracks/ntuples_loose_selections_${1}.root"
#  inputPath="${basePath}/skimmed_ntuples/data_doubleEG2/merged/merged_ntuples_${1}.root"
  secondaryInputPath="${basePath}/pixel_ntuples/ntuples_pixel_data.root"
  outputPath="${basePath}/skimmed_ntuples/data_doubleEG2_complete_full"
  mkdir -p $outputPath
  outputPath="${outputPath}/ntuples_${1}.root"
fi

echo "Input path: ${inputPath}"
echo "Secondary input path: ${secondaryInputPath}"
echo "Output path: ${outputPath}"

echo "Executing command:"
echo "/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/addPixelTrackInfo ${inputPath} ${secondaryInputPath} ${outputPath} ${sampleName}"

if [ -s ${outputPath} ]
then
  echo "File already exists, skipping"
else
  echo "File doesn't exist or is empty - running"
  cd /afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/
  . setenv.sh
  ./addPixelTrackInfo $inputPath $secondaryInputPath $outputPath $sampleName
fi


