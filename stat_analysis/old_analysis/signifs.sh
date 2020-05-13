#!/bin/bash


# for type in ged hybrid; do
for type in ged; do
   filename=${type}_final_histos_invmass5_diphoton_pt1.root
   echo
   echo
   echo
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!"
   echo "     " $type
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!"

   # for varname in counting hinvmass hdiphoton_pt hacoplanarity; do
   for varname in counting hacoplanarity; do
      echo
      echo "#########################"
      echo "     " $varname
      echo "#########################"
      if [ $varname != "counting" ]; then root -l -b -q prepareInput.C'("'${filename}'","'${varname}'")' 2>&1 >/dev/null 2>&1; fi
      
      echo "EXPECTED:"
      # asymptotic
      combine -M Significance --signif datacard_${type}_${varname}.txt -t -1 --expectSignal=1

      # frequentist
      # combine -M HybridNew --frequentist datacard_${type}_${varname}.txt --significance --saveToys --fullBToys --saveHybridResult   -T 100 -i 100 -s 123456 --testStat PL
      # combine -M HybridNew --frequentist datacard_${type}_${varname}.txt --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.5
      # combine -M HybridNew --frequentist datacard_${type}_${varname}.txt --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.16
      # combine -M HybridNew --frequentist datacard_${type}_${varname}.txt --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.84

      echo "OBSERVED:"
      # asymptotic
      combine -M Significance --signif datacard_${type}_${varname}.txt

      # frequentist
      # combine -M HybridNew -T 1000 --signif datacard_${type}_${varname}.txt --testStat PL

      echo "LH scan"
      # expected
      combine -n Exp -t -1 --expectSignal=1 -M MultiDimFit datacard_${type}_${varname}.txt --algo=grid --points 300 --setParameterRanges r=0.0,3.0 >/dev/null
      # observed
      combine -n Obs -M MultiDimFit datacard_${type}_${varname}.txt --algo=grid --points 300 --setParameterRanges r=0.0,3.0 >/dev/null
      # make the plot
      python plotMuScan.py
      mv muscan.pdf muscan_${type}_${varname}.pdf

      # print r value
      echo "----- Stat+syst: ----"
      combine -n Obs -M MultiDimFit datacard_${type}_${varname}.txt --algo=singles --setParameterRanges r=-1.0,4.0 
      echo "----- Stat only: ----"
      combine -n Obs -M MultiDimFit datacard_${type}_${varname}.txt --algo=singles --setParameterRanges r=-1.0,4.0 --freezeParameters all

      # and another plot
      # combine -M MultiDimFit --algo=grid --setParameterRanges r=0.0,3.0 datacard_${type}_${varname}.txt -n bestfit 
      # combine -n stat -M MultiDimFit datacard_${type}_${varname}.txt --algo=grid --points 300 --setParameterRanges r=0.0,3.0 --snapshotName MultiDimFit --freezeNuisanceGroups all # >/dev/null
      # plot1DScan.py -m higgsCombinenominal.MultiDimFit.mH125.root  -o statsyst --others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' --breakdown syst,stat
      # rename it

      # impacts
      text2workspace.py datacard_${type}_${varname}.txt -m 120
      combineTool.py -M Impacts -d datacard_${type}_${varname}.root -m 120 --doInitialFit
      combineTool.py -M Impacts -d datacard_${type}_${varname}.root -m 120 --doFits --parallel 4
      combineTool.py -M Impacts -d datacard_${type}_${varname}.root -m 120 -o impacts_${type}_${varname}.json
      plotImpacts.py -i impacts_${type}_${varname}.json -o impacts_${type}_${varname}

      # pre- and post-fit plots
      combine -n Obs -M FitDiagnostics datacard_${type}_${varname}.root --plots --saveNormalizations --saveShapes --saveWithUncertainties
   done
done

# #toys
# combineTool.py -M HybridNew datacard_ged_hacoplanarity.txt --LHCmode LHC-significance  --saveToys --fullBToys --saveHybridResult -T 10000 -s 1:1000:1 --job-mode lxbatch --task-name acoplanarity_observed --sub-opts='-q 1nd' --expectSignal 1
# # below does not work
# # hadd all output ROOT files...
# combine -M HybridNew datacard_ged_hacoplanarity.txt --LHCmode LHC-significance --readHybridResult --toysFile=testtoys.root
# # below works
# use hadd_hypotestresult.C
# HypoTestResult::Significance()
