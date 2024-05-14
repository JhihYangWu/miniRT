#include "bbox.hpp"
#include <limits>

#define EPSILON 0.000001

BBox::BBox(Vector3 p0, Vector3 p1) {
    minPt.x = std::min(p0.x, p1.x);
    minPt.y = std::min(p0.y, p1.y);
    minPt.z = std::min(p0.z, p1.z);
    maxPt.x = std::max(p0.x, p1.x);
    maxPt.y = std::max(p0.y, p1.y);
    maxPt.z = std::max(p0.z, p1.z);
}

BBox::BBox(const BBox& other) {
    minPt = other.minPt;
    maxPt = other.maxPt;
}

float BBox::intersect(Ray r) {
    // assumes axis-aligned bounding boxes (AABBs)
    // https://tavianator.com/2011/ray_box.html
    // https://github.com/JiayinCao/SORT/blob/master/src/math/bbox.h
    float tmin = std::numeric_limits<float>::min();
    float tmax = std::numeric_limits<float>::max();

    for (int axis = 0; axis < 3; axis++) {
        if (r.d[axis] < EPSILON && r.d[axis] > -EPSILON) {
            // ray does not change value in this axis
            // ray origin of this axis better already be inside the bbox
            if (r.o[axis] < minPt[axis] || r.o[axis] > maxPt[axis]) return -1.0f;
        } else {
            // slab method
            // "The ray is clipped by each pair of parallel planes, and if any portion of the ray remains, it intersected the box"
            // calculate time to reach planes
            float t1 = (minPt[axis] - r.o[axis]) / r.d[axis];
            float t2 = (maxPt[axis] - r.o[axis]) / r.d[axis];
            // clip tmin and tmax
            tmin = std::max(tmin, std::min(t1, t2)); // notice tmin = max(...)
            tmax = std::min(tmax, std::max(t1, t2)); // notice tmax = min(...)

            if (tmin > tmax) return -1.0f; // failed clipping test
        }
    }

    return tmin;
}

bool BBox::isInBox(Vector3 point) {
    if (point.x < minPt.x || point.x > maxPt.x) return false;
    if (point.y < minPt.y || point.y > maxPt.y) return false;
    if (point.z < minPt.z || point.z > maxPt.z) return false;
    return true;
}

void BBox::union_(Vector3 point) {
    minPt.x = std::min(minPt.x, point.x);
    minPt.y = std::min(minPt.y, point.y);
    minPt.z = std::min(minPt.z, point.z);
    maxPt.x = std::max(maxPt.x, point.x);
    maxPt.y = std::max(maxPt.y, point.y);
    maxPt.z = std::max(maxPt.z, point.z);
}

void BBox::union_(BBox box) {
    minPt.x = std::min(minPt.x, box.minPt.x);
    minPt.y = std::min(minPt.y, box.minPt.y);
    minPt.z = std::min(minPt.z, box.minPt.z);
    maxPt.x = std::max(maxPt.x, box.maxPt.x);
    maxPt.y = std::max(maxPt.y, box.maxPt.y);
    maxPt.z = std::max(maxPt.z, box.maxPt.z);
}

BBox union_(BBox& box, Vector3& point) {
    BBox retval(box);
    retval.union_(point);
    return retval;
}

BBox union_(BBox& box0, BBox& box1) {
    BBox retval(box0);
    retval.union_(box1);
    return retval;
}
