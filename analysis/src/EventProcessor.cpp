//  EventProcessor.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "Logger.hpp"

EventProcessor::EventProcessor(string inputPath, EDataset _dataset, vector<string> outputPaths,
                               string secondaryInputPath) :
dataset(_dataset),
currentEvent(new Event())
{
  for(auto type : physObjTypes) nPhysObjects[type] = 0;
  for(auto trigger : triggers) triggerValues[trigger] = 0;
  SetupBranches(inputPath, outputPaths, secondaryInputPath);
}

EventProcessor::~EventProcessor()
{
  
}

void EventProcessor::SetupBranches(string inputPath, vector<string> outputPaths, string secondaryInputPath)
{
  // Read trees from input files
  TFile *inFile = TFile::Open(inputPath.c_str());
  eventTree     = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  hltTree       = (TTree*)inFile->Get("hltanalysis/HltTree");
  l1Tree        = (TTree*)inFile->Get("l1object/L1UpgradeFlatTree");
  zdcTree       = (TTree*)inFile->Get("rechitanalyzerpp/zdcrechit");
  
  if(secondaryInputPath == ""){
    pixelTree = (TTree*)inFile->Get("pixelTracks/EventTree");
  }
  else{
    TFile *secondatyInFile = TFile::Open(secondaryInputPath.c_str());
    if(!secondatyInFile){
      cout<<"ERROR -- secondary input file not found: "<<secondaryInputPath<<endl;
    }
    pixelTree = (TTree*)secondatyInFile->Get("ggHiNtuplizer_pixelOnly/EventTree");
    if(!pixelTree){
      cout<<"ERROR -- pixel tree not found in file: "<<secondaryInputPath<<endl;
    }
  }
  
  for(string outputPath : outputPaths) SetupOutputTree(outputPath);
  
  for(auto &[trigger, name] : triggerNames){
    hltTree->SetBranchAddress(name.c_str()            , &triggerValues[trigger]);
  }
  eventTree->SetBranchAddress("nMC"                   , &nPhysObjects.at(kGenParticle));
  eventTree->SetBranchAddress("mcEta"                 , &mcEta);
  eventTree->SetBranchAddress("mcPhi"                 , &mcPhi);
  eventTree->SetBranchAddress("mcEt"                  , &mcEt);
  eventTree->SetBranchAddress("mcPID"                 , &mcPID);
  
  eventTree->SetBranchAddress("nPho"                  , &nPhysObjects.at(kPhoton));
  eventTree->SetBranchAddress("phoHoverE"             , &photonHoverE);
  eventTree->SetBranchAddress("phoEta"                , &photonEta);
  eventTree->SetBranchAddress("phoPhi"                , &photonPhi);
  eventTree->SetBranchAddress("phoEt"                 , &photonEt);
  eventTree->SetBranchAddress("phoE"                  , &photonE);
  eventTree->SetBranchAddress("phoSCEta"              , &photonSCEta);
  eventTree->SetBranchAddress("phoSCPhi"              , &photonSCPhi);
  eventTree->SetBranchAddress("phoSCEt"               , &photonSCEt);
  eventTree->SetBranchAddress("phoSCE"                , &photonSCE);
  eventTree->SetBranchAddress("phoSCEtaWidth"         , &photonSCEtaWidth);
  eventTree->SetBranchAddress("phoSigmaIEtaIEta_2012" , &photonSigmaEta2012);
  eventTree->SetBranchAddress("phoSCPhiWidth"         , &photonSCPhiWidth);
  
  eventTree->SetBranchAddress("phoMaxEnergyXtal"      , &photonEmax);
  eventTree->SetBranchAddress("phoETop"               , &photonEtop);
  eventTree->SetBranchAddress("phoEBottom"            , &photonEbottom);
  eventTree->SetBranchAddress("phoELeft"              , &photonEleft);
  eventTree->SetBranchAddress("phoERight"             , &photonEright);
  eventTree->SetBranchAddress("phoHasConversionTracks", &photonIsConverted);
  
  eventTree->SetBranchAddress("nTower"                , &nPhysObjects.at(kCaloTower));
  eventTree->SetBranchAddress("CaloTower_hadE"        , &towerEnergyHad);
  eventTree->SetBranchAddress("CaloTower_emE"         , &towerEnergyEm);
  eventTree->SetBranchAddress("CaloTower_e"           , &towerEnergy);
  eventTree->SetBranchAddress("CaloTower_et"          , &towerEt);
  eventTree->SetBranchAddress("CaloTower_eta"         , &towerEta);
  eventTree->SetBranchAddress("CaloTower_phi"         , &towerPhi);
  
  eventTree->SetBranchAddress("nTrk"                  , &nPhysObjects.at(kGeneralTrack));
  eventTree->SetBranchAddress("trkPt"                 , &generalTrackPt);
  eventTree->SetBranchAddress("trkP"                  , &generalTrackP);
  eventTree->SetBranchAddress("trkEta"                , &generalTrackEta);
  eventTree->SetBranchAddress("trkPhi"                , &generalTrackPhi);
  eventTree->SetBranchAddress("trkcharge"             , &generalTrackCharge);
  eventTree->SetBranchAddress("trkValidHits"          , &generalTrackValidHits);
  eventTree->SetBranchAddress("trkMissHits"           , &generalTrackMissingHits);
  eventTree->SetBranchAddress("trkPurity"             , &generalTrackPurity);
  eventTree->SetBranchAddress("trknormchi2"           , &generalTrackChi2);
  eventTree->SetBranchAddress("trkdxy"                , &generalTrackDxy);
  eventTree->SetBranchAddress("trkdz"                 , &generalTrackDz);
  eventTree->SetBranchAddress("trkdxyError"           , &generalTrackDxyErr);
  eventTree->SetBranchAddress("trkdzError"            , &generalTrackDzErr);
  eventTree->SetBranchAddress("trkvx"                 , &generalTrackVertexX);
  eventTree->SetBranchAddress("trkvy"                 , &generalTrackVertexY);
  eventTree->SetBranchAddress("trkvz"                 , &generalTrackVertexZ);
  
  eventTree->SetBranchAddress("nEle"                  , &nPhysObjects.at(kElectron));
  eventTree->SetBranchAddress("eleCharge"             , &electronCharge);
  eventTree->SetBranchAddress("eleMissHits"           , &electronNmissing);
  eventTree->SetBranchAddress("elePt"                 , &electronPt);
  eventTree->SetBranchAddress("eleEta"                , &electronEta);
  eventTree->SetBranchAddress("elePhi"                , &electronPhi);
  eventTree->SetBranchAddress("eleHoverE"             , &electronHoverE);
  eventTree->SetBranchAddress("elePFRelIsoWithEA"     , &electronRelIsoWithEA);
  eventTree->SetBranchAddress("eledEtaAtVtx"          , &electronDetaSeed);
  eventTree->SetBranchAddress("eleSCEta"              , &electronSCEta);
//  eventTree->SetBranchAddress("eleSCEt"               , &electronSCEt);
  eventTree->SetBranchAddress("eleSCPhi"              , &electronSCPhi);
  eventTree->SetBranchAddress("eleSCEn"               , &electronSCEn);
  
  eventTree->SetBranchAddress("elePFChIso"        , &electronChIso);
  eventTree->SetBranchAddress("elePFPhoIso"       , &electronPhoIso);
  eventTree->SetBranchAddress("elePFNeuIso"       , &electronNeuIso);

  eventTree->SetBranchAddress("nMu"              , &nPhysObjects.at(kMuon));
  eventTree->SetBranchAddress("muCharge"         , &muonCharge);
//  eventTree->SetBranchAddress("muMissHits"       , &muonNmissing);
  eventTree->SetBranchAddress("muPt"             , &muonPt);
  eventTree->SetBranchAddress("muEta"            , &muonEta);
  eventTree->SetBranchAddress("muPhi"            , &muonPhi);
//  eventTree->SetBranchAddress("muHoverE"         , &muonHoverE);
//  eventTree->SetBranchAddress("muPFRelIsoWithEA" , &muonRelIsoWithEA);
//  eventTree->SetBranchAddress("mudEtaAtVtx"      , &muonDetaSeed);
//  eventTree->SetBranchAddress("muSCEta"          , &muonSCEta);
//  eventTree->SetBranchAddress("muSCEt"           , &muonSCEt);
//  eventTree->SetBranchAddress("muSCPhi"          , &muonSCPhi);
//  eventTree->SetBranchAddress("muSCEn"           , &muonSCEn);
  
  eventTree->SetBranchAddress("muPFChIso"       , &muonChIso);
  eventTree->SetBranchAddress("muPFPhoIso"      , &muonPhoIso);
  eventTree->SetBranchAddress("muPFNeuIso"      , &muonNeuIso);
  
  l1Tree->SetBranchAddress("nEGs"               , &nL1EGs);
  l1Tree->SetBranchAddress("egEta"              , &L1EGeta);
  l1Tree->SetBranchAddress("egPhi"              , &L1EGphi);
  l1Tree->SetBranchAddress("egEt"               , &L1EGet);
  
  eventTree->SetBranchAddress("run"             , &runNumber);
  eventTree->SetBranchAddress("lumis"           , &lumiSection);
  eventTree->SetBranchAddress("event"           , &eventNumber);
  
  eventTree->SetBranchAddress("nDisplacedTracks", &nDisplacedTracks);
  eventTree->SetBranchAddress("nPixelClusters"  , &nPixelClusters);
  eventTree->SetBranchAddress("nPixelRecHits"   , &nPixelRecHits);
  eventTree->SetBranchAddress("nDedxHits"       , &nDedxHits);
 
  if(zdcTree){
    zdcTree->SetBranchAddress("n"                 , &nZDCs);
    zdcTree->SetBranchAddress("e"                 , zdcE);
    zdcTree->SetBranchAddress("saturation"        , zdcSaturation);
    zdcTree->SetBranchAddress("zside"             , zdcZside);
    zdcTree->SetBranchAddress("section"           , zdcSection);
    zdcTree->SetBranchAddress("channel"           , zdcChannel);
  }
  else{
    nZDCs = 0;
    Log(0)<<"WARNING -- no ZDC tree available. ZDC variables will not be set!\n";
  }
  
  if(!pixelTree){
    Log(0)<<"WARNING -- no pixel tree available. Pixel variables will not be set!\n";
    return;
  }
  
  pixelTree->SetBranchAddress("nPix"            , &nPhysObjects.at(kPixelTrack));
  pixelTree->SetBranchAddress("pixPt"           , &pixelTrackPt);
  pixelTree->SetBranchAddress("pixP"            , &pixelTrackP);
  pixelTree->SetBranchAddress("pixEta"          , &pixelTrackEta);
  pixelTree->SetBranchAddress("pixPhi"          , &pixelTrackPhi);
  pixelTree->SetBranchAddress("pixcharge"       , &pixelTrackCharge);
  pixelTree->SetBranchAddress("pixValidHits"    , &pixelTrackValidHits);
  pixelTree->SetBranchAddress("pixMissHits"     , &pixelTrackMissingHits);
  pixelTree->SetBranchAddress("pixPurity"       , &pixelTrackPurity);
  pixelTree->SetBranchAddress("pixnormchi2"     , &pixelTrackChi2);
  pixelTree->SetBranchAddress("pixdxy"          , &pixelTrackDxy);
  pixelTree->SetBranchAddress("pixdz"           , &pixelTrackDz);
  pixelTree->SetBranchAddress("pixdxyError"     , &pixelTrackDxyErr);
  pixelTree->SetBranchAddress("pixdzError"      , &pixelTrackDzErr);
  pixelTree->SetBranchAddress("pixvx"           , &pixelTrackVertexX);
  pixelTree->SetBranchAddress("pixvy"           , &pixelTrackVertexY);
  pixelTree->SetBranchAddress("pixvz"           , &pixelTrackVertexZ);
  
}

