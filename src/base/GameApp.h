//
// Created by bligh on 2023/11/27.
//

#ifndef GAMEBOOT_GAMEAPP_H
#define GAMEBOOT_GAMEAPP_H

struct GLFWwindow;
class ShaderProgram;
class Geometry;
class Camera;

class GameApp {
public:
    GameApp(int width, int height, const char *title,bool fullScreen);
    void runLoop();
    void setTimer(double interval);
    GLFWwindow *getWindow() const;
    virtual ~GameApp();
    //载入Shader代码
    virtual void loadShaders();
    //载入几何模型
    virtual void loadGeometry() const;
    //绘制场景
    virtual void drawScene();
    //处理交互事件
    virtual void onSize(int width, int height);
    virtual void onKey(int key, int action);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseButton(int button, int action);
    virtual void onTimer();
protected:
    GLFWwindow* mWindow;
    ShaderProgram* mShaderProgram;
    Geometry* mGeometry;
    Camera* mCamera;
    double mTimerInterval;
private:
    static void initContext() ;
    void createWindow(int width, int height, const char *title,bool fullScreen);
    void bindEvents() const;
};


#endif //GAMEBOOT_GAMEAPP_H
