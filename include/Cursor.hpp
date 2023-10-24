#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "Vector2.hpp"

class Cursor {
private:
public:
    Vector2<double> position;
    bool hidden;
    bool centered;

    void (*onMouvement)(void *data, Vector2<double> newPos, Vector2<double> oldPos);

};

#endif