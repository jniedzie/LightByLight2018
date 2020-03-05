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
p(-1),

energyHad(-9999),
energyEm(-9999),
energyMax(-9999),
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
purity(-9999),
chi2(-9999),
dxy(-9999),
dz(-9999),
dxyErr(-9999),
dzErr(-9999),
vx(-9999),
vy(-9999),
vz(-9999),

chargedIso(-9999),
photonIso(-9999),
neutralIso(-9999),

relIsoWithEA(-9999),
dEtaSeed(-9999),

hasConversionTracks(false)
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

double PhysObject::GetMomentum()  const
{
  if(p<0) cout<<"WARNING - carefull, p probably not set"<<endl;
  return p;
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

int PhysObject::GetPurity() const
{
  if(purity < -999) cout<<"WARNING - carefull, purity probably not set"<<endl;
  return purity;
}

double PhysObject::GetChi2() const
{
  if(chi2 < -999) cout<<"WARNING - carefull, chi2 probably not set"<<endl;
  return chi2;
}

double PhysObject::GetDxy() const
{
  if(dxy < -999) cout<<"WARNING - carefull, dxy probably not set"<<endl;
  return dxy;
}

double PhysObject::GetDz() const
{
  if(dz < -999) cout<<"WARNING - carefull, dz probably not set"<<endl;
  return dz;
}

double PhysObject::GetDxyErr() const
{
  if(dxyErr < -999) cout<<"WARNING - carefull, dxyErr probably not set"<<endl;
  return dxyErr;
}

double PhysObject::GetDzErr() const
{
  if(dzErr < -999) cout<<"WARNING - carefull, dzErr probably not set"<<endl;
  return dzErr;
}

double PhysObject::GetXYdistanceFromBeamSpot(EDataset dataset) const
{
  if(vx < -999 || vy < -999) cout<<"WARNING - carefull, vx or vy probably not set"<<endl;
  auto [bs_x, bs_y, bs_z] = GetBeamSpot(dataset);
  double px = pt * cos(phi);
  double py = pt * sin(phi);
  
  return (-(vx - bs_x) * py + (vy - bs_y) * px) / pt;
//  return sqrt(pow(bs_x - vx, 2) + pow(bs_y - vy, 2));
}

double PhysObject::GetZdistanceFromBeamSpot(EDataset dataset) const
{
  if(vz < -999) cout<<"WARNING - carefull, vz probably not set"<<endl;
  auto [bs_x, bs_y, bs_z] = GetBeamSpot(dataset);
  double px = pt * cos(phi);
  double py = pt * sin(phi);
  
  double theta = 2*atan(exp(-eta));
  double pz = p * cos(theta);
  
  return (vz - bs_z) - ((vx - bs_x) * px + (vy - bs_y) * py) / pt * pz / pt;
//  return fabs(bs_z - vz);
}

double PhysObject::GetVertexX() const
{
  if(vx < -999) cout<<"WARNING - carefull, vx probably not set"<<endl;
  return vx;
}

double PhysObject::GetVertexY() const
{
  if(vy < -999) cout<<"WARNING - carefull, vy probably not set"<<endl;
  return vy;
}

double PhysObject::GetVertexZ() const
{
  if(vz < -999) cout<<"WARNING - carefull, vz probably not set"<<endl;
  return vz;
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

double PhysObject::GetEnergyCrystalMax() const
{
  if(energyMax < -999) cout<<"WARNING - carefull, energyMax probably not set"<<endl;
  return energyMax;
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

bool PhysObject::IsConverted() const
{
  return hasConversionTracks;
}
