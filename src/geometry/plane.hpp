#ifndef PLANE_H
#define PLANE_H

#include "../mymath/vector3.hpp"
#include "../color/color.hpp"
#include "../mymath/ray.hpp"

class Plane{
public:
    // constructors
    Plane(Vector3 upperLeft, Vector3 lowerLeft, Vector3 lowerRight, Color c);
    Plane(const Plane& other); // copy constructor

    // methods
    float intersect(Ray r); // intersects ray r with plane and returns time of intersection
                            // returns -1.0f if no intersection

    // attributes
    Vector3 upperLeft;
    Vector3 lowerLeft;
    Vector3 lowerRight;
    Color c;
    Vector3 n; // normal
private:
    Vector3 u, v; // for intersect algo
    float uDirLen, vDirLen;
};

#endif
