#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../mymath/vector3.hpp"
#include "../mymath/ray.hpp"
#include "../color/color.hpp"

class Triangle{
public:
    // constructors
    Triangle(Vector3 p0, Vector3 p1, Vector3 p2, Color c); // assumes points are specified in CCW order
    Triangle(const Triangle& other); // copy constructor

    // methods
    float intersect(Ray r); // intersects ray r with triangle and returns time of intersection
                            // returns -1.0f if no intersection

    // attributes
    Vector3 A, B, C;
    Vector3 n; // normal of triangle
    Color c;
private:
    Vector3 edge1, edge2; // for intersect algo
};

#endif
