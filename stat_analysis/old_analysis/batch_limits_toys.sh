#!/bin/bash

pwd_=$PWD

basedir=/afs/cern.ch/user/e/echapon/workspace/private/higgs_combine/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/test/FSQ16012
asymfile=${basedir}/limits_asym.txt


cd $basedir
eval `scramv1 runtime -sh`
cd $pwd_

pwd
# cp $basedir/datacard .
ls

axionN=`echo $2 | grep -o "axion."`

if [ $1 -eq 0 ]; then 
   limit=`grep obs $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --plot=limit_scan_obs_${axionN}.png ${2}" 
   text="Observed"

elif [ $1 -eq 1 ]; then 
   limit=`grep expm2 $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   # command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0.0 --toysH 1000 -i 10 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.025 ${2}"   
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.025 --plot=limit_scan_expm2sd_${axionN}.png ${2}"
   text="Expected 0.025"

elif [ $1 -eq 2 ]; then 
   limit=`grep expm1 $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.16 --plot=limit_scan_expm1sd_${axionN}.png ${2}"   
   text="Expected 0.16"

elif [ $1 -eq 3 ]; then
   limit=`grep exp0 $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.5 --plot=limit_scan_exp_${axionN}.png ${2}"
   text="Expected 0.5"

elif [ $1 -eq 4 ]; then 
   limit=`grep expp1 $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.84 --plot=limit_scan_expp1sd_${axionN}.png ${2}"
   text="Expected 0.84"

elif [ $1 -eq 5 ]; then
   limit=`grep expp2 $asymfile | grep $axionN | awk '{print $3}'`
   rmin=`bc -l <<< $limit'/2'`
   rmax=`bc -l <<< $limit'*2'`
   # command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0.0 --toysH 1000 -i 10 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.975 ${2}"
   command="combine -M HybridNew --cminDefaultMinimizerStrategy 0 --cminPreScan --rMin ${rmin} --rMax ${rmax} --rRelAcc=0 --toysH 1000 -i 15 --rule CLs --cl=0.95 --LHCmode LHC-limits --expectedFromGrid=0.975 --plot=limit_scan_expp2sd_${axionN}.png ${2}"
   text="Expected 0.975"
fi

echo $command
$command

cp *png ${basedir}/clsplots

echo "FINISHED!"
echo "We just computed: " $text " using file: " $2
