#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Matrix.hpp"

template <class T = int>
class Vector3: public Matrix<3, 1, T> {
public:

    typedef Matrix<3, 1, T> MatrixType;

    T &x;
    T &y;
    T &z;

    Vector3()
    : x(this->data[0]), y(this->data[1]), z(this->data[2])
    {}

    Vector3(T xVal, T yVal, T zVal)
    : x(this->data[0]), y(this->data[1]), z(this->data[2])
    {
        x = xVal;
        y = yVal;
        z = zVal;
    }

    Vector3(const Vector3<T> &ref)
    : x(this->data[0]), y(this->data[1]), z(this->data[2])
    {
        x = ref.x;
        y = ref.y;
        z = ref.z;
    }

    Vector3(const MatrixType &ref)
    : x(this->data[0]), y(this->data[1]), z(this->data[2])
    {
        x = ref[0];
        y = ref[1];
        z = ref[2];
    }

    MatrixType getMatrice() {
        return *this;
    }

    Vector3 &operator=(const MatrixType &ref) {
        x = ref[0];
        y = ref[1];
        z = ref[2];
        return *this;
    }

    Vector3 &operator=(const Vector3<T> &ref) {
        x = ref.x;
        y = ref.y;
        z = ref.z;
        return *this;
    }
};

#endif