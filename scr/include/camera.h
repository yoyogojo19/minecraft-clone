#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include "text.h"
#include "shader.h"
#ifndef MYAPP_CAMERA_H
#define MYAPP_CAMERA_H

struct camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float yaw;
    float pitch;
    float FOV;
    float sensitivity;

    camera(glm::vec3 position, float yaw, float pitch, float fov, float sensitivity) : position(position), yaw(yaw), pitch(pitch), FOV(fov), sensitivity(sensitivity) {}

    void update() {
        glm::mat3 rx = glm::mat3(
        1, 0, 0,
        0, cos(pitch), -sin(pitch),
        0, sin(pitch), cos(pitch)
        );
        glm::mat3 ry = glm::mat3(
        cos(yaw), 0 , sin(yaw),
        0, 1, 0,
        -sin(yaw), 0, cos(yaw)
        );
        front = glm::vec3(0.0f, 0.0f, 1.0f) * rx * ry;
        up = glm::vec3(0.0f, 1.0f, 0.0f) * rx * ry;
        right = glm::vec3(1.0f, 0.0f, 0.0f) * rx * ry;
    }
    void print(Shader shaderProgram) {
        renderText("Camera Position: " + glm::to_string(position), 960.0f, 1060.0f, 0.6f, glm::vec3(1.0f), shaderProgram.ID);
        renderText("Camera Front: " + glm::to_string(front), 960.0f, 1045.0f, 0.6f, glm::vec3(1.0f), shaderProgram.ID);
        renderText("Camera Yaw: " + std::to_string(yaw), 960.0f, 1030.0f, 0.6f, glm::vec3(1.0f), shaderProgram.ID);
        renderText("Camera Pitch: " + std::to_string(pitch), 960.0f, 1015.0f, 0.6f, glm::vec3(1.0f), shaderProgram.ID);
    }

    void move(float deltaTime, GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.x += front.x * deltaTime;
            position.z += front.z * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.x -= front.x * deltaTime;
            position.z -= front.z * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position.x += right.x * deltaTime;
            position.z += right.z * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position.x -= right.x * deltaTime;
            position.z -= right.z * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            position += glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            position -= glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime;
        }
    }

    void rotate(GLFWwindow* window, double &lastx, double &lasty) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            yaw -= glm::radians(xpos-lastx) * sensitivity;
            pitch += glm::radians(ypos-lasty) * sensitivity;
        }
        lastx = xpos;
        lasty = ypos;
    }
};

#endif
