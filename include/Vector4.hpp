#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "Matrix.hpp"

template <class T = int>
class Vector4: public Matrix<4, 1, T> {
public:

    typedef Matrix<4, 1, T> MatrixType;

    T &x;
    T &y;
    T &z;
    T &w;

    Vector4()
    : x(this->data[0]), y(this->data[1]), z(this->data[2]), w(this->data[3])
    {}

    Vector4(T xVal, T yVal, T zVal, T wVal)
    : x(this->data[0]), y(this->data[1]), z(this->data[2]), w(this->data[3])
    {
        x = xVal;
        y = yVal;
        z = zVal;
        w = wVal;
    }

    Vector4(const Vector4<T> &ref)
    : x(this->data[0]), y(this->data[1]), z(this->data[2]), w(this->data[3])
    {
        x = ref.x;
        y = ref.y;
        z = ref.z;
        w = ref.w;
    }

    Vector4(const MatrixType &ref)
    : x(this->data[0]), y(this->data[1]), z(this->data[2]), w(this->data[3])
    {
        x = ref[0];
        y = ref[1];
        z = ref[2];
        w = ref[3];
    }

    MatrixType getMatrice() {
        return *this;
    }

    Vector4<T> &operator=(const MatrixType &ref) {
        x = ref[0];
        y = ref[1];
        z = ref[2];
        return *this;
    }

    Vector4<T> &operator=(const Vector4<T> &ref) {
        x = ref.x;
        y = ref.y;
        z = ref.z;
        w = ref.w;
        return *this;
    }

    // Vector4<T> cross(const Vector4<T> &ref) {
    //     Vector4<T> result;
    //     result.x = (y * ref.z) - (z * ref.y);
    //     result.y = (z * ref.x) - (x * ref.z);
    //     result.z = (x * ref.y) - (y * ref.x);
    //     return result;
    // }

    Vector4<T> operator*(int i) {
        return Vector4<T>(x * i, y * i, z * i);
    }

    Vector4<T> operator*(float i) {
        return Vector4<T>(x * i, y * i, z * i);
    }
};

#endif