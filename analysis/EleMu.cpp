//Based on applySelections.cpp

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies_eleNoIsolation_newThresholdsEta2p2.md";
bool storeHLTtrees = false;
bool storeZDCtrees = true;//ZDC tree
/// checks if event has muon and electron (opposite sign)
bool IsGoodForMuEle(Event &event)
{
  // Check trigger
  if(!(event.HasTrigger(kSingleMuOpenNoHF) or event.HasTrigger(kSingleEG3noHF)  or event.HasTrigger(kSingleEG5noHF))) return false;
  //if(!(event.HasTrigger(kSingleMuOpenNoHF) or event.HasTrigger(kSingleEG3noHF) or event.HasTrigger(kSingleEG5noHF) or event.HasTrigger(kDoubleEG2noHF))) return false;
  //if(!(event.HasTrigger(kSingleEG5noHF))) return false;
  //Check one eltron, one muon and two track should be in an event
  if(event.GetPhysObjects(EPhysObjType::kGoodElectron).size() != 1) return false;
  if(event.GetPhysObjects(EPhysObjType::kGoodMuon).size() != 1) return false;
  if(event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size() !=2) return false;
  if(event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]->GetCharge() ==
     event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]->GetCharge()) return false;
  
  //if(event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]->GetCharge() !=
    // event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0]->GetCharge()) return false;
  //if(event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]->GetCharge() !=
    // event.GetPhysObjects(EPhysObjType::kGeneralTrack)[1]->GetCharge()) return false;
  //if(event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0]->GetCharge() ==
    // event.GetPhysObjects(EPhysObjType::kGeneralTrack)[1]->GetCharge()) return false;

  
  //Exclusivity criteria
  if(event.HasAdditionalTowers()) return false;
   
  //Adding acoplanarity cut
 // double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
 //                                                  *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);
 // if(aco < 0.01 || aco > 0.4) return false;
  
  return true;
}
  

/// Application starting point

int main(int argc, char* argv[])
{
 if( argc != 5){

  //cout<<"This app requires 0, 1, 2 or 6 parameters"<<endl;
  cout<<"./getEfficienciesData configPath inputPath  outputPathMuEle datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;

  exit(0);

} 

 cout<<"Starting applySelections"<<endl;
 string inFilePath;
 vector<string> outFilePaths;
 string sampleName = "";

 if(argc == 5){

    configPath = argv[1];
    inFilePath = argv[2];
    outFilePaths.push_back(argv[3]); // MuEle
    sampleName = argv[4];

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
    if(iEvent%3000 == 0) cout<<"Processing event "<<iEvent<<endl; //counts the events from inputTree
    if(iEvent >= config.params("maxEvents")) break;
    auto event = events->GetEvent(iEvent);
  
    if(argc==5){
//      if(IsGoodForMuEle(*event))                events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
      if(IsGoodForMuEle(*event))                events->AddEventToOutputTree(iEvent, outFilePaths[0], storeZDCtrees);
   //     cout<<"test4"<<endl;
     
   
   }

 }


  cout<<"Saving output trees"<<endl;
  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
 return 0;
}


