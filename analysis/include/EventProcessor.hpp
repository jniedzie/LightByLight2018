//  EventProcessor.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef EventProcessor_hpp
#define EventProcessor_hpp

#include "Helpers.hpp"
#include "Event.hpp"

class EventProcessor {
public:
  /// Default constructor
  EventProcessor(string inFileName);
  
  /// Default destructor
  ~EventProcessor();
  
  inline long long GetNevents() const { return eventTree->GetEntries(); }
  
  Event GetEvent(int iEvent);
  
private:
  TTree *hltTree;
  TTree *eventTree;
  
  Event currentEvent;
};

#endif /* EventProcessor_hpp */
