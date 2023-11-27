//
// Created by bligh on 2023/11/27.
//

#include "MyGameApp.h"
#include <iostream>
#include "glad/gl.h"
#include "glfw/glfw3.h"

void MyGameApp::drawScene() {
    //Render Here
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGameApp::onSize(int width, int height) {
    GameApp::onSize(width, height);
}

void MyGameApp::onKey(int key, int action) {
    GameApp::onKey(key, action);
}

void MyGameApp::onMouseMove(int x, int y) {

}

void MyGameApp::onMouseButton(int button, int action) {

}