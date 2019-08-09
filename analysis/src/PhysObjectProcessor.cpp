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

TLorentzVector PhysObjectProcessor::GetObjectsSum(const PhysObject &a, const PhysObject &b)
{
  TLorentzVector aVec, bVec;
  aVec.SetPtEtaPhiE(a.pt, a.eta, a.phi, a.energy);
  bVec.SetPtEtaPhiE(b.pt, b.eta, b.phi, b.energy);

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