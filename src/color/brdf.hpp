#ifndef BRDF_H
#define BRDF_H

#include "../mymath/vector3.hpp"

class BRDF{
public:
    virtual float reflectance(Vector3 wi, Vector3 wo, Vector3 normal) = 0;
};

class BlinnPhongBRDF : public BRDF {
public:
    float reflectance(Vector3 wi, Vector3 wo, Vector3 normal);
};

#endif
