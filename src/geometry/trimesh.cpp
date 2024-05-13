#include "trimesh.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

TriMesh::TriMesh(std::string filename) {
    // make sure filename ends with obj
    assert(filename.substr(filename.length() - 3) == "obj");

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open obj file at " << filename << std::endl;
        assert(0);
    }

    std::string line;
    numTriangles = 0;
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
            triangles.push_back(Triangle(A, B, C));
        }
    }
}

std::string TriMesh::str() {
    return "Mesh with " + std::to_string(numTriangles) + " triangles";
}
