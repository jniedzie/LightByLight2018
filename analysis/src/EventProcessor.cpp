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
  eventTree->SetBranchAddress("phoSCPhi"      , &photonSCPhi);
  eventTree->SetBranchAddress("phoSCEt"       , &photonSCEt);
  eventTree->SetBranchAddress("phoSCPhiWidth" , &photonSCPhiWidth);
  
  eventTree->SetBranchAddress("nTower"          , &currentEvent->nCaloTowers);
  eventTree->SetBranchAddress("CaloTower_hadE"  , &towerEnergyHad);
  eventTree->SetBranchAddress("CaloTower_emE"   , &towerEnergyEm);
  eventTree->SetBranchAddress("CaloTower_e"     , &towerEnergy);
  eventTree->SetBranchAddress("CaloTower_et"    , &towerEt);
  eventTree->SetBranchAddress("CaloTower_eta"   , &towerEta);
  eventTree->SetBranchAddress("CaloTower_phi"   , &towerPhi);
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
    photonSC->phi      = photonSCPhi->at(iPhotonSC);
    photonSC->et       = photonSCEt->at(iPhotonSC);
    photonSC->phiWidth = photonSCPhiWidth->at(iPhotonSC);
    
    currentEvent->photonSC.push_back(photonSC);
  }
  
  // Clear and fill in collection of calo towers
  currentEvent->caloTowers.clear();
  
  for(size_t iTower=0; iTower<currentEvent->nCaloTowers; iTower++){
    auto tower = make_shared<PhysObject>();
    
    tower->eta       = towerEta->at(iTower);
    tower->phi       = towerPhi->at(iTower);
    tower->energy    = towerEnergy->at(iTower);
    tower->et        = towerEt->at(iTower);
    tower->energyHad = towerEnergyHad->at(iTower);
    tower->energyEm  = towerEnergyEm->at(iTower);
    
    currentEvent->caloTowers.push_back(tower);
  }
  
  return currentEvent;
}
