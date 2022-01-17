#pragma once

#include "./core/base.h"
#include "./core/time.h"
#include "./core/pixels.h"
#include "./core/memory.h"
#include "./core/controls.h"

struct Defaults {
    char* title = (char*)"";
    u16 width = 480,
        height = 360;
    u64 additional_memory_size = 0;
};

struct AppCallbacks {
    void (*windowRedraw)() = nullptr;
    void (*windowResize)(u16 width, u16 height) = nullptr;
    void (*keyChanged)(  u8 key, bool pressed) = nullptr;
    void (*mouseButtonUp)(  MouseButton *mouse_button) = nullptr;
    void (*mouseButtonDown)(MouseButton *mouse_button) = nullptr;
    void (*mouseButtonDoubleClicked)(MouseButton *mouse_button) = nullptr;
    void (*mouseWheelScrolled)(f32 amount) = nullptr;
    void (*mousePositionSet)(i32 x, i32 y) = nullptr;
    void (*mouseMovementSet)(i32 x, i32 y) = nullptr;
    void (*mouseRawMovementSet)(i32 x, i32 y) = nullptr;
};

struct App {
    Controls controls;
    PixelGrid window_content;
    Time time;
    AppCallbacks on;

    bool is_running = true;
    void *user_data = nullptr;

//    App() = delete;
    App(const KeyMap key_map, Pixel* pixels, Defaults *defaults) : controls(key_map), window_content(pixels) {
        init(defaults);
    }
    void init(Defaults *defaults);

    bool initMemory(u64 size) {
        if (memory.address) return false;

        void* memory_address = os::getMemory(size);
        if (!memory_address) {
            is_running = false;
            return false;
        }

        memory.init((u8*)memory_address, size);
        return true;
    }

    void* allocateMemory(u64 size) {
        void *new_memory = memory.allocate(size);
        if (new_memory) return new_memory;

        is_running = false;
        return null;
    }

private:
    Memory memory;
};

App *app;

#include "./platforms/win32.h"