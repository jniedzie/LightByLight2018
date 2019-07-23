//  ConfigManager.hpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#ifndef ConfigManager_hpp
#define ConfigManager_hpp

#include "Helpers.hpp"

struct ConfigManager;
extern ConfigManager config;

/// Wrapper on a config file that provides access to options from the code.
/// Reads a config file in markdown format. For all options that are not specified in the config
/// default values will be used.
struct ConfigManager {
  /// Default constructor
  /// \param _path Path to the config file
  ConfigManager(string _path="");
  
  map<string, double> params; ///< All bool, int and double parameters from the config file
  
  string outputPath;  ///< Output file path
  
private:
  unique_ptr<TEnv> configFile;
};

#endif /* ConfigManager_hpp */
