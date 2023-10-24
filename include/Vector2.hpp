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
    : x(this->data[0]), y(this->data[1])
    {}

    Vector2(T xVal, T yVal)
    : x(this->data[0]), y(this->data[1])
    {
        x = xVal;
        y = yVal;
    }

    Vector2(const Vector2<T> &ref)
    : x(this->data[0]), y(this->data[1])
    {
        x = ref.x;
        y = ref.y;
    }

    Vector2(const MatrixType &ref)
    : x(this->data[0]), y(this->data[1])
    {
        x = ref[0];
        y = ref[1];
    }

    Vector2<T> &operator=(const Vector2<T> &ref) {
        x = ref.x;
        y = ref.y;
        return *this;
    }
    
    Vector2<T> &operator=(const MatrixType &ref) {
        x = ref[0];
        y = ref[1];
        return *this;
    }
};

#endif