#include "Face.hpp"

Face::Face(int index1, int index2, int index3, int smoothGrp = 0) {
    verticesIndex[0] = index1;
    verticesIndex[1] = index2;
    verticesIndex[2] = index3;
    smoothingGroup = smoothGrp;
}