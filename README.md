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

## Authors

* Émilien Chapon
* Ruchi Chudasama 
* David d’Enterria
* Jeremi Niedziela
