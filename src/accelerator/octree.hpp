#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include "../mymath/bbox.hpp"
#include "../geometry/triangle.hpp"

class Octree{
public:
    // constructor
    Octree(BBox bbox, std::vector<Triangle*> trigs, int maxDepth, int approxTrigPerBBox);
    ~Octree(); // deconstructor

    // methods
    float intersect(Ray r, Triangle** hitTrig); // hitTrig is out variable for nearest triangle hit
                                                // returns time of intersection
                                                // returns -1.0f if nothing hit

    // attributes
    BBox bbox; // bbox this node is responsible for
    bool isLeaf;
    Octree* children[8]; // all nullptr if leaf node
    std::vector<Triangle*> trigs; // empty if not leaf node
};

#endif
