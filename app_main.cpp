#include "App.h"

int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 600, 600, "OpenGL Demo"); //create new app with height and width of 600px


    app->run();
}
