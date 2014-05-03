#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
//#include <windows.h>  //pro wokna
#include <X11/Xlib.h> //pro X11

#define PI 3.141592654f
#define PI2 6.283185307f
#define EUL 2.718281829f

#define RIGHT 0.0f
#define UP   1.570796327f
#define LEFT 3.141592654f
#define DOWN 4.712388980f

#define POLYG_N 4
#define PARTICLES 256
#define FRICTION 0.1f
#define SPEED 1.0f
#define MSPF 15
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
  Vector add(Vector v){
   this->x += v.x;
   this->y += v.y;
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
   return this->dist(*v);
  };
  float dir(Vector v){
   return v.y - this->y >= 0
    ? acos((v.x - this->x) / this->dist(v))
    :-acos((v.x - this->x) / this->dist(v))+PI2;
  };
  float dir(Vector* v){
   return this->dir(*v);
  };
  float abs(){
   return sqrt(
    pow2(this->x)+
    pow2(this->y)
   );
  };
  float angle(){
   return this->y >= 0
    ? acos(this->x / this->abs())
    :-acos(this->x / this->abs())+PI2;
  };
  Vector times(Vector* v){
   return this->times(*v);
  };
  Vector add(Vector* v){
   return this->add(*v);
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
   float mass;
   bool render;
   Particle(Vector* coord, float mass, float radius, Color* color)
   {
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
   void draw(){
    if(!this->render){return;}
    changeColor(this->color);
    polygonAlpha(
     POLYG_N,
     this->coord->x,
     this->coord->y,
     this->radius
    );
   };
   void forceReaction(){
    if(
     fabs(this->coord->x) + this->radius > 1
    ){
     this->applyForceVa(
      pow(fabs(this->coord->x) + this->radius - 1,2),
      this->coord->x > 0
       ? LEFT
       : RIGHT
     );
    }
    if(
     fabs(this->coord->y) + this->radius > 1
    ){
     this->applyForceVa(
      pow(fabs(this->coord->y) + this->radius - 1,2),
      this->coord->y > 0
       ? DOWN
       : UP
     );
    }
   };
   void applyForce(Vector v){
    this->force->add(v);
   }
   void applyForce(Vector* v){
    this->applyForce(*v);
   };
   void applyForceV(float x, float y){
    this->applyForce(Vector(x,y));
   };
   void applyForceVa(float s, float a){
    this->applyForce(VectorAngle(s,a));
   };
   void move(){
    this->speed->add(
     this->force->times(SPEED/mass)
    );
    delete this->force;
    this->force = new Vector(0,0);
    
    this->coord->add(this->speed);
    
    this->speed->x -= this->speed->x * FRICTION;
    this->speed->y -= this->speed->y * FRICTION;
   };
   void limit(){
    if(this->speed->abs() > 1){
     this->speed = new VectorAngle(1,this->speed->angle());
    }
    if(this->coord->abs() > 100){
     this->coord = new VectorAngle(1,this->coord->angle());
    }
   }
   void done(){
    forceReaction();
    move();
    draw();
    limit();
    //play(http://youtu.be/GBHPowULV7k);
   }
   void setColor(Color* color){
    this->color = color;
   };
};

/* * * * * * *
 * main.cpp  *
 * * * * * * */
Particle* particles [PARTICLES]; //Party!

void display(){
 glClearColor(0,0,0,1);
 glClear(GL_COLOR_BUFFER_BIT);
 
 int i = 0,
     j = 0;
 float x = .0f;
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
  particles[i]->applyForceVa(0.001f,DOWN);
 }
 
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
