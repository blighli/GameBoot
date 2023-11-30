
#include "MyGameApp.h"

#include <assimp/scene.h>
#include <assimp/cimport.h>

int main() {
    const aiScene* sc = aiImportFile("../media/object/man_head.obj", 0);
    MyGameApp app(800, 600, "Game Boot", false);
    app.loadShaders();
    app.loadGeometry();
    app.runLoop();
    return 0;
}

