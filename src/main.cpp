#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 150

void onError(std::string str) {
    std::cerr << str << "\n";
    exit(1);
}

void onUpdate(Window<> *win, void *data) {
    static int len = 0;
    (void)win;
    (void)data;
    
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);

    glEnd();

    glFlush();




    std::cout << "update " << len++ << "\n";
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }
    const ObjParser parser(av[1]);

    Window<void> window;

    window.create();
    window.updateFunction = onUpdate;

    window.start();
}