//  EventProcessor.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "EventProcessor.hpp"

EventProcessor::EventProcessor(EDataset dataset) :
currentEvent(new Event())
{
  for(auto triggerName : triggerNamesLbL) triggersLbL.push_back(0);
  
  SetupBranches(inFileNames.at(dataset));
}

EventProcessor::EventProcessor(string inputPath) :
currentEvent(new Event())
{
  for(auto triggerName : triggerNamesLbL) triggersLbL.push_back(0);
  
  SetupBranches(inputPath);
}

EventProcessor::~EventProcessor()
{
  
}

void EventProcessor::SetupBranches(string inputPath)
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inputPath.c_str());
  eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  hltTree   = (TTree*)inFile->Get("hltanalysis/HltTree");
  
  for(int iTrigger=0; iTrigger<triggerNamesLbL.size(); iTrigger++){
    hltTree->SetBranchAddress(triggerNamesLbL[iTrigger].c_str(), &triggersLbL[iTrigger]);
  }
  eventTree->SetBranchAddress("nMC"   , &currentEvent->nGenParticles);
  eventTree->SetBranchAddress("mcEta" , &mcEta);
  eventTree->SetBranchAddress("mcPhi" , &mcPhi);
  eventTree->SetBranchAddress("mcEt"  , &mcEt);
  eventTree->SetBranchAddress("mcPID" , &mcPID);
  
  eventTree->SetBranchAddress("nPho"              , &currentEvent->nPhotons);
  eventTree->SetBranchAddress("phoHoverE"         , &photonHoverE);
  
  eventTree->SetBranchAddress("phoSCEta"          , &photonSCEta);
  eventTree->SetBranchAddress("phoSCPhi"          , &photonSCPhi);
  eventTree->SetBranchAddress("phoSCEt"           , &photonSCEt);
  eventTree->SetBranchAddress("phoSCE"            , &photonSCE);
  eventTree->SetBranchAddress("phoSCEtaWidth"     , &photonSCEtaWidth);
  eventTree->SetBranchAddress("phoSCPhiWidth"     , &photonSCPhiWidth);
  
  eventTree->SetBranchAddress("nTower"            , &currentEvent->nCaloTowers);
  eventTree->SetBranchAddress("CaloTower_hadE"    , &towerEnergyHad);
  eventTree->SetBranchAddress("CaloTower_emE"     , &towerEnergyEm);
  eventTree->SetBranchAddress("CaloTower_e"       , &towerEnergy);
  eventTree->SetBranchAddress("CaloTower_et"      , &towerEt);
  eventTree->SetBranchAddress("CaloTower_eta"     , &towerEta);
  eventTree->SetBranchAddress("CaloTower_phi"     , &towerPhi);
  
  eventTree->SetBranchAddress("ngenTrk"           , &currentEvent->nGeneralTracks);
  eventTree->SetBranchAddress("gentrkPt"          , &generalTrackPt);
  eventTree->SetBranchAddress("gentrkEta"         , &generalTrackEta);
  eventTree->SetBranchAddress("gentrkPhi"         , &generalTrackPhi);
  eventTree->SetBranchAddress("gentrkcharge"      , &generalTrackCharge);
  
  eventTree->SetBranchAddress("nEle"              , &currentEvent->nElectrons);
  eventTree->SetBranchAddress("eleCharge"         , &electronCharge);
  eventTree->SetBranchAddress("eleMissHits"       , &electronNmissing);
  eventTree->SetBranchAddress("elePt"             , &electronPt);
  eventTree->SetBranchAddress("eleEta"            , &electronEta);
  eventTree->SetBranchAddress("elePhi"            , &electronPhi);
  eventTree->SetBranchAddress("eleHoverE"         , &electronHoverE);
  eventTree->SetBranchAddress("elePFRelIsoWithEA" , &electronRelIsoWithEA);
  eventTree->SetBranchAddress("eledEtaAtVtx"      , &electronDetaSeed);
  eventTree->SetBranchAddress("eleSCEta"          , &electronSCEta);
  eventTree->SetBranchAddress("eleSCPhi"          , &electronSCPhi);
  eventTree->SetBranchAddress("eleSCEn"           , &electronSCEn);
}