void EventProcessor::SetupOutputTree(string outFileName)
{
  outFile[outFileName] = new TFile(outFileName.c_str(), "recreate");
  outFile[outFileName]->cd();
  
  dirEvent[outFileName]     = outFile[outFileName]->mkdir("ggHiNtuplizer");
  dirHLT[outFileName]       = outFile[outFileName]->mkdir("hltanalysis");
  dirL1[outFileName]        = outFile[outFileName]->mkdir("l1object");
  dirZdc[outFileName]       = outFile[outFileName]->mkdir("rechitanalyzerpp");
  
  outEventTree[outFileName] = eventTree->CloneTree(0);
  outHltTree[outFileName]   = hltTree->CloneTree(0);
  outL1Tree[outFileName]    = l1Tree->CloneTree(0);
  outZdcTree[outFileName]   = zdcTree->CloneTree(0);
  
  outEventTree[outFileName]->Reset();
  outHltTree[outFileName]->Reset();
  outL1Tree[outFileName]->Reset();
  outZdcTree[outFileName]->Reset();
  
  if(pixelTree){
    dirPixel[outFileName] = outFile[outFileName]->mkdir("pixelTracks");
    outPixelTree[outFileName] = pixelTree->CloneTree(0);
    outPixelTree[outFileName]->Reset();
  }
}

