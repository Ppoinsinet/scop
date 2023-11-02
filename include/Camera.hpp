#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3.hpp"
#include "Quaternion.hpp"

template <typename T>
Vector3<T> rotate(float angle, const Vector3<T> &a, const Vector3<T> &b) {
    Quaternion rota(angle, b);

    Quaternion conjugate = rota.conjugate();

    Quaternion w = rota * a * conjugate;

    return Vector3<T>(w.x, w.y, w.z);
}

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
        nearZ = 0.01f;
        farZ = 10.f;
        FOV = 45;

        U = Vector3<float>(1.0f, 0.0f, 0.0f);
        V = Vector3<float>(0.0f, 1.0f, 0.0f);
        N = Vector3<float>(0.0f, 0.0f, 1.0f);
    }

    Matrix<4, 4, float> getMatrix() {
        Vector3<float> tmpU = U;
        Vector3<float> tmpV = V;
        Vector3<float> tmpN = N;

        if (pitch != 0.0f) {
            tmpN = rotate(pitch, tmpN, U);
            tmpN.normalize();

            tmpV = tmpN.cross(U);
            tmpV.normalize();
        }

        if (yaw != 0.0f) {
            tmpN = rotate(yaw, tmpN, tmpV);
            tmpN.normalize();

            tmpU = tmpN.cross(tmpV) * -1;
            tmpU.normalize();
        }

        U = tmpU;
        V = tmpV;
        N = tmpN;
        
        pitch = 0.0f;
        yaw = 0.0f;

        // std::cout << "tmpU : \n" << tmpU << "\n\n";
        // std::cout << "tmpV : \n" << tmpV << "\n\n";
        // std::cout << "tmpN : \n" << tmpN << "\n\n";
        
        Matrix<4, 4, float> m = (float[]) {
            tmpU.x, tmpU.y, tmpU.z, 0.0f,
            tmpV.x, tmpV.y, tmpV.z, 0.0f,
            tmpN.x, tmpN.y, tmpN.z, 0.0f,
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