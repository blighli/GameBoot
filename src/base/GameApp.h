//
// Created by bligh on 2023/11/27.
//

#ifndef GAMEBOOT_GAMEAPP_H
#define GAMEBOOT_GAMEAPP_H

struct GLFWwindow;

class GameApp {
public:
    GameApp(bool fullScreen, int width, int height, const char* title);

    void loadShaders();
    void loadModels();

    void runLoop();
    GLFWwindow *getWindow() const;

    //draw scene
    virtual void drawScene();

    //event process
    virtual void onSize(int width, int height);
    virtual void onKey(int key, int action);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseButton(int button, int action);

    virtual ~GameApp();
protected:
    GLFWwindow* mWindow;
    int mShaderProgram;
};


#endif //GAMEBOOT_GAMEAPP_H
