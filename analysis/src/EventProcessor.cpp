//  EventProcessor.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "EventProcessor.hpp"

EventProcessor::EventProcessor(string inFileName)
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inFileName.c_str());
  eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  hltTree   = (TTree*)inFile->Get("hltanalysis/HltTree");
  
  for(int iTrigger=0; iTrigger<triggerNamesLbL.size(); iTrigger++){
    hltTree->SetBranchAddress(triggerNamesLbL[iTrigger].c_str(), &currentEvent.triggersLbL[iTrigger]);
  }
  eventTree->SetBranchAddress("nMC"   , &currentEvent.nGenPhotons);
  eventTree->SetBranchAddress("mcEta" , &currentEvent.genEta);
  eventTree->SetBranchAddress("mcEt"  , &currentEvent.genEt);
  
  eventTree->SetBranchAddress("nPho"    , &currentEvent.nRecPhotonSCs);
  eventTree->SetBranchAddress("phoSCEta", &currentEvent.photonSCEta);
  eventTree->SetBranchAddress("phoSCEt" , &currentEvent.photonSCEt);

}

EventProcessor::~EventProcessor()
{
  
}

Event EventProcessor::GetEvent(int iEvent)
{
  hltTree->GetEntry(iEvent);
  eventTree->GetEntry(iEvent);
  
  return currentEvent;
}
