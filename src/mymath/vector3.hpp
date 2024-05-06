#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

class Vector3{
public:
    // constructors
    Vector3(); // zero vector
    Vector3(float x, float y, float z);
    Vector3(float val); // x = y = z = val
    Vector3(const Vector3& other); // copy constructor

    // operators and methods
    Vector3& operator=(const Vector3& other);
    float operator[](int index);
    float len();
    float lenSquared();
    Vector3& normalize();
    std::string str();

    // attributes
    // the 3 float in Vector3 can be accessed in different ways
    union{
        struct{
            float x, y, z;
        };
        struct{
            float r, g, b;
        };
        struct{
            float data[3];
        };
    };
};

// operators and functions
float dot(const Vector3& v0, const Vector3& v1);
Vector3 cross(const Vector3& v0, const Vector3& v1);
Vector3 normalize(Vector3& v);

Vector3 operator+(const Vector3& v0, const Vector3& v1);
Vector3 operator-(const Vector3& v0, const Vector3& v1);
Vector3 operator*(const Vector3& v0, const Vector3& v1); // element wise multiplication
Vector3 operator/(const Vector3& v0, const Vector3& v1); // element wise division

Vector3 operator+(const Vector3& v, const float scalar);
Vector3 operator-(const Vector3& v, const float scalar);
Vector3 operator*(const Vector3& v, const float scalar);
Vector3 operator/(const Vector3& v, const float scalar);

Vector3 operator+(const float scalar, const Vector3& v);
Vector3 operator-(const float scalar, const Vector3& v);
Vector3 operator*(const float scalar, const Vector3& v);
Vector3 operator/(const float scalar, const Vector3& v);

const Vector3 operator-(const Vector3& v); // negate vector

#endif
