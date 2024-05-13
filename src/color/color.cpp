#include "color.hpp"
#include <algorithm>

Color::Color(char r, char g, char b, char a) {
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = a / 255.0f;
}

Color::Color(Vector3 v) {
    r = v.x;
    g = v.y;
    b = v.z;
    a = 1.0f;
}

Color::Color(const Color& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

void Color::setRGBA(char r, char g, char b, char a) {
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = a / 255.0f;
}

void Color::clamp() {
    r = std::min(std::max(r, 0.0f), 1.0f);
    g = std::min(std::max(g, 0.0f), 1.0f);
    b = std::min(std::max(b, 0.0f), 1.0f);
    a = std::min(std::max(a, 0.0f), 1.0f);
}
