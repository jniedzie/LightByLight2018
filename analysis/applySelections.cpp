//  applySelections.cpp
//
//  Created by Jeremi Niedziela on 16/01/2020.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

#include <iostream>
#include <fstream>
#include <string>

string configPath = "configs/efficiencies.md";
bool storeHLTtrees = true;

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
  bool checkHF = false;
  if(event.HasAdditionalTowers(checkHF)) return false;
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


/// checks if event has single muon
bool IsGoodForSingleMuon(Event &event)
{
  // Check trigger
  if(!event.HasSingleMuonTrigger()) return false;
    
  return true;
}

/// checks if event has muon and electron (opposite sign)
bool IsGoodForMuEle(Event &event)
{
  // Check trigger
  if(!event.HasSingleMuonTrigger()) return false; 
  // Check Electrons
  if(event.GetNelectrons() <1) return false;
  
  return true;
}

/// checks if event has di muon (opposite sign)
bool IsGoodForMuMu(Event &event)
{
  // Check trigger
  if(!event.HasSingleMuonTrigger()) return false; 
  // Check muons in the future
  if(event.GetNchargedTracks() != 2) return false;
  
  return true;
}




/// Application starting point
int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 9 && argc != 4){
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

/// read text file with arguments in lines 0 - 8
  if(argc == 4){
    std::string arg_1 = argv[1];
    std::string arg_2 = argv[2];
    std::string arg_3 = argv[3];
    if(arg_1 == "MuMu"){
    std::string tmp_configPath = "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/efficiencies.md";
    std::string tmp_inputPath = "/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/data_ntuples/HIForward/ntuples_data_new/200105_192027/000";
    std::string tmp_outputPath = "/eos/user/m/mnickel/TauTau/testdata/";
    std::string tmp_infilename = "/data_HiForestAOD_";
    std::string tmp_ending = arg_2 + "-" + arg_3 + ".root";
    std::string tmp_folder = std::to_string(std::stoi(arg_3)/1000);
    cout << "testing tmp_folder " << tmp_folder << "testing argv" << arg_1 << endl;
    vector<string> arg_list; 
    arg_list.push_back(tmp_outputPath + "data_reco" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_trigger" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_HF_veto" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_exclusivity" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_LbL_sig" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_QED_sig" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_sig_mu" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_muele" + tmp_ending);
    arg_list.push_back(tmp_outputPath + "data_mumu" + tmp_ending);
    configPath = tmp_configPath;
    inFilePath = tmp_inputPath + tmp_folder + tmp_infilename + tmp_ending;
    outFilePaths.push_back(arg_list[0]); // reco
    outFilePaths.push_back(arg_list[1]); // trigger
    outFilePaths.push_back(arg_list[2]); // HF veto
    outFilePaths.push_back(arg_list[3]); // exclusivity
    outFilePaths.push_back(arg_list[4]); // LbL signal extraction
    outFilePaths.push_back(arg_list[5]); // QED signal extraction
    outFilePaths.push_back(arg_list[6]); // single mu
    outFilePaths.push_back(arg_list[7]); // muon electron
    outFilePaths.push_back(arg_list[8]); // dimuon
    cout << "testing infile   " << inFilePath << "     testing outfile   " << arg_list[0] << endl;

    }
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
    if(IsGoodForSingleMuon(*event))        events->AddEventToOutputTree(iEvent, outFilePaths[6], storeHLTtrees);
    if(IsGoodForMuEle(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[7], storeHLTtrees);
    if(IsGoodForMuMu(*event))          events->AddEventToOutputTree(iEvent, outFilePaths[8], storeHLTtrees);

  }

  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
  return 0;
}

