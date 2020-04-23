//  PhysObject.cpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#include "PhysObject.hpp"
#include "Logger.hpp"

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
sigmaEta2012(-9999),
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

hasConversionTracks(false),
zSide(-9999)
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

  Log(0)<<"ERROR - could not determine calo tower sub-det!!\n";
  
  return nCaloTypes;
}

ECaloType PhysObject::GetTowerSubdetEm() const
{
  if(eta > -maxEtaHF && eta < -minEtaHF) return kHFm;
  if(eta >  minEtaHF && eta <  maxEtaHF) return kHFp;
  
  if(fabs(eta) > 0 && fabs(eta) < maxEtaEB) return kEB;
  if(fabs(eta) > minEtaEE && fabs(eta) < maxEtaEE) return kEE;
  
  Log(0)<<"ERROR - could not determine calo tower sub-det!!\n";
  
  return nCaloTypes;
}


double PhysObject::GetEta() const
{
  if(eta>999) Log(1)<<"WARNING - carefull, eta probably not set\n";
  return eta;
}

double PhysObject::GetPhi() const
{
  if(phi>999) Log(1)<<"WARNING - carefull, phi probably not set\n";
  return phi;
}

double PhysObject::GetEt()  const
{
  if(et < 0) Log(1)<<"WARNING - carefull, et probably not set\n";
  return et;
}

double PhysObject::GetPt()  const
{
  if(pt<0) Log(1)<<"WARNING - carefull, pt probably not set\n";
  return pt;
}

double PhysObject::GetMomentum()  const
{
  if(p<0) Log(1)<<"WARNING - carefull, p probably not set\n";
  return p;
}

double PhysObject::GetEtaWidth()  const
{
  if(etaWidth < 0) Log(1)<<"WARNING - carefull, etaWidth probably not set\n";
  return etaWidth;
}

double PhysObject::GetSigmaEta2012()  const
{
  if(sigmaEta2012 < 0) Log(1)<<"WARNING - carefull, sigmaEta2012 probably not set\n";
  return sigmaEta2012;
}

double PhysObject::GetPhiWidth()  const
{
  if(phiWidth < 0) Log(1)<<"WARNING - carefull, phiWidth probably not set\n";
  return phiWidth;
}

double PhysObject::GetHoverE()  const
{
  if(hOverE < 0) Log(1)<<"WARNING - carefull, hOverE probably not set\n";
  return hOverE;
}

int PhysObject::GetPID() const
{
  if(pdgID==0) Log(1)<<"WARNING - carefull, pdgID probably not set\n";
  return pdgID;
}

int PhysObject::GetCharge() const
{
  if(charge > 999) Log(1)<<"WARNING - carefull, charge probably not set\n";
  return charge;
}

int PhysObject::GetNmissingHits() const
{
  if(nMissingHits < 0) Log(1)<<"WARNING - carefull, nMissingHits probably not set\n";
  return nMissingHits;
}

int PhysObject::GetNvalidHits() const
{
  if(nValidHits < 0) Log(1)<<"WARNING - carefull, nValidHits probably not set\n";
  return nValidHits;
}

int PhysObject::GetPurity() const
{
  if(purity < -999) Log(1)<<"WARNING - carefull, purity probably not set\n";
  return purity;
}

double PhysObject::GetChi2() const
{
  if(chi2 < -999) Log(1)<<"WARNING - carefull, chi2 probably not set\n";
  return chi2;
}

double PhysObject::GetDxy() const
{
  if(dxy < -999) Log(1)<<"WARNING - carefull, dxy probably not set\n";
  return dxy;
}

double PhysObject::GetDz() const
{
  if(dz < -999) Log(1)<<"WARNING - carefull, dz probably not set\n";
  return dz;
}

double PhysObject::GetDxyErr() const
{
  if(dxyErr < -999) Log(1)<<"WARNING - carefull, dxyErr probably not set\n";
  return dxyErr;
}

double PhysObject::GetDzErr() const
{
  if(dzErr < -999) Log(1)<<"WARNING - carefull, dzErr probably not set\n";
  return dzErr;
}

