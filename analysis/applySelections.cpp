  
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
  if(!event.HasTrigger(kSingleEG3noHF) && !event.HasTrigger(kSingleEG5noHF)) return false;
  
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
  if(!event.HasTrigger(kSingleEG3noHF) && !event.HasTrigger(kSingleEG5noHF)) return false;
  
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
  if(!event.HasTrigger(kSingleEG3singleTrack)) return false;
  
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
  if(!event.HasTrigger(kDoubleEG2noHF)) return false;
  
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
  if(!event.HasTrigger(kDoubleEG2noHF)) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 0) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsGoodForQEDsignal(Event &event)
{
  // Check trigger
  if(!event.HasTrigger(kDoubleEG2noHF)) return false;
  
  // Check exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsPassingLooseSelection(Event &event)
{
  // Check trigger
  if(!event.HasTrigger(kDoubleEG2noHF)) return false;
  
  // Check exclusivity criteria
  //  if(event.HasAdditionalTowers()) return false;
  //  if(event.GetPhysObjects(kGoodGeneralTrack).size() > 10) return false;
  
  return true;
}

/// Check if this event is a good candidate for the signal extraction
bool IsPassingAllLbLCuts(Event &event, bool doHighAco)
{
  // Check trigger
  //  if(!event.HasTrigger(kDoubleEG2noHF)) return false;
  
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


/// checks if event has single muon SET TO RETURN FALSE
bool IsGoodForSingleMuon(Event &event)
{
  // Check trigger
  if(!event.HasTrigger(kSingleMuOpenNoHF)) return false;
  
  return false;
}

/// checks if event has muon and electron (opposite sign)
bool IsGoodForMuEle(Event &event)
{
  // Check trigger
  if(!event.HasTrigger(kSingleMuOpenNoHF)) return false;
  // Check Electrons
  if(event.GetPhysObjects(kElectron).size() != 1) return false;
  if(event.GetPhysObjects(kMuon).size() != 1) return false;
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return false;
  if(event.GetPhysObjects(kMuon)[0]->GetCharge() ==
     event.GetPhysObjects(kElectron)[0]->GetCharge()) return false;
  
  return true;
}

/// checks if event has di muon (opposite sign)
bool IsGoodForMuMu(Event &event)
{
  // Check trigger
  if(!event.HasTrigger(kSingleMuOpenNoHF)) return false;
  if(event.GetPhysObjects(kMuon).size() != 2) return false;
  if(event.GetPhysObjects(kGeneralTrack).size() != 2 ) return false;
  if(event.GetPhysObjects(kMuon)[0]->GetCharge() ==
     event.GetPhysObjects(kMuon)[1]->GetCharge()) return false;
  
  return true;
}




/// Application starting point
int main(int argc, char* argv[])
{
  if(argc != 2 && argc != 10 && argc != 6 && argc != 5 && argc != 4){
    cout<<"This app requires 0, 1, 2 or 8 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPathReco outputPathTrigger outputPathHFveto outputPathExclusivity outputPathLbLsignal outputPathQEDsignal datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;
    cout<<"or\n"<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPathLowAco outputPathHighAco datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;
    cout<<"or\n"<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;
    cout<<"or\n"<<endl;
    cout<<"./getEfficienciesData flag setupFilePath datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl; // setupFile contains all paths for configs, input and outputs
    
    exit(0);
  }
  
  cout<<"Starting applySelections"<<endl;
  
  string inFilePath;
  vector<string> outFilePaths;
  string sampleName = "";
  
  if(argc == 10){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]); // reco
    outFilePaths.push_back(argv[4]); // trigger
    outFilePaths.push_back(argv[5]); // HF veto
    outFilePaths.push_back(argv[6]); // exclusivity
    outFilePaths.push_back(argv[7]); // LbL signal extraction
    outFilePaths.push_back(argv[8]); // QED signal extraction
    sampleName = argv[9];
  }
  
  if(argc == 6){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]);
    outFilePaths.push_back(argv[4]);
    sampleName = argv[5];
  }
  
  if(argc == 5){
    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]);
    sampleName = argv[4];
  }
  
  if(argc == 4){
    string flag = argv[1];
    string setupFilePath = argv[2];
    sampleName = argv[3];
    if(flag == "TauTau"){
      vector<string> argList;
      ifstream file(setupFilePath);
      string str;
      while(getline(file, str)){
        argList.push_back(str);
      }
      configPath = argList[0];
      inFilePath = argList[1];
      outFilePaths.push_back(argList[2]); // single mu
      outFilePaths.push_back(argList[3]); // muon electron
      outFilePaths.push_back(argList[4]); // dimuon
    }
  }
  
  EDataset dataset = nDatasets;
  if(sampleName == "Data")    dataset = kData;
  if(sampleName == "QED_SC")  dataset = kMCqedSC;
  if(sampleName == "QED_SL")  dataset = kMCqedSL;
  if(sampleName == "LbL")     dataset = kMClbl;
  if(sampleName == "CEP")     dataset = kMCcep;
  
  config = ConfigManager(configPath);
  cout<<"Config manager created"<<endl;
  
  auto events = make_unique<EventProcessor>(inFilePath, dataset, outFilePaths);
  cout<<"Event processor created"<<endl;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    if(argc==10){
      if(IsGoodForRecoEfficiency(*event))     events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
      if(IsGoodForTrigger(*event))            events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
      if(IsGoodForHFveto(*event))             events->AddEventToOutputTree(iEvent, outFilePaths[2], storeHLTtrees);
      if(IsGoodForExclusivity(*event))        events->AddEventToOutputTree(iEvent, outFilePaths[3], storeHLTtrees);
      if(IsGoodForLbLsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[4], storeHLTtrees);
      if(IsGoodForQEDsignal(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[5], storeHLTtrees);
    }
    else if(argc==6){
      if(IsPassingAllLbLCuts(*event, false))  events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
      if(IsPassingAllLbLCuts(*event, true))   events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
    }
    else if(argc==5){
      if(IsPassingLooseSelection(*event))     events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
    }
    else if(argc==4){
      string flag = argv[1];
      if(flag == "TauTau"){
        if(IsGoodForSingleMuon(*event))       events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
        if(IsGoodForMuEle(*event))            events->AddEventToOutputTree(iEvent, outFilePaths[1], storeHLTtrees);
        if(IsGoodForMuMu(*event))             events->AddEventToOutputTree(iEvent, outFilePaths[2], storeHLTtrees);
      }
    }
  }
  
  cout<<"Saving output trees"<<endl;
  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
  return 0;
}