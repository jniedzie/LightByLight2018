//  Event.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Event.hpp"

Event::Event()
{
  for(auto triggerName : triggerNamesLbL) triggersLbL.push_back(0);
}

Event::~Event()
{
  
}

bool Event::HasLbLTrigger()
{
  for(int trigger : triggersLbL){
    if(trigger != 0) return true;
  }
  return false;
}
