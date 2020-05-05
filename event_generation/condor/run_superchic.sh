#!/bin/bash

#------------------------------------------------------------------------------------
# Modify those variables if needed:


# Modify this path to point to your superchic installation directory

gcc6_path=/cvmfs/sft.cern.ch/lcg/releases/LCG_87/gcc/6.2.0/x86_64-slc6/setup.sh
lhapdf_path=/afs/cern.ch/work/j/jniedzie/private/light_by_light/superchic3.0/lhapdf
minFileSize=7000000 # re-run job if output file exists, but has a size below this value (in bytes)
#
#------------------------------------------------------------------------------------

# Things below will be set automatically, no need to modify

superchic_path=/afs/cern.ch/work/j/jniedzie/private/light_by_light/superchic3.03/bin
output_path=/eos/cms/store/group/phys_diffraction/lbyl_2018/pbpb_ee

jobOffset=1000
arg1=$1
iJob=$((arg1+jobOffset))

outfilename=$output_path/evrec_p$iJob.out

source $gcc6_path

export LHAPDFSYS=$lhapdf_path
export PATH=${PATH}:${LHAPDFSYS}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LHAPDFSYS}/lib

fileSize=`wc -c $outfilename | awk '{print $1}'`

if [[ ! -s $outfilename || $fileSize -le $minFileSize ]]; then
  echo "Output file not found, has zero size or is smaller than requested minimum"
  echo "(Re-)running command:cmsRun $config_path outputFile=$outfilename inputFiles=$infilename"
  cd $superchic_path/parallel/p$iJob/
  ./superchic < input.DAT
  xrdcp -N -v evrecs/evrec.dat root://eoscms.cern.ch/$outfilename
  rm evrecs/evrec.dat
  rm outputs/output.dat
else
  echo "File already exists and is not empty. Quitting..."
fi









































































































































