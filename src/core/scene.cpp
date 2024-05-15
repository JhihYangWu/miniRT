#include "scene.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

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
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        float x, y, z;
        int R, G, B, A;
        char ch;
        if (type[0] == '#') {
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
            objs.push_back(new TriMesh(path, R, G));
        } else if (type == "sphere") {
            // get radius
            float radius;
            iss >> radius;
            // get location
            iss >> x >> ch >> y >> ch >> z;
            // get RGBA
            iss >> R >> ch >> G >> ch >> B >> ch >> A;
            spheres.push_back(Sphere(radius, Vector3(x, y, z), Color(R, G, B, A)));
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
            planes.push_back(Plane(upperLeft, lowerLeft, lowerRight, Color(R, G, B, A)));
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
