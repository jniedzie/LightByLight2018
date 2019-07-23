//  EventProcessor.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "EventProcessor.hpp"

EventProcessor::EventProcessor(EDataset dataset) :
currentEvent(new Event())
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inFileNames[dataset].c_str());
  eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  hltTree   = (TTree*)inFile->Get("hltanalysis/HltTree");
  
  for(int iTrigger=0; iTrigger<triggerNamesLbL.size(); iTrigger++){
    hltTree->SetBranchAddress(triggerNamesLbL[iTrigger].c_str(), &currentEvent->triggersLbL[iTrigger]);
  }
  eventTree->SetBranchAddress("nMC"   , &currentEvent->nGenParticles);
  eventTree->SetBranchAddress("mcEta" , &mcEta);
  eventTree->SetBranchAddress("mcEt"  , &mcEt);
  eventTree->SetBranchAddress("mcPID" , &mcPID);
  
  eventTree->SetBranchAddress("nPho"          , &currentEvent->nPhotonSCs);
  eventTree->SetBranchAddress("phoSCEta"      , &photonSCEta);
  eventTree->SetBranchAddress("phoSCEt"       , &photonSCEt);
  eventTree->SetBranchAddress("phoSCPhiWidth" , &photonSCPhiWidth);

}

EventProcessor::~EventProcessor()
{
  
}

shared_ptr<Event> EventProcessor::GetEvent(int iEvent)
{
  // Move to desired entry in all trees
  hltTree->GetEntry(iEvent);
  eventTree->GetEntry(iEvent);
  
  // Clear and fill in collection of gen particles
  currentEvent->genParticles.clear();
  
  for(int iGenPart=0; iGenPart<currentEvent->nGenParticles; iGenPart++){
    auto genParticle = make_shared<PhysObject>();
    
    genParticle->eta   = mcEta->at(iGenPart);
    genParticle->et    = mcEt->at(iGenPart);
    genParticle->pdgID = mcPID->at(iGenPart);
    
    currentEvent->genParticles.push_back(genParticle);
  }
  
  // Clear and fill in collection of photon superclusters
  currentEvent->photonSC.clear();
  
  for(size_t iPhotonSC=0; iPhotonSC<currentEvent->nPhotonSCs; iPhotonSC++){
    auto photonSC = make_shared<PhysObject>();
    
    photonSC->eta      = photonSCEta->at(iPhotonSC);
    photonSC->et       = photonSCEt->at(iPhotonSC);
    photonSC->phiWidth = photonSCPhiWidth->at(iPhotonSC);
    
    currentEvent->photonSC.push_back(photonSC);
  }
  
  return currentEvent;
}
