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
    void setAspect(float aspect);
    void orbit(float xDegree, float yDegree);
    void rotate(float xDegree, float yDegree);
    void move(float forwardBack, float leftRight);
    glm::mat4 mat4();
private:
    float fovy, aspect, zNear, zFar;


private:
    glm::vec3 eye, center, up;
};


#endif //GAMEBOOT_CAMERA_H