void EventProcessor::AddEventToOutputTree(int iEvent, string outFileName, bool saveHLTtree)
{
  eventTree->GetEntry(iEvent);
  hltTree->GetEntry(iEvent);
  l1Tree->GetEntry(iEvent);
  zdcTree->GetEntry(iEvent);
  
  outEventTree[outFileName]->Fill();
  if(saveHLTtree) outHltTree[outFileName]->Fill();
  outL1Tree[outFileName]->Fill();
  outZdcTree[outFileName]->Fill();
  
  if(pixelTree){
    long long secondaryTreeEntry = GetEntryNumber(pixelTree, runNumber, lumiSection, eventNumber);
    
    if(secondaryTreeEntry < 0){
      Log(0)<<"Couldn't find secondary entry for this event.\n";
      return;
    }
    pixelTree->GetEntry(secondaryTreeEntry);
    outPixelTree[outFileName]->Fill();
  }
}

void EventProcessor::SaveOutputTree(string outFileName)
{
  dirHLT[outFileName]->cd();
  outHltTree[outFileName]->Write();
  dirL1[outFileName]->cd();
  outL1Tree[outFileName]->Write();
  dirEvent[outFileName]->cd();
  outEventTree[outFileName]->Write();
  dirZdc[outFileName]->cd();
  outZdcTree[outFileName]->Write();
  
  if(pixelTree){
    dirPixel[outFileName]->cd();
    outPixelTree[outFileName]->Write();
  }
  
  outFile[outFileName]->Close();
}

