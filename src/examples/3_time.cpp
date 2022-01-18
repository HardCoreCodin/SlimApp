#include "../SlimApp.h"

// To provide custom behaviour, create a sub-struct of SlimApp and override methods:
struct TimerApp : public SlimApp {
    bool OnReady() override {
        // Defaults can also be overridden here
        window_title = (char*)"0";
        return true;
    }

    void OnWindowRedraw() override {
        // Track the time difference since last time this was called:
        time.timers.update.startFrame();
        static f32 before = 0;
        f32 now = before + time.timers.update.delta_time;

        if ((u32)now > (u32)before) { // If on a seconds border:
            // Update the window title with the current time:
            static NumberString number;
            number = (i32)now;
            os::setWindowTitle(number.string.char_ptr);
        }
        before = now;
        time.timers.update.endFrame();
    }
};

// Return an instance of your sub-struct:
SlimApp* createApp() { return new TimerApp(); }