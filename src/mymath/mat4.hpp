#ifndef MAT4_H
#define MAT4_H

#include <string>
#include "vector3.hpp"

class Mat4{
public:
    // constructors
    Mat4(); // identity
    Mat4(float i00, float i01, float i02, float i03,
         float i10, float i11, float i12, float i13,
         float i20, float i21, float i22, float i23,
         float i30, float i31, float i32, float i33);
    Mat4(const Mat4& other); // copy constructor

    // operators and methods
    Mat4& operator=(const Mat4& other);
    float& operator()(int row, int col);
    Vector3 operator()(Vector3 v); // transforms (trans, rot, scale, etc) a vector
    Mat4 T(); // returns a new Mat4 with values transposed
    std::string str();
    
    // attributes
    // 16 floats accessed in two ways
    union{
        struct{
            float i00, i01, i02, i03,
                  i10, i11, i12, i13,
                  i20, i21, i22, i23,
                  i30, i31, i32, i33;
        };
        struct{
            float data[4][4];
        };
        struct{
            float line[16];
        };
    };
};

// operators and functions
Mat4 matmul(Mat4 m0, Mat4 m1);
Mat4 rotXAxis(float phi); // all in degrees
Mat4 rotYAxis(float theta);
Mat4 rotZAxis(float psi);

// following functions are all element wise
Mat4 operator+(Mat4& m0, Mat4& m1);
Mat4 operator-(Mat4& m0, Mat4& m1);
Mat4 operator*(Mat4& m0, Mat4& m1);
Mat4 operator/(Mat4& m0, Mat4& m1);

Mat4 operator+(Mat4& m, float scalar);
Mat4 operator-(Mat4& m, float scalar);
Mat4 operator*(Mat4& m, float scalar);
Mat4 operator/(Mat4& m, float scalar);

Mat4 operator+(float scalar, Mat4& m);
Mat4 operator-(float scalar, Mat4& m);
Mat4 operator*(float scalar, Mat4& m);
Mat4 operator/(float scalar, Mat4& m);

#endif
