#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
//#include <windows.h>  //pro wokna
#include <X11/Xlib.h> //pro X11
#define PI 3.1415926535f
#define PI2 6.283185307f
#define POLYG_N 16
using namespace std;


/* * * * * * * *
 * helpers.cpp *
 * * * * * * * */
int    pow2(int x   ){return x*x;}
float  pow2(float x ){return x*x;}
double pow2(double x){return x*x;}
void polygon(
 int n,
 float x,
 float y,
 float radius,
 float R = .0f,
 float G = .0f,
 float B = .0f,
 float A = .0f,
 bool multiColor = false
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
}

void polygonGrad3f(int n, float x, float y, float radius, float R, float G, float B){
 polygon(n,x,y,radius,R,G,B,0.f,true);
}
void polygonGrad4f(int n, float x, float y, float radius, float R, float G, float B, float A){
 polygon(n,x,y,radius,R,G,B,A,true);
}
void polygonAlpha(int n, float x, float y, float radius){
 polygon(n,x,y,radius,0,0,0,0,true);
}


/* * * * * * * *
 * classes.cpp *
 * * * * * * * */
class Vector {
 public:
  float x;
  float y;
  Vector(float x, float y){
   this->x = x;
   this->y = y;
  };
  Vector times(float s){
   this->x *= s;
   this->y *= s;
   return *this;
  };
  Vector times(Vector v){
   this->x *= v.x;
   this->y *= v.y;
   return *this;
  };
  Vector times(Vector* v){
   this->x *= v->x;
   this->y *= v->y;
   return *this;
  };
  Vector add(Vector v){
   this->x += v.x;
   this->y += v.y;
   return *this;
  };
  Vector add(Vector* v){
   this->x += v->x;
   this->y += v->y;
   return *this;
  };
  Vector clone(){
   return Vector(this->x, this->y);
  };
  float dist(Vector v){
   return sqrt(
    pow2(
     fabs(this->x - v.x)
    )+
    pow2(
     fabs(this->y - v.y)
    )
   );
  };
  float dist(Vector* v){
   return sqrt(
    pow2(
     fabs(this->x - v->x)
    )+
    pow2(
     fabs(this->y - v->y)
    )
   );
  };
  float dir(Vector v){
   return atan(
    fabs(this->y - v.y)/
    fabs(this->x - v.x)
   );
  };
  float dir(Vector* v){
   return atan(
    fabs(this->y - v->y)/
    fabs(this->x - v->x)
   );
  };
  float abs(){
   return sqrt(
    pow2(this->x)+
    pow2(this->y)
   );
  };
  float angle(){
   return atan(
    this->y/
    this->x
   );
  };
};
class VectorAngle: public Vector {
 public:
  VectorAngle(float s,float a): Vector(x,y){
   this->x = cos(a)*s;
   this->y = sin(a)*s;
  };
};

class Color {
 public:
  float R;
  float G;
  float B;
  float A;
  Color(float R, float G, float B, float A = 1.0f)
  {
   this->R = R;
   this->G = G;
   this->B = B;
   this->A = A;
  };
  ~Color(){};
};
void changeColor(Color* c){
 glColor4f(c->R,c->G,c->B,c->A);
}

class Particle {
 public:
   Vector* coord;
   Vector* speed;
   Vector* force;
   Color* color;
   float radius;
   float invmass;
   Particle(Vector* coord, float invmass, float radius, Color* color)
   {
    this->speed = new Vector(0,0);
    this->force = new Vector(0,0);
    this->coord   = coord;
    this->radius  = radius;
    this->invmass = invmass;
    this->color   = color;
   };
   ~Particle(){
    delete this->coord;
    delete this->speed;
    delete this->force;
    delete this->color;
   };
   void draw(){
    changeColor(this->color);
    polygonAlpha(
     POLYG_N,
     this->coord->x,
     this->coord->y,
     this->radius
    );
   };
   void forceReaction(){
    /* Not exacty the right way FIXME */
    this->speed->x =
     this->coord->x + this->radius*3/5 > 1 ?
      -fabs(this->speed->x):
     this->coord->x - this->radius*3/5 < -1 ?
      fabs(this->speed->x):
     //:
      this->speed->x;
    
    this->speed->y =
     this->coord->y + this->radius*3/5 > 1 ?
      -fabs(this->speed->y):
     this->coord->y - this->radius*3/5 < -1 ?
      fabs(this->speed->y):
     //:
      this->speed->y;
   };
   void applyForce(Vector v){
    this->force->add(v);
   }
   void applyForce(Vector* v){
    this->force->add(v);
   };
   void move(){
    this->speed->add(
     this->force->times(invmass)
    );
    delete this->force;
    this->force = new Vector(0,0);
    
    this->coord->add(this->speed);
   };
   void done(){
    forceReaction();
    move();
    draw();
    //play(http://youtu.be/GBHPowULV7k);
   }
   void setColor(Color* color){
    this->color = color;
   };
};

/* * * * * * *
 * main.cpp  *
 * * * * * * */
Particle* particles [5];

void display(){
 glClearColor(0,0,0,1); //Černá
 glClear(GL_COLOR_BUFFER_BIT);
 
 int i = 0;
 int j = 0;
 do{
  do{
   if(i!=j){
    particles[i]->applyForce(
     new VectorAngle(
      particles[i]->coord->dist(particles[j]->coord),
      particles[i]->coord-> dir(particles[j]->coord)
     )
    );
   }
  }while(
   ++j<sizeof(particles)
  );
 }while(
  ++i<sizeof(particles)
 );
 
 glFlush(); //Render now
}

void timer(int value){
 glutPostRedisplay();
 glutTimerFunc(15,timer,0);
}

int main(int argc, char** argv){
 int i = 0;
 do{
  particles[i] = new Particle(
   new Vector(rand()%100/100.0f-0.5f,rand()%100/100.0f-0.5f),
   1, 0.1f, new Color(1,0,0)
  );
 }while(
  ++i<sizeof(particles)
 );
 glutInit(&argc, argv);
 glutCreateWindow("Use the force, Luke");
 glutInitWindowSize(640,640);
 glutInitWindowPosition(50,50);
 glutDisplayFunc(display);
 glutTimerFunc(15,timer,0);
 glutMainLoop();
 return 0;
}
