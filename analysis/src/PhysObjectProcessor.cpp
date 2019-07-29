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
