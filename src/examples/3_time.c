#include "../app.h"
// Or using the single-header file:
// #include "../SlimApp.h"

void timer() {
    // Track the time difference since last time this was called:
    startFrameTimer(&app->time.timers.update);
    static float before = 0;
    float now = before + app->time.timers.update.delta_time;
    // If on a seconds border:
    if ((int)now > (int)before) {
        // Update the window title with the current time:
        static NumberStringBuffer number;
        printNumberIntoString((int)now, &number);
        app->platform.setWindowTitle(number.string);
    }
    before = now;
    endFrameTimer(&app->time.timers.update);
}
void initApp(Defaults *defaults) {
    // 'app' is a global pointer to the application instance.
    // It is the only global variable in the app library.
    app->on.windowRedraw = timer;
}

