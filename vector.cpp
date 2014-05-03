#include "vector.hpp"

Vector Vector::times(float s){
 this->x *= s;
 this->y *= s;
 return *this;
};

Vector Vector::add(Vector v){
 this->x += v.x;
 this->y += v.y;
 return *this;
};
  
const float Vector::dist(Vector v){
 return sqrt(
  pow2(
   fabs(this->x - v.x)
  )+
  pow2(
   fabs(this->y - v.y)
  )
 );
};

const float Vector::dir(Vector v){
 return v.y - this->y >= 0
  ? acos((v.x - this->x) / this->dist(v))
  :-acos((v.x - this->x) / this->dist(v))+PI2;
};

const float Vector::abs(){
 return sqrt(
  pow2(this->x)+
  pow2(this->y)
 );
};
const float Vector::angle(){
 return this->y >= 0
  ? acos(this->x / this->abs())
  :-acos(this->x / this->abs())+PI2;
};
