//
// Created by bligh on 2023/11/27.
//

#ifndef GAMEBOOT_MYGAMEAPP_H
#define GAMEBOOT_MYGAMEAPP_H

#include "base/GameApp.h"

class MyGameApp : public GameApp {

public:
    using GameApp::GameApp;

    void loadGeometry() const override;
    void loadShaders() override;
    void drawScene() override;
    void onSize(int width, int height) override;
    void onKey(int key, int action) override;
    void onMouseMove(int x, int y) override;
    void onMouseButton(int button, int action) override;
    void onTimer() override;
};


#endif //GAMEBOOT_MYGAMEAPP_H
