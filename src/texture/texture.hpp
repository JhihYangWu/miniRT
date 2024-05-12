#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "../color/color.hpp"

// colors stored as char between 0 and 255
// Color should be between 0.0f and 1.0f
// RGBA should be between 0 and 255
class Texture{
public:
    // constructor
    Texture(std::string filename);
    Texture(unsigned int width, unsigned int height, char color);
    ~Texture(); // deconstructor

    // methods
    void save(std::string filename);
    Color getColor(unsigned int row, unsigned int col);
    void setColor(Color c, unsigned int row, unsigned int col);

    // attributes
    unsigned int width;
    unsigned int height;
    char* data; // pointer to width * height * 4 chars
};

#endif
