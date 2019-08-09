//  PhysObject.hpp
//
//  Created by Jeremi Niedziela on 23/07/2019.

#ifndef PhysObject_hpp
#define PhysObject_hpp

#include "Helpers.hpp"

/// Class representing a physics object, such as gen particle, reconstructed photon/electron,
/// calorimeter tower, supercluster etc.
class PhysObject {
public:
  /// Default constructor
  PhysObject();
  
  /// Default destructor
  ~PhysObject();
  
  // Trivial getters:
  double GetEta() const;
  double GetPhi() const;
  double GetEt()  const;
  double GetPt()  const;
  
  double GetEtaSC()     const;
  double GetPhiSC()     const;
  double GetEnergySC()  const;
  
  double GetEtaWidth()  const;
  double GetPhiWidth()  const;
  double GetHoverE()    const;
  
  int    GetPID()           const;
  int    GetCharge()        const;
  int    GetNmissingHits()  const;
  
  double GetEnergy()     const;
  double GetEnergyHad()  const;
  double GetEnergyEm()   const;
  
  double GetRelIsoWithEA()  const;
  double GetDetaSeed()      const;
  
  /// Returns calo sub-det
  ECaloType GetTowerSubdetHad() const;
  ECaloType GetTowerSubdetEm()  const;
  
private:
  double eta;       ///< Pseudorapidity
  double phi;       ///< Azimuthal angle
  double energy;    ///< Energy
  
  double etaSC;     ///< Pseudorapidity of the supercluster
  double phiSC;     ///< Azimuthal angle of the supercluster
  double energySC;  ///< Energy of the supercluster
  
  double et;        ///< Transverse energy
  double pt;        ///< Transverse momentum
  
  double energyHad; ///< Energy in hadronic part of calo
  double energyEm;  ///< Energy in EM part of calo
  
  double etaWidth;  ///< Width in eta direction
  double phiWidth;  ///< Width in phi direction
  
  double hOverE;    ///< Hadronic/EM energy
  
  int pdgID;        ///< PDG PID code
  int charge;       ///< Particle charge
  int nMissingHits; ///< Number of missing hits
  
  double relIsoWithEA;  ///< Relative isolation
  double dEtaSeed;      ///< Seed Δη
  
  friend class EventProcessor;
  friend class PhysObjectProcessor;
};

#endif /* PhysObject_hpp */
