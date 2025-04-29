#pragma once

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <unordered_set>

using namespace std;

class Camera
{
public:
    glm::vec3 position = { 0.0f, 0.0f, 3.0f };
    float yaw = -90.0f; // Horizontal rotation
    float pitch = 0.0f; // Vertical rotation
    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    bool firstMouse = true;
    float lastX = 400.0f; // Initial window center
    float lastY = 300.0f;

    glm::mat4 getViewMatrix() const {
        glm::vec3 front = calculateFrontVector();
        glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);  // Up vector (world space, fixed Y-axis)

        return glm::lookAt(position, position + front, up);
    }

    void processKeyboardInput(unordered_set<int>& keys, float deltaTime) {
        if (keys.find(GLFW_KEY_W) != keys.end()) {
            position += movementSpeed * deltaTime * calculateFrontVector();
        }
        if (keys.find(GLFW_KEY_A) != keys.end()) {
            position -= movementSpeed * deltaTime * calculateRightVector();
        }
        if (keys.find(GLFW_KEY_S) != keys.end()) {
            position -= movementSpeed * deltaTime * calculateFrontVector();
        }
        if (keys.find(GLFW_KEY_D) != keys.end()) {
            position += movementSpeed * deltaTime * calculateRightVector();
        }

    }

    void processMouseMovement(float xpos, float ypos) {

        // Only perform the calculation for mouse movement after the first input
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        // Calculate offsets for mouse movement
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        // Apply sensitivity to the offsets
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        // Update yaw and pitch
        yaw += xoffset;
        pitch += yoffset;

        // Constrain pitch to avoid the camera flipping upside down
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

private:
    glm::vec3 calculateFrontVector() const {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        return glm::normalize(front);
    }

    glm::vec3 calculateRightVector() const {
        glm::vec3 front = calculateFrontVector();
        glm::vec3 up(0.0f, 0.0f, 1.0f);
        return glm::normalize(glm::cross(front, up));
    }
};

