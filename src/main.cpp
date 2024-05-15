#include <iostream>
#include "core/scene.hpp"
#include "core/system.hpp"

int main(int argc, char* argv[]) {
    Scene scene("example_scene/example_scene.scene");
    System system(scene);
    system.render();
    system.renderTarget.save("render.ppm");

    return 0;
}
