#include "brdf.hpp"
#include <cmath>

#define PHONG_EXP 50
#define PHONG_DIFFUSE_K 0.5
#define PHONG_SPECULAR_K 5

float BlinnPhongBRDF::reflectance(Vector3 wi, Vector3 wo, Vector3 normal) {
    // reflect wi and dot with wo
    Vector3 refWi = -wi + 2 * dot(wi, normal) * normal;
    return PHONG_DIFFUSE_K + PHONG_SPECULAR_K * powf(dot(refWi, wo), PHONG_EXP);
}
