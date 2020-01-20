//  applySelections.cpp
//
//  Created by Jeremi Niedziela on 16/01/2020.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies.md";

string inFilePath   = "ntuples/ntuples_mc_qed_withSingleEG3.root";
string outFilePath  = "ntuples/ntuples_mc_qed_triggerEffEvents.root";

/// Check if this event is a good candidate for reco+ID efficiency estimation
bool IsGoodForRecoEfficiency(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return false;
  
  // Make sure that there are 2 tracks with opposite charges
  if(event.GetNgeneralTracks() != 2) return false;
  if(event.GetGeneralTrack(0)->GetCharge() == event.GetGeneralTrack(1)->GetCharge()) return false;
  
  // Check if there is at lest one photon and one electon in the event
  if(event.GetNelectrons() < 1) return false;
  if(event.GetNphotons() < 1) return false;
  
  return true;
}

/// Check if this event is a good candidate for reco+ID efficiency estimation
bool IsGoodForTrigger(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetNelectrons() < 2) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}

/// Application starting point
int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 4){
    cout<<"This app requires 0 or 3 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPath"<<endl;
    exit(0);
  }
  if(argc == 4){
    configPath    = argv[1];
    inFilePath    = argv[2];
    outFilePath   = argv[3];
  }
 
  config = ConfigManager(configPath);
  auto events = make_unique<EventProcessor>(inFilePath, outFilePath);
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
    
    auto event = events->GetEvent(iEvent);
//    if(IsGoodForRecoEfficiency(*event)) events->AddEventToOutputTree(iEvent);
    if(IsGoodForTrigger(*event)) events->AddEventToOutputTree(iEvent);
  }

  events->SaveOutputTree();
  
  return 0;
}

