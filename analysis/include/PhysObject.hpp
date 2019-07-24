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
  
  double GetEtaWidth() const;
  double GetPhiWidth() const;
  
  int    GetPID() const;
  
  double GetEnergy()     const;
  double GetEnergyHad()  const;
  double GetEnergyEm()   const;
  
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
