//  Logger.hpp
//
//  Created by Jeremi Niedziela on 06/03/2020.

#ifndef Logger_hpp
#define Logger_hpp

#include "ConfigManager.hpp"

class Log {
public:
  Log(int _level) : level(_level) {}
  
  template <class T>
  Log &operator<<(const T &v){
    if(config.params("verbosityLevel",true) >= level) cout << v;
    return *this;
  }
  
  ~Log() {}
  
private:
  int level;
};

#endif /* Logger_hpp */
