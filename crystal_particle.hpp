#ifndef CRYSTAL_PARTICLE_H
#define CRYSTAL_PARTICLE_H

#include <vector>
#include "particle.hpp"
#include "crystal_bond.hpp"

class CrystalBond;

class CrystalParticle: public Particle {
 public:
  std::vector<CrystalBond*> bonds;
};

#endif
