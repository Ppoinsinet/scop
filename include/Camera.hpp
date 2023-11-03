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
        position = Vector3<float>(0.0f, 0.0f, -5.0f);
        nearZ = 0.01f;
        farZ = 10.f;
        FOV = 45;

        U = Vector3<float>(1.0f, 0.0f, 0.0f);
        V = Vector3<float>(0.0f, 1.0f, 0.0f);
        N = Vector3<float>(0.0f, 0.0f, 1.0f);
    }

    Camera(const Camera &ref) {
        position = ref.position;
        nearZ = ref.nearZ;
        farZ = ref.farZ;
        FOV = ref.FOV;

        U = ref.U;
        V = ref.V;
        N = ref.N;
    }

    Camera &operator=(const Camera &ref) {
        position = ref.position;
        nearZ = ref.nearZ;
        farZ = ref.farZ;
        FOV = ref.FOV;

        U = ref.U;
        V = ref.V;
        N = ref.N;
        return *this;
    }

    Matrix<3, 3, float> getRotatedVectors() {
        Matrix<3, 3, float> result;

        Vector3<float> tmpU = U;
        Vector3<float> tmpV = V;
        Vector3<float> tmpN = N;

        tmpN = rotate(yaw, tmpN, V);
        tmpN.normalize();

        tmpU = tmpN.cross(tmpV);
        tmpU.normalize();

        tmpN = rotate(pitch, tmpN, tmpU);
        tmpN.normalize();

        tmpV = tmpN.cross(tmpU);
        if (tmpV.y < 0)
            tmpV = tmpV * -1;
        tmpV.normalize();


        result = (float[]) {
            tmpU.x, tmpV.x, tmpN.x,
            tmpU.y, tmpV.y, tmpN.y,
            tmpU.z, tmpV.z, tmpN.z
        };

        return result;
    }

    Matrix<4, 4, float> getMatrix() {
        Matrix<3, 3, float> rotated = getRotatedVectors();
        Vector3<float> tmpU = rotated.getColumn(0);
        Vector3<float> tmpV = rotated.getColumn(1);
        Vector3<float> tmpN = rotated.getColumn(2);
        
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