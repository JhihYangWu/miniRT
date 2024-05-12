#ifndef COLOR_H
#define COLOR_H

class Color{
public:
    // constructors
    Color(char r, char g, char b, char a);
    Color(const Color& other); // copy constructor

    // operators and methods
    void setRGBA(char r, char g, char b, char a);
    void clamp(); // champs r, g, b, a to be between 0.0f and 1.0f

    // attributes
    float r, g, b, a; // normally between 0.0f and 1.0f
};

#endif
