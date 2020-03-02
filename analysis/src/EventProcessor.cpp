//  EventProcessor.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"

EventProcessor::EventProcessor(string inputPath, vector<string> outputPaths) :
currentEvent(new Event())
{
  for(auto triggerName : triggerNamesLbL) triggersLbL.push_back(0);
  SetupBranches(inputPath, outputPaths);
}

EventProcessor::~EventProcessor()
{
  
}

void EventProcessor::SetupBranches(string inputPath, vector<string> outputPaths)
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inputPath.c_str());
  eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  hltTree   = (TTree*)inFile->Get("hltanalysis/HltTree");
  l1Tree    = (TTree*)inFile->Get("l1object/L1UpgradeFlatTree");
  
  for(string outputPath : outputPaths) SetupOutputTree(outputPath);
  
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
//  eventTree->SetBranchAddress("phoSigmaIEtaIEta"  , &photonSCEtaWidth);
  eventTree->SetBranchAddress("phoSCPhiWidth"     , &photonSCPhiWidth);
  
  eventTree->SetBranchAddress("phoMaxEnergyXtal"  , &photonEmax);
  eventTree->SetBranchAddress("phoETop"           , &photonEtop);
  eventTree->SetBranchAddress("phoEBottom"        , &photonEbottom);
  eventTree->SetBranchAddress("phoELeft"          , &photonEleft);
  eventTree->SetBranchAddress("phoERight"         , &photonEright);
  
  eventTree->SetBranchAddress("nTower"            , &currentEvent->nCaloTowers);
  eventTree->SetBranchAddress("CaloTower_hadE"    , &towerEnergyHad);
  eventTree->SetBranchAddress("CaloTower_emE"     , &towerEnergyEm);
  eventTree->SetBranchAddress("CaloTower_e"       , &towerEnergy);
  eventTree->SetBranchAddress("CaloTower_et"      , &towerEt);
  eventTree->SetBranchAddress("CaloTower_eta"     , &towerEta);
  eventTree->SetBranchAddress("CaloTower_phi"     , &towerPhi);
  
  eventTree->SetBranchAddress("nTrk"              , &currentEvent->nGeneralTracks);
  eventTree->SetBranchAddress("trkPt"             , &generalTrackPt);
  eventTree->SetBranchAddress("trkEta"            , &generalTrackEta);
  eventTree->SetBranchAddress("trkPhi"            , &generalTrackPhi);
  eventTree->SetBranchAddress("trkcharge"         , &generalTrackCharge);
  eventTree->SetBranchAddress("trkValidHits"      , &generalTrackValidHits);
  eventTree->SetBranchAddress("trkMissHits"       , &generalTrackMissingHits);
  
  eventTree->SetBranchAddress("trkPurity"         , &generalTrackPurity);
  eventTree->SetBranchAddress("trknormchi2"       , &generalTrackChi2);
  eventTree->SetBranchAddress("trkdxy"            , &generalTrackDxy);
  eventTree->SetBranchAddress("trkdz"             , &generalTrackDz);
  eventTree->SetBranchAddress("trkdxyError"       , &generalTrackDxyErr);
  eventTree->SetBranchAddress("trkdzError"        , &generalTrackDzErr);
  eventTree->SetBranchAddress("trkvx"             , &generalTrackVertexX);
  eventTree->SetBranchAddress("trkvy"             , &generalTrackVertexY);
  eventTree->SetBranchAddress("trkvz"             , &generalTrackVertexZ);
  
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
//  eventTree->SetBranchAddress("eleSCEt"           , &electronSCEt);
  eventTree->SetBranchAddress("eleSCPhi"          , &electronSCPhi);
  eventTree->SetBranchAddress("eleSCEn"           , &electronSCEn);
  
  eventTree->SetBranchAddress("elePFChIso"        , &electronChIso);
  eventTree->SetBranchAddress("elePFPhoIso"       , &electronPhoIso);
  eventTree->SetBranchAddress("elePFNeuIso"       , &electronNeuIso);
  
  l1Tree->SetBranchAddress("nEGs"                 , &currentEvent->nL1EGs);
  l1Tree->SetBranchAddress("egEta"                , &L1EGeta);
  l1Tree->SetBranchAddress("egPhi"                , &L1EGphi);
  l1Tree->SetBranchAddress("egEt"                 , &L1EGet);
}

void EventProcessor::SetupOutputTree(string outFileName)
{
  outFile[outFileName] = new TFile(outFileName.c_str(), "recreate");
  outFile[outFileName]->cd();
  
  dirEvent[outFileName]  = outFile[outFileName]->mkdir("ggHiNtuplizer");
  dirHLT[outFileName]    = outFile[outFileName]->mkdir("hltanalysis");
  dirL1[outFileName]     = outFile[outFileName]->mkdir("l1object");
  
  outEventTree[outFileName] = eventTree->CloneTree(0);
  outHltTree[outFileName]   = hltTree->CloneTree(0);
  outL1Tree[outFileName]    = l1Tree->CloneTree(0);
  
  outEventTree[outFileName]->Reset();
  outHltTree[outFileName]->Reset();
  outL1Tree[outFileName]->Reset();
}

void EventProcessor::AddEventToOutputTree(int iEvent, string outFileName, bool saveHLTtree)
{
  eventTree->GetEntry(iEvent);
  hltTree->GetEntry(iEvent);
  l1Tree->GetEntry(iEvent);
  
  outEventTree[outFileName]->Fill();
  if(saveHLTtree) outHltTree[outFileName]->Fill();
  outL1Tree[outFileName]->Fill();
}

