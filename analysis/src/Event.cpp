//  Event.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Event.hpp"
#include "PhysObjectProcessor.hpp"
#include "Logger.hpp"

Event::Event()
{
  for(auto type : physObjTypes){
    physObjectsReady[type] = false;
    physObjects[type] = PhysObjects();
  }
  nDisplacedTracks = 0;
  nPixelClusters = 0;
  nPixelRecHits = 0;
  nDedxHits = 0;
}

Event::~Event()
{

}

void Event::Reset()
{
  for(auto &[type, objects] : physObjects)    objects.clear();
  for(auto &[type, ready] : physObjectsReady) ready = false;
  
  nDisplacedTracks = 0;
  nPixelClusters = 0;
  nPixelRecHits = 0;
  nDedxHits = 0;
}

bool Event::HasTrigger(ETrigger trigger) const
{
  return triggerValues.at(trigger);
}

PhysObjects Event::GetPhysObjects(EPhysObjType type, TH1D *cutFlowHist)
{
  if(   type == kPhoton
     || type == kElectron
     || type == kMuon
     || type == kCaloTower
     || type == kGeneralTrack
     || type == kL1EG
     || type == kZDC
     || type == kPixelTrack){
    return physObjects.at(type);
  }
  else if(type == kGoodGenPhoton)       return GetGoodGenPhotons();
  else if(type == kPhotonInAcceptance)  return GetPhotonsInAcceptance();
  else if(type == kGoodPhoton)          return GetGoodPhotons();
  else if(type == kGoodElectron)        return GetGoodElectrons(cutFlowHist);
  else if(type == kGoodMatchedElectron) return GetGoodMatchedElectron();
  else if(type == kGoodMuon)            return GetGoodMuons(cutFlowHist);
  else if(type == kGoodGeneralTrack)    return GetGoodGeneralTracks(cutFlowHist);
  else if(type == kGoodPixelTrack)      return GetGoodPixelTracks(cutFlowHist);
  
  Log(0)<<"ERROR -- unrecognized phys object type: "<<type<<"!!!\n";
  return PhysObjects();
}

PhysObjects Event::GetGoodGenPhotons() const
{
  PhysObjects goodGenPhotons;
  
  for(auto genPhoton : physObjects.at(kGenParticle)){
    
    if(genPhoton->GetPID() != 22) continue;
    if(fabs(genPhoton->GetEta()) > config.params("photonMaxEta")) continue;
    if(genPhoton->GetEt() < config.params("photonMinEt")) continue;
    
    goodGenPhotons.push_back(genPhoton);
  }
  
  return goodGenPhotons;
}

PhysObjects Event::GetPhotonsInAcceptance()
{
  if(physObjectsReady.at(kPhotonInAcceptance)) return physObjects.at(kPhotonInAcceptance);
  
  physObjects.at(kPhotonInAcceptance).clear();
  
  for(auto photon : physObjects.at(kPhoton)){
    
   
    // Check Et
    if(photon->GetEt() < config.params("photonMinEt")) continue;
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEta());
    if(absEta > config.params("photonMaxEta")) continue;
    if(absEta > config.params("ecalCrackMin") && absEta < config.params("ecalCrackMax")) continue;
    if(photon->GetEta() < -minEtaEE &&
       photon->GetPhi() > config.params("ecalHEMmin") &&
       photon->GetPhi() < config.params("ecalHEMmax")) continue;
    
    
    physObjects.at(kPhotonInAcceptance).push_back(photon);
  }
  physObjectsReady.at(kPhotonInAcceptance) = true;
  return physObjects.at(kPhotonInAcceptance);
}

