set(SOURCES
main.cpp
mymath/vector3.hpp
mymath/vector3.cpp
mymath/ray.hpp
mymath/ray.cpp
texture/texture.hpp
texture/texture.cpp
color/color.hpp
color/color.cpp
mymath/mat4.hpp
mymath/mat4.cpp
camera/perspective.hpp
camera/perspective.cpp
geometry/triangle.hpp
geometry/triangle.cpp
geometry/trimesh.hpp
geometry/trimesh.cpp
)

# create executable
add_executable(${PROJECT_NAME} ${SOURCES})
