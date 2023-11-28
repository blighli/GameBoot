//
// Created by bligh on 2023/11/28.
//

#ifndef GAMEBOOT_CAMERA_H
#define GAMEBOOT_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    void perspective(float fovy, float aspect, float zNear, float zFar);
    void setPosition(const glm::vec3& eye);
    glm::vec3& getPosition();

    void orbit(float longitude, float latitude);
    glm::mat4 mat4();
private:
    float fovy, aspect, zNear, zFar;
    glm::vec3 eye, center, up;
};


#endif //GAMEBOOT_CAMERA_H
