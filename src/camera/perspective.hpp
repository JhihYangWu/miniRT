#ifndef PERSPECTIVE_CAM_H
#define PERSPECTIVE_CAM_H

#include "../mymath/vector3.hpp"
#include "../mymath/ray.hpp"

class PerspectiveCam{
public:
    // constructors
    // camera located at loc and looking at point lookAt
    PerspectiveCam(Vector3 loc, Vector3 lookAt, float fovY);

    // methods
    // generates a ray shooting towards image plane
    //         (1, 1)
    //     .  .  .
    //     .  .  .
    //     .  .  .
    // (-1, -1)
    // x can exceed -1.0f and 1.0f range if not square image
    // y should be between -1.0f and 1.0f
    Ray generateRay(float x, float y);

private:
    // attributes, not allowed to change so private
    Vector3 loc; // location of the camera
    Vector3 up; // up vector, default (0, 1, 0)
    float imgPlaneDist;
    Vector3 u; // vector towards right of image plane
    Vector3 v; // vector towards top of image plane
    Vector3 w; // vector towards back of camera
};

#endif
