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
)

# create executable
add_executable(${PROJECT_NAME} ${SOURCES})
