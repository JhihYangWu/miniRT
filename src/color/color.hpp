#ifndef COLOR_H
#define COLOR_H

#include "../mymath/vector3.hpp"

class Color{
public:
    // constructors
    Color(); // black
    Color(int r, int g, int b, int a);
    Color(Vector3 v); // x, y, z should be between 0.0f and 1.0f
    Color(const Color& other); // copy constructor

    // operators and methods
    void setRGBA(int r, int g, int b, int a);
    void clamp(); // champs r, g, b, a to be between 0.0f and 1.0f

    // attributes
    float r, g, b, a; // normally between 0.0f and 1.0f
    float luminance = 0.0f;
    bool isMirror = false;
};

#endif
