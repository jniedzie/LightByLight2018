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
  
  params["maxEvents"]         = configFile->GetValue("maxEvents", 99999999.9);
  params["maxEta"]            = configFile->GetValue("maxEta", 10.0);
  params["minEt"]             = configFile->GetValue("minEt", 0.0);
  params["maxEtaWidthBarrel"] = configFile->GetValue("maxEtaWidthBarrel", 9999.9);
  params["maxEtaWidthEndcap"] = configFile->GetValue("maxEtaWidthEndcap", 9999.9);
  params["maxDeltaEtaEB"]     = configFile->GetValue("maxDeltaEtaEB", 9999.9);
  params["maxDeltaPhiEB"]     = configFile->GetValue("maxDeltaPhiEB", 9999.9);
  params["maxDeltaEtaEE"]     = configFile->GetValue("maxDeltaEtaEE", 9999.9);
  params["maxDeltaPhiEE"]     = configFile->GetValue("maxDeltaPhiEE", 9999.9);
  params["maxEtaEEtower"]     = configFile->GetValue("maxEtaEEtower", 9999.9);
  params["trackMinPt"]        = configFile->GetValue("trackMinPt", 0.0);
  params["diphotonMaxPt"]     = configFile->GetValue("diphotonMaxPt", 9999.9);
  params["maxDeltaR"]         = configFile->GetValue("maxDeltaR", 9999.9);

}
