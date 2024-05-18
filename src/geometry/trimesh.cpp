#include "trimesh.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

TriMesh::TriMesh(std::string filename, int octreeMaxDepth, int octreeApproxTrigPerBBox, Mat4 transform, Color& c) {
    // make sure filename ends with obj
    assert(filename.substr(filename.length() - 3) == "obj");

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open obj file at " << filename << std::endl;
        assert(0);
    }

    std::string line;
    numTriangles = 0;
    BBox bbox;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        float x, y, z;
        int i, j, k;
        char ch;
        if (type == "v") {
            iss >> x >> y >> z;
            vertexBuffer.push_back(Vector3(x, y, z));
        } else if (type == "vn") {
            iss >> x >> y >> z;
            normalBuffer.push_back(Vector3(x, y, z));
        } else if (type == "f") {
            numTriangles++;
            iss >> i >> ch >> j >> ch >> k;
            Vector3 A = vertexBuffer[i - 1]; // - 1 because obj format is 1-indexed
            iss >> i >> ch >> j >> ch >> k;
            Vector3 B = vertexBuffer[i - 1];
            iss >> i >> ch >> j >> ch >> k;
            Vector3 C = vertexBuffer[i - 1];
            A = transform(A); // apply transformation
            B = transform(B);
            C = transform(C);
            triangles.push_back(Triangle(A, B, C, c));
            bbox.union_(A);
            bbox.union_(B);
            bbox.union_(C);
        }
    }

    if (numTriangles == 0) {
        std::cout << "Obj file at " << filename << " has 0 triangles, perhaps the path is incorrect?" << std::endl;
        assert(0);
    }

    // put triangles in octree
    std::vector<Triangle*> trigRefs;
    for (Triangle& t : triangles) trigRefs.push_back(&t);
    octree = new Octree(bbox, trigRefs, octreeMaxDepth, octreeApproxTrigPerBBox);
}

TriMesh::~TriMesh() {
    delete octree;
}

std::string TriMesh::str() {
    return "Mesh with " + std::to_string(numTriangles) + " triangles";
}
