//  getDiphotonEfficiency
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Calculates diphoton efficiency, defined as:
// Eff^{\gamma\gamma} = N^{reco}/N^{gen}
//
// where:
//
// N^{reco}: number of reconstructed diphoton events with E_T^{reco} > 2 GeV, |\eta^{reco}|<2.4,
// passing trigger, identification and exclusivity cuts
//
// N^{gen}: number of generated events with E_T^{gen} > 2 GeV, |\eta^{gen}|<2.4

#include "Helpers.hpp"
#include "EventProcessor.hpp"

// Eta and pt cuts
const double maxEta = 2.4;
const double minEt = 2; // GeV

// Criteria to reject photons coming from e.g. pi0 decays
const double maxEtaWidthBarrel = 0.02;
const double maxEtaWidthEndcap = 0.06;

// Criteria to match calo tower with photon SC
const double maxDeltaEtaEB = 0.15;
const double maxDeltaPhiEB = 0.7;
const double maxDeltaEtaEE = 0.15;
const double maxDeltaPhiEE = 0.4;

// Reject EE tower that are in very noisy region
const double maxEtaEEtower = 2.3;

// You can limit number of events analyzed here:
const int maxEvents = 10000;

int main()
{
  unique_ptr<EventProcessor> eventProcessor(new EventProcessor(kMClbl));
  
  int nGenEvents = 0;
  int nRecEvents = 0;
  int iEvent;
  
  for(iEvent=0; iEvent<eventProcessor->GetNevents(); iEvent++){
    if(iEvent >= maxEvents) break;
    
    auto event = eventProcessor->GetEvent(iEvent);
    
    // Check if gen event is within η and Et limits
    int nGenPhotonsPassing=0;
    
    for(int iGenPhoton=0; iGenPhoton<event->GetNgenParticles(); iGenPhoton++){
      auto genPhoton = event->GetGenParticle(iGenPhoton);
      
      if(genPhoton->GetPID() != 22) continue;
      if(fabs(genPhoton->GetEta()) > maxEta) continue;
      if(genPhoton->GetEt() < minEt) continue;
      
      nGenPhotonsPassing++;
    }
    if(nGenPhotonsPassing == 2) nGenEvents++;
    
    // Check if event has any of the LbL triggers
    if(!event->HasLbLTrigger()) continue;
    
    // Find photon candidates
    vector<shared_ptr<PhysObject>> photonSCpassing;
    
    for(int iPhotonSC=0; iPhotonSC<event->GetNphotonSCs(); iPhotonSC++){
      auto photonSC = event->GetPhotonSC(iPhotonSC);

      // Check eta and Et
      if(fabs(photonSC->GetEta()) > maxEta) continue;
      if(photonSC->GetEt() < minEt) continue;
      
      // Check η shower shape
      if(fabs(photonSC->GetEta()) < maxEtaEB &&
         photonSC->GetEtaWidth() > maxEtaWidthBarrel) continue;
      
      if(fabs(photonSC->GetEta()) > minEtaEE &&
         fabs(photonSC->GetEta()) < maxEtaEE &&
         photonSC->GetEtaWidth() > maxEtaWidthEndcap) continue;
      
      photonSCpassing.push_back(photonSC);
    }
    
    // Check if there are exactly 2 passing photon candidates
    if(photonSCpassing.size() != 2) continue;
    
    // Neutral exclusivity
    
    bool hasAdditionalTowers = false;
    
    
    for(int iTower=0; iTower<event->GetNcaloTowers(); iTower++){
      auto tower = event->GetCaloTower(iTower);
      
      double energyHad = tower->GetEnergyHad();
      
      if(energyHad > 0){
        if(energyHad > caloNoiseThreshold[tower->GetTowerSubdetHad()]){
          hasAdditionalTowers = true;
          break;
        }
      }
      
      // Check if tower is above the noise threshold
      bool overlapsWithPhoton = false;
      
      ECaloType subdetEm = tower->GetTowerSubdetEm();
      
      if(subdetEm == kEE && fabs(tower->GetEta()) > maxEtaEEtower) continue;
      
      double maxDeltaEta = (subdetEm == kEB ) ? maxDeltaEtaEB : maxDeltaEtaEE;
      double maxDeltaPhi = (subdetEm == kEB ) ? maxDeltaPhiEB : maxDeltaPhiEE;
        
      for(int iPhotonSC=0; iPhotonSC<event->GetNphotonSCs(); iPhotonSC++){
        auto photon = event->GetPhotonSC(iPhotonSC);
        
        double deltaEta = fabs(photon->GetEta() - tower->GetEta());
        double deltaPhi = fabs(photon->GetPhi() - tower->GetPhi());
        
        if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
          overlapsWithPhoton = true;
          break;
        }
      }
      
      if(!overlapsWithPhoton){
        if(tower->GetEnergyEm() > caloNoiseThreshold[subdetEm]){
          hasAdditionalTowers = true;
          break;
        }
      }
    }
    if(hasAdditionalTowers) continue;
    
    nRecEvents++;
  }
  
  cout<<"N event analyzed: "<<iEvent<<endl;
  cout<<"N gen events within limits: "<<nGenEvents<<endl;
  cout<<"N rec events passing selection: "<<nRecEvents<<endl;
  
  cout<<"Diphoton efficiency : "<<(double)nRecEvents/nGenEvents<<endl;
  
  return 0;
}

