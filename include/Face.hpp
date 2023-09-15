#ifndef FACE_HPP
#define FACE_HPP

class Face {
public:
    int verticesIndex[3];
    int smoothingGroup;

    Face(int index1, int index2, int index3, int smoothGrp);
};

#endif