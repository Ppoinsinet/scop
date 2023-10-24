#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3.hpp"
#include "Quaternion.hpp"

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

    float pitch; // Rotation around X
    float yaw; // Rotation around Y
    float roll; // Rotation around Z

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
        Vector3<float> tmpU = U;
        Vector3<float> tmpV = V;
        Vector3<float> tmpN = N;

        // Quaternion rotaU(pitch, U); // Pitch
        // Quaternion conju = rotaU.conjugate();

        // Quaternion test = rotaU * U * conju;
        // tmpU.x = test.x;
        // tmpU.y = test.y;
        // tmpU.z = test.z;

        // tmpU.normalize();

        std::cout << "Test avec pitch " << pitch << " et yaw " << yaw << "\n";
        



        Matrix<4, 4, float> m = (float[]) {
            tmpU.x, tmpU.y, tmpU.z, 0.0f,
            V.x, V.y, V.z, 0.0f,
            N.x, N.y, N.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Matrix<4, 4, float> n = (float[]) {
            1.0f, 0.0f, 0.0f, -position.x,
            0.0f, 1.0f, 0.0f, -position.y,
            0.0f, 0.0f, 1.0f, -position.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return (m * n);
    }


};


#endif