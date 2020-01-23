//  PhysObjectProcessor.cpp
//
//  Created by Jeremi Niedziela on 29/07/2019.

#include "PhysObjectProcessor.hpp"

PhysObjectProcessor physObjectProcessor = PhysObjectProcessor();

PhysObjectProcessor::PhysObjectProcessor()
{
  
}

PhysObjectProcessor::~PhysObjectProcessor()
{
  
}


double PhysObjectProcessor::GetDeltaR(const PhysObject &a, const PhysObject &b)
{
  return sqrt(pow(a.eta-b.eta, 2) + pow(a.phi-b.phi, 2));
}

double PhysObjectProcessor::GetDeltaR_SC(const PhysObject &a, const PhysObject &b)
{
  return sqrt(pow(a.etaSC-b.eta, 2) + pow(a.phiSC-b.phi, 2));
}

TLorentzVector PhysObjectProcessor::GetDiphoton(const PhysObject &a, const PhysObject &b)
{
  TLorentzVector aVec, bVec;
  
//  aVec.SetPtEtaPhiE(a.GetEtSC(), a.GetEtaSC(), a.GetPhiSC(), a.GetEnergySC());
//  bVec.SetPtEtaPhiE(b.GetEtSC(), b.GetEtaSC(), b.GetPhiSC(), b.GetEnergySC());
  
  aVec.SetPtEtaPhiE(a.GetEtSC(), a.GetEtaSC(), a.GetPhiSC(), a.GetEnergySC());
  bVec.SetPtEtaPhiE(b.GetEtSC(), b.GetEtaSC(), b.GetPhiSC(), b.GetEnergySC());

  return aVec + bVec;
}

TLorentzVector PhysObjectProcessor::GetDielectron(const PhysObject &a, const PhysObject &b)
{
  TLorentzVector aVec, bVec;
  
  double eleMass = 0.5109989461e-3;
  aVec.SetPtEtaPhiM(a.pt, a.eta, a.phi, eleMass);
  bVec.SetPtEtaPhiM(b.pt, b.eta, b.phi, eleMass);

  return aVec + bVec;
}

double PhysObjectProcessor::GetAcoplanarity(const PhysObject &a, const PhysObject &b)
{
  double phi1 = a.phi;
  double phi2 = b.phi;
  
  // Make sure that angles are in range [0, 2π)
  while(phi1 < 0)               phi1 += 2*TMath::Pi();
  while(phi1 >= 2*TMath::Pi())  phi1 -= 2*TMath::Pi();
  
  while(phi2 < 0)               phi2 += 2*TMath::Pi();
  while(phi2 >= 2*TMath::Pi())  phi2 -= 2*TMath::Pi();
  
  double deltaPhi = fabs(phi2-phi1);
  
  // Make sure that Δφ is in range [0, π]
  if(deltaPhi > TMath::Pi()) deltaPhi = 2*TMath::Pi() - deltaPhi;
  
  // Calcualte acoplanarity
  double aco = 1 - deltaPhi/TMath::Pi();
  
  if(aco < 0){
    cout<<"ERROR -- acoplanarity <0, which should never happen!!"<<endl;
  }
  
  return aco;
}
