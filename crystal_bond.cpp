#include "crystal_bond.hpp"
using namespace std;

void CrystalBond::done(float c){
 for(int i = 0; i<this->particles.size(); i++){
  for(int j = 0; j<this->particles.size(); j++){
   if(i!=j){
    this->particles[i]->applyForceSA(
     c/pow2(
      fabs(
       this->particles[i]->dist(this->particles[j])
       -this->length
      )
     ),
     this->particles[i]->dir(this->particles[j])
    );
   }
  }
 }
};
