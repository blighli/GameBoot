//
// Created by bligh on 2023/11/28.
//

#ifndef GAMEBOOT_CAMERA_H
#define GAMEBOOT_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    glm::mat4 mat4();
private:
    float fovy, aspect, zNear, zFar;
    glm::vec3 eye, center, up;
};


#endif //GAMEBOOT_CAMERA_H
