//  ConfigManager.hpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#ifndef ConfigManager_hpp
#define ConfigManager_hpp

#include "Helpers.hpp"

struct ConfigManager;
extern ConfigManager config;

/// Wrapper on a config file that provides access to options from the code.
/// Reads a config file in text/markdown format.
struct ConfigManager {
  /// Default constructor
  /// \param path Path to the config file
  ConfigManager(string path="");
  
  /// Returns value of given parameter from the config file. Prints and error and returns 0
  /// if parameter could not be found.
  double params(string name="");
  
  string outputPath;  ///< Output file path
  
private:
  map<string, double> _params; ///< All bool, int and double parameters from the config file
};

#endif /* ConfigManager_hpp */
