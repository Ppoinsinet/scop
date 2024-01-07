#ifndef SCENE_HPP
#define SCENE_HPP

#include "VAO.hpp"
#include "Camera.hpp"
#include <vector>

class Scene {
public:
    std::vector<VAO*> listVAO;
    Camera camera;

    Scene() {}

    Scene(const Scene &ref) {
        listVAO = ref.listVAO;
        camera = ref.camera;
    }

    Scene &operator=(const Scene &ref) {
        listVAO = ref.listVAO;
        camera = ref.camera;
        return *this;
    }

    static void onMouvement(void *data, Vector2<double> newPos, Vector2<double> oldPos) {
        Vector2<double> diff;
        diff.x = -(newPos.x - oldPos.x);
        diff.y = (newPos.y - oldPos.y);

        Window<Scene> *win = static_cast<Window<Scene>*>(data);

        // std::cout << " test " << win->camera.pitch << " et " << win->camera.yaw << "\n";
        if (win->data->camera.pitch > 89)
            win->data->camera.pitch = 89;
        else if (win->data->camera.pitch < -89)
            win->data->camera.pitch = -89;
        else
            win->data->camera.pitch -= diff.y;
        std::cout << "camera pitch : " << win->data->camera.pitch << "\n";
        
        win->data->camera.yaw += diff.x;
        
    }
};

#endif