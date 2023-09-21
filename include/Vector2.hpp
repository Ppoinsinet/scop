#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template <class T = int>
class Vector2 {
public:
    T x;
    T y;
    Vector2() : x(0), y(0) {}
    Vector2(T xVal, T yVal): x(xVal), y(yVal) {}
};

#endif