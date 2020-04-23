//  PhysObject.hpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#ifndef PhysObject_hpp
#define PhysObject_hpp

#include "Helpers.hpp"


class PhysObject;
typedef vector<shared_ptr<PhysObject>> PhysObjects;

/// Class representing a physics object, such as gen particle, reconstructed photon/electron,
/// calorimeter tower, supercluster etc.
class PhysObject {
public:
  /// Default constructor
  PhysObject();
  
  /// Default destructor
  ~PhysObject();
  
  // Trivial getters:
  double GetEta()       const;
  double GetPhi()       const;
  double GetEt()        const;
  double GetPt()        const;
  double GetMomentum()  const;
  
  double GetEtaSC()     const;
  double GetEtSC()      const;
  double GetPhiSC()     const;
  double GetEnergySC()  const;
  
  double GetEtaWidth()      const;
  double GetSigmaEta2012()  const;
  double GetPhiWidth()      const;
  double GetHoverE()        const;
  
  int    GetPID()           const;
  int    GetCharge()        const;
  int    GetNmissingHits()  const;
  int    GetNvalidHits()    const;
  int    GetPurity()        const;
  double GetChi2()          const;
  double GetDxy()           const;
  double GetDz()            const;
  double GetDxyErr()        const;
  double GetDzErr()         const;
  double GetXYdistanceFromBeamSpot(EDataset dataset) const;
  double GetZdistanceFromBeamSpot(EDataset dataset)  const;
  double GetVertexX()       const;
  double GetVertexY()       const;
  double GetVertexZ()       const;
  
  double GetEnergy()     const;
  double GetEnergyHad()  const;
  double GetEnergyEm()   const;
  
  double GetEnergyCrystalMax()    const;
  double GetEnergyCrystalTop()    const;
  double GetEnergyCrystalBottom() const;
  double GetEnergyCrystalLeft()   const;
  double GetEnergyCrystalRight()  const;
  
  double GetChargedIso() const;
  double GetPhotonIso()  const;
  double GetNeutralIso() const;
  
  double GetRelIsoWithEA()  const;
  double GetDetaSeed()      const;
  
  /// Returns calo sub-det
  ECaloType GetTowerSubdetHad() const;
  ECaloType GetTowerSubdetEm()  const;
  
  bool IsConverted()  const;
  int  GetZside()     const;
  
private:
  double eta;       ///< Pseudorapidity
  double phi;       ///< Azimuthal angle
  double energy;    ///< Energy
  
  double etaSC;     ///< Pseudorapidity of the supercluster
  double etSC;      ///< Transverse energy of the supercluster
  double phiSC;     ///< Azimuthal angle of the supercluster
  double energySC;  ///< Energy of the supercluster
  
  double et;        ///< Transverse energy
  double pt;        ///< Transverse momentum
  double p;         ///< Momentum
  
  double energyHad; ///< Energy in hadronic part of calo
  double energyEm;  ///< Energy in EM part of calo
  
  double energyMax;   ///< Energy of the seed (max energy in the cluster)
  double energyTop;   ///< Energy in the crytal on the top of the photon seed
  double energyBottom;///< Energy in the crytal on the bottom of the photon seed
  double energyLeft;  ///< Energy in the crytal on the left of the photon seed
  double energyRight; ///< Energy in the crytal on the right of the photon seed
  
  double etaWidth;      ///< Width in eta direction
  double phiWidth;      ///< Width in phi direction
  double sigmaEta2012;  ///< Shower width in eta as in 2012
  
  double hOverE;    ///< Hadronic/EM energy
  
  int pdgID;        ///< PDG PID code
  int charge;       ///< Particle charge
  int nMissingHits; ///< Number of missing hits
  int nValidHits;   ///< Number of valid hits
  int purity;       ///< Purity of the track
  double chi2;      ///< chi2 of the track fit
  double dxy, dz;   ///< distance between track and primary vertex
  double dxyErr, dzErr;///< uncertainties on dxy and dz
  double vx, vy, vz;///< vertex coordinates
  
  double chargedIso;  ///< Isolation wrt. charged particles
  double photonIso;   ///< Isolation wrt. photons
  double neutralIso;  ///< Isolation wrt. neutral particles
  
  double relIsoWithEA;  ///< Relative isolation
  double dEtaSeed;      ///< Seed Δη
  
  bool hasConversionTracks; ///< Is it a converted photon
  
  int zSide;          ///< z-side for ZDC
  
  friend class EventProcessor;
  friend class PhysObjectProcessor;
};

#endif /* PhysObject_hpp */
