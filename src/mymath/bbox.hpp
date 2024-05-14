#ifndef BBOX_H
#define BBOX_H

#include "ray.hpp"

class BBox{ // bounding box class
public:
    // constructors
    BBox(); // p0 = p1 = (0, 0, 0)
    BBox(Vector3 p0, Vector3 p1);
    BBox(const BBox& other); // copy constructor

    // methods
    float intersect(Ray r); // intersects ray r with bounding box and returns time of intersection
                            // returns -1.0f if no intersection
    bool isInBox(Vector3 point); // returns whether a point is in the bounding box
    void union_(Vector3 point); // enlarge bbox to contain point
    void union_(BBox box); // enlarge bbox to contain other box

    // attributes
    Vector3 minPt;
    Vector3 maxPt;
};

BBox union_(BBox& box, Vector3& point);
BBox union_(BBox& box0, BBox& box1);

#endif
