//  PhysObject.cpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#include "PhysObject.hpp"

PhysObject::PhysObject() :
eta(9999),
phi(9999),
energy(-1),

etaSC(9999),
etSC(-9999),
phiSC(9999),
energySC(-1),

et(-1),
pt(-1),

energyHad(-9999),
energyEm(-9999),
energyTop(-9999),
energyBottom(-9999),
energyLeft(-9999),
energyRight(-9999),

etaWidth(-9999),
phiWidth(-9999),
hOverE(-9999),

pdgID(0),
charge(9999),
nMissingHits(-1),
nValidHits(-1),

chargedIso(-9999),
photonIso(-9999),
neutralIso(-9999),

relIsoWithEA(-9999),
dEtaSeed(-9999)
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
  if(eta > -maxEtaHF && eta < -minEtaHF) return kHFm;
  if(eta >  minEtaHF && eta <  maxEtaHF) return kHFp;
  
  if(fabs(eta) > 0 && fabs(eta) < maxEtaEB) return kEB;
  if(fabs(eta) > minEtaEE && fabs(eta) < maxEtaEE) return kEE;
  
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
  if(et < 0) cout<<"WARNING - carefull, et probably not set"<<endl;
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

double PhysObject::GetHoverE()  const
{
  if(hOverE < 0) cout<<"WARNING - carefull, hOverE probably not set"<<endl;
  return hOverE;
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

int PhysObject::GetNmissingHits() const
{
  if(nMissingHits < 0) cout<<"WARNING - carefull, nMissingHits probably not set"<<endl;
  return nMissingHits;
}

int PhysObject::GetNvalidHits() const
{
  if(nValidHits < 0) cout<<"WARNING - carefull, nValidHits probably not set"<<endl;
  return nValidHits;
}

double PhysObject::GetEnergy()     const
{
  if(energy<0) cout<<"WARNING - carefull, energy probably not set"<<endl;
  return energy;
}

double PhysObject::GetEnergyHad() const
{
  if(energyHad < -999) cout<<"WARNING - carefull, energyHad probably not set"<<endl;
  return energyHad;
}

double PhysObject::GetEnergyCrystalTop() const
{
  if(energyTop < -999) cout<<"WARNING - carefull, energyTop probably not set"<<endl;
  return energyTop;
}

double PhysObject::GetEnergyCrystalBottom() const
{
  if(energyBottom < -999) cout<<"WARNING - carefull, energyBottom probably not set"<<endl;
  return energyBottom;
}

double PhysObject::GetEnergyCrystalLeft() const
{
  if(energyLeft < -999) cout<<"WARNING - carefull, energyLeft probably not set"<<endl;
  return energyLeft;
}

double PhysObject::GetEnergyCrystalRight() const
{
  if(energyRight < -999) cout<<"WARNING - carefull, energyRight probably not set"<<endl;
  return energyRight;
}

double PhysObject::GetEnergyEm() const
{
  if(energyEm < -999) cout<<"WARNING - carefull, energyEm probably not set"<<endl;
  return energyEm;
}

double PhysObject::GetEtaSC() const
{
  if(etaSC > 999) cout<<"WARNING - carefull, etaSC probably not set"<<endl;
  return etaSC;
}

double PhysObject::GetEtSC() const
{
  if(etSC < 0) cout<<"WARNING - carefull, etSC probably not set"<<endl;
  return etSC;
}

double PhysObject::GetPhiSC() const
{
  if(phiSC > 999) cout<<"WARNING - carefull, phiSC probably not set"<<endl;
  return phiSC;
}

double PhysObject::GetEnergySC() const
{
  if(energySC < 0) cout<<"WARNING - carefull, energySC probably not set"<<endl;
  return energySC;
}

double PhysObject::GetRelIsoWithEA() const
{
  if(relIsoWithEA < 0) cout<<"WARNING - carefull, relIsoWithEA probably not set"<<endl;
  return relIsoWithEA;
}

double PhysObject::GetDetaSeed() const
{
  if(dEtaSeed < -999) cout<<"WARNING - carefull, dEtaSeed probably not set"<<endl;
  return dEtaSeed;
}

double PhysObject::GetChargedIso() const
{
  if(chargedIso < 0) cout<<"WARNING - carefull, chargedIso probably not set"<<endl;
  return chargedIso;
}

double PhysObject::GetPhotonIso() const
{
  if(photonIso < 0) cout<<"WARNING - carefull, photonIso probably not set"<<endl;
  return photonIso;
}

double PhysObject::GetNeutralIso() const
{
  if(neutralIso < 0) cout<<"WARNING - carefull, neutralIso probably not set"<<endl;
  return neutralIso;
}
