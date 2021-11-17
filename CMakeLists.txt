cmake_minimum_required(VERSION 3.19)
project(vkDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(vkDemo main.cpp VulkanFrame.cpp VulkanFrame.h)

include_directories("/Volumes/T7/Library/glm")
include_directories("/Volumes/T7/GLFW/glfw-3.3.5/glfw-3.3.5.bin.MACOS/include")
target_link_libraries(vkDemo "/Volumes/T7/GLFW/glfw-3.3.5/glfw-3.3.5.bin.MACOS/lib-arm64/libglfw.3.dylib")

find_package(Vulkan)
if (Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries(vkDemo ${Vulkan_LIBRARIES})
endif (Vulkan_FOUND)