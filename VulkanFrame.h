////
//// Created by john on 2021/11/16.
////
//
#ifndef VKDEMO_VULKANFRAME_H
#define VKDEMO_VULKANFRAME_H
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>
#include <algorithm>
#include <map>
struct WindowSetting{
    WindowSetting(){};
    virtual ~WindowSetting(){};
    uint mHeight;
    uint mWidth;
    std::string mTitle;
};

class VulkanFrame {
public:
    void run();

public:
    void setWindowSize(const uint &width,const uint &height);
    void setWindowTitle(const std::string &title);
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

private:
    bool checkValidationLayerSupport();
    void createInstance();
private:
    VkInstance mInstance;
    GLFWwindow *mWindow;
    WindowSetting mWindowSetting;
};

#endif //VKDEMO_VulkanFrame_H
