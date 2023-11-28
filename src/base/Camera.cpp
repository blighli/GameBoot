//
// Created by bligh on 2023/11/28.
//

#include "Camera.h"
#include <glm/ext.hpp>

Camera::Camera() {
    fovy = 45.0f;
    aspect = 3.0f/4.0f;
    zNear = 1.0f;
    zFar = 10.0f;
    eye = glm::vec3(0.0f, 0.0f, 3.0f);
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

}

glm::mat4 Camera::mat4() {
    glm::mat4 Proj = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
    glm::mat4 View = glm::lookAt(eye, center, up);
    return Proj * View;
}

void Camera::perspective(float fovy, float aspect, float zNear, float zFar) {
    this->fovy = fovy;
    this->aspect = aspect;
    this->zNear = zNear;
    this->zFar = zFar;
}

void Camera::setPosition(const glm::vec3& eye) {
    this->eye = eye;
}

glm::vec3& Camera::getPosition() {
    return eye;
}

void Camera::orbit(float longitude, float latitude) {
    glm::mat4 matLongitude = glm::rotate(glm::mat4 (1.0f), glm::radians(longitude), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 matLatitude = glm::rotate(glm::mat4 (1.0f), glm::radians(latitude), glm::vec3(1.0f, 0.0f, 0.0f));
    eye = glm::vec3( matLatitude * matLongitude * glm::vec4(eye, 1.0f));
}

void Camera::setAspect(float aspect) {
   this->aspect = aspect;
}
