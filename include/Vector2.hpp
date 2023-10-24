#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Matrix.hpp"

template <class T = int>
class Vector2: public Matrix<2, 1, T> {
public:

    typedef Matrix<2, 1, T> MatrixType;

    T &x;
    T &y;

    Vector2()
    : x(MatrixType::data[0]), y(MatrixType::data[1])
    {}

    Vector2(T xVal, T yVal)
    : x(MatrixType::data[0]), y(MatrixType::data[1])
    {
        x = xVal;
        y = yVal;
    }

    Vector2(const Vector2<T> &ref)
    : x(MatrixType::data[0]), y(MatrixType::data[1])
    {
        x = ref.x;
        y = ref.y;
    }

    Vector2<T> &operator=(const Vector2<T> &ref) {
        x = ref.x;
        y = ref.y;
        return *this;
    }
};

#endif