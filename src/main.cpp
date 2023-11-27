
#include "MyGameApp.h"

int main() {
    MyGameApp app(false, 800, 600, "Game Boot");
    app.loadShaders();
    app.loadModels();
    app.runLoop();
    return 0;
}

