#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H
#include "GLFW/glfw3.h"

class ImguiManager {
private:
    static ImguiManager* instance;
public:
    static ImguiManager* getInstance();

    bool* shouldUpdate = new bool(false);
    bool* shouldDraw = new bool(false);

    void init(GLFWwindow *window );
    void render();
    void destroy();
};

#endif //IMGUIMANAGER_H
