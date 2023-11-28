//
// Created by bligh on 2023/11/27.
//

#ifndef GAMEBOOT_GAMEAPP_H
#define GAMEBOOT_GAMEAPP_H

struct GLFWwindow;
class ShaderProgram;

class GameApp {
public:
    GameApp(bool fullScreen, int width, int height, const char* title);

    void loadModels() const;

    void runLoop();
    GLFWwindow *getWindow() const;

    virtual ~GameApp();

    //载入Shader代码
    virtual void loadShaders();
    //绘制场景
    virtual void drawScene();
    //处理交互事件
    virtual void onSize(int width, int height);
    virtual void onKey(int key, int action);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseButton(int button, int action);

protected:
    GLFWwindow* mWindow;
    ShaderProgram* mShaderProgram;

private:
    void bindEvents() const;
};


#endif //GAMEBOOT_GAMEAPP_H
