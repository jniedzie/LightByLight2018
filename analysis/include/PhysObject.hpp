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
  inline double GetEta() const { return eta; }
  inline double GetPhi() const { return phi; }
  inline double GetEt()  const { return et; }
  inline double GetPt()  const { return pt; }
  
  inline double GetEtaWidth()  const { return etaWidth; }
  inline double GetPhiWidth()  const { return phiWidth; }
  
  inline int    GetPID() const { return pdgID; }
  
  inline double GetEnergy()     const { return energy; }
  inline double GetEnergyHad()  const { return energyHad; }
  inline double GetEnergyEm()   const { return energyEm; }
  
  /// Returns calo sub-det
  ECaloType GetTowerSubdetHad() const;
  ECaloType GetTowerSubdetEm()  const;
  
private:
  double eta;       ///< Pseudorapidity
  double phi;       ///< Azimuthal angle
  double energy;    ///< Energy
  double et;        ///< Transverse energy
  double pt;        ///< Transverse momentum
  
  double energyHad; ///< Energy in hadronic part of calo
  double energyEm;  ///< Energy in EM part of calo
  
  double etaWidth;  ///< Width in eta direction
  double phiWidth;  ///< Width in phi direction
  
  int pdgID;        ///< PDG PID code
  
  friend class EventProcessor;
};

#endif /* PhysObject_hpp */
