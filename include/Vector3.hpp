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
    : x(MatrixType::data[0]), y(MatrixType::data[1]), z(MatrixType::data[2])
    {}

    Vector3(T xVal, T yVal, T zVal)
    : x(MatrixType::data[0]), y(MatrixType::data[1]), z(MatrixType::data[2])
    {
        x = xVal;
        y = yVal;
        z = zVal;
    }

    Vector3(const Vector3<T> &ref)
    : x(MatrixType::data[0]), y(MatrixType::data[1]), z(MatrixType::data[2])
    {
        x = ref.x;
        y = ref.y;
        z = ref.z;
    }

    MatrixType getMatrice() {
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