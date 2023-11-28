
#include "MyGameApp.h"

int main() {
    MyGameApp app(800, 600, "Game Boot", false);
    app.loadShaders();
    app.loadGeometry();
    app.runLoop();
    return 0;
}

