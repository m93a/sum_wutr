#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.hpp"
#include "color.hpp"
#include "gl.hpp"

class Particle {
 public:
   Vector* coord;
   Vector* speed;
   Vector* force;
   Color* color;
   float radius;
   float mass;
   float gamma;
   bool render;
   Particle(Vector* coord, float mass, float radius, Color* color){
    this->render = true;
    this->speed  = new Vector(0,0);
    this->force  = new Vector(0,0);
    this->coord  = coord;
    this->radius = radius;
    this->mass   = mass;
    this->color  = color;
   };
   ~Particle(){
    delete this->coord;
    delete this->speed;
    delete this->force;
    delete this->color;
   };
   
   void applyForce(Vector v){ this->force->add(v); };
   void applyForce(Vector* v){ this->applyForce(*v); };
   void applyForce(float x, float y){ this->applyForce(Vector(x,y)); };
   void applyForceSA(float s, float a){
    this->applyForce(VectorAngle(s,a));
   };
   
   float dist(Vector v){ return this->coord->dist(v); };
   float dist(Vector* v){ return this->coord->dist(v); };
   float dist(Particle p){ return this->coord->dist(p.coord); };
   float dist(Particle* p){ return this->coord->dist(p->coord); };
   
   float dir(Vector v){ return this->coord->dir(v); };
   float dir(Vector* v){ return this->coord->dir(v); };
   float dir(Particle p){ return this->coord->dir(p.coord); };
   float dir(Particle* p){ return this->coord->dir(p->coord); };
   void setColor(Color* color){ this->color = color; };
   
   void move();
   void limit();
   void forceReaction();
   const void draw();
   
   void done(){
    forceReaction();
    move();
    draw();
    limit();
    //play(http://youtu.be/GBHPowULV7k);
   }
};

#endif
