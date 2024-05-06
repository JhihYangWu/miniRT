set(SOURCES
main.cpp
mymath/vector3.hpp
mymath/vector3.cpp
mymath/ray.hpp
mymath/ray.cpp
)

# create executable
add_executable(${PROJECT_NAME} ${SOURCES})
