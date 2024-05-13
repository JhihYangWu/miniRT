#include "vector3.hpp"
#include <cassert>
#include <math.h>
#include <sstream>
#include <iomanip>

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(float val) {
    this->x = val;
    this->y = val;
    this->z = val;
}

Vector3::Vector3(const Vector3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

Vector3& Vector3::operator=(const Vector3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

float Vector3::operator[](int index) {
    assert(index >= 0 && index <= 2);
    return data[index];
}

float Vector3::len() {
    return sqrt(this->lenSquared());
}

float Vector3::lenSquared() {
    return x * x + y * y + z * z;
}

Vector3& Vector3::normalize() {
    float length = this->len();
    if (length != 0) {
        this->x /= length;
        this->y /= length;
        this->z /= length;
    }
    return *this;
}

std::string Vector3::str() {
    std::stringstream ss;
    ss << "<" << std::fixed << std::setprecision(2) << this->x << ", " << this->y << ", " << this->z << ">";
    return ss.str();
}

float dot(const Vector3& v0, const Vector3& v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

Vector3 cross(const Vector3& v0, const Vector3& v1) {
    return Vector3(
        v0.y * v1.z - v0.z * v1.y,
        v0.z * v1.x - v0.x * v1.z,
        v0.x * v1.y - v0.y * v1.x
    );
}

Vector3 proj(const Vector3& v0, const Vector3& v1) {
    return (dot(v0, v1) / dot(v1, v1)) * v1;
}

Vector3 normalize(Vector3& v) {
    float length = v.len();
    if (length == 0) return v;
    return v / length;
}

Vector3 operator+(const Vector3& v0, const Vector3& v1) {
    return Vector3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

Vector3 operator-(const Vector3& v0, const Vector3& v1) {
    return Vector3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

Vector3 operator*(const Vector3& v0, const Vector3& v1) {
    return Vector3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

Vector3 operator/(const Vector3& v0, const Vector3& v1) {
    return Vector3(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

Vector3 operator+(const Vector3& v, const float scalar) {
    return Vector3(v.x + scalar, v.y + scalar, v.z + scalar);
}

Vector3 operator-(const Vector3& v, const float scalar) {
    return Vector3(v.x - scalar, v.y - scalar, v.z - scalar);
}

Vector3 operator*(const Vector3& v, const float scalar) {
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3 operator/(const Vector3& v, const float scalar) {
    return Vector3(v.x / scalar, v.y / scalar, v.z / scalar);
}

Vector3 operator+(const float scalar, const Vector3& v) {
    return Vector3(scalar + v.x, scalar + v.y, scalar + v.z);
}

Vector3 operator-(const float scalar, const Vector3& v) {
    return Vector3(scalar - v.x, scalar - v.y, scalar - v.z);
}

Vector3 operator*(const float scalar, const Vector3& v) {
    return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
}

Vector3 operator/(const float scalar, const Vector3& v) {
    return Vector3(scalar / v.x, scalar / v.y, scalar / v.z);
}

const Vector3 operator-(const Vector3& v) {
    return Vector3(-v.x, -v.y, -v.z);
}
