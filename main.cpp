#include "VulkanFrame.h"

int main() {
    VulkanFrame app;
    app.setWindowSize(800,600);
    app.setWindowTitle("vulkan");

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
