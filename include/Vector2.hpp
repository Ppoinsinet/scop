#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Matrix.hpp"

template <class T = int>
class Vector2: public Matrix<2, 1, T> {
public:

    Vector2()
    : Matrix<2, 1, T>()
    {}

    Vector2(T xVal, T yVal)
    : Matrix<2, 1, T>()
    {
        Matrix<2, 1, T>::data[0] = xVal;
        Matrix<2, 1, T>::data[1] = yVal;
    }

    Vector2(const Vector2<T> &ref)
    : Matrix<2, 1, T>()
    {
        Matrix<2, 1, T>::data[0] = ref.data[0];
        Matrix<2, 1, T>::data[1] = ref.data[1];
    }

    T &x() {return Matrix<2, 1, T>::data[0];}
    T &y() {return Matrix<2, 1, T>::data[1];}

    Vector2 &operator=(const Vector2<T> &ref) {
        x() = ref.x();
        y() = ref.y();
        return *this;
    }
};

#endif