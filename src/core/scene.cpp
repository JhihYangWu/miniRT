#include "scene.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../mymath/mat4.hpp"

Scene::Scene(std::string filename) {
    // make sure filename ends with scene
    assert(filename.substr(filename.length() - 5) == "scene");

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open scene file at " << filename << std::endl;
        assert(0);
    }

    // default values
    numThreads = 1;
    Vector3 camLoc = Vector3(0, 0, 10);
    Vector3 camLookAt = Vector3(0, 0, 0);
    float camFovY = 90;
    float targetWidth = 100;
    float targetHeight = 100;

    std::string line;
    int lineNum = 0;
    Mat4 transform;
    while (std::getline(file, line)) {
        lineNum++;
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        float x, y, z;
        int R, G, B, A;
        char ch;
        if (type[0] == '#' || line.size() == 0) {
            continue; // skip comment lines
        } else if (type == "numThreads") {
            iss >> numThreads;
        } else if (type == "camLoc") {
            iss >> x >> ch >> y >> ch >> z;
            camLoc = Vector3(x, y, z);
        } else if (type == "lookAt") {
            iss >> x >> ch >> y >> ch >> z;
            camLookAt = Vector3(x, y, z);
        } else if (type == "fovY") {
            iss >> camFovY;
        } else if (type == "renderWidth") {
            iss >> targetWidth;
        } else if (type == "renderHeight") {
            iss >> targetHeight;
        } else if (type == "obj") {
            // get path
            std::string path;
            iss >> path;
            // get octree maxDepth
            iss >> R;
            // get octree approxTrigPerBBox
            iss >> G;
            objs.push_back(new TriMesh(path, R, G, transform));
        } else if (type == "sphere") {
            // get radius
            float radius;
            iss >> radius;
            // get location
            iss >> x >> ch >> y >> ch >> z;
            // get RGBA
            iss >> R >> ch >> G >> ch >> B >> ch >> A;
            Vector3 loc(x, y, z);
            // apply transformation (if any)
            loc = transform(loc);
            spheres.push_back(Sphere(radius, loc, Color(R, G, B, A)));
        } else if (type == "plane") {
            // get upper left
            iss >> x >> ch >> y >> ch >> z;
            Vector3 upperLeft = Vector3(x, y, z);
            // get lower left
            iss >> x >> ch >> y >> ch >> z;
            Vector3 lowerLeft = Vector3(x, y, z);
            // get lower right
            iss >> x >> ch >> y >> ch >> z;
            Vector3 lowerRight = Vector3(x, y, z);
            // get RGBA
            iss >> R >> ch >> G >> ch >> B >> ch >> A;
            // apply transformation (if any)
            upperLeft = transform(upperLeft);
            lowerLeft = transform(lowerLeft);
            lowerRight = transform(lowerRight);
            planes.push_back(Plane(upperLeft, lowerLeft, lowerRight, Color(R, G, B, A)));
        } else if (type == "transform") {
            // get translation
            iss >> x >> ch >> y >> ch >> z;
            Vector3 trans(x, y, z);
            // get rotation
            iss >> x >> ch >> y >> ch >> z;
            Vector3 rot(x, y, z);
            // get scale
            iss >> x >> ch >> y >> ch >> z;
            Vector3 scale(x, y, z);
            // set transformation matrix
            transform = Mat4(); // reset to identity
            transform(0, 0) = scale.x; // apply scale
            transform(1, 1) = scale.y; // apply scale
            transform(2, 2) = scale.z; // apply scale
            transform = matmul(rotXAxis(rot.x), transform); // apply rotation
            transform = matmul(rotYAxis(rot.y), transform);
            transform = matmul(rotZAxis(rot.z), transform);
            transform(0, 3) = trans.x; // apply translation
            transform(1, 3) = trans.y;
            transform(2, 3) = trans.z;
        } else {
            std::cout << "Scene file has syntax error on line " << lineNum << std::endl;
            assert(0);
        }
    }

    cam = new PerspectiveCam(camLoc, camLookAt, camFovY);
    renderTarget = new Texture(targetWidth, targetHeight, 0);
}

Scene::~Scene() {
    delete cam;
    delete renderTarget;
    for (TriMesh* t : objs) {
        delete t;
    }
}
