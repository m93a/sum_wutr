#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "crystal_particle.hpp"
#include "crystal_bond.hpp"

class Crystal {
 public:
  vector<CrystalParticle*> partices;
  vector<CrystalBond*> bonds;
};

#endif
