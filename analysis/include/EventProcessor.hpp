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
  EventProcessor(TTree *_hltTree, TTree *_eventTree);
  
  /// Default destructor
  ~EventProcessor();
  
  Event GetEvent(int iEvent);
  
private:
  TTree *hltTree;
  TTree *eventTree;
  
  Event currentEvent;
};

#endif /* EventProcessor_hpp */
