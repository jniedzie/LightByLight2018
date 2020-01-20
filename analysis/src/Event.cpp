//  Event.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Event.hpp"

Event::Event()
{

}

Event::~Event()
{

}

void Event::Reset()
{
  genParticles.clear();
  photons.clear();
  goodPhotons.clear();
  caloTowers.clear();
  generalTracks.clear();
  electrons.clear();
  goodElectrons.clear();
  L1EGs.clear();
  
  goodPhotonsReady = false;
  goodElectronsReady = false;
}

bool Event::HasSingleEG3Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG3_NotMBHF2AND_v1");
}

bool Event::HasSingleEG5Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG5_NotMBHF2AND_v1");
}

bool Event::HasDoubleEG2Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1");
}

bool Event::HasSingleEG3noHFvetoTrigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG3_BptxAND_SinglePixelTrack_MaxPixelTrack_v1");
}

vector<shared_ptr<PhysObject>> Event::GetGoodGenPhotons() const
{
  vector<shared_ptr<PhysObject>> goodGenPhotons;
  
  for(int iGenPhoton=0; iGenPhoton<nGenParticles; iGenPhoton++){
    auto genPhoton = genParticles[iGenPhoton];
    
    if(genPhoton->GetPID() != 22) continue;
    if(fabs(genPhoton->GetEta()) > config.params("maxEta")) continue;
    if(genPhoton->GetEt() < config.params("minEt")) continue;
    
    goodGenPhotons.push_back(genPhoton);
  }
  
  return goodGenPhotons;
}

vector<shared_ptr<PhysObject>> Event::GetGoodPhotons()
{
  goodPhotons.clear();
  
  for(int iPhoton=0; iPhoton<nPhotons; iPhoton++){
    auto photon = photons[iPhoton];
    
    // Check Et
    if(photon->GetEt() < config.params("photonMinEt")) continue;
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEtaSC());
    if(absEta > config.params("photonMaxEta")) continue;
    if(absEta > config.params("ecalCrackMin") && absEta < config.params("ecalCrackMax")) continue;
    if(photon->GetEtaSC() < -minEtaEE &&
       photon->GetPhiSC() > config.params("ecalHEMmin") &&
       photon->GetPhiSC() < config.params("ecalHEMmax")) continue;
    
    // Check η shower shape
    if((absEta < maxEtaEB) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthBarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthEndcap"))) continue;
    
    // Check H/E
    if((absEta < maxEtaEB) && (photon->GetHoverE() > config.params("photonMaxHoverEbarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetHoverE() > config.params("photonMaxHoverEendcap"))) continue;
    
    goodPhotons.push_back(photon);
  }
  goodPhotonsReady = true;
  return goodPhotons;
}

vector<shared_ptr<PhysObject>> Event::GetGoodElectrons()
{
  goodElectrons.clear();
  
  for(auto electron : electrons){

    // Check pt
    if(electron->GetPt() < config.params("electronMinPt")) continue;
    
    // Check eta
    double eta = fabs(electron->GetEtaSC());
    if(eta > config.params("ecalCrackMin") &&
       eta < config.params("ecalCrackMax"))   continue;
    if(eta >= config.params("electronMaxEta")) continue;
    
    // Check for HEM issue
    if(electron->GetEtaSC() < -minEtaEE &&
       electron->GetPhiSC() > config.params("ecalHEMmin") &&
       electron->GetPhiSC() < config.params("ecalHEMmax")) continue;
    
    // Check n missing hits
    if(electron->GetNmissingHits() > config.params("electronMaxNmissingHits")) continue;
    
    string subdet = "";
    if((eta < maxEtaEB)) subdet = "Barrel";
    else if((eta < maxEtaEE)) subdet = "Endcap";
    
    // Check H/E
    if(electron->GetHoverE() >= config.params("electronMaxHoverE_"+subdet)) continue;
    
    // Check Δη at vertex
    if(electron->GetDetaSeed() >= config.params("electronMaxDetaSeed"+subdet)) continue;
    
    // Check isolation
    if(electron->GetChargedIso() >= config.params("electronMaxChargedIso"+subdet)) continue;
    if(electron->GetPhotonIso()  >= config.params("electronMaxPhotonIso" +subdet))  continue;
    if(electron->GetNeutralIso() >= config.params("electronMaxNeutralIso"+subdet)) continue;

    goodElectrons.push_back(electron);
  }
  return goodElectrons;
}

double Event::GetDiphotonInvMass()
{
  if(!goodPhotonsReady) GetGoodPhotons();
  
  if(goodPhotons.size() !=2 ) return -1;
  
  TLorentzVector pho1, pho2;
  
  pho1.SetPtEtaPhiE(goodPhotons[0]->GetEt(),
                    goodPhotons[0]->GetEta(),
                    goodPhotons[0]->GetPhi(),
                    goodPhotons[0]->GetEnergy());
  
  pho2.SetPtEtaPhiE(goodPhotons[1]->GetEt(),
                    goodPhotons[1]->GetEta(),
                    goodPhotons[1]->GetPhi(),
                    goodPhotons[1]->GetEnergy());
  
  TLorentzVector diphoton = pho1+pho2;
  
  return diphoton.M();
}

bool Event::DiphotonPtAboveThreshold()
{
  if(!goodPhotonsReady) GetGoodPhotons();
  
  if(goodPhotons.size() != 2) return true;
  
  double pt_1 = goodPhotons[0]->GetEt();
  double pt_2 = goodPhotons[1]->GetEt();
  double deltaPhi = goodPhotons[0]->GetPhi() - goodPhotons[1]->GetPhi();
  
  double pairPt = sqrt(pt_1*pt_1 + pt_2*pt_2 + 2*pt_1*pt_2*cos(deltaPhi));
  if(pairPt > config.params("diphotonMaxPt")) return true;
  
  return false;
}

bool Event::HasAdditionalTowers()
{
  if(!goodPhotonsReady) GetGoodPhotons();
  
  for(int iTower=0; iTower<nCaloTowers; iTower++){
    auto tower = caloTowers[iTower];
    
    double energyHad = tower->GetEnergyHad();
    
    if(energyHad > 0){
      if(energyHad > caloNoiseThreshold.at(tower->GetTowerSubdetHad())) return true;
    }
    
    // Check if tower is above the noise threshold
    bool overlapsWithPhoton = false;
    
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    if(subdetEm == kEE && fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
    
    double maxDeltaEta = (subdetEm == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
    double maxDeltaPhi = (subdetEm == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
    
    for(int iPhotonSC=0; iPhotonSC<goodPhotons.size(); iPhotonSC++){
      auto photon = goodPhotons[iPhotonSC];
      
      double deltaEta = fabs(photon->GetEta() - tower->GetEta());
      double deltaPhi = fabs(photon->GetPhi() - tower->GetPhi());
      
      if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
        overlapsWithPhoton = true;
        break;
      }
    }
    
    if(!overlapsWithPhoton){
      if(tower->GetEnergyEm() > caloNoiseThreshold.at(subdetEm)) return true;
    }
  }
  return false;
}

bool Event::HasChargedTracks() const
{
  if(nElectrons != 0) return true;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    auto track = generalTracks[iTrack];
    if(track->GetPt() > config.params("trackMinPt")) return true;
  }
  return false;
}

int Event::GetNchargedTracks() const
{
  int nTracks=0;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    if(generalTracks[iTrack]->GetPt() > config.params("trackMinPt")) nTracks++;
  }
  return nTracks;
}
