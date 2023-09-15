#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

class IVector2 {
public:
    int x;
    int y;
    IVector2() : x(0), y(0) {}
    IVector2(int xVal, int yVal): x(xVal), y(yVal) {}
};

#endif