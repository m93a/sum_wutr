#ifndef VECTOR_H
#define VECTOR_H

#include "math.hpp"

class Vector {
 public:
  float x;
  float y;
  Vector(float x, float y){
   this->x = x;
   this->y = y;
  };
  
  const Vector clone(){ return Vector(this->x, this->y); };
  
  Vector times(float s);
  Vector add(Vector v);
  Vector add(Vector* v){ return this->add(*v); };
  
  const float dist(Vector v);
  const float dist(Vector* v){ return this->dist(*v); };
  
  const float dir(Vector v);
  const float dir(Vector* v){ return this->dir(*v); };
  
  const float abs();
  const float angle();
};

class VectorAngle: public Vector {
 public:
  VectorAngle(float s,float a): Vector(x,y){
   this->x = cos(a)*s;
   this->y = sin(a)*s;
  };
};

#endif
