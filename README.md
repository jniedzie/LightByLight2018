## LightByLight2018

This repository containts code and documentation for light-by-light analysis of 2018 data.


## Useful links

[Main TWiki page](https://twiki.cern.ch/twiki/bin/view/CMS/LightbyLight2018)


## MC samples generation

In order to keep track of parameters used to generate MC samples, config files are stored in **generatorConfigs** directory.

List of content:
* input_QED.DAT - used with superchic 3.03 to generate 50M QED events [ongoing]
* slight_QED.in - STARlight v.2.47 config used to produce 40M QED samples
* input_LbL.DAT - [will be] used with superchic 3.03 to generate 0.5M LbL events
* input_CEP.DAT - [will be] used with superchic 3.03 to generate 1M CEP events
* input_ALP.DAT - basic config for ALPs to be used with superchic 3.03 (mass and coupling should be set in the config)

* s2int_dependance.txt - results of the study of total cross section dependance on *s2int* parameter of superchic


## MC samples reconstruction

1. Set CMSSW environment before running the scripts (currently preferred CMSSW version: CMSSW_10_3_2):

```
cd CMSSW_10_3_2/src
cmsenv
```

2. Prepare scripts and submit jobs:

* Go to the correct directory depending on the step you want to run:
	* Step 1 (Gen_Sim): MC_reconstruction/gen_sim
	* Step 2 (Digi_Raw): MC_reconstruction/digi_raw
* Modify paths in the top section of the _batch.sh_ script
* Create output, error and log directories: `mkdir -p output error log`
* Open _condorConfig.sub_ file and change number next to _queue_ to the desired number of files to process,
* Submit jobs: `condor_submit condorConfig.sub` 

3. Reconstruction with modified Egamma thresholds:
* `git clone git@github.com:jniedzie/LightByLight2018.git` in CMSSW_10_3_2
*  compile these packages with `scarm b -j4`
* `cd MC_reconstruction/reco` contains the reconstruction step script
* Submit the jobs in condor with `condor_submit condorConfig.sub` as decribed above. 

4. HiForest
* `cd HeavyIonAnalyis/PhotonAnalysis/test`
* change the input file path in runForestAOD_pponAA_MIX_103X.py scipt and `cmsRun runForestAOD_pponAA_MIX_103X.py`  


## Flat MC photon and electron sample generation and reconstruction
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


## Calo noise study with EmptyBx

### Hiforest production 

* Clone HeavyIonsAnalysis, RecoBTag, RecoHI, RecoJets and RecoVertex modules from this repo to CMSSW_10_3_2/src 
* Compile them with `scram b -j 16`
* For HiForest production, `cd HeavyIonsAnalysis/PhotonAnalysis/test` 
* To test if everything is running ok, test on data with one of the HIForward AOD files `cmsRun runForestAOD_pponAA_DATA_103X.py` and check the output for calotower variables 
* Then submit the crab jobs with `crab submit -c crabConfig.py` 
* Prameters for crab jobs can be modified in crabConfig.py script 

### Preparing energy histograms

* Login to lxplus7 (with centos7)
* Go to `caloNoiseStudy` and compile binaries with `./build.sh`
* Create a list of hiforest files to be processed and put it in `input_filelist.txt` (make sure that each entry starts wit _/store/_)
* Create output, error and log directories: `mkdir -p output error log`
* Modify paths in the top section of the `run_calo_study.sh` script
* Open _condorConfig.sub_ file and change number next to _queue_ to the desired number of files to process
* Submit jobs: `condor_submit condorConfig.sub`


## Authors

* Émilien Chapon
* Ruchi Chudasama 
* David d’Enterria
* Jeremi Niedziela
