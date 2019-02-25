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
CMSSW version: CMSSW_10_3_2

* Step1: Gen_Sim - Submit the gen sim jobs with condorConfig.sub script, it uses 1ststep_GEN_SIM.py file in MC_reconstruction/gen_sim repo
* Step2: Digi_Raw - Submit the digi raw jobs with condorConfig.sub script, it uses step2_DIGI_L1_DIGI2RAW_HLT.py script in MC_reconstruction/gen_sim repo
change the current directory to your own and output eosarea in batch.sh script.

## Authors

* Émilien Chapon
* Ruchi Chudasama 
* David d’Enterria
* Jeremi Niedziela
