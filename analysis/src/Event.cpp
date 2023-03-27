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
  if(   type == EPhysObjType::kGenParticle
     || type == EPhysObjType::kPhoton
     || type == EPhysObjType::kElectron
     || type == EPhysObjType::kMuon
     || type == EPhysObjType::kCaloTower
     || type == EPhysObjType::kCastor
     || type == EPhysObjType::kGeneralTrack
     || type == EPhysObjType::kL1EG
     || type == EPhysObjType::kZDC
     || type == EPhysObjType::kPixelTrack
     || type == EPhysObjType::kVertex){
    return physObjects.at(type);
  }
  else if(type == EPhysObjType::kGoodGenPhoton)       return GetGoodGenPhotons();
  else if(type == EPhysObjType::kPhotonInAcceptance)  return GetPhotonsInAcceptance();
  else if(type == EPhysObjType::kGoodPhoton)          return GetGoodPhotons();
  else if(type == EPhysObjType::kGoodGenElectron)     return GetGoodGenElectrons();
  else if(type == EPhysObjType::kElectronInAcceptance)return GetElectronsInAcceptance();
  else if(type == EPhysObjType::kGoodElectron)        return GetGoodElectrons(cutFlowHist);
  else if(type == EPhysObjType::kGoodMatchedElectron) return GetGoodMatchedElectron();
  else if(type == EPhysObjType::kGoodMuon)            return GetGoodMuons(cutFlowHist);
  else if(type == EPhysObjType::kGoodGeneralTrack)    return GetGoodGeneralTracks(cutFlowHist);
  else if(type == EPhysObjType::kGoodPixelTrack)      return GetGoodPixelTracks(cutFlowHist);
  
  Log(0)<<"ERROR -- unrecognized phys object type: "<<(int)type<<"!!!\n";
  return PhysObjects();
}

PhysObjects Event::GetGoodGenPhotons() const
{
  PhysObjects goodGenPhotons;
  
  for(auto genPhoton : physObjects.at(EPhysObjType::kGenParticle)){
    
    if(genPhoton->GetPID() != 22) continue;
    if(fabs(genPhoton->GetEta()) > config.params("photonMaxEta")) continue;
    if(genPhoton->GetEt() < config.params("photonMinEt")) continue;
    if(physObjectProcessor.IsInCrack(*genPhoton)) continue;
    if(physObjectProcessor.IsInHEM(*genPhoton)) continue;
 
    goodGenPhotons.push_back(genPhoton);
  }
  
  return goodGenPhotons;
}

PhysObjects Event::GetGoodGenElectrons() const
{
  PhysObjects goodGenElectrons;

  for(auto genElectron : physObjects.at(EPhysObjType::kGenParticle)){

    //if(genElectron->GetPID() != 11 || genElectron->GetPID() != -11) continue;
    if(fabs(genElectron->GetEta()) > config.params("electronMaxEta")) continue;
    if(genElectron->GetEt() < config.params("electronMinPt")) continue;
    if(physObjectProcessor.IsInCrack(*genElectron)) continue;
    if(physObjectProcessor.IsInHEM(*genElectron)) continue;

    goodGenElectrons.push_back(genElectron);
  }

  return goodGenElectrons;
}

PhysObjects Event::GetPhotonsInAcceptance()
{
  if(physObjectsReady.at(EPhysObjType::kPhotonInAcceptance)) return physObjects.at(EPhysObjType::kPhotonInAcceptance);
  
  physObjects.at(EPhysObjType::kPhotonInAcceptance).clear();
  
  for(auto photon : physObjects.at(EPhysObjType::kPhoton)){
    
   
    // Check Et
    if(photon->GetEt() < config.params("photonMinEt")) continue;
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEta());
    if(absEta > config.params("photonMaxEta")) continue;
    if(physObjectProcessor.IsInCrack(*photon)) continue;
    if(physObjectProcessor.IsInHEM(*photon)) continue;
    
    
    physObjects.at(EPhysObjType::kPhotonInAcceptance).push_back(photon);
  }
  physObjectsReady.at(EPhysObjType::kPhotonInAcceptance) = true;
  return physObjects.at(EPhysObjType::kPhotonInAcceptance);
}

