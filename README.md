# miniRT
miniRT is a small but powerful ray tracer I built from scratch to learn more about computer graphics  
no dependencies, pure c++ and math  

---
## Render Example Scene
```sh
git clone https://github.com/JhihYangWu/miniRT.git
cd miniRT
./run.sh
```
the render will be saved as render.ppm  
checkpoints are saved in snapshots/
![example_scene](/example_scene/example_scene.png)

---
## Features
Möller–Trumbore triangle ray intersection algorithm  
Octree  
Multithreading  
Path tracing  
The rendering equation  
Indirect lighting  
Ambient occlusion  
Blinn/Phong BRDF  
Colored/uncolored mirrors  
Refraction (Snell law)

---
## Gallery
![stanford_dragon](/more_example_scenes/stanford_dragon/stanford_dragon.png)
[Stanford Dragon](https://graphics.stanford.edu/data/3Dscanrep/)  

---
inspired by the project structure and design of [SORT](https://github.com/JiayinCao/SORT)  
