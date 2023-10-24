#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "scop.hpp"
#define MAX_BUFFER
#include "Cursor.hpp"
#include "Camera.hpp"

template <class T = void>
class Window {
private:

    static void defaultOnEscape(Window *a, T data, int key) {
        (void)data;
        (void)key;
        a->running = false;
    }

    void draw() {
        glfwSwapBuffers(window);
    }

    void clear() {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void centerCursor() {
        glfwSetCursorPos(window, width / 2, height / 2);
    }

    void input() {
        glfwPollEvents();

        typename std::map<int, keyCallbackFunction>::iterator it = keyHandle.begin();
        for (; it != keyHandle.end(); it++) {
            if (glfwGetKey(window, it->first) == GLFW_PRESS && it->second != nullptr)
                it->second(this, data, it->first);
        }

        Vector2<double> tmp;
        glfwGetCursorPos(window, &tmp.x, &tmp.y);
        if (tmp.x != cursor.position.x || tmp.y != cursor.position.y) {
            if (cursor.onMouvement)
                cursor.onMouvement(this, tmp, cursor.position);
            cursor.position.setData(tmp.data);
            if (this->cursor.centered == true)
                centerCursor();
        }
    }

public:
    typedef void(*callbackFunction)(Window*, T);
    typedef void(*keyCallbackFunction)(Window*, T, int);

    GLFWwindow *window;
    GLFWmonitor *monitor;
    bool running;
    bool resizable;
    int height;
    int width;
    std::string title;
    Vector2<int> position;

    int fpsLimit;
    std::map<int, keyCallbackFunction> keyHandle;

    callbackFunction updateFunction;
    callbackFunction initFunction;
    callbackFunction closeFunction;

    T data;
    Cursor cursor;
    Camera camera;

    static void onMouvement(void *data, Vector2<double> newPos, Vector2<double> oldPos) {
        Vector2<double> diff;
        diff.x = newPos.x - oldPos.x;
        diff.y = newPos.y - oldPos.y;
        std::cout << " test " << diff.x << " et " << diff.y << "\n";

        Window<T> *win = static_cast<Window<T>*>(data);
        win->camera.pitch += diff.y;
        win->camera.yaw += diff.x;
        
    }


    Window() : window(nullptr), monitor(nullptr), running(false), resizable(true), height(500), width(500), title("My super window"), fpsLimit(60), updateFunction(nullptr), initFunction(nullptr), closeFunction(nullptr), data(nullptr)
    {
        cursor.onMouvement = onMouvement;
        keyHandle[GLFW_KEY_ESCAPE] = defaultOnEscape;
    }

    ~Window() {
        glBindVertexArray(0);

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void initGlfw() {
        if (!glfwInit())
            throw "Failed to init GLFW";
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, resizable == true ? GLFW_TRUE : GLFW_FALSE);
    }

    void initGlew() {
        // https://glew.sourceforge.net/basic.html
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Error occured\n";
            exit(1);
        }
        // int width, height;
        // glfwGetFramebufferSize(window, &width, &height);
        // glViewport(0, 0, width, height);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);

        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::cout << "OPENGL VERSION : " << glGetString(GL_VERSION) << "\n";
        std::cout << "GLSL VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

        int i;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &i);
        std::cout << "GL MAX TEXTURE IMAGE UNITS : " << i << "\n";
    }


    void create() {
        initGlfw();

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr)
            throw std::runtime_error("Could not create window");
        glfwMakeContextCurrent(window);
        monitor = glfwGetPrimaryMonitor();
        
        if (cursor.hidden == true)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (cursor.centered == true)
            centerCursor();

        initGlew();
    }

    void stop() {
        running = false;
    }

    void start() {
        running = true;
        double lastTime = 0.0;

        if (initFunction != nullptr)
            initFunction(this, data);

        while (running && !glfwWindowShouldClose(window)) {

            double time = glfwGetTime();
            
            if ((time - lastTime) >= 1/static_cast<double>(fpsLimit)) {
                clear();
                if (updateFunction)
                    updateFunction(this, data);

                input();


                lastTime = time;
                draw();
            }
        }

        if (closeFunction != nullptr)
            closeFunction(this, data);
    }
};

#endif