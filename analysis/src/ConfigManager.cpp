//  ConfigManager.cpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#include "ConfigManager.hpp"
#include "Logger.hpp"

ConfigManager config("init");

ConfigManager::ConfigManager(string path)
{
  if(path=="init") return;
  
  ifstream infile(path);
  
  string line;
  while (getline(infile, line)){
    if(line.find("#") != string::npos) continue;
    if(line.find("*") != string::npos) continue;
    
    if(line.find_first_not_of(' ') == string::npos) continue;
    
    stringstream lineStream(line);
    string key, value;
    
    getline(lineStream, key, ':');
    getline(lineStream, value);

    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
    value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
    
    _params[key] =  stod(value);
  }
}

double ConfigManager::params(string name)
{
  if(_params.find(name) == _params.end()){
    Log(0)<<"ERROR -- requested param "<<name<<" doesn't exist in the configuration\n";
    return 0;
  }
  return _params.at(name);
}
