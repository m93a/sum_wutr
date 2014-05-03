#include "gl.hpp"

void polygon(
 //required:
  int n,
  float x,
  float y,
  float radius,
 //optional:
  float R,
  float G,
  float B,
  float A,
  bool multiColor
){
 if(n==0){return;}
 float a = 0;
 float step = PI2/n;
 float limit = PI2+step;
 
 glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x,y);
  
  if(multiColor==true){
   glColor4f(R,G,B,A);
  }
  
  while(a<=limit){
   glVertex2f(cos(a)*radius+x,sin(a)*radius+y);
   a+=step;
  }
 glEnd();
};

void polygonGrad3f(int n, float x, float y, float radius, float R, float G, float B){
 polygon(n,x,y,radius,R,G,B,0.f,true);
};

void polygonGrad4f(int n, float x, float y, float radius, float R, float G, float B, float A){
 polygon(n,x,y,radius,R,G,B,A,true);
};

void polygonAlpha(int n, float x, float y, float radius){
 polygon(n,x,y,radius,0,0,0,0,true);
};

void changeColor(Color* c){
 glColor4f(c->R,c->G,c->B,c->A);
}
