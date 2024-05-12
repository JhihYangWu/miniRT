#include "texture.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

Texture::Texture(std::string filename) {
    // loads ppm image to texture
    assert(filename.substr(filename.length() - 3) == "ppm");
    // open file
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "Failed to open texture at " << filename << std::endl;
        assert(0);
    }

    // read from file
    std::string line;
    std::getline(inFile, line); // next line
    size_t p3Pos = line.find("P3");
    size_t p6Pos = line.find("P6");
    if (p3Pos == std::string::npos && p6Pos == std::string::npos) assert(0);
    std::getline(inFile, line); // next line
    std::istringstream iss1(line);
    iss1 >> width >> height;
    data = new char[width * height * 4]; // allocate memory
    std::getline(inFile, line); // next line
    assert(std::stoi(line) == 255);
    if (p3Pos != std::string::npos) {
        // in ASCII format
        std::getline(inFile, line); // next line
        std::istringstream iss2(line);
        int j = 0;
        int val;
        for (int i = 0; i < 3 * width * height; i++) {
            iss2 >> val;
            data[j] = val;
            j++;
            if (i % 3 == 2) {
                data[j] = (char)255; // fully opaque
                j++;
            }
        }
    } else if (p6Pos != std::string::npos) {
        // in binary format
        int j = 0;
        int count = 0;
        char ch;
        while (inFile.get(ch)) {
            data[j] = ch;
            j++;
            count++;
            if (count % 3 == 0) {
                data[j] = (char)255; // fully opaque
                j++;
            }
        }
        assert(count == 3 * width * height);
    }

    // close file
    inFile.close();
}

Texture::Texture(unsigned int width, unsigned int height, char color) {
    this->width = width;
    this->height = height;
    data = new char[width * height * 4]; // allocate memory
    for (int i = 0; i < width * height * 4; i++) {
        data[i] = color;
        if (i % 4 == 3) data[i] = 255; // fully opaque
    }
}

void Texture::save(std::string filename) {
    // saves the texture as ppm binary file
    // open file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Failed to save texture at " << filename << std::endl;
        assert(0);
    }

    // write to file
    outFile << "P6" << std::endl; // binary format 
    outFile << width << " " << height << std::endl; // width and height of img
    outFile << 255 << std::endl; // maximum color value
    // write color values
    for (int i = 0; i < 4 * width * height; i += 4) {
       outFile << data[i + 0];
       outFile << data[i + 1];
       outFile << data[i + 2];
    }

    // close file
    outFile.close();
}

Color Texture::getColor(unsigned int row, unsigned int col) {
    char* addr = data + (row * width + col) * 4;
    Color c(addr[0], addr[1], addr[2], addr[3]);
    return c;
}

void Texture::setColor(Color c, unsigned int row, unsigned int col) {
    char* addr = data + (row * width + col) * 4;
    // programmer is responsible for clamping it first
    addr[0] = c.r * 255.0f;
    addr[1] = c.g * 255.0f;
    addr[2] = c.b * 255.0f;
    addr[3] = c.a * 255.0f;
}
