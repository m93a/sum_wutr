#ifndef COLOR_H
#define COLOR_H

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

#endif
