#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Matrix.hpp"

template <class T = int>
class Vector3: public Matrix<3, 1, T> {
public:

    Vector3()
    : Matrix<3, 1, T>()
    {}

    Vector3(T xVal, T yVal, T zVal)
    : Matrix<3, 1, T>()
    {
        Matrix<3, 1, T>::data[0] = xVal;
        Matrix<3, 1, T>::data[1] = yVal;
        Matrix<3, 1, T>::data[2] = zVal;
    }

    Vector3(const Matrix<3, 1, T> &ref)
    : Matrix<3, 1, T>()
    {
        Matrix<3, 1, T>::data[0] = ref.data[0];
        Matrix<3, 1, T>::data[1] = ref.data[1];
        Matrix<3, 1, T>::data[2] = ref.data[2];
    }

    Matrix<3, 1, T> getMatrice() {
        return Matrix<3, 1, T>(Matrix<3, 1, T>::data);
    }

    T &x() {return Matrix<3, 1, T>::data[0];}
    T &y() {return Matrix<3, 1, T>::data[1];}
    T &z() {return Matrix<3, 1, T>::data[2];}

    Vector3 &operator=(const Matrix<3, 1, T> &ref) {
        Matrix<3, 1, T>::data[0] = ref.data[0];
        Matrix<3, 1, T>::data[1] = ref.data[1];
        Matrix<3, 1, T>::data[2] = ref.data[2];
        return *this;
    }
};

#endif