shared_ptr<Event> EventProcessor::GetEvent(int iEvent)
{
  // Move to desired entry in all trees
  hltTree->GetEntry(iEvent);
  eventTree->GetEntry(iEvent);
  l1Tree->GetEntry(iEvent);
  if(zdcTree) zdcTree->GetEntry(iEvent);
  
  currentEvent->Reset();
  
  currentEvent->dataset = dataset;
  
  currentEvent->runNumber   = runNumber;
  currentEvent->lumiSection = lumiSection;
  currentEvent->eventNumber = eventNumber;
  
  currentEvent->nDisplacedTracks = nDisplacedTracks;
  currentEvent->nPixelRecHits = nPixelRecHits;
  currentEvent->nPixelClusters = nPixelClusters;
  currentEvent->nDedxHits = nDedxHits;
  
  for(ETrigger trigger : triggers){
    currentEvent->triggerValues[trigger] = triggerValues[trigger];
  }
  
  // Fill in collection of gen particles
  for(int iGenPart=0; iGenPart<nPhysObjects.at(kGenParticle); iGenPart++){
    auto genParticle = make_shared<PhysObject>();
    
    genParticle->eta   = mcEta->at(iGenPart);
    genParticle->phi   = mcPhi->at(iGenPart);
    genParticle->et    = mcEt->at(iGenPart);
    genParticle->pdgID = mcPID->at(iGenPart);
    
    currentEvent->physObjects.at(kGenParticle).push_back(genParticle);
  }
  
  // Fill in collection of photon superclusters
  
  for(size_t iPhoton=0; iPhoton<nPhysObjects.at(kPhoton); iPhoton++){
    auto photon = make_shared<PhysObject>();
    
    photon->hOverE   = photonHoverE->at(iPhoton);
    photon->eta      = photonEta->at(iPhoton);
    photon->etaSC    = photonSCEta->at(iPhoton);
    photon->phi      = photonPhi->at(iPhoton);
    photon->phiSC    = photonSCPhi->at(iPhoton);
    photon->et       = photonEt->at(iPhoton);
    photon->etSC     = photonSCEt->at(iPhoton);
    photon->pt       = photonSCEt->at(iPhoton);
    photon->energy   = photonE->at(iPhoton);
    photon->energySC = photonSCE->at(iPhoton);
    photon->etaWidth = photonSCEtaWidth->at(iPhoton);
    photon->sigmaEta2012 = photonSigmaEta2012->at(iPhoton);
    photon->phiWidth = photonSCPhiWidth->at(iPhoton);
    
    if(photonEmax)    photon->energyMax    = photonEmax->at(iPhoton);
    if(photonEtop)    photon->energyTop    = photonEtop->at(iPhoton);
    if(photonEbottom) photon->energyBottom = photonEbottom->at(iPhoton);
    if(photonEleft)   photon->energyLeft   = photonEleft->at(iPhoton);
    if(photonEright)  photon->energyRight  = photonEright->at(iPhoton);
    
    photon->hasConversionTracks = photonIsConverted->at(iPhoton);
    
    currentEvent->physObjects.at(kPhoton).push_back(photon);
  }
  
  // Fill in collection of calo towers
  
  for(size_t iTower=0; iTower<nPhysObjects.at(kCaloTower); iTower++){
    auto tower = make_shared<PhysObject>();
    
    tower->eta       = towerEta->at(iTower);
    tower->etaSC     = towerEta->at(iTower);
    tower->phi       = towerPhi->at(iTower);
    tower->phiSC     = towerPhi->at(iTower);
    tower->energy    = towerEnergy->at(iTower);
    tower->energySC  = towerEnergy->at(iTower);
    tower->et        = towerEt->at(iTower);
    tower->etSC      = towerEt->at(iTower);
    tower->energyHad = towerEnergyHad->at(iTower);
    
    tower->energyEm  = towerEnergyEm->at(iTower);
    
    currentEvent->physObjects.at(kCaloTower).push_back(tower);
  }
  
  // Fill in collection of general tracks
  
  for(size_t iTrack=0; iTrack<nPhysObjects.at(kGeneralTrack); iTrack++){
    auto track = make_shared<PhysObject>();
    
    track->charge       = generalTrackCharge->at(iTrack);
    track->pt           = generalTrackPt->at(iTrack);
    track->p            = generalTrackP->at(iTrack);
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
    
    currentEvent->physObjects.at(kGeneralTrack).push_back(track);
  }
  
  // Fill in collection of electrons
  
  for(size_t iElectron=0; iElectron<nPhysObjects.at(kElectron); iElectron++){
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
    
    currentEvent->physObjects.at(kElectron).push_back(electron);
  }

  // Fill in collection of muons
  
  for(size_t iMuon=0; iMuon<nPhysObjects.at(kMuon); iMuon++){
    auto muon = make_shared<PhysObject>();
    
    muon->charge       = muonCharge->at(iMuon);
//    muon->nMissingHits = muonNmissing->at(iMuon);
    muon->pt           = muonPt->at(iMuon);
    muon->eta          = muonEta->at(iMuon);
    muon->phi          = muonPhi->at(iMuon);
//    muon->hOverE       = muonHoverE->at(iMuon);
    // TODO: fix missing RelIsoWithEA branch!!
//    muon->relIsoWithEA = muonRelIsoWithEA->at(iMuon);
//    muon->dEtaSeed     = muonDetaSeed->at(iMuon);
//    muon->etaSC        = muonSCEta->at(iMuon);
//    muon->etSC         = muonSCEt->at(iMuon);
//    muon->phiSC        = muonSCPhi->at(iMuon);
//    muon->energySC     = muonSCEn->at(iMuon);
    muon->chargedIso   = muonChIso->at(iMuon);
    muon->photonIso    = muonPhoIso->at(iMuon);
    muon->neutralIso   = muonNeuIso->at(iMuon);
    
    currentEvent->physObjects.at(kMuon).push_back(muon);
  }

  
  // Fill in collection of L1 EG objects
  
  for(size_t iL1EG=0; iL1EG<nL1EGs; iL1EG++){
    auto L1EG = make_shared<PhysObject>();
    
    L1EG->eta = L1EGeta->at(iL1EG);
    L1EG->phi = L1EGphi->at(iL1EG);
    L1EG->et  = L1EGet->at(iL1EG);
    
    currentEvent->physObjects.at(kL1EG).push_back(L1EG);
  }
  
  for(size_t iZDC=0; iZDC<nZDCs; iZDC++){
    auto zdc = make_shared<PhysObject>();
    
    zdc->energy = zdcE[iZDC];
    zdc->zSide  = zdcZside[iZDC];
    
    currentEvent->physObjects.at(kZDC).push_back(zdc);
  }
  
  if(!pixelTree) return currentEvent;
  
  pixelTree->GetEntry(iEvent);
  
  // Fill in collection of pixel tracks
   for(size_t iTrack=0; iTrack<nPhysObjects.at(kPixelTrack); iTrack++){
     auto track = make_shared<PhysObject>();
     
     track->charge       = pixelTrackCharge->at(iTrack);
     track->pt           = pixelTrackPt->at(iTrack);
     track->p            = pixelTrackP->at(iTrack);
     track->eta          = pixelTrackEta->at(iTrack);
     track->phi          = pixelTrackPhi->at(iTrack);
     track->nValidHits   = pixelTrackValidHits->at(iTrack);
     track->nMissingHits = pixelTrackMissingHits->at(iTrack);
     track->purity       = pixelTrackPurity->at(iTrack);
     track->chi2         = pixelTrackChi2->at(iTrack);
     track->dxy          = pixelTrackDxy->at(iTrack);
     track->dz           = pixelTrackDz->at(iTrack);
     track->dxyErr       = pixelTrackDxyErr->at(iTrack);
     track->dzErr        = pixelTrackDzErr->at(iTrack);
     track->vx           = pixelTrackVertexX->at(iTrack);
     track->vy           = pixelTrackVertexY->at(iTrack);
     track->vz           = pixelTrackVertexZ->at(iTrack);
     
     currentEvent->physObjects.at(kPixelTrack).push_back(track);
   }
  
  return currentEvent;
}


