#ifndef CRYSTAL_BOND_H
#define CRYSTAL_BOND_H

#include <vector>
#include "crystal_particle.hpp"
#include "math.h"

class CrystalBond {
 public:
  float length;
  float strength;
  std::vector<CrystalParticle*> particles;
  
  CrystalBond(float l, float s, CrystalParticle* p0, CrystalParticle* p1){
   this->length = l;
   this->strength = s;
   this->particles.resize(2);
   this->particles[0]=p0;
   this->particles[1]=p1;
  };
  
  void done(float c);
};

#endif
