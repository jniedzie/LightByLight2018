//  applySelections.cpp
//
//  Created by Jeremi Niedziela on 16/01/2020.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies.md";
bool storeHLTtrees = false;

/// Check if this event is a good candidate for reco+ID efficiency estimation
bool IsGoodForRecoEfficiency(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3Trigger() && !event.HasSingleEG5Trigger()) return false;
  
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
  if(!event.HasSingleEG3Trigger() && !event.HasSingleEG5Trigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetNelectrons() < 2) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for HF veto efficiency estimation
bool IsGoodForHFveto(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3noHFvetoTrigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetNelectrons() < 2) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for exclusivity efficiency estimation
bool IsGoodForExclusivity(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetNelectrons() < 2) return false;
  
  // Check exclusivity criteria
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsGoodForLbLsignal(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetNchargedTracks() != 0) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsGoodForQEDsignal(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}

/// Application starting point
int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 9){
    cout<<"This app requires 0 or 8 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPathReco outputPathTrigger outputPathHFveto outputPathExclusivity outputPathLbLsignal outputPathQEDsignal"<<endl;
    exit(0);
  }
  
  string inFilePath;
  vector<string> outFilePaths;
  
  if(argc == 9){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]); // reco
    outFilePaths.push_back(argv[4]); // trigger
    outFilePaths.push_back(argv[5]); // HF veto
    outFilePaths.push_back(argv[6]); // exclusivity
    outFilePaths.push_back(argv[7]); // LbL signal extraction
    outFilePaths.push_back(argv[8]); // QED signal extraction
  }
 
  config = ConfigManager(configPath);
  auto events = make_unique<EventProcessor>(inFilePath, outFilePaths);
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    if(IsGoodForRecoEfficiency(*event))     events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
    if(IsGoodForTrigger(*event))            events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
    if(IsGoodForHFveto(*event))             events->AddEventToOutputTree(iEvent, outFilePaths[2], storeHLTtrees);
    if(IsGoodForExclusivity(*event))        events->AddEventToOutputTree(iEvent, outFilePaths[3], storeHLTtrees);
    if(IsGoodForLbLsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[4], storeHLTtrees);
    if(IsGoodForQEDsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[5], storeHLTtrees);
  }

  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
  return 0;
}

