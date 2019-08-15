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
  _params["electronMaxHoverEbarrel"]   = configFile->GetValue("electronMaxHoverEbarrel", 9999.9);
  _params["electronMaxHoverEendcap"]   = configFile->GetValue("electronMaxHoverEendcap", 9999.9);
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
}

double ConfigManager::params(string name)
{
  if(_params.find(name) == _params.end()){
    cout<<"ERROR -- requested param "<<name<<" doesn't exist in the configuration"<<endl;
    return 0;
  }
  return _params.at(name);
}
