#include <iostream>
#include "geometry/trimesh.hpp"
#include "texture/texture.hpp"
#include "core/system.hpp"
#include "camera/perspective.hpp"
#include "core/timer.hpp"

int main(int argc, char* argv[]) {
    TriMesh monkey("scenes/monkey/monkey.obj");
    Texture renderTarget(400, 300, 0);
    PerspectiveCam cam(Vector3(0, 0, 8), Vector3(0, 0, 0), 90);
    Vector3 lightLoc = Vector3(100, 100, 100);
    Timer timer;
    System system(timer, cam, renderTarget, lightLoc);
    system.addTriMesh(&monkey);
    system.render();
    renderTarget.save("render.ppm");

    return 0;
}
