#ifndef SPHERE_H
#define SPHERE_H

#include "../mymath/vector3.hpp"
#include "../color/color.hpp"
#include "../mymath/ray.hpp"

class Sphere{
public:
    // constructors
    Sphere(float radius, Vector3 loc, Color c);
    Sphere(const Sphere& other); // copy constructor

    // methods
    float intersect(Ray r); // intersects ray r with sphere and returns time of intersection
                            // returns -1.0f if no intersection
    Vector3 getNormal(Vector3 hitPt);

    // attributes
    float radius;
    Vector3 loc;
    Color c;
};

#endif
