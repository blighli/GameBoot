#include <iostream>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "base/GameApp.h"
#include "MyGameApp.h"




void setup() {

}

int main() {

    MyGameApp app(false, 800, 600, "Game Boot");
    app.loadShaders();
    app.loadModels();
    setup();
    app.runLoop();
    return 0;
}

