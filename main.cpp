#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "constants.hpp"
#include "math.hpp"
#include "gl.hpp"

#include "particle.hpp"
using namespace std;


/* * * * * * *
 * main.cpp  *
 * * * * * * */
Particle* particles [PARTICLES]; //Party!

void display(){
 glClearColor(0,0,0,1);
 glClear(GL_COLOR_BUFFER_BIT);
 
 int i = 0,
     j = 0;
 float x = .0f,
       maxSpeed = .0f,
       maxCoord = .0f,
       maxForce = .0f,
       maxGamma = .0f;
 for(i=0;i<PARTICLES;i++){
  for(j=0;j<PARTICLES;j++){
   if(i!=j){
    x = particles[i]->coord->dist(particles[j]->coord);
    if(x!=0){
     particles[i]->applyForce(new VectorAngle(
      -pow(1/(400*x),2),
      particles[i]->coord->dir (particles[j]->coord)
     ));
    }
   }
  }
  particles[i]->applyForceSA(0.001f,DOWN);
  maxSpeed = particles[i]->speed->x > maxSpeed ? particles[i]->speed->x : maxSpeed;
  maxSpeed = particles[i]->speed->y > maxSpeed ? particles[i]->speed->y : maxSpeed;
  maxCoord = particles[i]->coord->x > maxCoord ? particles[i]->coord->x : maxCoord;
  maxCoord = particles[i]->coord->y > maxCoord ? particles[i]->coord->y : maxCoord;
  maxForce = particles[i]->coord->x > maxForce ? particles[i]->coord->x : maxForce;
  maxForce = particles[i]->coord->y > maxForce ? particles[i]->coord->y : maxForce;
  maxGamma = particles[i]->gamma    > maxGamma ? particles[i]->gamma    : maxGamma;
 }
 
 cout<<"____________________________________\n";
 cout<<" >speed | >coord | >force | >gamma |\n";
 cout<<to_string(maxSpeed)+"|";
 cout<<to_string(maxCoord)+"|";
 cout<<to_string(maxForce)+"|";
 cout<<to_string(maxGamma)+"|";
 cout<<"\n";
 
 for(i=0;i<PARTICLES;i++){
  particles[i]->done();
 }
 
 
 glFlush(); //Render now
}

void timer(int value){
 glutPostRedisplay();
 glutTimerFunc(MSPF,timer,0);
}

int main(int argc, char** argv){
 srand(time(0)); //Ať je sranda
 int i;
 for(i=0;i<PARTICLES;i++){
  particles[i] = new Particle(
   new Vector(1.0f*rand()/RAND_MAX-0.5f, 1.0f*rand()/RAND_MAX-0.5f),
   1, 0.05f, new Color(1,0,0)
  );
 }
 
 glutInit(&argc, argv);
 glutInitWindowSize(800,800);
 glutCreateWindow("title");
 glutDisplayFunc(display);
 glutTimerFunc(MSPF,timer,0);
 glutMainLoop();
 return 0;
}
