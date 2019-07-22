//  Event.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef Event_hpp
#define Event_hpp

#include "Helpers.hpp"

class Event {
public:
  /// Default constructor
  Event();
  
  /// Default destructor
  ~Event();
  
  inline int    GetNgenPhotons()              const { return nGenPhotons; }
  inline double GetGenPhotonEta(int iPhoton)  const { return genEta->at(iPhoton); }
  inline double GetGenPhotonEt(int iPhoton)   const { return genEt->at(iPhoton); }
  
  inline int    GetNphotonSCs()               const { return nRecPhotonSCs; }
  inline double GetPhotonSCeta(int iPhoton)   const { return photonSCEta->at(iPhoton); }
  inline double GetPhotonSCet(int iPhoton)    const { return photonSCEt->at(iPhoton); }
  
  bool HasLbLTrigger();
  
private:
  vector<int> triggersLbL;
  
  int nGenPhotons = 0;
  vector<double> *genEta = nullptr;
  vector<double> *genEt = nullptr;
  
  int nRecPhotonSCs = 0;
  vector<double> *photonSCEta = nullptr;
  vector<double> *photonSCEt = nullptr;
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
