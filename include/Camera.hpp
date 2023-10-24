#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3.hpp"

class Camera {
private:
public:
    float FOV;
    Vector3<float> position;

    float nearZ;
    float farZ;

    Vector3<float> U;
    Vector3<float> V;
    Vector3<float> N;


    Camera() {
        position = Vector3<float>(0.0f, 0.0f, 0.0f);
        nearZ = 1.0f;
        farZ = 10.0f;
        FOV = 45;

        U = Vector3<float>(1.0f, 0.0f, 0.0f);
        V = Vector3<float>(0.0f, 1.0f, 0.0f);
        N = Vector3<float>(0.0f, 0.0f, 1.0f);
    }

    Matrix<4, 4, float> getMatrix() {
        Matrix<4, 4, float> m = (float[]) {
            U.x(), U.y(), U.z(), 0.0f,
            V.x(), V.y(), V.z(), 0.0f,
            N.x(), N.y(), N.z(), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Matrix<4, 4, float> n = (float[]) {
            1.0f, 0.0f, 0.0f, -position.x(),
            0.0f, 1.0f, 0.0f, -position.y(),
            0.0f, 0.0f, 1.0f, -position.z(),
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return (m * n);
    }


};


#endif