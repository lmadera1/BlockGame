#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "BlockGame.h"


int main() {
    BlockGame app;

    try {
        app.run();
    }
    catch (const exception& e) {
        cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}