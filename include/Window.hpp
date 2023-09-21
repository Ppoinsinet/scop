#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "scop.hpp"
#define MAX_BUFFER

template <class T = void>
class Window {
public:
    typedef void(*callbackFunction)(Window*, T*);

    bool running;
    bool resizable;
    int height;
    int width;
    std::string title;
    Vector2<int> position;

    int fpsLimit;
    std::map<int, callbackFunction> keyHandle;
    unsigned int buffers[2];

    callbackFunction updateFunction;

    T *data;

    GLFWwindow *window;
    GLFWmonitor *monitor;

    Window() : running(false), resizable(true), height(500), width(500), title("My super window"), fpsLimit(60), updateFunction(nullptr), data(nullptr), window(nullptr), monitor(nullptr)
    {
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_RESIZABLE, resizable == true ? GLFW_TRUE : GLFW_FALSE);
        if (!glfwInit())
            throw "Failed to init GLFW";

        keyHandle[GLFW_KEY_ESCAPE] = defaultOnEscape;
    }

    ~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    static void defaultOnEscape(Window *a, T *data) {
        (void)data;
        a->running = false;
    }

    void create() {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr)
            throw "Could not create window";
        glfwMakeContextCurrent(window);
        monitor = glfwGetPrimaryMonitor();
    }

    void input() {
        glfwPollEvents();

        typename std::map<int, callbackFunction>::iterator it = keyHandle.begin();
        for (; it != keyHandle.end(); it++) {
            if (glfwGetKey(window, it->first) == GLFW_PRESS && it->second != nullptr)
                it->second(this, data);
        }
    }

    void draw() {
        glfwSwapBuffers(window);
    }

    void clear() {
        glClearColor(0.0, 0.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void start() {
        running = true;
        double lastTime = 0.0;

        while (running && !glfwWindowShouldClose(window)) {
            clear();

            if (updateFunction)
                updateFunction(this, data);

            input();

            double time = glfwGetTime();
            if ((time - lastTime) >= 1/fpsLimit) {
                lastTime = time;
                draw();
            }
        }
    }
};

#endif