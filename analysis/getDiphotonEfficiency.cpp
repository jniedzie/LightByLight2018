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

const double maxEtaWidthBarrel = 0.02;
const double maxEtaWidthEndcap = 0.06;

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
      
      if(fabs(photonSC->GetEta()) > maxEta) continue;
      if(photonSC->GetEt() < minEt) continue;
      
      if(fabs(photonSC->GetEta()) < maxEtaEB &&
         photonSC->GetEtaWidth() > maxEtaWidthBarrel) continue;
      
      if(fabs(photonSC->GetEta()) > minEtaEE &&
         fabs(photonSC->GetEta()) < maxEtaEE &&
         photonSC->GetEtaWidth() > maxEtaWidthEndcap) continue;
      
      // Here check also other selections!
      // ...
      
      photonSCpassing.push_back(photonSC);
    }
    
    // Check if there are exactly 2 passing photon candidates
    if(photonSCpassing.size() != 2) continue;
    
    // Check exclusivity conditions
    
    
    
    
    nRecEvents++;
  }
  
  cout<<"N event analyzed: "<<iEvent<<endl;
  cout<<"N gen events within limits: "<<nGenEvents<<endl;
  cout<<"N rec events passing selection: "<<nRecEvents<<endl;
  
  cout<<"Diphoton efficiency : "<<(double)nRecEvents/nGenEvents<<endl;
  
  return 0;
}

