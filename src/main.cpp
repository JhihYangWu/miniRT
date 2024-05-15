#include <iostream>
#include "core/scene.hpp"
#include "core/system.hpp"

int main(int argc, char* argv[]) {
    Scene scene("scenes/monkey/monkey.scene");
    System system(scene);
    system.render();
    system.renderTarget.save("render.ppm");

    return 0;
}
