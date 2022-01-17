#include "../SlimApp.h"

void timer() {
    // Track the time difference since last time this was called:
    Timer &timer = app->time.timers.update;
    timer.startFrame();
    static f32 before = 0;
    f32 now = before + timer.delta_time;

    if ((u32)now > (u32)before) { // If on a seconds border:
        // Update the window title with the current time:
        static NumberString number;
        number = (i32)now;
        os::setWindowTitle(number.string.char_ptr);
    }
    before = now;
    timer.endFrame();
}

void App::init(Defaults *defaults) {
    on.windowRedraw = timer;
    defaults->title = (char*)"0";
}

