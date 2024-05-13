#ifndef TRIMESH_H
#define TRIMESH_H

#include <vector>
#include <string>
#include "triangle.hpp"

class TriMesh{
public:
    // constructors
    TriMesh(std::string filename); // creates triangle mesh from obj file
    
    // methods
    std::string str();

    // attributes
    std::vector<Vector3> vertexBuffer;
    std::vector<Vector3> normalBuffer;
    int numTriangles;
    std::vector<Triangle> triangles;
};

#endif