shared_ptr<Event> EventProcessor::GetEvent(int iEvent)
{
  // Move to desired entry in all trees
  hltTree->GetEntry(iEvent);
  eventTree->GetEntry(iEvent);
  
  // Clear and fill in collection of gen particles
  currentEvent->genParticles.clear();
  
  for(int iTrigger=0; iTrigger<triggerNamesLbL.size(); iTrigger++){
    currentEvent->triggersLbL[triggerNamesLbL[iTrigger]] = triggersLbL[iTrigger];
  }
  
  for(int iGenPart=0; iGenPart<currentEvent->nGenParticles; iGenPart++){
    auto genParticle = make_shared<PhysObject>();
    
    genParticle->eta   = mcEta->at(iGenPart);
    genParticle->phi   = mcPhi->at(iGenPart);
    genParticle->et    = mcEt->at(iGenPart);
    genParticle->pdgID = mcPID->at(iGenPart);
    
    currentEvent->genParticles.push_back(genParticle);
  }
  
  // Clear and fill in collection of photon superclusters
  currentEvent->photons.clear();
  
  for(size_t iPhoton=0; iPhoton<currentEvent->nPhotons; iPhoton++){
    auto photon = make_shared<PhysObject>();
    
    photon->hOverE   = photonHoverE->at(iPhoton);
    photon->eta      = photonSCEta->at(iPhoton);
    photon->etaSC    = photonSCEta->at(iPhoton);
    photon->phi      = photonSCPhi->at(iPhoton);
    photon->phiSC    = photonSCPhi->at(iPhoton);
    photon->et       = photonSCEt->at(iPhoton);
    photon->pt       = photonSCEt->at(iPhoton);
    photon->energy   = photonSCE->at(iPhoton);
    photon->energySC = photonSCE->at(iPhoton);
    photon->etaWidth = photonSCEtaWidth->at(iPhoton);
    photon->phiWidth = photonSCPhiWidth->at(iPhoton);
    
    currentEvent->photons.push_back(photon);
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
  
  // Clear and fill in collection of general tracks
  currentEvent->generalTracks.clear();
  
  for(size_t iTrack=0; iTrack<currentEvent->nGeneralTracks; iTrack++){
    auto track = make_shared<PhysObject>();
    
    track->charge = generalTrackCharge->at(iTrack);
    track->pt     = generalTrackPt->at(iTrack);
    track->eta    = generalTrackEta->at(iTrack);
    track->phi    = generalTrackPhi->at(iTrack);
    
    currentEvent->generalTracks.push_back(track);
  }
  
  // Clear and fill in collection of electrons
  currentEvent->electrons.clear();
  
  for(size_t iElectron=0; iElectron<currentEvent->nElectrons; iElectron++){
    auto electron = make_shared<PhysObject>();
    
    electron->charge       = electronCharge->at(iElectron);
    electron->nMissingHits = electronNmissing->at(iElectron);
    electron->pt           = electronPt->at(iElectron);
    electron->eta          = electronEta->at(iElectron);
    electron->phi          = electronPhi->at(iElectron);
    electron->hOverE       = electronHoverE->at(iElectron);
    electron->relIsoWithEA = electronRelIsoWithEA->at(iElectron);
    electron->dEtaSeed     = electronDetaSeed->at(iElectron);
    electron->etaSC        = electronSCEta->at(iElectron);
    electron->phiSC        = electronSCPhi->at(iElectron);
    electron->energySC     = electronSCEn->at(iElectron);
    
    currentEvent->electrons.push_back(electron);
  }
  
  return currentEvent;
}
