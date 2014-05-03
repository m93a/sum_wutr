#ifndef POLYGON_H
#define POLYGON_H

#include <GL/glut.h>
#include "math.hpp"
#include "config.hpp"
#include "color.hpp"

void polygon(int n, float x, float y, float radius, float R = .0f, float G = .0f, float B = .0f, float A = .0f, bool multiColor = false);
void polygonGrad3f(int n, float x, float y, float radius, float R, float G, float B);
void polygonGrad4f(int n, float x, float y, float radius, float R, float G, float B, float A);
void polygonAlpha(int n, float x, float y, float radius);
void changeColor(Color* c);

#endif
