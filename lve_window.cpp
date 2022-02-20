#include "lve_window.hpp"
#include <iostream>
#include <stdexcept>

namespace lve {
    LveWindow::LveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
        initWindow();
    }

    LveWindow::~LveWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void LveWindow::initWindow() {
        glfwInit();

        // tell glfw to not use openGL
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // tell glfwWindow to not resize window
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::cout << extensionCount << " extensions supported. \n";
    }

    void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface.");
        }
    }
}