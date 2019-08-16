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
  inline int GetNgenParticles()   const { return nGenParticles;   }
  inline int GetNphotons()        const { return nPhotons;        }
  inline int GetNelectrons()      const { return nElectrons;      }
  inline int GetNcaloTowers()     const { return nCaloTowers;     }
  inline int GetNgeneralTracks()  const { return nGeneralTracks;  }
  
  // Those return i-th object in this event:
  inline shared_ptr<PhysObject> GetGenParticle(size_t i)  const { return genParticles[i];  }
  inline shared_ptr<PhysObject> GetPhoton(size_t i)       const { return photons[i];       }
  inline shared_ptr<PhysObject> GetElectron(size_t i)     const { return generalTracks[i]; }
  inline shared_ptr<PhysObject> GetCaloTower(size_t i)    const { return caloTowers[i];    }
  inline shared_ptr<PhysObject> GetGeneralTrack(size_t i) const { return generalTracks[i]; }
  
  
  inline vector<shared_ptr<PhysObject>> GetPhotons()      const { return photons;     }
  inline vector<shared_ptr<PhysObject>> GetElectrons()    const { return electrons;   }
  inline vector<shared_ptr<PhysObject>> GetCaloTowers()   const { return caloTowers;  }
  
  /// Returns vector of gen particles passing η and Et cuts specified in the config
  vector<shared_ptr<PhysObject>> GetGoodGenPhotons() const;
  
  /// Updates and returns vector of photons passing all photon ID cuts
  vector<shared_ptr<PhysObject>> GetGoodPhotons();
  
  /// Updates and returns vector of electrons passing all electron ID cuts
  vector<shared_ptr<PhysObject>> GetGoodElectrons();
  
  /// Finds two photons passing cuts (if not done yet) and returns diphoton invariant mass
  double GetDiphotonInvMass();
  
  /// Finds two photons passing cuts (if not done yet) and returns false if diphoton pt is
  /// within limit specified in config, or true otherwise
  bool DiphotonPtAboveThreshold();
  
  /// Finds two photons passing cuts (if not done yet) and checks if there are towers above
  /// threshold not overlapping with reconstructed photons
  bool HasAdditionalTowers();
  
  /// Checks if there are any charged tracks in the event (above pt specified in config)
  bool HasChargedTracks() const;
  
  /// Returns number of charged tracks with pt above threshold specifined in the config
  int GetNchargedTracks() const;
  
  /// Checks if SingleEG3 fired
  bool HasSingleEG3Trigger() const;
  
  /// Checks if SingleEG5 fired
  bool HasSingleEG5Trigger() const ;
  
  /// Checks if DoubleEG2 fired
  bool HasDoubleEG2Trigger() const;
  
  
private:
  map<string, bool> triggersLbL; ///< Vactor of booleans corresponding to LbL triggers
  
  int nGenParticles = 0;                        ///< Number of gen particles
  vector<shared_ptr<PhysObject>> genParticles;  ///< Vector of gen particles
  
  int nPhotons = 0;                             ///< Number of photon superclusters
  vector<shared_ptr<PhysObject>> photons;       ///< Vector of photon superclusters
  
  bool goodPhotonsReady = false;                ///< Were photon cuts already applied?
  vector<shared_ptr<PhysObject>> goodPhotons;   ///< Vector of photons passing cuts
  
  int nCaloTowers = 0;                          ///< Number of calorimeter towers
  vector<shared_ptr<PhysObject>> caloTowers;    ///< Vector of calorimeter tower
  
  int nGeneralTracks = 0;                       ///< Number of general tracks
  vector<shared_ptr<PhysObject>> generalTracks; ///< Vector of general tracks
  
  int nElectrons = 0;                           ///< Number of electrons
  vector<shared_ptr<PhysObject>> electrons;     ///< Vector of electrons
  
  bool goodElectronsReady = false;              ///< Were electron cuts already applied?
  vector<shared_ptr<PhysObject>> goodElectrons; ///< Vector of electrons passing cuts
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
