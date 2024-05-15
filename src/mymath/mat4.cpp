#include "mat4.hpp"
#include <cassert>
#include <sstream>
#include <iomanip>

Mat4::Mat4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                data[i][j] = 1.0f;
            } else {
                data[i][j] = 0.0f;
            }
        }
    }
}

Mat4::Mat4(float j00, float j01, float j02, float j03,
           float j10, float j11, float j12, float j13,
           float j20, float j21, float j22, float j23,
           float j30, float j31, float j32, float j33) {
    i00 = j00; i01 = j01; i02 = j02; i03 = j03;
    i10 = j10; i11 = j11; i12 = j12; i13 = j13;
    i20 = j20; i21 = j21; i22 = j22; i23 = j23;
    i30 = j30; i31 = j31; i32 = j32; i33 = j33;
}

Mat4::Mat4(const Mat4& o) {
    for (int i = 0; i < 16; i++) {
        line[i] = o.line[i];
    }
}

Mat4& Mat4::operator=(const Mat4& o) {
    for (int i = 0; i < 16; i++) {
        line[i] = o.line[i];
    }
    return *this;
}

float& Mat4::operator()(int row, int col) {
    assert(row >= 0 && row <= 3);
    assert(col >= 0 && col <= 3);
    return data[row][col];
}

Vector3 Mat4::operator()(Vector3 v) {
    // homogenous coordinates
    float x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3];
    float y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3];
    float z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3];
    float w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3];
    Vector3 retval(x / w, y / w, z / w);
    return retval;
}

Mat4 Mat4::T() {
    Mat4 m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m(i, j) = (*this)(j, i);
        }
    }
    return m;
}

std::string Mat4::str() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) ss << "[";
            ss << data[i][j];
            if (j != 3) ss << " ";
            if (j == 3) ss << "]\n";
        }
    }
    return ss.str();
}

Mat4 matmul(Mat4 m0, Mat4 m1) {
    Mat4 retval;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            retval(i, j) = 0.0f;
            // dot product row i from m0 and col j from m1
            for (int k = 0; k < 4; k++) {
                retval(i, j) += m0(i, k) * m1(k, j);
            }
        }
    }
    return retval;
}

Mat4 rotXAxis(float phi) {
    phi = phi * M_PI / 180.0f;
    return Mat4(1, 0, 0, 0,
                0, cos(phi), -sin(phi), 0,
                0, sin(phi), cos(phi), 0,
                0, 0, 0, 1);
}

Mat4 rotYAxis(float theta) {
    theta = theta * M_PI / 180.0f;
    return Mat4(cos(theta), 0, sin(theta), 0,
                0, 1, 0, 0,
                -sin(theta), 0, cos(theta), 0,
                0, 0, 0, 1);
}

Mat4 rotZAxis(float psi) {
    psi = psi * M_PI / 180.0f;
    return Mat4(cos(psi), -sin(psi), 0, 0,
                sin(psi), cos(psi), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

Mat4 operator+(Mat4& m0, Mat4& m1) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m0.line[i] + m1.line[i];
    return retval;
}

Mat4 operator-(Mat4& m0, Mat4& m1) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m0.line[i] - m1.line[i];
    return retval;
}

Mat4 operator*(Mat4& m0, Mat4& m1) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m0.line[i] * m1.line[i];
    return retval;
}

Mat4 operator/(Mat4& m0, Mat4& m1) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m0.line[i] / m1.line[i];
    return retval;
}

Mat4 operator+(Mat4& m, float scalar) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m.line[i] + scalar;
    return retval;
}

Mat4 operator-(Mat4& m, float scalar) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m.line[i] - scalar;
    return retval;
}

Mat4 operator*(Mat4& m, float scalar) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m.line[i] * scalar;
    return retval;
}

Mat4 operator/(Mat4& m, float scalar) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = m.line[i] / scalar;
    return retval;
}

Mat4 operator+(float scalar, Mat4& m) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = scalar + m.line[i];
    return retval;
}

Mat4 operator-(float scalar, Mat4& m) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = scalar - m.line[i];
    return retval;
}

Mat4 operator*(float scalar, Mat4& m) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = scalar * m.line[i];
    return retval;
}

Mat4 operator/(float scalar, Mat4& m) {
    Mat4 retval;
    for (int i = 0; i < 16; i++) retval.line[i] = scalar / m.line[i];
    return retval;
}
