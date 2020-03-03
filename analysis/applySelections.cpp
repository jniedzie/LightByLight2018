//  applySelections.cpp
//
//  Created by Jeremi Niedziela on 16/01/2020.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/applySelections.md";
bool storeHLTtrees = false;

/// Check if this event is a good candidate for reco+ID efficiency estimation
bool IsGoodForRecoEfficiency(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3Trigger() && !event.HasSingleEG5Trigger()) return false;
  
  // Make sure that there are 2 tracks with opposite charges
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  if(event.GetPhysObjects(kGeneralTrack)[0]->GetCharge() ==
     event.GetPhysObjects(kGeneralTrack)[1]->GetCharge()) return false;
  
  // Check if there is at lest one photon and one electon in the event
  if(event.GetPhysObjects(kElectron).size() < 1) return false;
  if(event.GetPhysObjects(kPhoton).size() < 1) return false;
  
  return true;
}

/// Check if this event is a good candidate for reco+ID efficiency estimation
bool IsGoodForTrigger(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3Trigger() && !event.HasSingleEG5Trigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetPhysObjects(kElectron).size() < 2) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for HF veto efficiency estimation
bool IsGoodForHFveto(Event &event)
{
  // Check trigger
  if(!event.HasSingleEG3noHFvetoTrigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetPhysObjects(kElectron).size() < 2) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for exclusivity efficiency estimation
bool IsGoodForExclusivity(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check if there are at least two electrons
  if(event.GetPhysObjects(kElectron).size() < 2) return false;
  
  // Check exclusivity criteria
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsGoodForLbLsignal(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 0) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsGoodForQEDsignal(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsPassingLooseSelection(Event &event)
{
  // Check trigger
  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
//  if(event.HasAdditionalTowers()) return false;
//  if(event.GetPhysObjects(kGoodGeneralTrack).size() > 10) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsPassingAllLbLCuts(Event &event, bool doHighAco)
{
  // Check trigger
  //  if(!event.HasDoubleEG2Trigger()) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 0) return false;
  
  auto photons = event.GetPhysObjects(kGoodPhoton);
  if(photons.size() != 2) return false;
  
  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*photons[0], *photons[1]);
  if(diphoton.M() < 5.0) return false;
  if(diphoton.Pt() > 1.0) return false;
  
  double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
  
  if(doHighAco){
    if(aco < 0.01) return false;
  }
  else{
    if(aco > 0.01) return false;
  }
  
  return true;
}

/// Application starting point
int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 9 && argc != 5 && argc != 4){
    cout<<"This app requires 0, 1, 2 or 8 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPathReco outputPathTrigger outputPathHFveto outputPathExclusivity outputPathLbLsignal outputPathQEDsignal"<<endl;
    cout<<"or\n"<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPathLowAco outputPathHighAco"<<endl;
    cout<<"or\n"<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPath"<<endl;
    
    exit(0);
  }
  
  cout<<"Starting applySelections"<<endl;
  
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
  if(argc == 5){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]);
    outFilePaths.push_back(argv[4]);
  }
  if(argc == 4){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]);
  }
  
  config = ConfigManager(configPath);
  cout<<"Config manager created"<<endl;
  
  auto events = make_unique<EventProcessor>(inFilePath, outFilePaths);
  cout<<"Event processor created"<<endl;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    if(argc==9){
      if(IsGoodForRecoEfficiency(*event))     events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
      if(IsGoodForTrigger(*event))            events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
      if(IsGoodForHFveto(*event))             events->AddEventToOutputTree(iEvent, outFilePaths[2], storeHLTtrees);
      if(IsGoodForExclusivity(*event))        events->AddEventToOutputTree(iEvent, outFilePaths[3], storeHLTtrees);
      if(IsGoodForLbLsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[4], storeHLTtrees);
      if(IsGoodForQEDsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[5], storeHLTtrees);
    }
    else if(argc==5){
      if(IsPassingAllLbLCuts(*event, false))  events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
      if(IsPassingAllLbLCuts(*event, true))   events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
    }
    else if(argc==4){
      if(IsPassingLooseSelection(*event))     events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
    }
  }

  cout<<"Saving output trees"<<endl;
  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
  return 0;
}

