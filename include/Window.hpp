#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "scop.hpp"
#define MAX_BUFFER

template <class T = void>
class Window {
private:
    GLFWwindow *window;
    GLFWmonitor *monitor;

    static void defaultOnEscape(Window *a, T data) {
        (void)data;
        a->running = false;
    }

    void draw() {
        glfwSwapBuffers(window);
    }

    void clear() {
        glClearColor(0.0, 0.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void input() {
        glfwPollEvents();

        typename std::map<int, callbackFunction>::iterator it = keyHandle.begin();
        for (; it != keyHandle.end(); it++) {
            if (glfwGetKey(window, it->first) == GLFW_PRESS && it->second != nullptr)
                it->second(this, data);
        }
    }

public:
    typedef void(*callbackFunction)(Window*, T);

    bool running;
    bool resizable;
    int height;
    int width;
    std::string title;
    Vector2<int> position;

    int fpsLimit;
    std::map<int, callbackFunction> keyHandle;

    callbackFunction updateFunction;

    T data;

    Window() : window(nullptr), monitor(nullptr), running(false), resizable(true), height(500), width(500), title("My super window"), fpsLimit(60), updateFunction(nullptr), data(nullptr)
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


    void create() {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr)
            throw std::runtime_error("Could not create window");
        glfwMakeContextCurrent(window);
        monitor = glfwGetPrimaryMonitor();
    }

    void stop() {
        running = false;
    }

    void start() {
        running = true;
        double lastTime = 0.0;

        while (running && !glfwWindowShouldClose(window)) {
            clear();

            double time = glfwGetTime();
            
            if ((time - lastTime) >= 1/static_cast<double>(fpsLimit)) {
                if (updateFunction)
                    updateFunction(this, data);

                input();


                lastTime = time;
                draw();
            }
        }
    }
};

#endif