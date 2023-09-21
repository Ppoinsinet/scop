#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 150

#define VERTEX_SHADER_FILEPATH "./vertex.shader"
#define FRAGMENT_SHADER_FILEPATH "./fragment.shader"

void onError(std::string str) {
    std::cerr << str << "\n";
    exit(1);
}

void onUpdate(Window<int> *win, int *data) {
    static int len = 0;
    (void)win;
    (void)data;

    std::cout << "onUpdate : " << *data << "\n";
    
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

    Window<int> window;

    int success;
    char logs[512];

    try
    {
        Shader vertex(VERTEX_SHADER, VERTEX_SHADER_FILEPATH);
        std::cout << "coucou\n";
        Shader fragment(FRAGMENT_SHADER, FRAGMENT_SHADER_FILEPATH);

        int programId = glCreateProgram();
        glAttachShader(programId, vertex.getId());
        glAttachShader(programId, fragment.getId());
        glLinkProgram(programId);

        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programId, sizeof(logs), NULL, logs);
            throw logs;
        }
        window.data = &programId;
        std::cout << "Set data = " << programId << "\n";
        
        window.create();
        window.updateFunction = onUpdate;

        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}