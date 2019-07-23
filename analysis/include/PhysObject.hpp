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
  inline double GetEt()  const { return et; }
  
  inline double GetEtaWidth()  const { return etaWidth; }
  inline double GetPhiWidth()  const { return phiWidth; }
  
  inline int    GetPID() const { return pdgID; }
  
private:
  double eta;       ///< Pseudorapidity
  double phi;       ///< Azimuthal angle
  double energy;    ///< Energy
  double et;        ///< Transverse energy
  
  double etaWidth;  ///< Width in eta direction
  double phiWidth;  ///< Width in phi direction
  
  int pdgID;        ///< PDG PID code
  
  friend class EventProcessor;
};

#endif /* PhysObject_hpp */
