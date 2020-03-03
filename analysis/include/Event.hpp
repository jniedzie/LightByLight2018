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
  
  void Reset();
  
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
  
  // Check if triggers fired
  bool HasSingleEG3Trigger()          const;
  bool HasSingleEG5Trigger()          const;
  bool HasDoubleEG2Trigger()          const;
  bool HasSingleEG3noHFvetoTrigger()  const;
 
  /// Checks if UPC Single Mu Open fired
  bool HasSingleMuonTrigger() const;
 
  
  /// Sorts calo towers by energy, from highest to lowest
  void SortCaloTowersByEnergy();
  
  /// Returns map of towers by subdetector which are above threshold and do not overlap with good photons nor electrons
  map<ECaloType, PhysObjects> GetCaloTowersAboveThresholdByDet();

private:
  map<string, bool> triggersLbL; ///< Vactor of booleans corresponding to LbL triggers
  
  
  map<EPhysObjType, PhysObjects> physObjects;      ///< Map of physics objects in the event
  map<EPhysObjType, bool>        physObjectsReady; ///< Is collection ready?
  
  
  /// Updates and returns vector of objects passing selections
  PhysObjects GetGoodGenPhotons() const;
  PhysObjects GetGoodPhotons();
  PhysObjects GetGoodElectrons(TH1D *cutFlowHist=nullptr);
  PhysObjects GetGoodMuons(TH1D *cutFlowHist=nullptr);
  PhysObjects GetGoodMatchedElectron();
  PhysObjects GetGoodGeneralTracks(TH1D *cutFlowHist=nullptr);
  
  /// Checks if given tower overlaps with one of the photons passing selections
  bool IsOverlappingWithGoodPhoton(const PhysObject &tower);
  
  /// Checks if given tower overlaps with one of the electrons passing selections
  bool IsOverlappingWithGoodElectron(const PhysObject &tower);
  
  /// Returns noise threshold for given tower in EM calos
  double GetEmThresholdForTower(const PhysObject &tower);
  
  friend class EventProcessor;
};

#endif /* Event_hpp */