void EventProcessor::SaveOutputTree(string outFileName)
{
  dirHLT[outFileName]->cd();
  outHltTree[outFileName]->Write();
  dirL1[outFileName]->cd();
  outL1Tree[outFileName]->Write();
  dirEvent[outFileName]->cd();
  outEventTree[outFileName]->Write();
  outFile[outFileName]->Close();
}

shared_ptr<Event> EventProcessor::GetEvent(int iEvent)
{
  // Move to desired entry in all trees
  hltTree->GetEntry(iEvent);
  eventTree->GetEntry(iEvent);
  l1Tree->GetEntry(iEvent);
  
  currentEvent->Reset();
  
  // Fill in collection of gen particles
  
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
  
  // Fill in collection of photon superclusters
  
  for(size_t iPhoton=0; iPhoton<currentEvent->nPhotons; iPhoton++){
    auto photon = make_shared<PhysObject>();
    
    photon->hOverE   = photonHoverE->at(iPhoton);
    photon->eta      = photonSCEta->at(iPhoton);
    photon->etaSC    = photonSCEta->at(iPhoton);
    photon->phi      = photonSCPhi->at(iPhoton);
    photon->phiSC    = photonSCPhi->at(iPhoton);
    photon->et       = photonSCEt->at(iPhoton);
    photon->etSC     = photonSCEt->at(iPhoton);
    photon->pt       = photonSCEt->at(iPhoton);
    photon->energy   = photonSCE->at(iPhoton);
    photon->energySC = photonSCE->at(iPhoton);
    photon->etaWidth = photonSCEtaWidth->at(iPhoton);
    photon->phiWidth = photonSCPhiWidth->at(iPhoton);
    
    if(photonEmax)    photon->energyMax    = photonEmax->at(iPhoton);
    if(photonEtop)    photon->energyTop    = photonEtop->at(iPhoton);
    if(photonEbottom) photon->energyBottom = photonEbottom->at(iPhoton);
    if(photonEleft)   photon->energyLeft   = photonEleft->at(iPhoton);
    if(photonEright)  photon->energyRight  = photonEright->at(iPhoton);
    
    currentEvent->photons.push_back(photon);
  }
  
  // Fill in collection of calo towers
  
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
  
  // Fill in collection of general tracks
  
  for(size_t iTrack=0; iTrack<currentEvent->nGeneralTracks; iTrack++){
    auto track = make_shared<PhysObject>();
    
    track->charge       = generalTrackCharge->at(iTrack);
    track->pt           = generalTrackPt->at(iTrack);
    track->eta          = generalTrackEta->at(iTrack);
    track->phi          = generalTrackPhi->at(iTrack);
    track->nValidHits   = generalTrackValidHits->at(iTrack);
    track->nMissingHits = generalTrackMissingHits->at(iTrack);
    track->purity       = generalTrackPurity->at(iTrack);
    track->chi2         = generalTrackChi2->at(iTrack);
    track->dxy          = generalTrackDxy->at(iTrack);
    track->dz           = generalTrackDz->at(iTrack);
    track->dxyErr       = generalTrackDxyErr->at(iTrack);
    track->dzErr        = generalTrackDzErr->at(iTrack);
    track->vx           = generalTrackVertexX->at(iTrack);
    track->vy           = generalTrackVertexY->at(iTrack);
    track->vz           = generalTrackVertexZ->at(iTrack);
    
    currentEvent->generalTracks.push_back(track);
  }
  
  // Fill in collection of electrons
  
  for(size_t iElectron=0; iElectron<currentEvent->nElectrons; iElectron++){
    auto electron = make_shared<PhysObject>();
    
    electron->charge       = electronCharge->at(iElectron);
    electron->nMissingHits = electronNmissing->at(iElectron);
    electron->pt           = electronPt->at(iElectron);
    electron->eta          = electronEta->at(iElectron);
    electron->phi          = electronPhi->at(iElectron);
    electron->hOverE       = electronHoverE->at(iElectron);
    // TODO: fix missing RelIsoWithEA branch!!
//    electron->relIsoWithEA = electronRelIsoWithEA->at(iElectron);
    electron->dEtaSeed     = electronDetaSeed->at(iElectron);
    electron->etaSC        = electronSCEta->at(iElectron);
//    electron->etSC         = electronSCEt->at(iElectron);
    electron->phiSC        = electronSCPhi->at(iElectron);
    electron->energySC     = electronSCEn->at(iElectron);
    electron->chargedIso   = electronChIso->at(iElectron);
    electron->photonIso    = electronPhoIso->at(iElectron);
    electron->neutralIso   = electronNeuIso->at(iElectron);
    
    currentEvent->electrons.push_back(electron);
  }
  
  // Fill in collection of L1 EG objects
  
  for(size_t iL1EG=0; iL1EG<currentEvent->nL1EGs; iL1EG++){
    auto L1EG = make_shared<PhysObject>();
    
    L1EG->eta = L1EGeta->at(iL1EG);
    L1EG->phi = L1EGphi->at(iL1EG);
    L1EG->et  = L1EGet->at(iL1EG);
    
    currentEvent->L1EGs.push_back(L1EG);
  }
  
  return currentEvent;
}