PhysObjects Event::GetGoodPhotons()
{
  if(physObjectsReady.at(EPhysObjType::kGoodPhoton)) return physObjects.at(EPhysObjType::kGoodPhoton);
  
  physObjects.at(EPhysObjType::kGoodPhoton).clear();
  
  for(auto photon : physObjects.at(EPhysObjType::kPhoton)){
    
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
      if(swissCross > config.params("photonMinSwissCross")) continue;
    }
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEta());
    if(absEta > config.params("photonMaxEta")) continue;
    if(physObjectProcessor.IsInCrack(*photon)) continue;
    if(physObjectProcessor.IsInHEM(*photon)) continue;
    
    // Check η shower shape
    if((absEta < maxEtaEB) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthBarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthEndcap"))) continue;
    
    if((absEta < maxEtaEB) && (photon->GetSigmaEta2012() > config.params("photonMaxSigmaEta2012Barrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetSigmaEta2012() > config.params("photonMaxSigmaEta2012Endcap"))) continue;
    
    
    // Check H/E
    if((absEta < maxEtaEB) && (photon->GetHoverE() > config.params("photonMaxHoverEbarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetHoverE() > config.params("photonMaxHoverEendcap"))) continue;
    
    physObjects.at(EPhysObjType::kGoodPhoton).push_back(photon);
  }
  physObjectsReady.at(EPhysObjType::kGoodPhoton) = true;
  return physObjects.at(EPhysObjType::kGoodPhoton);
}

PhysObjects Event::GetElectronsInAcceptance()
{
  if(physObjectsReady.at(EPhysObjType::kElectronInAcceptance)) return physObjects.at(EPhysObjType::kElectronInAcceptance);
  
  physObjects.at(EPhysObjType::kElectronInAcceptance).clear();
  
  for(auto electron : physObjects.at(EPhysObjType::kElectron)){
    
   
    // Check Et
    if(electron->GetPt() < config.params("electronMinPt")) continue;
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(electron->GetEta());
    if(absEta > config.params("electronMaxEta")) continue;
    if(physObjectProcessor.IsInCrack(*electron)) continue;
    if(physObjectProcessor.IsInHEM(*electron)) continue;
    
    
    physObjects.at(EPhysObjType::kElectronInAcceptance).push_back(electron);
  }
  physObjectsReady.at(EPhysObjType::kElectronInAcceptance) = true;
  return physObjects.at(EPhysObjType::kElectronInAcceptance);
}


PhysObjects Event::GetGoodElectrons(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(EPhysObjType::kGoodElectron)) return physObjects.at(EPhysObjType::kGoodElectron);
  
  physObjects.at(EPhysObjType::kGoodElectron).clear();
  
  for(auto electron : physObjects.at(EPhysObjType::kElectron)){
    int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Keep or reject electrons coming from photon conversion
    if(electron->IsFromConversion() && config.params("skipElectronsFromConversions")) continue;
    
    // Check pt
    if(electron->GetPt() < config.params("electronMinPt")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1
    
    // Check eta
    double eta = fabs(electron->GetEtaSC());
    if(physObjectProcessor.IsInCrack(*electron)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 2
    
    if(eta >= config.params("electronMaxEta")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 3
    
    // Check for HEM issue
    if(physObjectProcessor.IsInHEM(*electron)) continue;
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
    
    physObjects.at(EPhysObjType::kGoodElectron).push_back(electron);
  }
  physObjectsReady.at(EPhysObjType::kGoodElectron) = true;
  return physObjects.at(EPhysObjType::kGoodElectron);
}

PhysObjects Event::GetGoodMuons(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(EPhysObjType::kGoodMuon)) return physObjects.at(EPhysObjType::kGoodMuon);
  
  physObjects.at(EPhysObjType::kGoodMuon).clear();
  
  for(auto muon : physObjects.at(EPhysObjType::kMuon)){
     int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 0
    
    // Check pt
   // if(muon->GetPt() < config.params("muonMinPt")) continue;
   // if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 1 
    
//    if(fabs(muon->GetEta()) >= config.params("muonMaxEta")) continue;// ADD date: 29/12/2022, for the max eta cut
  //  double absEta = fabs(muon->GetEta());
   // if((absEta < config.params("muonMaxEtaEB")) && (muon->GetPt() < config.params("muonMinPtEB"))) continue;
   // else if(((absEta > config.params("muonMinEtaEE")) && absEta < config.params("muonMaxEtaEE")) && (muon->GetPt() < config.params("muonMinPtEE"))) continue;


//    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++); // 3
//Soft Muons ID
   //OneMuonStation tight   
     //if(config.params("muonOnestationTight") && muon->IsGood()) continue;
   // if(muon->GetIsGood() == config.params("muonOnestationTight")) continue;
    //if(muon->GetIsGlobal() < config.params("muonGlobal")) continue;
    //if(muon->GetIsTracker() < config.params("muonTracker")) continue;
    // if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
   //Min innertracker layers
   // if(muon->GetTrkLayers() <= config.params("muonMinTrkInnLayers")) continue; 
   //Min. PixelLayers
   // if(muon->GetPixelLayers() < config.params("muonMinTrkPixelLayers")) continue;
   //InnerTrack Quality
   // if(config.params("muonTrkQuality") && muon->TrkQuality()) continue;
    // if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
   // max dxy
  //  if(fabs(muon->GetInnerD0()) > config.params("muonMaxDxy")) continue;
   //Max dz
  //  if(fabs(muon->GetInnerDz()) > config.params("muonMaxDz")) continue;


    physObjects.at(EPhysObjType::kGoodMuon).push_back(muon);
  }
  physObjectsReady.at(EPhysObjType::kGoodMuon) = true;
  return physObjects.at(EPhysObjType::kGoodMuon);
}


PhysObjects Event::GetGoodMatchedElectron()
{
  if(physObjectsReady.at(EPhysObjType::kGoodMatchedElectron)){
    return physObjects.at(EPhysObjType::kGoodMatchedElectron);
  }
  
  physObjects.at(EPhysObjType::kGoodMatchedElectron).clear();
  
  for(auto electron : GetPhysObjects(EPhysObjType::kGoodElectron)){
    for(auto &L1EG : GetPhysObjects(EPhysObjType::kL1EG)){
      if(L1EG->GetEt() < 2.0) continue;
      
      if(physObjectProcessor.GetDeltaR_SC(*electron, *L1EG) < 0.3){
        physObjects.at(EPhysObjType::kGoodMatchedElectron).push_back(electron);
        break;
      }
    }
  }
  
  physObjectsReady.at(EPhysObjType::kGoodMatchedElectron) = true;
  return physObjects.at(EPhysObjType::kGoodMatchedElectron);
}

PhysObjects Event::GetGoodGeneralTracks(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(EPhysObjType::kGoodGeneralTrack)){
    return physObjects.at(EPhysObjType::kGoodGeneralTrack);
  }
    
  physObjects.at(EPhysObjType::kGoodGeneralTrack).clear();
  
  for(auto track : physObjects.at(EPhysObjType::kGeneralTrack)){
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
    
    physObjects.at(EPhysObjType::kGoodGeneralTrack).push_back(track);
  }
  physObjectsReady.at(EPhysObjType::kGoodGeneralTrack) = true;
  return physObjects.at(EPhysObjType::kGoodGeneralTrack);
}

PhysObjects Event::GetGoodPixelTracks(TH1D *cutFlowHist)
{
  if(physObjectsReady.at(EPhysObjType::kGoodPixelTrack)){
    return physObjects.at(EPhysObjType::kGoodPixelTrack);
  }
  
  physObjects.at(EPhysObjType::kGoodPixelTrack).clear();
  
  for(auto track : physObjects.at(EPhysObjType::kPixelTrack)){
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
    
    physObjects.at(EPhysObjType::kGoodPixelTrack).push_back(track);
  }
  physObjectsReady.at(EPhysObjType::kGoodPixelTrack) = true;
  return physObjects.at(EPhysObjType::kGoodPixelTrack);
}

//////////////////////////////////////////////////////////////////

constexpr std::array<double, 42> etaedge = {
      {0.000, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.870, 0.957, 1.044, 1.131,
       1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.740, 1.830, 1.930, 2.043, 2.172, 2.322, 2.500, 2.650,
       2.853, 3.000, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191}};

static constexpr int ietaMax = 42;

template <class valType>
  inline constexpr valType make0To2pi(valType angle) {
    constexpr valType twoPi = 2*M_PI;
    constexpr valType oneOverTwoPi = 1. / twoPi;
    constexpr valType epsilon = 1.e-13;

    if ((std::abs(angle) <= epsilon) || (std::abs(twoPi - std::abs(angle)) <= epsilon))
      return (0.);
    if (std::abs(angle) > twoPi) {
      valType nFac = trunc(angle * oneOverTwoPi);
      angle -= (nFac * twoPi);
      if (std::abs(angle) <= epsilon)
        return (0.);
    }
    if (angle < 0.)
      angle += twoPi;
    return (angle);
  }



// helper functions
int eta2ieta(double eta) {
  // binary search in the array of towers eta edges

  int ieta = 1;
  double xeta = fabs(eta);
  while (xeta > etaedge[ieta] && ieta < ietaMax - 1) {
    ++ieta;
  }

  if (eta < 0)
    ieta = -ieta;
  return ieta;
}

int phi2iphi(double phi, int ieta){
  phi = make0To2pi(phi);
  int nphi = 72;
  int n = 1;
  if (abs(ieta) > 20)
    n = 2;
  if (abs(ieta) >= 40)
    n = 4;

  int iphi = (int)std::ceil(phi / 2.0 / M_PI * nphi / n);

  iphi = n * (iphi - 1) + 1;

  return iphi;
}

//////////////////////////////////////////////////////////////////

bool Event::HasAdditionalTowers()
{
  for(auto tower : physObjects.at(EPhysObjType::kCaloTower)){

    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm = tower->GetTowerSubdetEm();

    int ieta = eta2ieta(tower->GetEta());

    if(subdetHad==kHFp || subdetHad==kHFm){ // Check HF exclusivity
      if(subdetHad==kHFp && (ieta == 29 || ieta == 30)) continue;
      if(subdetHad==kHFm && (ieta == -29 || ieta == -30)) continue;    

      if(tower->GetEnergy() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        return true;
      }
    }
    if(subdetHad==kHB || subdetHad==kHE){ // Check HB and HE exclusivity
      if(subdetHad==kHE && (ieta == 16 || ieta == -16 )) continue;
      
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
      //if(ieta == 27 || ieta == 28 || ieta == 29 || ieta == -27 || ieta == -28 || ieta == -29) continue;
      if(fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
      if(physObjectProcessor.IsInHEM(*tower)) continue;
      if(IsOverlappingWithGoodPhoton(*tower)) continue;
      if(IsOverlappingWithGoodElectron(*tower)) continue;
      
      if(tower->GetEnergyEm() > GetEmThresholdForTower(*tower)){
        return true;
      }
    }
  }

/*    if(subdetHad==kHFp || subdetHad==kHFm){ // Check HF exclusivity
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
*/
  // Check castor towers too
  if(config.params("doCASTOR")){
    return HasCastorTowers();
  }

  return false;
}

bool Event::HasCastorTowers(){
  for(auto castor : physObjects.at(EPhysObjType::kCastor)){
    if(castor->GetEnergy() > GetCastorThreshold(*castor))
      return true;
  }
  return false;
}

bool Event::HasAdditionalTowers(map<ECaloType, bool> &failingCalo)
{
  bool passes = true;
  for(ECaloType caloType : calotypes) failingCalo[caloType] = false;
  
  
  for(auto tower : physObjects.at(EPhysObjType::kCaloTower)){

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
  sort(physObjects.at(EPhysObjType::kCaloTower).begin(),
       physObjects.at(EPhysObjType::kCaloTower).end(),
       PhysObjectProcessor::CompareByEnergy());
}


bool Event::IsOverlappingWithGoodPhoton(const PhysObject &tower)
{
  bool overlapsWithPhoton = false;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  double maxDeltaEta = (subdet == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
  double maxDeltaPhi = (subdet == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
  
  for(int iPhoton=0; iPhoton<GetPhysObjects(EPhysObjType::kGoodPhoton).size(); iPhoton++){
    auto photon = GetPhysObjects(EPhysObjType::kGoodPhoton)[iPhoton];
    
    double deltaEta = fabs(photon->GetEtaSC() - tower.GetEta());
    double deltaPhi = fabs(TVector2::Phi_mpi_pi(photon->GetPhiSC() - tower.GetPhi()));
    
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
    double deltaPhi = fabs(TVector2::Phi_mpi_pi(electron->GetPhiSC() - tower.GetPhi()));
    
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

double Event::GetCastorThreshold(const PhysObject &castor)
{
  double threshold;

  if(config.params("doNoiseCASTORphiDependant")){
    int index;
    
    // converting CASTOR phi to index=0-15
    vector<double> possiblePhiValues = {-2.95,-2.55,-2.16,-1.77,-1.37,-0.98,-0.59,-0.20,0.20,0.59,0.98,1.37,1.77,2.16,2.55,2.95};
    for(unsigned int i = 0; i < possiblePhiValues.size(); i++)
      if(fabs(possiblePhiValues[i]-castor.GetPhi()) < 0.2)
        index = i;
    
    threshold = config.params("noiseThresholdCASTOR_"+to_string(index));
  }
  else{
    threshold = config.params("noiseThresholdCASTOR");
  }

  return threshold;
}




map<ECaloType, PhysObjects> Event::GetCaloTowersAboveThresholdByDet()
{
  map<ECaloType, PhysObjects> caloTowersByDet;
  
  for(auto tower : physObjects.at(EPhysObjType::kCaloTower)){
    
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

double Event::GetTotalZDCenergy() const
{
  double zdcEnergySum = 0;
  for(auto zdc : physObjects.at(EPhysObjType::kZDC)) zdcEnergySum += zdc->GetEnergy();
  return zdcEnergySum;
}

double Event::GetTotalZDCenergyPos() const
{
  double zdcEnergySum = 0;
  for(auto zdc : physObjects.at(EPhysObjType::kZDC)){
    if(zdc->GetZside() > 0) zdcEnergySum += zdc->GetEnergy();
  }
  return zdcEnergySum;
}

double Event::GetTotalZDCenergyNeg() const
{
  double zdcEnergySum = 0;
  for(auto zdc : physObjects.at(EPhysObjType::kZDC)){
    if(zdc->GetZside() < 0) zdcEnergySum += zdc->GetEnergy();
  }
  return zdcEnergySum;
}
