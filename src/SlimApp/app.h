#pragma once

#include "./core/base.h"
#include "./core/time.h"
#include "./core/pixels.h"
#include "./core/memory.h"
#include "./core/controls.h"

struct SlimApp {
    Controls controls;
    PixelGrid window_content;
    Time time;

    bool is_running = true;
    void *user_data = nullptr;
    char* window_title = (char*)"";
    u16 window_width = 480,
            window_height = 360;
    u64 additional_memory_size = 0;

    virtual bool OnReady() { return true; }
    virtual void OnWindowRedraw() {};
    virtual void OnWindowResize(u16 width, u16 height) {};
    virtual void OnKeyChanged(  u8 key, bool pressed) {};
    virtual void OnMouseButtonUp(  MouseButton *mouse_button) {};
    virtual void OnMouseButtonDown(MouseButton *mouse_button) {};
    virtual void OnMouseButtonDoubleClicked(MouseButton *mouse_button) {};
    virtual void OnMouseWheelScrolled(f32 amount) {};
    virtual void OnMousePositionSet(i32 x, i32 y) {};
    virtual void OnMouseMovementSet(i32 x, i32 y) {};
    virtual void OnMouseRawMovementSet(i32 x, i32 y) {};

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

SlimApp* createApp();
SlimApp *app;

#include "./platforms/win32.h"