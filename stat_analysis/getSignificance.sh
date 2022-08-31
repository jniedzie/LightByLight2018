#!/bin/bash

datacard_path=datacards/datacard_acoplanarity_2018_withSFs.txt
 
echo "EXPECTED:"
# asymptotic
#combine -M Significance --signif $datacard_path -t -1 --expectSignal=1

# frequentist
# combine -M HybridNew --frequentist $datacard_path --significance --saveToys --fullBToys --saveHybridResult   -T 100 -i 100 -s 123456 --testStat PL
# combine -M HybridNew --frequentist $datacard_path --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.5
# combine -M HybridNew --frequentist $datacard_path --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.16
# combine -M HybridNew --frequentist $datacard_path --significance --readHybridResult --toysFile=higgsCombineTest.HybridNew.mH120.123456.root --expectedFromGrid=0.84

echo "OBSERVED:"
# asymptotic
#combine -M Significance --signif $datacard_path

# frequentist
# combine -M HybridNew -T 1000 --signif $datacard_path --testStat PL

#echo "LH scan"
# expected
#combine -n Exp -t -1 --expectSignal=1 -M MultiDimFit $datacard_path --algo=grid --points 300 --setParameterRanges r=0.0,3.0 >/dev/null
# observed
#combine -n Obs -M MultiDimFit $datacard_path --algo=grid --points 300 --setParameterRanges r=0.0,3.0 >/dev/null
# make the plot
#python plotMuScan.py
#mv muscan.pdf muscan_${type}_${varname}.pdf

# print r value
#echo "----- Stat+syst: ----"
#combine -n Obs -M MultiDimFit $datacard_path --algo=singles --setParameterRanges r=-1.0,4.0
#echo "----- Stat only: ----"
#combine -n Obs -M MultiDimFit $datacard_path --algo=singles --setParameterRanges r=-1.0,4.0 --freezeParameters all

# and another plot
# combine -M MultiDimFit --algo=grid --setParameterRanges r=0.0,3.0 $datacard_path -n bestfit
# combine -n stat -M MultiDimFit $datacard_path --algo=grid --points 300 --setParameterRanges r=0.0,3.0 --snapshotName MultiDimFit --freezeNuisanceGroups all # >/dev/null
# plot1DScan.py -m higgsCombinenominal.MultiDimFit.mH125.root  -o statsyst --others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' --breakdown syst,stat
# rename it

# impacts
#text2workspace.py $datacard_path -m 120
#combineTool.py -M Impacts -d datacard_acoplanarity.root -m 120 --doInitialFit
#combineTool.py -M Impacts -d datacard_acoplanarity.root -m 120 --doFits --parallel 4
#combineTool.py -M Impacts -d datacard_acoplanarity.root -m 120 -o impacts_acoplanarity.json
#plotImpacts.py -i impacts_acoplanarity.json -o impacts_acoplanarity

# pre- and post-fit plots
#combine -n Obs -M FitDiagnostics datacard_acoplanarity.root --plots --saveNormalizations --saveShapes --saveWithUncertainties

# #toys
combineTool.py -M HybridNew datacards/datacard_hacoplanarity.txt --LHCmode LHC-significance  --saveToys --fullBToys --saveHybridResult -T 10 -s 1:1000:1 --job-mode lxbatch --task-name acoplanarity_observed --sub-opts='-q 1nd' --expectSignal 1
# # below does not work
# # hadd all output ROOT files...
# combine -M HybridNew datacards/datacard_hacoplanarity.txt --LHCmode LHC-significance --readHybridResult --toysFile=testtoys.root
# # below works
# use hadd_hypotestresult.C
# HypoTestResult::Significance()
