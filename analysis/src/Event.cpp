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

bool Event::HasLbLTrigger() const
{
  for(auto &[triggerName, fired] : triggersLbL){
    if(fired) return true;
  }
  return false;
}

bool Event::HasSingleEG3Trigger()
{
  return triggersLbL["HLT_HIUPC_SingleEG3_NotMBHF2AND_v1"];
}

bool Event::HasDoubleEG2Trigger()
{
  return triggersLbL["HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1"];
}

vector<shared_ptr<PhysObject>> Event::GetGoodGenPhotons() const
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

double Event::GetDiphotonInvMass()
{
  if(!passingPhotonSCready) GetGoodPhotonSCs();
  
  if(photonSCpassing.size() !=2 ){
    cout<<"ERROR - asked for inv mass of diphoton, but n!=2"<<endl;
    return 0;
  }
  
  TLorentzVector pho1, pho2;
  
  pho1.SetPtEtaPhiE(photonSCpassing[0]->GetEt(),
                    photonSCpassing[0]->GetEta(),
                    photonSCpassing[0]->GetPhi(),
                    photonSCpassing[0]->GetEnergy());
  
  pho2.SetPtEtaPhiE(photonSCpassing[1]->GetEt(),
                    photonSCpassing[1]->GetEta(),
                    photonSCpassing[1]->GetPhi(),
                    photonSCpassing[1]->GetEnergy());
  
  TLorentzVector diphoton = pho1+pho2;
  
  return diphoton.M();
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

bool Event::HasChargedTracks() const
{
  if(nElectrons != 0) return true;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    auto track = generalTracks[iTrack];
    if(track->GetPt() > config.params["trackMinPt"]) return true;
  }
  return false;
}
