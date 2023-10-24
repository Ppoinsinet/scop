#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "math.h"
#include "Vector3.hpp"

#define TO_RADIAN(x) (x * M_PI / 180)

class Quaternion {
private:
public:
    float x;
    float y;
    float z;
    float w;

    Quaternion(float xVal, float yVal, float zVal, float wVal) {
        
        w = wVal;
        x = xVal;
        y = yVal;
        z = zVal;
    }

    Quaternion(const float angle, Vector3<float> vector) {
        float half = TO_RADIAN(angle/2);
        float sine = sinf(half);

        w = cosf(half);
        x = vector.x * sine;
        y = vector.y * sine;
        z = vector.z * sine;
    }

    Quaternion conjugate() const {
        return Quaternion(-x, -y, -z, w);
    }

    void normalize() {
        float len = sqrtf(x * x + y * y + z * z + w * w);

        w /= len;
        x /= len;
        y /= len;
        z /= len;
    }

    Quaternion operator*(Vector3<float> vec) {
        return Quaternion(
            w * vec.x + y * vec.z - z * vec.y,
            w * vec.y + z * vec.x - x * vec.z,
            w * vec.z + x * vec.y - y * vec.x,
            x * vec.x - y * vec.y - z * vec.z
        );
    }

    Quaternion operator*(const Quaternion &ref) {
        return Quaternion(
            x * ref.w + w * ref.x + y * ref.z - z * ref.y,
            y * ref.w + w * ref.y + z * ref.x - x * ref.z,
            z * ref.w + w * ref.z + x * ref.y - y * ref.x,
            w * ref.w - x * ref.x - y * ref.y - z * ref.z
        );
    }
};

#endif