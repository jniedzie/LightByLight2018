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
string outFilePath  = "ntuples/ntuples_mc_qed_recoEffEvents.root";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  //  kData,
  kMCqedSC_SingleEG3,
  //  kMCqedSC,
  //  kMCqedSL
};

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

/// Application starting point
int main(int argc, char* argv[])
{
  config = ConfigManager(configPath);
  
  auto events = make_unique<EventProcessor>(inFilePath, outFilePath);
    
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
    
    auto event = events->GetEvent(iEvent);
    if(IsGoodForRecoEfficiency(*event)) events->AddEventToOutputTree(iEvent);
  }

  events->SaveOutputTree();
  
  return 0;
}

