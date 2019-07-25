//  PhysObject.cpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#include "PhysObject.hpp"

PhysObject::PhysObject() :
eta(9999),
phi(9999),
energy(-1),
et(-1),
pt(-1),

energyHad(-9999),
energyEm(-9999),

etaWidth(-1),
phiWidth(-1),

pdgID(0),
charge(9999)
{
  
}

PhysObject::~PhysObject()
{
  
}

ECaloType PhysObject::GetTowerSubdetHad() const
{
  if(eta > -maxEtaHF && eta < -minEtaHF) return kHFm;
  if(eta >  minEtaHF && eta <  maxEtaHF) return kHFp;
  if(fabs(eta) > 0 && fabs(eta) < maxEtaHB) return kHB;
  if(fabs(eta) > minEtaHE && fabs(eta) < maxEtaHE) return kHE;

  cout<<"ERROR - could not determine calo tower sub-det!!"<<endl;
  
  return nCaloTypes;
}

ECaloType PhysObject::GetTowerSubdetEm() const
{
  if(fabs(eta) > 0 && fabs(eta) < maxEtaEB) return kEB;
  if(fabs(eta) > minEtaEE && fabs(eta) < maxEtaEE) return kEE;
  if(eta > -maxEtaHF && eta < -minEtaHF) return kHFm;
  if(eta >  minEtaHF && eta <  maxEtaHF) return kHFp;
  
  cout<<"ERROR - could not determine calo tower sub-det!!"<<endl;
  
  return nCaloTypes;
}



double PhysObject::GetEta() const
{
  if(eta>999) cout<<"WARNING - carefull, eta probably not set"<<endl;
  return eta;
}

double PhysObject::GetPhi() const
{
  if(phi>999) cout<<"WARNING - carefull, phi probably not set"<<endl;
  return phi;
}

double PhysObject::GetEt()  const
{
  if(et<0) cout<<"WARNING - carefull, et probably not set"<<endl;
  return et;
}

double PhysObject::GetPt()  const
{
  if(pt<0) cout<<"WARNING - carefull, pt probably not set"<<endl;
  return pt;
}

double PhysObject::GetEtaWidth()  const
{
  if(etaWidth < 0)
    cout<<"WARNING - carefull, etaWidth probably not set"<<endl;
  return etaWidth;
}
double PhysObject::GetPhiWidth()  const
{
  if(phiWidth < 0) cout<<"WARNING - carefull, phiWidth probably not set"<<endl;
  return phiWidth;
}

int PhysObject::GetPID() const
{
  if(pdgID==0) cout<<"WARNING - carefull, pdgID probably not set"<<endl;
  return pdgID;
}

int PhysObject::GetCharge() const
{
  if(charge > 999) cout<<"WARNING - carefull, charge probably not set"<<endl;
  return charge;
}

double PhysObject::GetEnergy()     const
{
  if(energy<0) cout<<"WARNING - carefull, energy probably not set"<<endl;
  return energy;
}

double PhysObject::GetEnergyHad()  const
{
  if(energyHad < -999) cout<<"WARNING - carefull, energyHad probably not set"<<endl;
  return energyHad;
}

double PhysObject::GetEnergyEm()   const
{
  if(energyEm < -999) cout<<"WARNING - carefull, energyEm probably not set"<<endl;
  return energyEm;
}
