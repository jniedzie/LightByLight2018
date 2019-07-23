//  EventProcessor.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef EventProcessor_hpp
#define EventProcessor_hpp

#include "Helpers.hpp"
#include "Event.hpp"

/// This class keeps a link to input ROOT trees and creates Event class objects when moving
/// to next event.
class EventProcessor {
public:
  /// Default constructor.
  /// \param dataset Determines which events will be kept here (data, MC lbl, MC cep etc.)
  EventProcessor(EDataset dataset);
  
  /// Default destructor
  ~EventProcessor();
  
  /// Returns number of events
  inline long long GetNevents() const { return eventTree->GetEntries(); }
  
  /// Returns Event object for given tree entry index
  shared_ptr<Event> GetEvent(int iEvent);
  
private:
  TTree *hltTree;   ///< Pointer to the hlt tree
  TTree *eventTree; ///< Pointer to the event tree
  
  shared_ptr<Event> currentEvent; ///< Pointer to the current event
  
  // Handles to variables stored in ntuple trees
  vector<double> *mcEta = nullptr;
  vector<double> *mcEt  = nullptr;
  vector<double> *mcPID = nullptr;
  
  vector<double> *photonSCEta      = nullptr;
  vector<double> *photonSCPhi      = nullptr;
  vector<double> *photonSCEt       = nullptr;
  vector<double> *photonSCPhiWidth = nullptr;
  
  vector<double> *towerEta       = nullptr;
  vector<double> *towerPhi       = nullptr;
  vector<double> *towerEnergy    = nullptr;
  vector<double> *towerEt        = nullptr;
  vector<double> *towerEnergyHad = nullptr;
  vector<double> *towerEnergyEm  = nullptr;
};

#endif /* EventProcessor_hpp */
