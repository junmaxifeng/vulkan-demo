////
//// Created by john on 2021/11/16.
////
//
#include <iostream>
#include <stdexcept>
#include "VulkanFrame.h"

const std::vector<const char *> validationLayers = {
//        "VK_LAYER_LUNARG_standard_validation"
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void VulkanFrame::setWindowSize(const uint &width, const uint &height) {
    mWindowSetting.mWidth = width;
    mWindowSetting.mHeight = height;
}

void VulkanFrame::setWindowTitle(const std::string &title) {
    mWindowSetting.mTitle = title;
}

void VulkanFrame::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void VulkanFrame::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mWindow = glfwCreateWindow(mWindowSetting.mWidth, mWindowSetting.mHeight, mWindowSetting.mTitle.c_str(), nullptr,
                               nullptr);
}

void VulkanFrame::initVulkan() {
    createInstance();
}

void VulkanFrame::mainLoop() {
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
    }
}

void VulkanFrame::cleanup() {
    vkDestroyInstance(mInstance, nullptr);
    glfwDestroyWindow(mWindow);
}

bool VulkanFrame::checkValidationLayerSupport() {
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName: validationLayers) {
        bool layerFound = false;

        for (const auto &layerProperties: availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}

void VulkanFrame::createInstance() {
    /**
     * Ch 01
     */
    /*  填写应用程序信息，这些信息的填写不是必须的，但填写的信息可能会作为驱动程序的优化依据，让驱动程序进行一些特殊的优化。
     *  比如，应用程序使用了某个引擎，驱动程序对这个引擎有一些特殊处理，这时就可能有很大的优化提升
     */
    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Hello Triangle";
    applicationInfo.pEngineName = "No Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;
    /*  Vulkan的很多结构体需要我们显式地在sType成员变量中指定结构体的类型。
     *  此外，许多Vulkan的结构体还有一个pNext成员变量，用来指向未来可能扩展的参数信息，现在，我们并没有使用它，将其设置为nullptr
     */
    applicationInfo.pNext = nullptr;

    /*  Vulkan倾向于通过结构体传递信息，我们需要填写一个或多个结构体来提供足够的信息创建Vulkan实例。
     *  下面的这个结构体类型是必须的，它告诉Vulkan的驱动程序需要使用的全局扩展和校验层(instance中的设置是作用全局的)。
     *  全局是指这里的设置对于整个应用程序都有效，而不仅仅对一个设备有效，在之后的章节，我们会对此有更加清晰得认识。
     */
    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    /* Vulkan与平台无关，所以需要一个和窗口系统交互的扩展。GLFW库包含了一个可以返回当前平台窗口系统交互扩展的函数，我们可以直接使用它
     */
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);//该函数返回的是字符串数组，函数返回后count中保存字符串的个数
    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
    if (!enableValidationLayers || !checkValidationLayerSupport()) {
        instanceCreateInfo.enabledLayerCount = 0;//全局校验层(暂不开启)
    }else{
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    }

    uint32_t extensionCount = 0;
    //该函数第一次调用时，pProperties传null，函数返回时会在count中填入支持的扩展数量
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);//初始化长度为count的extension数组
    //该函数第二次调用时，已知了count，此时pProperties传入刚初始化的count长度的数组即可
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    /**
     * 创建instance
     * 创建Vulkan对象的函数参数的一般形式就是：
     * 一个包含了创建信息的结构体指针
     * 一个自定义的分配器回调函数，在本教程，我们没有使用自定义的分配器，总是将它设置为nullptr
     * 一个指向新对象句柄存储位置的指针
     */
    if (vkCreateInstance(&instanceCreateInfo, nullptr, &mInstance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

}