double PhysObject::GetXYdistanceFromBeamSpot(EDataset dataset) const
{
  if(vx < -999 || vy < -999) Log(1)<<"WARNING - carefull, vx or vy probably not set\n";
  auto [bs_x, bs_y, bs_z] = GetBeamSpot(dataset);
  double px = pt * cos(phi);
  double py = pt * sin(phi);
  
  return (-(vx - bs_x) * py + (vy - bs_y) * px) / pt;
//  return sqrt(pow(bs_x - vx, 2) + pow(bs_y - vy, 2));
}

double PhysObject::GetZdistanceFromBeamSpot(EDataset dataset) const
{
  if(vz < -999) Log(1)<<"WARNING - carefull, vz probably not set\n";
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
  if(vx < -999) Log(1)<<"WARNING - carefull, vx probably not set\n";
  return vx;
}

double PhysObject::GetVertexY() const
{
  if(vy < -999) Log(1)<<"WARNING - carefull, vy probably not set\n";
  return vy;
}

double PhysObject::GetVertexZ() const
{
  if(vz < -999) Log(1)<<"WARNING - carefull, vz probably not set\n";
  return vz;
}

double PhysObject::GetEnergy()     const
{
  if(energy<0) Log(1)<<"WARNING - carefull, energy probably not set\n";
  return energy;
}

double PhysObject::GetEnergyHad() const
{
  if(energyHad < -999) Log(1)<<"WARNING - carefull, energyHad probably not set\n";
  return energyHad;
}

double PhysObject::GetEnergyCrystalMax() const
{
  if(energyMax < -999) Log(1)<<"WARNING - carefull, energyMax probably not set\n";
  return energyMax;
}

double PhysObject::GetEnergyCrystalTop() const
{
  if(energyTop < -999) Log(1)<<"WARNING - carefull, energyTop probably not set\n";
  return energyTop;
}

double PhysObject::GetEnergyCrystalBottom() const
{
  if(energyBottom < -999) Log(1)<<"WARNING - carefull, energyBottom probably not set\n";
  return energyBottom;
}

double PhysObject::GetEnergyCrystalLeft() const
{
  if(energyLeft < -999) Log(1)<<"WARNING - carefull, energyLeft probably not set\n";
  return energyLeft;
}

double PhysObject::GetEnergyCrystalRight() const
{
  if(energyRight < -999) Log(1)<<"WARNING - carefull, energyRight probably not set\n";
  return energyRight;
}

double PhysObject::GetEnergyEm() const
{
  if(energyEm < -999) Log(1)<<"WARNING - carefull, energyEm probably not set\n";
  return energyEm;
}

double PhysObject::GetEtaSC() const
{
  if(etaSC > 999) Log(1)<<"WARNING - carefull, etaSC probably not set\n";
  return etaSC;
}

double PhysObject::GetEtSC() const
{
  if(etSC < 0) Log(1)<<"WARNING - carefull, etSC probably not set\n";
  return etSC;
}

double PhysObject::GetPhiSC() const
{
  if(phiSC > 999) Log(1)<<"WARNING - carefull, phiSC probably not set\n";
  return phiSC;
}

double PhysObject::GetEnergySC() const
{
  if(energySC < 0) Log(1)<<"WARNING - carefull, energySC probably not set\n";
  return energySC;
}

double PhysObject::GetRelIsoWithEA() const
{
  if(relIsoWithEA < 0) Log(1)<<"WARNING - carefull, relIsoWithEA probably not set\n";
  return relIsoWithEA;
}

double PhysObject::GetDetaSeed() const
{
  if(dEtaSeed < -999) Log(1)<<"WARNING - carefull, dEtaSeed probably not set\n";
  return dEtaSeed;
}

double PhysObject::GetChargedIso() const
{
  if(chargedIso < 0) Log(1)<<"WARNING - carefull, chargedIso probably not set\n";
  return chargedIso;
}

double PhysObject::GetPhotonIso() const
{
  if(photonIso < 0) Log(1)<<"WARNING - carefull, photonIso probably not set\n";
  return photonIso;
}

double PhysObject::GetNeutralIso() const
{
  if(neutralIso < 0) Log(1)<<"WARNING - carefull, neutralIso probably not set\n";
  return neutralIso;
}

bool PhysObject::IsConverted() const
{
  return hasConversionTracks;
}

int PhysObject::GetZside() const
{
  if(zSide < -999) Log(1)<<"WARNING - carefull, zSide probably not set\n";
  return zSide;
}
