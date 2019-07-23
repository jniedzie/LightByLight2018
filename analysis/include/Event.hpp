//  Event.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef Event_hpp
#define Event_hpp

#include "Helpers.hpp"
#include "PhysObject.hpp"

/// This class represents a single event with all its gen-level and reconstructed objects,
/// as well as triggers and other event-wide properties
class Event {
public:
  /// Default constructor
  Event();
  
  /// Copy constructor
  Event(const Event &e);
  
  /// Default destructor
  ~Event();
  
  /// Returns number of gen-level particles in this event
  inline int GetNgenParticles() const { return nGenParticles; }
  
  /// Returns number of photon superclusters in this event
  inline int GetNphotonSCs()  const { return nPhotonSCs; }
  
  /// Returns i-th gen particle
  inline shared_ptr<PhysObject> GetGenParticle(size_t iPart) const { return genParticles[iPart]; }
  
  /// Returns i-th photon supercluster
  inline shared_ptr<PhysObject> GetPhotonSC(size_t iPhoton)  const { return photonSC[iPhoton]; }
  
  /// Returns true if any of the LbL triggers (as defined in Helpers.hpp) fired, false otherwise.
  bool HasLbLTrigger();
  
private:
  vector<int> triggersLbL; ///< Vactor of booleans corresponding to LbL triggers
  
  int nGenParticles = 0; ///< Number of gen particles in this event
  vector<shared_ptr<PhysObject>> genParticles; ///< Vector of gen particles in this event
  
  int nPhotonSCs = 0; ///< Number of photon superclusters in this event
  vector<shared_ptr<PhysObject>> photonSC; ///< Vector of photon superclusters in this event
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
