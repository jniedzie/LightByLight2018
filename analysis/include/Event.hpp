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
  
  /// Removes all physics objects from the event, resets all flags
  void Reset();
  
  /// Returns a vector of physics objects
  /// \param type Defines which type of physics objects to return (as defined in Helpers.hpp)
  /// \param cutFlowHist Optional. Will be filled in case selections are applied to get requested
  /// type and they have not been applied before for this event
  PhysObjects GetPhysObjects(EPhysObjType type, TH1D *cutFlowHist=nullptr);

  /// Check if there are calo towers above noise threshold. In ECal they must not overlap with
  /// photons nor electrons passing ID selections. Returns true as soon as the first tower above
  /// the threshold is found.
  bool HasAdditionalTowers();
  
  /// Check if there are calo towers above noise threshold. In ECal they must not overlap with
  /// photons nor electrons passing ID selections. Continues to loop over towers even after the
  /// first tower above the noise threshold is found.
  /// \param failingCalo A map of bool values that will be filled, indicating which sub-detectors
  /// contained towers above noise threshold
  bool HasAdditionalTowers(map<ECaloType, bool> &failingCalo);
  
  /// Checks if given trigger fired in the event
  /// \param trigger Trigger to check, as defined in Helpers.hpp
  bool HasTrigger(ETrigger trigger) const;
 
  /// Sorts calo towers by energy, from highest to lowest
  void SortCaloTowersByEnergy();
  
  /// Returns map of towers by subdetector which are above threshold and do not overlap with good photons nor electrons
  map<ECaloType, PhysObjects> GetCaloTowersAboveThresholdByDet();

  /// Checks if given tower overlaps with one of the photons passing selections
  bool IsOverlappingWithGoodPhoton(const PhysObject &tower);
  
  /// Checks if given tower overlaps with one of the electrons passing selections
  bool IsOverlappingWithGoodElectron(const PhysObject &tower);
  
  inline uint      GetRunNumber()   const { return runNumber;   }
  inline uint      GetLumiSection() const { return lumiSection; }
  inline ULong64_t GetEventNumber() const { return eventNumber; }
  
  inline int GetNdisplacedTracks()  const { return nDisplacedTracks;}
  inline int GetNpixelClusters()    const { return nPixelClusters;  }
  inline int GetNpixelRecHits()     const { return nPixelRecHits;   }
  inline int GetNdedxHits()         const { return nDedxHits;       }
  
private:
  map<ETrigger, bool> triggerValues; ///< Vactor of booleans corresponding to LbL triggers
  
  map<EPhysObjType, PhysObjects> physObjects;      ///< Map of physics objects in the event
  map<EPhysObjType, bool>        physObjectsReady; ///< Is collection ready?
  
  /// Updates and returns vector of objects passing selections
  PhysObjects GetGoodGenPhotons() const;
  PhysObjects GetPhotonsInAcceptance();
  PhysObjects GetGoodPhotons();
  PhysObjects GetGoodElectrons(TH1D *cutFlowHist=nullptr);
  PhysObjects GetGoodMuons(TH1D *cutFlowHist=nullptr);
  PhysObjects GetGoodMatchedElectron();
  PhysObjects GetGoodGeneralTracks(TH1D *cutFlowHist=nullptr);
  PhysObjects GetGoodPixelTracks(TH1D *cutFlowHist=nullptr);
  
  /// Returns noise threshold for given tower in EM calos
  double GetEmThresholdForTower(const PhysObject &tower);
  
  EDataset dataset;
  
  int nDisplacedTracks;
  int nPixelClusters;
  int nPixelRecHits;
  int nDedxHits;
  
  uint runNumber;
  uint lumiSection;
  ULong64_t eventNumber;
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
