#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

WNDCLASSA window_class;
HWND window;
HDC win_dc;
BITMAPINFO info;
RECT win_rect;
RAWINPUT raw_inputs;
HRAWINPUT raw_input_handle;
RAWINPUTDEVICE raw_input_device;
UINT raw_input_size;
PUINT raw_input_size_ptr = (PUINT)(&raw_input_size);
UINT raw_input_header_size = sizeof(RAWINPUTHEADER);

u64 Win32_ticksPerSecond;
LARGE_INTEGER performance_counter;

void Win32_setWindowTitle(char* str) { SetWindowTextA(window, str); }
void Win32_setCursorVisibility(bool on) { ShowCursor(on); }
void Win32_setWindowCapture(bool on) { if (on) SetCapture(window); else ReleaseCapture(); }
u64 Win32_getTicks() {
    QueryPerformanceCounter(&performance_counter);
    return (u64)performance_counter.QuadPart;
}
void* Win32_getMemory(u64 size) {
    return VirtualAlloc((LPVOID)MEMORY_BASE, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

inline UINT getRawInput(LPVOID data) {
    return GetRawInputData(raw_input_handle, RID_INPUT, data, raw_input_size_ptr, raw_input_header_size);
}
inline bool hasRawInput() {
    return getRawInput(0) == 0 && raw_input_size != 0;
}
inline bool hasRawMouseInput(LPARAM lParam) {
    raw_input_handle = (HRAWINPUT)(lParam);
    return (
        hasRawInput() &&
        getRawInput((LPVOID)&raw_inputs) == raw_input_size &&
        raw_inputs.header.dwType == RIM_TYPEMOUSE
    );
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            app->is_running = false;
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            GetClientRect(window, &win_rect);

            info.bmiHeader.biWidth = win_rect.right - win_rect.left;
            info.bmiHeader.biHeight = win_rect.top - win_rect.bottom;

            _windowResize((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);

            break;

        case WM_PAINT:
            SetDIBitsToDevice(win_dc,
                              0, 0, app->window_content.dimensions.width, app->window_content.dimensions.height,
                              0, 0, 0, app->window_content.dimensions.height,
                              (u32*)app->window_content.pixels, &info, DIB_RGB_COLORS);

            ValidateRgn(window, null);
            break;

        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            _keyChanged((u32)wParam, true);
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:
            _keyChanged((u32)wParam, false);
            break;

        case WM_MBUTTONUP:
            _mouseButtonUp(  &app->controls.mouse.middle_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;

        case WM_MBUTTONDOWN:
            _mouseButtonDown(&app->controls.mouse.middle_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;

        case WM_LBUTTONDOWN: _mouseButtonDown(&app->controls.mouse.left_button,  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_LBUTTONUP  : _mouseButtonUp(  &app->controls.mouse.left_button,  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_RBUTTONDOWN: _mouseButtonDown(&app->controls.mouse.right_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_RBUTTONUP:   _mouseButtonUp(  &app->controls.mouse.right_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;

        case WM_LBUTTONDBLCLK:
            app->controls.mouse.double_clicked = true;
            break;

        case WM_MOUSEWHEEL:
            _mouseWheelScrolled((f32)(GET_WHEEL_DELTA_WPARAM(wParam)) / (f32)(WHEEL_DELTA));
            break;

        case WM_MOUSEMOVE:
            _mouseMovementSet(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            _mousePositionSet(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;

        case WM_INPUT:
            if ((hasRawMouseInput(lParam)) && (
                raw_inputs.data.mouse.lLastX != 0 ||
                raw_inputs.data.mouse.lLastY != 0))
                _mouseRawMovementSet(
                        raw_inputs.data.mouse.lLastX,
                        raw_inputs.data.mouse.lLastY
                );

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {

    void* app_memory = GlobalAlloc(GPTR, sizeof(App));
    if (!app_memory)
        return -1;

    app = (App*)app_memory;

    void* window_content_memory = GlobalAlloc(GPTR, RENDER_SIZE);
    if (!window_content_memory)
        return -1;

    LARGE_INTEGER performance_frequency;
    QueryPerformanceFrequency(&performance_frequency);
    Win32_ticksPerSecond = (u64)performance_frequency.QuadPart;

    app->controls.key_map.space = VK_SPACE;
    app->controls.key_map.shift = VK_SHIFT;
    app->controls.key_map.ctrl  = VK_CONTROL;
    app->controls.key_map.alt   = VK_MENU;
    app->controls.key_map.tab   = VK_TAB;

    app->platform.ticks_per_second    = Win32_ticksPerSecond;
    app->platform.getTicks            = Win32_getTicks;
    app->platform.getMemory           = Win32_getMemory;
    app->platform.setWindowTitle      = Win32_setWindowTitle;
    app->platform.setWindowCapture    = Win32_setWindowCapture;
    app->platform.setCursorVisibility = Win32_setCursorVisibility;

    Defaults defaults;
    _initApp(&defaults, window_content_memory);

    info.bmiHeader.biSize        = sizeof(info.bmiHeader);
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biBitCount    = 32;
    info.bmiHeader.biPlanes      = 1;

    window_class.lpszClassName  = "RnDer";
    window_class.hInstance      = hInstance;
    window_class.lpfnWndProc    = WndProc;
    window_class.style          = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
    window_class.hCursor        = LoadCursorA(null, IDC_ARROW);

    if (!RegisterClassA(&window_class)) return -1;

    win_rect.top = 0;
    win_rect.left = 0;
    win_rect.right  = defaults.width;
    win_rect.bottom = defaults.height;
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    window = CreateWindowA(
            window_class.lpszClassName,
            defaults.title,
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,
            CW_USEDEFAULT,
            win_rect.right - win_rect.left,
            win_rect.bottom - win_rect.top,

            null,
            null,
            hInstance,
            null
    );
    if (!window)
        return -1;

    raw_input_device.usUsagePage = 0x01;
    raw_input_device.usUsage = 0x02;
    if (!RegisterRawInputDevices(&raw_input_device, 1, sizeof(raw_input_device)))
        return -1;

    win_dc = GetDC(window);

    SetICMMode(win_dc, ICM_OFF);



    ShowWindow(window, nCmdShow);

    MSG message;
    while (app->is_running) {
        while (PeekMessageA(&message, null, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        _windowRedraw();
        InvalidateRgn(window, null, false);
    }

    return 0;// (int)message.wParam;
}