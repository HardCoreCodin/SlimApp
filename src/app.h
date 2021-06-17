#pragma once

#include "./base.h"
#include "./time.h"
#include "./pixels.h"
#include "./memory.h"
#include "./controls.h"

typedef struct AppCallbacks {
    void (*windowRedraw)();
    void (*windowResize)(u16 width, u16 height);
    void (*keyChanged)(  u8 key, bool pressed);
    void (*mouseButtonUp)(  MouseButton *mouse_button);
    void (*mouseButtonDown)(MouseButton *mouse_button);
    void (*mouseWheelScrolled)(f32 amount);
    void (*mousePositionSet)(i32 x, i32 y);
    void (*mouseMovementSet)(i32 x, i32 y);
    void (*mouseRawMovementSet)(i32 x, i32 y);
} AppCallbacks;

typedef struct Platform {
    CallbackWithCharPtr setWindowTitle;
    CallbackWithBool    setWindowCapture;
    CallbackWithBool    setCursorVisibility;
    CallbackWithInt getMemory;
    GetTicks getTicks;
    u64 ticks_per_second;
} Platform;

typedef struct Defaults {
    char* title;
    u16 width, height;
} Defaults;

typedef struct App {
    Platform platform;
    Controls controls;
    PixelGrid window_content;
    AppCallbacks on;
    Time time;
    bool is_running;
    void *user_data;

    ArenaAllocator arena_allocator;
    bool (*initMemory)(u64 size);
    void* (*allocateMemory)(u64 size);
} App;

App *app;

void initApp(Defaults *defaults);

void _windowRedraw() {
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _windowResize(u16 width, u16 height) {
    updateDimensions(&app->window_content.dimensions, width, height);

    if (app->on.windowResize) app->on.windowResize(width, height);
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _keyChanged(u8 key, bool pressed) {
         if (key == app->controls.key_map.ctrl) app->controls.is_pressed.ctrl  = pressed;
    else if (key == app->controls.key_map.alt) app->controls.is_pressed.alt   = pressed;
    else if (key == app->controls.key_map.shift) app->controls.is_pressed.shift = pressed;
    else if (key == app->controls.key_map.space) app->controls.is_pressed.space = pressed;
    else if (key == app->controls.key_map.tab) app->controls.is_pressed.tab   = pressed;

    if (app->on.keyChanged) app->on.keyChanged(key, pressed);
}

void _mouseButtonDown(MouseButton *mouse_button, i32 x, i32 y) {
    mouse_button->is_pressed = true;
    mouse_button->is_handled = false;

    mouse_button->down_pos.x = x;
    mouse_button->down_pos.y = y;

    if (app->on.mouseButtonDown) app->on.mouseButtonDown(mouse_button);
}

void _mouseButtonUp(MouseButton *mouse_button, i32 x, i32 y) {
    mouse_button->is_pressed = false;
    mouse_button->is_handled = false;

    mouse_button->up_pos.x = x;
    mouse_button->up_pos.y = y;

    if (app->on.mouseButtonUp) app->on.mouseButtonUp(mouse_button);
}

void _mouseWheelScrolled(f32 amount) {
    app->controls.mouse.wheel_scroll_amount += amount * 100;
    app->controls.mouse.wheel_scrolled = true;

    if (app->on.mouseWheelScrolled) app->on.mouseWheelScrolled(amount);
}

void _mousePositionSet(i32 x, i32 y) {
    app->controls.mouse.pos.x = x;
    app->controls.mouse.pos.y = y;

    if (app->on.mousePositionSet) app->on.mousePositionSet(x, y);
}

void _mouseMovementSet(i32 x, i32 y) {
    app->controls.mouse.movement.x = x - app->controls.mouse.pos.x;
    app->controls.mouse.movement.y = y - app->controls.mouse.pos.y;
    app->controls.mouse.moved = true;

    if (app->on.mouseMovementSet) app->on.mouseMovementSet(x, y);
}

void _mouseRawMovementSet(i32 x, i32 y) {
    app->controls.mouse.pos_raw_diff.x += x;
    app->controls.mouse.pos_raw_diff.y += y;
    app->controls.mouse.moved = true;

    if (app->on.mouseRawMovementSet) app->on.mouseRawMovementSet(x, y);
}

bool _initMemory(u64 size) {
    if (app->arena_allocator.address) return false;

    void* memory_address = app->platform.getMemory(size);
    if (!memory_address) {
        app->is_running = false;
        return false;
    }

    initArenaAllocator(&app->arena_allocator, (u8*)memory_address);
    return true;
}

void* _allocateMemory(u64 size) {
    void* memory = allocateMemory(&app->arena_allocator, size);
    if (memory) return memory;

    app->is_running = false;
    return null;
}

void _initApp(Defaults *defaults, void* window_content_memory) {
    defaults->title = "";
    defaults->width = 480;
    defaults->height = 360;

    app->is_running = true;
    app->user_data = null;
    app->arena_allocator.address = null;
    app->initMemory     = _initMemory;
    app->allocateMemory = _allocateMemory;

    app->on.windowRedraw = null;
    app->on.keyChanged = null;
    app->on.mouseButtonUp = null;
    app->on.mouseButtonDown = null;
    app->on.mouseWheelScrolled = null;
    app->on.mousePositionSet = null;
    app->on.mouseMovementSet = null;
    app->on.mouseRawMovementSet = null;

    initTime(&app->time, app->platform.getTicks, app->platform.ticks_per_second);
    initControls(&app->controls);
    initPixelGrid(&app->window_content, (Pixel*)window_content_memory);
    initApp(defaults);
}

#include "./platforms/win32.h"