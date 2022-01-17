#include "../SlimApp.h"

void App::init(Defaults *defaults) {
    // Some initial defaults can be overridden 
    // before the window is displayed:
    defaults->title  = (char*)"My Title";
    defaults->width  = 300;
    defaults->height = 60;
}