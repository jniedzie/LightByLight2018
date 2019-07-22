## LightByLight2018

This repository containts code and documentation for light-by-light analysis of 2018 data.


## Useful links

[Main TWiki page](https://twiki.cern.ch/twiki/bin/view/CMS/LightbyLight2018)


## MC samples generation

#### Background samples:

In order to keep track of parameters used to generate MC samples, config files are stored in **generatorConfigs** directory.

List of content:
* input_QED.DAT - used with superchic 3.03 to generate QED events
* slight_QED.in - STARlight v.3.0 config used to produce QED events
* input_LbL.DAT - used with superchic 3.03 to generate LbL events
* input_CEP.DAT - used with superchic 3.03 to generate CEP events
* input_ALP.DAT - basic config for ALPs to be used with superchic 3.03 (mass and coupling should be set in the config)

* s2int_dependance.txt - results of the study of total cross section dependance on *s2int* parameter of superchic

#### Flat p_T MC photon and electron samples:

* Use CMSSW_10_3_2 and cmsenv
* Copy Configuration/Generator from this repo
```
scram build
cd Configuration/Generator/python
cmsDriver.py SingleGammaFlatPt_pythia8_cfi --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 103X_upgrade2018_realistic_HI_v9 --step GEN,SIM --geometry DB:Extended --era Run2_2018 --no_exec --customise Configuration/Generator/RandomSeed_cfi.customizeRandomSeed, Configuration/DataProcessing/Utils.addMonitoring
```
* Open SingleGammaFlatPt_pythia8_cfi_GEN_SIM.py and change the number of events from 1 to the number of events you want to generate  
* Modify paths in the top section of the _batch.sh_ script
* Create output, error and log directories: `mkdir -p output error log`
* Open _condorConfig.sub_ file and change number next to _queue_ to the desired number of events you want to generate
* Submit jobs: `condor_submit condorConfig.sub`
* For electron sample, change the particle ID to 11 `ParticleID = cms.vint32(11)` in SingleGammaFlatPt_pythia8_cfi_GEN_SIM.py script and submit the jobs

## MC samples reconstruction

0. Connect to lxplus6.
1. Set CMSSW environment, pull modifications in reconstruction, build:

```
cd CMSSW_10_3_2/src
cmsenv
git cms-merge-topic rchudasa:LightByLightMod_1032
scram b -j8
```

2. Prepare scripts and submit jobs:

* Go to the correct directory depending on the step you want to run:
	`MC_reconstruction/reco_step/sample_type/`
* In _crabConfig.py_ check and modify if needed the following:
	* name for the dataset you want to process (ideally followig convension used for all the other samples):
	```
	config.General.requestName
	config.Data.outputPrimaryDataset 
	config.Data.outputDatasetTag
	```
	* the output path: `config.Data.outLFNDirBase`
* Update the list of input files in _input.txt_ file if needed. Each entry should begin with `/store/` rather than `/eos/cms/store/`!!!
* If you don't have crab already set up, run `source /cvmfs/cms.cern.ch/crab3/crab.sh`
* Then submit the crab jobs with `crab submit -c crabConfig.py` 

* if you need to resubmit failed jobs, run `crab resubmit -d crab_projects/job_name/`

* Command used to generate reco scipt:
```
cmsDriver.py step3 --mc --eventcontent AODSIM --datatier AODSIM --conditions 103X_upgrade2018_realistic_HI_v11 --step RAW2DIGI,L1Reco,RECO --geometry DB:Extended --era Run2_2018,lightByLightLowPt --customise Configuration/DataProcessing/Utils.addMonitoring --customise_commands 'process.AODSIMoutput.outputCommands.extend(["keep *_towerMaker_*_*", "keep *_siPixelRecHits_*_*", "keep *_siPixelClusters_*_*","keep *_g4SimHits_*_*"])' -n -1 --no_exec 
```

## Produce HiForest ntuples

* Clone HeavyIonsAnalysis, RecoBTag, RecoHI, RecoJets and RecoVertex modules from this repo to CMSSW_10_3_2/src 
* Compile them with `scram b -j 16`
* `cd HeavyIonAnalyis/PhotonAnalysis/test`
* change the input file path in:
	* for MC: runForestAOD_pponAA_MC_103X.py
	* for data: runForestAOD_pponAA_DATA_103X.py
* to test if everything is running ok, test on one HIForward AOD files `cmsRun correct_script_name.py` and check the output for calotower variables,
* modify parameters in crabConfig.py script,
* if you don't have crab already set up, run `source /cvmfs/cms.cern.ch/crab3/crab.sh`
* submit the crab jobs with `crab submit -c crabConfig.py` 

## Check luminosity in data

* Check the crab report to estimate how much lumi available: `crab report -d crab_projects/name_of_the_project`, it creates the processedLumis.json in crab_projects/name_of_the_project/results repo
* To check the lumi: run brilcalc using following command at lxplus
	*  `export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH`
	*  `pip install --user --upgrade brilws`
	*  `brilcal -i processedLumis.json`

## Run the Egamma regression
```
cd CMSSW_10_3_2/src
cmsenv
git clone git@github.com:cms-egamma/EgRegresTrainerLegacy.git
cd EgRegresTrainerLegacy 
gmake RegressionTrainerExe -j 8
gmake RegressionApplierExe -j 8
export PATH=$PATH:./bin/$SCRAM_ARCH #add the binary location to path
export PYTHON27PATH=$PYTHON27PATH:python

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PWD/include//includes the headers, 

//copy runSCRegJob.py to your  EgRegresTrainerLegacy/scripts directory from this githubs repo
cd CMSSW_10_3_2/src/EgRegresTrainerLegacy
./scripts/runSCRegJob.py
```

## Calo noise study with EmptyBx

### Preparing energy histograms

* Login to lxplus7 (with centos7)
* Go to `caloNoiseStudy` and compile binaries with `./build.sh`
* Create a list of hiforest files to be processed and put it in `input_filelist.txt` (make sure that each entry starts wit _/store/_)
* Create output, error and log directories: `mkdir -p output error log`
* Modify paths in the top section of the `run_calo_study.sh` script
* Open _condorConfig.sub_ file and change number next to _queue_ to the desired number of files to process
* Submit jobs: `condor_submit condorConfig.sub`


## Build analysis toolkit

* Login to lxplus7 (with centos7), go to top directory of this repo and run these commands:
```
 cd analysis
 ./setenv.sh
 cmake .
 make -j8
```
* if everything went well, you should see executables such as "getDiphotonEfficiency" ready to run.


## Authors

* Émilien Chapon
* Ruchi Chudasama 
* David d’Enterria
* Jeremi Niedziela
