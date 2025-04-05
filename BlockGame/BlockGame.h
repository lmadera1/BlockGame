#pragma once
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>

using namespace std;

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class BlockGame {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    //Class Structs
    struct QueueFamilyIndices {
        optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };

private:
    //Class Members
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;


    //Functions
    void initVulkan() {
        createInstance();
        pickPhysicalDevice();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void createInstance();

    bool checkValidationLayerSupport();

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        return indices.isComplete();
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);


};

