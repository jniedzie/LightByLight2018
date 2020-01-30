//  ConfigManager.cpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#include "ConfigManager.hpp"

ConfigManager config("init");

ConfigManager::ConfigManager(string _path)
{
  if(_path=="init") return;
  
  configFile = unique_ptr<TEnv>(new TEnv());
  
  if(configFile->ReadFile(_path.c_str(), kEnvUser) < 0){
    cout<<"ERROR - could not load config file:"<<_path<<". Will use default values"<<endl;
    return;
  }
  else{
    cout<<"INFO -- Successfully read config file: "<<_path<<endl;
  }
  
  outputPath  = configFile->GetValue("output_path","unnamed.root");
  
  _params["maxEvents"]         = configFile->GetValue("maxEvents", 99999999.9);
  
  _params["maxDeltaEtaEB"]     = configFile->GetValue("maxDeltaEtaEB", 9999.9);
  _params["maxDeltaPhiEB"]     = configFile->GetValue("maxDeltaPhiEB", 9999.9);
  _params["maxDeltaEtaEE"]     = configFile->GetValue("maxDeltaEtaEE", 9999.9);
  _params["maxDeltaPhiEE"]     = configFile->GetValue("maxDeltaPhiEE", 9999.9);
  
  _params["maxEtaEEtower"]     = configFile->GetValue("maxEtaEEtower", 9999.9);
  
  _params["trackMinPt"]        = configFile->GetValue("trackMinPt", 0.0);
  _params["diphotonMaxPt"]     = configFile->GetValue("diphotonMaxPt", 9999.9);
  
  _params["maxDeltaR"]         = configFile->GetValue("maxDeltaR", 9999.9);

  // Photon ID cuts
  _params["photonMinEt"]             = configFile->GetValue("photonMinEt"            , 9999.9);
  _params["photonMaxEta"]            = configFile->GetValue("photonMaxEta"           , 9999.9);
  _params["photonMaxHoverEbarrel"]   = configFile->GetValue("photonMaxHoverEbarrel"  , 9999.9);
  _params["photonMaxHoverEendcap"]   = configFile->GetValue("photonMaxHoverEendcap"  , 9999.9);
  _params["photonMaxEtaWidthBarrel"] = configFile->GetValue("photonMaxEtaWidthBarrel", 9999.9);
  _params["photonMaxEtaWidthEndcap"] = configFile->GetValue("photonMaxEtaWidthEndcap", 9999.9);
  
  _params["electronMinPt"]             = configFile->GetValue("electronMinPt", 9999.9);
  _params["electronMaxEta"]            = configFile->GetValue("electronMaxEta", 9999.9);
  _params["electronMaxNmissingHits"]   = configFile->GetValue("electronMaxNmissingHits", 9999);
  _params["electronMaxHoverE_Barrel"]   = configFile->GetValue("electronMaxHoverEbarrel", 9999.9);
  _params["electronMaxHoverE_Endcap"]   = configFile->GetValue("electronMaxHoverEendcap", 9999.9);
  _params["electronMaxDetaSeedBarrel"] = configFile->GetValue("electronMaxDetaSeedBarrel", 9999.9);
  _params["electronMaxDetaSeedEndcap"] = configFile->GetValue("electronMaxDetaSeedEndcap", 9999.9);
  
  _params["electronMaxChargedIsoBarrel"] = configFile->GetValue("electronMaxChargedIsoBarrel", 9999.9);
  _params["electronMaxChargedIsoEndcap"] = configFile->GetValue("electronMaxChargedIsoEndcap", 9999.9);
  _params["electronMaxPhotonIsoBarrel"]  = configFile->GetValue("electronMaxPhotonIsoBarrel", 9999.9);
  _params["electronMaxPhotonIsoEndcap"]  = configFile->GetValue("electronMaxPhotonIsoEndcap", 9999.9);
  _params["electronMaxNeutralIsoBarrel"] = configFile->GetValue("electronMaxNeutralIsoBarrel", 9999.9);
  _params["electronMaxNeutralIsoEndcap"] = configFile->GetValue("electronMaxNeutralIsoEndcap", 9999.9);
  
  _params["ecalCrackMin"] = configFile->GetValue("ecalCrackMin", 9999.9);
  _params["ecalCrackMax"] = configFile->GetValue("ecalCrackMax", 9999.9);
  _params["ecalHEMmin"]   = configFile->GetValue("ecalHEMmin", 9999.9);
  _params["ecalHEMmax"]   = configFile->GetValue("ecalHEMmax", 9999.9);
  
  _params["noiseThresholdEB"]     = configFile->GetValue("noiseThresholdEB", 9999.9);
  _params["noiseThresholdEE"]     = configFile->GetValue("noiseThresholdEE", 9999.9);
  _params["noiseThresholdHB"]     = configFile->GetValue("noiseThresholdHB", 9999.9);
  _params["noiseThresholdHE"]     = configFile->GetValue("noiseThresholdHE", 9999.9);
  _params["noiseThresholdHFp"]    = configFile->GetValue("noiseThresholdHFp", 9999.9);
  _params["noiseThresholdHFm"]    = configFile->GetValue("noiseThresholdHFm", 9999.9);
  
  
  _params["doNoiseEEetaDependant"]    = configFile->GetValue("doNoiseEEetaDependant", 0);
  _params["noiseEEetaStep"]   = configFile->GetValue("noiseEEetaStep", 9999.9);
  _params["noiseEEetaMin"]    = configFile->GetValue("noiseEEetaMin", 9999.9);
  _params["noiseEEetaMax"]    = configFile->GetValue("noiseEEetaMax", 9999.9);
  
  _params["noiseThresholdEE_1.5"]    = configFile->GetValue("noiseThresholdEE_1.5", 9999.9);
  _params["noiseThresholdEE_1.6"]    = configFile->GetValue("noiseThresholdEE_1.6", 9999.9);
  _params["noiseThresholdEE_1.7"]    = configFile->GetValue("noiseThresholdEE_1.7", 9999.9);
  _params["noiseThresholdEE_1.8"]    = configFile->GetValue("noiseThresholdEE_1.8", 9999.9);
  _params["noiseThresholdEE_1.9"]    = configFile->GetValue("noiseThresholdEE_1.9", 9999.9);
  _params["noiseThresholdEE_2.0"]    = configFile->GetValue("noiseThresholdEE_2.0", 9999.9);
  _params["noiseThresholdEE_2.1"]    = configFile->GetValue("noiseThresholdEE_2.1", 9999.9);
  _params["noiseThresholdEE_2.2"]    = configFile->GetValue("noiseThresholdEE_2.2", 9999.9);
  _params["noiseThresholdEE_2.3"]    = configFile->GetValue("noiseThresholdEE_2.3", 9999.9);
  _params["noiseThresholdEE_2.4"]    = configFile->GetValue("noiseThresholdEE_2.4", 9999.9);
  _params["noiseThresholdEE_2.5"]    = configFile->GetValue("noiseThresholdEE_2.5", 9999.9);
  _params["noiseThresholdEE_2.6"]    = configFile->GetValue("noiseThresholdEE_2.6", 9999.9);
  _params["noiseThresholdEE_2.7"]    = configFile->GetValue("noiseThresholdEE_2.7", 9999.9);
  _params["noiseThresholdEE_2.8"]    = configFile->GetValue("noiseThresholdEE_2.8", 9999.9);
  _params["noiseThresholdEE_2.9"]    = configFile->GetValue("noiseThresholdEE_2.9", 9999.9);
  _params["noiseThresholdEE_3.0"]    = configFile->GetValue("noiseThresholdEE_3.0", 9999.9);
}

double ConfigManager::params(string name)
{
  if(_params.find(name) == _params.end()){
    cout<<"ERROR -- requested param "<<name<<" doesn't exist in the configuration"<<endl;
    return 0;
  }
  return _params.at(name);
}
