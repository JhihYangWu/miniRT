#ifndef TRIMESH_H
#define TRIMESH_H

#include <vector>
#include <string>
#include "triangle.hpp"
#include "../accelerator/octree.hpp"

class TriMesh{
public:
    // constructors
    // creates triangle mesh from obj file
    // also puts triangles in octree
    TriMesh(std::string filename, int octreeMaxDepth, int octreeApproxTrigPerBBox);
    ~TriMesh(); // deconstructor
    
    // methods
    std::string str();

    // attributes
    std::vector<Vector3> vertexBuffer;
    std::vector<Vector3> normalBuffer;
    int numTriangles;
    std::vector<Triangle> triangles;
    Octree* octree; // accelerator
};

#endif
