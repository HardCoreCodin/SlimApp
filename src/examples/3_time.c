#include "../app.h"
// Or using the single-header file:
// #include "../SlimApp.h"

void timer() {
    // App already has a few timers:
    // Use the update timer to track the time difference since the last time this function was called (delta_time):
    startFrameTimer(&app->time.timers.update);

    // Accumulate time deltas:
    static float accumulated_time = 0;
    accumulated_time += app->time.timers.update.delta_time;

    // Store a number as a string:
    static NumberStringBuffer number;
    int seconds = (int)accumulated_time;
    printNumberIntoString(seconds, &number);

    app->platform.setWindowTitle(number.string);

    endFrameTimer(&app->time.timers.update);
}

void initApp(Defaults *defaults) {
    // Tell the app what to do whenever it needs to redraw the window:
    app->on.windowRedraw = timer;
}
