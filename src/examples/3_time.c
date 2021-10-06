#include "../SlimApp/app.h"
// Or using the single-header file:
//#include "../SlimApp.h"

void timer() {
    // Track the time difference since last time this was called:
    startFrameTimer(&app->time.timers.update);
    static f32 before = 0;
    f32 now = before + app->time.timers.update.delta_time;

    if ((u32)now > (u32)before) { // If on a seconds border:
        // Update the window title with the current time:
        static NumberString number;
        printNumberIntoString((int)now, &number);
        app->platform.setWindowTitle(number.string.char_ptr);
    }
    before = now;
    endFrameTimer(&app->time.timers.update);
}
void initApp(Defaults *defaults) {
    // 'app' is a global pointer to the application instance.
    // It is the only global variable in this library.
    app->on.windowRedraw = timer;
    defaults->title = (char*)"0";
}

