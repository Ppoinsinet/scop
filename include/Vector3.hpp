#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>

template <class T = int>
class Vector3 {
public:

    T x;
    T y;
    T z;

    Vector3() : x(T()), y(T()), z(T())
    {}

    Vector3(T xVal, T yVal, T zVal):
    x(xVal), y(yVal), z(zVal) {}

    Vector3(const Vector3<T> &ref)
    : x(ref.x), y(ref.y), z(ref.z) {}

    Vector3 &operator=(const Vector3<T> &ref) {
        x = ref.x;
        y = ref.y;
        z = ref.z;
        return *this;
    }
};

#endif