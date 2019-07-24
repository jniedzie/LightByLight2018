//  Event.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Event.hpp"

Event::Event()
{
  for(auto triggerName : triggerNamesLbL) triggersLbL.push_back(0);
}

Event::~Event()
{
  
}

bool Event::HasLbLTrigger()
{
  for(int trigger : triggersLbL){
    if(trigger != 0) return true;
  }
  return false;
}

vector<shared_ptr<PhysObject>> Event::GetGoodGenPhotons()
{
  vector<shared_ptr<PhysObject>> goodGenPhotons;
  
  for(int iGenPhoton=0; iGenPhoton<nGenParticles; iGenPhoton++){
    auto genPhoton = genParticles[iGenPhoton];
    
    if(genPhoton->GetPID() != 22) continue;
    if(fabs(genPhoton->GetEta()) > config.params["maxEta"]) continue;
    if(genPhoton->GetEt() < config.params["minEt"]) continue;
    
    goodGenPhotons.push_back(genPhoton);
  }
  
  return goodGenPhotons;
}

vector<shared_ptr<PhysObject>> Event::GetGoodPhotonSCs()
{
  photonSCpassing.clear();
  
  for(int iPhotonSC=0; iPhotonSC<nPhotonSCs; iPhotonSC++){
    auto cluster = photonSC[iPhotonSC];
    
    // Check eta and Et
    if(fabs(cluster->GetEta()) > config.params["maxEta"]) continue;
    if(cluster->GetEt() < config.params["minEt"]) continue;
    
    // Check η shower shape
    if(fabs(cluster->GetEta()) < maxEtaEB &&
       cluster->GetEtaWidth() > config.params["maxEtaWidthBarrel"]) continue;
    
    if(fabs(cluster->GetEta()) > minEtaEE &&
       fabs(cluster->GetEta()) < maxEtaEE &&
       cluster->GetEtaWidth() > config.params["maxEtaWidthEndcap"]) continue;
    
    photonSCpassing.push_back(cluster);
  }
  passingPhotonSCready = true;
  return photonSCpassing;
}

bool Event::HasAdditionalTowers()
{
  if(!passingPhotonSCready) GetGoodPhotonSCs();
  
  for(int iTower=0; iTower<nCaloTowers; iTower++){
    auto tower = caloTowers[iTower];
    
    double energyHad = tower->GetEnergyHad();
    
    if(energyHad > 0){
      if(energyHad > caloNoiseThreshold[tower->GetTowerSubdetHad()]) return true;
    }
    
    // Check if tower is above the noise threshold
    bool overlapsWithPhoton = false;
    
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    if(subdetEm == kEE && fabs(tower->GetEta()) > config.params["maxEtaEEtower"]) continue;
    
    double maxDeltaEta = (subdetEm == kEB ) ? config.params["maxDeltaEtaEB"] : config.params["maxDeltaEtaEE"];
    double maxDeltaPhi = (subdetEm == kEB ) ? config.params["maxDeltaPhiEB"] : config.params["maxDeltaPhiEE"];
    
    for(int iPhotonSC=0; iPhotonSC<photonSCpassing.size(); iPhotonSC++){
      auto photon = photonSCpassing[iPhotonSC];
      
      double deltaEta = fabs(photon->GetEta() - tower->GetEta());
      double deltaPhi = fabs(photon->GetPhi() - tower->GetPhi());
      
      if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
        overlapsWithPhoton = true;
        break;
      }
    }
    
    if(!overlapsWithPhoton){
      if(tower->GetEnergyEm() > caloNoiseThreshold[subdetEm]) return true;
    }
  }
  return false;
}

bool Event::HasChargedTracks()
{
  if(nElectrons != 0) return true;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    auto track = generalTracks[iTrack];
    if(track->GetPt() > config.params["trackMinPt"]) return true;
  }
  return false;
}
