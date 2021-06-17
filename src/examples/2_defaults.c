#include "../app.h"

void initApp(Defaults *defaults) {
    // Some initial defaults can be overridden before the window is displayed:
    defaults->title  = "My Title";
    defaults->width  = 800;
    defaults->height = 600;
}
