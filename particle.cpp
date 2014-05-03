#include "particle.hpp"
#include "constants.hpp"
#include "config.hpp"


void Particle::move(){
 float beta = this->speed->abs()/LIGHTSPEED;
 this->gamma = 1/sqrt(1-(beta*beta));
 this->speed->add(
  this->force->times(SPEED/(this->gamma*this->mass))
 );
 delete this->force;
 this->force = new Vector(0,0);
 
 this->coord->add(this->speed);
 
 this->speed->x -= this->speed->x * FRICTION;
 this->speed->y -= this->speed->y * FRICTION;
};


void Particle::limit(){
 if(this->speed->abs() > LIGHTSPEED){
  this->speed = new VectorAngle(1,this->speed->angle());
 }
 if(this->coord->abs() > 100){
  this->coord = new VectorAngle(1,this->coord->angle());
 }
}


void Particle::forceReaction(){
 if(
  fabs(this->coord->x) + this->radius > 1
 ){
  this->applyForceSA(
   pow(fabs(this->coord->x) + this->radius - 1,2),
   this->coord->x > 0
    ? LEFT
    : RIGHT
  );
 }
 if(
  fabs(this->coord->y) + this->radius > 1
 ){
  this->applyForceSA(
   pow(fabs(this->coord->y) + this->radius - 1,2),
   this->coord->y > 0
    ? DOWN
    : UP
  );
 }
};


const void Particle::draw(){
 if(!this->render){return;}
 changeColor(this->color);
 polygonAlpha(
  POLYG_N,
  this->coord->x,
  this->coord->y,
  this->radius
 );
};
