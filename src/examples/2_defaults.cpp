#include "../SlimApp.h"

SlimApp* createApp() {
    // Some initial defaults can be overridden before the window is displayed:
    auto my_app = new SlimApp();
    my_app->window_title  = (char*)"My Title";
    my_app->window_width  = 300;
    my_app->window_height = 60;
    return my_app;
}