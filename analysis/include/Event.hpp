//  Event.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef Event_hpp
#define Event_hpp

#include "Helpers.hpp"
#include "PhysObject.hpp"
#include "ConfigManager.hpp"

/// This class represents a single event with all its gen-level and reconstructed objects,
/// as well as triggers and other event-wide properties
class Event {
public:
  /// Default constructor
  Event();
  
  /// Default destructor
  ~Event();
  
  // Those return number of objects in this event:
  inline int GetNgenParticles()   const { return nGenParticles; }
  inline int GetNphotonSCs()      const { return nPhotonSCs; }
  inline int GetNcaloTowers()     const { return nCaloTowers; }
  inline int GetNgeneralTracks()  const { return nGeneralTracks; }
  inline int GetNelectrons()      const { return nElectrons; }
  
  // Those return i-th object in this event:
  inline shared_ptr<PhysObject> GetGenParticle(size_t iPart)    const { return genParticles[iPart]; }
  inline shared_ptr<PhysObject> GetPhotonSC(size_t iPhoton)     const { return photonSC[iPhoton]; }
  inline shared_ptr<PhysObject> GetCaloTower(size_t iTower)     const { return caloTowers[iTower]; }
  inline shared_ptr<PhysObject> GetGeneralTrack(size_t iTrack)  const { return generalTracks[iTrack]; }
  
  inline vector<shared_ptr<PhysObject>> GetPhotonSCs() const { return photonSC; }
  
  /// Returns vector of gen particles passing η and Et cuts specified in the config
  vector<shared_ptr<PhysObject>> GetGoodGenPhotons();
  
  /// Returns vector of photon superclusters passing η, Et and shower shape cuts specified in config
  vector<shared_ptr<PhysObject>> GetGoodPhotonSCs();
  
  /// Checks if there are towers above threshold not overlapping with reconstructed photons
  bool HasAdditionalTowers();
  
  /// Checks if there are any charged tracks in the event (above pt specified in config)
  bool HasChargedTracks();
  
  /// Returns true if any of the LbL triggers (as defined in Helpers.hpp) fired, false otherwise.
  bool HasLbLTrigger();
  
  
  
private:
  vector<int> triggersLbL; ///< Vactor of booleans corresponding to LbL triggers
  
  int nGenParticles = 0;                        ///< Number of gen particles
  vector<shared_ptr<PhysObject>> genParticles;  ///< Vector of gen particles
  
  int nPhotonSCs = 0;                           ///< Number of photon superclusters
  vector<shared_ptr<PhysObject>> photonSC;      ///< Vector of photon superclusters
  
  bool passingPhotonSCready = false;              ///< Were photon SC cuts already applied?
  vector<shared_ptr<PhysObject>> photonSCpassing; ///< Vector of photon superclusters passing cuts
  
  int nCaloTowers = 0;                          ///< Number of calorimeter towers
  vector<shared_ptr<PhysObject>> caloTowers;    ///< Vector of calorimeter tower
  
  int nGeneralTracks = 0;                       ///< Number of general tracks
  vector<shared_ptr<PhysObject>> generalTracks; ///< Vector of general tracks
  
  int nElectrons = 0;                           ///< Number of electrons
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
