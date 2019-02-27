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
 
## Authors

* Émilien Chapon
* Ruchi Chudasama 
* David d’Enterria
* Jeremi Niedziela