PhysObjects Event::GetGoodPhotons()
{
  if(physObjectsReady.at(kGoodPhoton)) return physObjects.at(kGoodPhoton);
  
  physObjects.at(kGoodPhoton).clear();
  
  for(auto photon : physObjects.at(kPhoton)){
    
    // Check if photon converted
    if(config.params("photonRejectConverted") && photon->IsConverted()) continue;
    
    // Check Et
    if(photon->GetEt() < config.params("photonMinEt")) continue;
    
    // Check swiss cross
    double E4 = photon->GetEnergyCrystalTop() +
    photon->GetEnergyCrystalBottom() +
    photon->GetEnergyCrystalLeft() +
    photon->GetEnergyCrystalRight();
    
    if(E4 < 0){
      Log(1)<<"WARNING -- swiss cross cannot be calculated. The event will pass this selection automatically!!\n";
    }
    else{
      double swissCross = E4/photon->GetEnergyCrystalMax();
      if(swissCross < config.params("photonMinSwissCross")) continue;
    }
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEta());
    if(absEta > config.params("photonMaxEta")) continue;
    if(absEta > config.params("ecalCrackMin") && absEta < config.params("ecalCrackMax")) continue;
    if(photon->GetEta() < -minEtaEE &&
       photon->GetPhi() > config.params("ecalHEMmin") &&
       photon->GetPhi() < config.params("ecalHEMmax")) continue;
    
    // Check η shower shape
    if((absEta < maxEtaEB) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthBarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthEndcap"))) continue;
    
    if((absEta < maxEtaEB) && (photon->GetSigmaEta2012() > config.params("photonMaxSigmaEta2012Barrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetSigmaEta2012() > config.params("photonMaxSigmaEta2012Endcap"))) continue;
    
    
    // Check H/E
    if((absEta < maxEtaEB) && (photon->GetHoverE() > config.params("photonMaxHoverEbarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetHoverE() > config.params("photonMaxHoverEendcap"))) continue;
    
    physObjects.at(kGoodPhoton).push_back(photon);
  }
  physObjectsReady.at(kGoodPhoton) = true;
  return physObjects.at(kGoodPhoton);
}

PhysObjects Event::GetGoodElectrons(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(kGoodElectron)) return physObjects.at(kGoodElectron);
  
  physObjects.at(kGoodElectron).clear();
  
  for(auto electron : physObjects.at(kElectron)){
    int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Check pt
    if(electron->GetPt() < config.params("electronMinPt")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1
    
    // Check eta
    double eta = fabs(electron->GetEtaSC());
    if(eta > config.params("ecalCrackMin") &&
       eta < config.params("ecalCrackMax"))   continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 2
    
    if(eta >= config.params("electronMaxEta")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 3
    
    // Check for HEM issue
    if(electron->GetEtaSC() < -minEtaEE &&
       electron->GetPhiSC() > config.params("ecalHEMmin") &&
       electron->GetPhiSC() < config.params("ecalHEMmax")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 4
    
    // Check n missing hits
    if(electron->GetNmissingHits() > config.params("electronMaxNmissingHits")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 5
    
    string subdet = "";
    if((eta < maxEtaEB)) subdet = "Barrel";
    else if((eta < maxEtaEE)) subdet = "Endcap";
    
    // Check H/E
    if(electron->GetHoverE() >= config.params("electronMaxHoverE_"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 6
    
    // Check Δη at vertex
    if(electron->GetDetaSeed() >= config.params("electronMaxDetaSeed"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 7
    
    // Check isolation
    if(electron->GetChargedIso() >= config.params("electronMaxChargedIso"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 8
    
    if(electron->GetPhotonIso()  >= config.params("electronMaxPhotonIso"+subdet))  continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 9
    
    if(electron->GetNeutralIso() >= config.params("electronMaxNeutralIso"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 10

    physObjects.at(kGoodElectron).push_back(electron);
  }
  physObjectsReady.at(kGoodElectron) = true;
  return physObjects.at(kGoodElectron);
}

PhysObjects Event::GetGoodMuons(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(kGoodMuon)) return physObjects.at(kGoodMuon);
  
  physObjects.at(kGoodMuon).clear();
  
  for(auto muon : physObjects.at(kMuon)){
//    int cutFlowIndex=0;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Check pt
//    if(muon->GetPt() < config.params("muonMinPt")) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1
    
    // Check eta
//    double eta = fabs(muon->GetEtaSC());
//    if(eta > config.params("ecalCrackMin") &&
//       eta < config.params("ecalCrackMax"))   continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 2
    
//    if(eta >= config.params("muonMaxEta")) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 3
    
    // Check for HEM issue
//    if(muon->GetEtaSC() < -minEtaEE &&
//       muon->GetPhiSC() > config.params("ecalHEMmin") &&
//       muon->GetPhiSC() < config.params("ecalHEMmax")) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 4
    
    // Check n missing hits
//    if(muon->GetNmissingHits() > config.params("muonMaxNmissingHits")) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 5
    
//    string subdet = "";
//    if((eta < maxEtaEB)) subdet = "Barrel";
//    else if((eta < maxEtaEE)) subdet = "Endcap";
    
    // Check H/E
//    if(muon->GetHoverE() >= config.params("muonMaxHoverE_"+subdet)) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 6
    
    // Check Δη at vertex
//    if(muon->GetDetaSeed() >= config.params("muonMaxDetaSeed"+subdet)) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 7
    
    // Check isolation
//    if(muon->GetChargedIso() >= config.params("muonMaxChargedIso"+subdet)) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 8
    
//    if(muon->GetPhotonIso()  >= config.params("muonMaxPhotonIso"+subdet))  continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 9
    
//    if(muon->GetNeutralIso() >= config.params("muonMaxNeutralIso"+subdet)) continue;
//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 10

    physObjects.at(kGoodMuon).push_back(muon);
  }
  physObjectsReady.at(kGoodMuon) = true;
  return physObjects.at(kGoodMuon);
}


PhysObjects Event::GetGoodMatchedElectron()
{
  if(physObjectsReady.at(kGoodMatchedElectron)) return physObjects.at(kGoodMatchedElectron);
  
  physObjects.at(kGoodMatchedElectron).clear();
  
  for(auto electron : GetPhysObjects(kGoodElectron)){
    for(auto &L1EG : GetPhysObjects(kL1EG)){
      if(L1EG->GetEt() < 2.0) continue;
      
      if(physObjectProcessor.GetDeltaR_SC(*electron, *L1EG) < 0.3){
        physObjects.at(kGoodMatchedElectron).push_back(electron);
        break;
      }
    }
  }
  
  physObjectsReady.at(kGoodMatchedElectron) = true;
  return physObjects.at(kGoodMatchedElectron);
}

PhysObjects Event::GetGoodGeneralTracks(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(kGoodGeneralTrack)) return physObjects.at(kGoodGeneralTrack);
  
  physObjects.at(kGoodGeneralTrack).clear();
  
  for(auto track : physObjects.at(kGeneralTrack)){
    int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Check pt
    if(track->GetPt() < config.params("trackMinPt")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1
    
    // Check eta
    if(fabs(track->GetEta()) > config.params("trackMaxEta")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 2
    
    // Check distance from PV
    if(fabs(track->GetDxy()) > config.params("trackMaxDxy")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 3
    
    if(fabs(track->GetXYdistanceFromBeamSpot(dataset)) > config.params("trackMaxXYdistanceFromBS")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 4
    
    if(fabs(track->GetDxy() / track->GetDxyErr()) > config.params("trackMaxDxyOverSigma")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 5
    
    if(fabs(track->GetDz()) > config.params("trackMaxDz")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 6
    
    if(fabs(track->GetZdistanceFromBeamSpot(dataset)) > config.params("trackMaxZdistanceFromBS")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 7
    
    if(fabs(track->GetDz() / track->GetDzErr()) > config.params("trackMaxDzOverSigma")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 8
    
    // Check n hits
    if(track->GetNvalidHits() < config.params("trackMinNvalidHits")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 9
    
    // Check chi2
    if(track->GetChi2() > config.params("trackMaxChi2")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 10
    
    physObjects.at(kGoodGeneralTrack).push_back(track);
  }
  physObjectsReady.at(kGoodGeneralTrack) = true;
  return physObjects.at(kGoodGeneralTrack);
}

PhysObjects Event::GetGoodPixelTracks(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(kGoodPixelTrack)) return physObjects.at(kGoodPixelTrack);
  
  physObjects.at(kGoodPixelTrack).clear();
  
  for(auto track : physObjects.at(kPixelTrack)){
    int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Check pt
    if(track->GetPt() < config.params("pixelTrackMinPt")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1
    
    // Check eta
    if(fabs(track->GetEta()) > config.params("pixelTrackMaxEta")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 2
    
    // Check n hits
    if(track->GetNvalidHits() < config.params("pixelTrackMinNvalidHits")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 9
    
    // Check chi2
    if(track->GetChi2() > config.params("pixelTrackMaxChi2")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 10
    
    physObjects.at(kGoodPixelTrack).push_back(track);
  }
  physObjectsReady.at(kGoodPixelTrack) = true;
  return physObjects.at(kGoodPixelTrack);
}

bool Event::HasAdditionalTowers()
{
  for(auto tower : physObjects.at(kCaloTower)){

    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm = tower->GetTowerSubdetEm();
        
    if(subdetHad==kHFp || subdetHad==kHFm){ // Check HF exclusivity
      if(tower->GetEnergy() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        return true;
      }
    }
    if(subdetHad==kHB || subdetHad==kHE){ // Check HB and HE exclusivity
      if(tower->GetEnergyHad() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        return true;
      }
    }
    if(subdetEm==kEB){
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if(tower->GetEnergyEm() > GetEmThresholdForTower(*tower)){
        return true;
      }
    }
    if(subdetEm==kEE){ // Check EB and EE exclusivity
      if(fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
      if(physObjectProcessor.IsInHEM(*tower)) continue;
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if(tower->GetEnergyEm() > GetEmThresholdForTower(*tower)){
        return true;
      }
    }
  }
  return false;
}

bool Event::HasAdditionalTowers(map<ECaloType, bool> &failingCalo)
{
  bool passes = true;
  for(ECaloType caloType : calotypes) failingCalo[caloType] = false;
  
  
  for(auto tower : physObjects.at(kCaloTower)){

    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    
    if((subdetHad==kHFp || subdetHad==kHFm) && !failingCalo[subdetHad]){ // Check HF exclusivity
      if(tower->GetEnergy() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        failingCalo[subdetHad] = true;
        passes = false;
      }
    }
    if((subdetHad==kHB || subdetHad==kHE) && !failingCalo[subdetHad]){ // Check HB and HE exclusivity
      if(tower->GetEnergyHad() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        failingCalo[subdetHad] = true;
        passes = false;
      }
    }
    if(subdetEm==kEB && !failingCalo[subdetEm]){ // Check EB and EE exclusivity
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if(tower->GetEnergyEm() > GetEmThresholdForTower(*tower)){
        failingCalo[subdetEm] = true;
        passes = false;
      }
    }
    if(subdetEm==kEE && !failingCalo[subdetEm]){ // Check EB and EE exclusivity
      if(fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
      if(physObjectProcessor.IsInHEM(*tower)) continue;
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if(tower->GetEnergyEm() > GetEmThresholdForTower(*tower)){
        failingCalo[subdetEm] = true;
        passes = false;
      }
    }
    
    // check if there is any calo that didn't fail yet
    bool allFailed = true;
    for(ECaloType caloType : calotypes) allFailed &= failingCalo[caloType];
    if(allFailed) break;
  }
  
  if(passes) return false;
  return true;
}

void Event::SortCaloTowersByEnergy()
{
  sort(physObjects.at(kCaloTower).begin(),
       physObjects.at(kCaloTower).end(),
       PhysObjectProcessor::CompareByEnergy());
}


bool Event::IsOverlappingWithGoodPhoton(const PhysObject &tower)
{
  bool overlapsWithPhoton = false;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  double maxDeltaEta = (subdet == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
  double maxDeltaPhi = (subdet == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
  
  for(int iPhoton=0; iPhoton<GetPhysObjects(kGoodPhoton).size(); iPhoton++){
    auto photon = GetPhysObjects(kGoodPhoton)[iPhoton];
    
    double deltaEta = fabs(photon->GetEtaSC() - tower.GetEta());
    double deltaPhi = fabs(photon->GetPhiSC() - tower.GetPhi());
    
    if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
      overlapsWithPhoton = true;
      break;
    }
  }
  return overlapsWithPhoton;
}

bool Event::IsOverlappingWithGoodElectron(const PhysObject &tower)
{
  bool overlapsWithElectron = false;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  double maxDeltaEta = (subdet == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
  double maxDeltaPhi = (subdet == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
  
  for(auto electron : GetGoodElectrons()){
    double deltaEta = fabs(electron->GetEtaSC() - tower.GetEta());
    double deltaPhi = fabs(electron->GetPhiSC() - tower.GetPhi());
    
    if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
      overlapsWithElectron = true;
      break;
    }
  }
  return overlapsWithElectron;
}

double Event::GetEmThresholdForTower(const PhysObject &tower)
{
  double threshold = -1;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  
  if(subdet==kEE && config.params("doNoiseEEetaDependant")){
    double etaStep = config.params("noiseEEetaStep");
    double etaMin = config.params("noiseEEetaMin");
    double etaMax = config.params("noiseEEetaMax");
    
    double towerEta = fabs(tower.GetEta());
    
    if(towerEta < etaMin || towerEta > etaMax) threshold = 99999;
    
    for(double eta=etaMin; eta<etaMax; eta += etaStep){
      if(towerEta > eta && towerEta < eta+etaStep){
        threshold = config.params("noiseThresholdEE_"+to_string_with_precision(eta, 1));
      }
    }
  }
  else{
    threshold = config.params("noiseThreshold"+caloName.at(subdet));
  }
  if(threshold < 0) Log(0)<<"ERROR - could not find threshold for thower !!\n";
  return threshold;
}

map<ECaloType, PhysObjects> Event::GetCaloTowersAboveThresholdByDet()
{
  map<ECaloType, PhysObjects> caloTowersByDet;
  
  for(auto tower : physObjects.at(kCaloTower)){
    
    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm  = tower->GetTowerSubdetEm();
    
    if(subdetEm == kEE && fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
    
    if(subdetHad==kHFp || subdetHad==kHFm){
      if(tower->GetEnergy() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        caloTowersByDet[subdetHad].push_back(tower);
      }
    }
    else if(subdetHad==kHB || subdetHad==kHE){
      if(physObjectProcessor.IsInCrack(*tower)) continue;
      if(tower->GetEnergyHad() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        caloTowersByDet[subdetHad].push_back(tower);
      }
    }
    else if(subdetEm == kEB || subdetEm == kEE){
      if(subdetEm == kEE && fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
      if(physObjectProcessor.IsInCrack(*tower)) continue;
      if(physObjectProcessor.IsInHEM(*tower)) continue;
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if((tower->GetEnergyEm() > GetEmThresholdForTower(*tower))){
        caloTowersByDet[subdetHad].push_back(tower);
      }
    }
  }
  return caloTowersByDet;
}
