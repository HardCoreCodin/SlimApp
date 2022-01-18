#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef NDEBUG
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <new.h>

void DisplayError(LPTSTR lpszFunction) {
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    unsigned int last_error = GetLastError();

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            null, last_error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf, 0, null);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

    if (FAILED( StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                                TEXT("%s failed with error code %d as follows:\n%s"), lpszFunction, last_error, lpMsgBuf)))
        printf("FATAL ERROR: Unable to output error code.\n");

    _tprintf(TEXT((LPTSTR)"ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
#endif

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

LARGE_INTEGER performance_counter;

void os::setWindowTitle(char* str) {
    SetWindowTextA(window, str);
}

void os::setCursorVisibility(bool on) {
    ShowCursor(on);
}

void os::setWindowCapture(bool on) {
    if (on) SetCapture(window);
    else ReleaseCapture();
}

u64 os::getTicks() {
    QueryPerformanceCounter(&performance_counter);
    return (u64)performance_counter.QuadPart;
}

void* os::getMemory(u64 size) {
    return VirtualAlloc((LPVOID)MEMORY_BASE, (SIZE_T)size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

void os::closeFile(void *handle) {
    CloseHandle(handle);
}

void* os::openFileForReading(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_READ,          // open for reading
                               FILE_SHARE_READ,       // share for reading
                               null,                  // default security
                               OPEN_EXISTING,         // existing file only
                               FILE_ATTRIBUTE_NORMAL, // normal file
                               null);                 // no attr. template
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), path);
        return null;
    }
#endif
    return handle;
}

void* os::openFileForWriting(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_WRITE,          // open for writing
                               0,                      // do not share
                               null,                   // default security
                               OPEN_ALWAYS,            // create new or open existing
                               FILE_ATTRIBUTE_NORMAL,  // normal file
                               null);
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for write.\n"), path);
        return null;
    }
#endif
    return handle;
}

bool os::readFromFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_read = 0;
    BOOL result = ReadFile(handle, out, size, &bytes_read, null);
#ifndef NDEBUG
    if (result == FALSE) {
        DisplayError(TEXT((LPTSTR)"ReadFile"));
        printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", (unsigned int)GetLastError());
        CloseHandle(handle);
    }
#endif
    return result != FALSE;
}

bool os::writeToFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_written = 0;
    BOOL result = WriteFile(handle, out, size, &bytes_written, null);
#ifndef NDEBUG
    if (result == FALSE) {
        DisplayError(TEXT((LPTSTR)"WriteFile"));
        printf("Terminal failure: Unable to write from file.\n GetLastError=%08x\n", (unsigned int)GetLastError());
        CloseHandle(handle);
    }
#endif
    return result != FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    MouseButton *mouse_button;
    IsPressed *is_pressed = &app->controls.is_pressed;
    bool pressed = message == WM_SYSKEYDOWN || message == WM_KEYDOWN;
    u8 key = (u8)wParam;
    i32 x, y;
    f32 scroll_amount;

    switch (message) {
        case WM_DESTROY:
            app->is_running = false;
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            GetClientRect(window, &win_rect);

            info.bmiHeader.biWidth = win_rect.right - win_rect.left;
            info.bmiHeader.biHeight = win_rect.top - win_rect.bottom;
            app->window_content.dimensions.update((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            app->OnWindowResize((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            app->OnWindowRedraw();

            break;

        case WM_PAINT:
            SetDIBitsToDevice(win_dc,
                              0, 0, app->window_content.dimensions.width, app->window_content.dimensions.height,
                              0, 0, 0, app->window_content.dimensions.height,
                              (u32*)app->window_content.pixels, &info, DIB_RGB_COLORS);

            ValidateRgn(window, null);
            break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
            switch (key) {
                case VK_CONTROL: is_pressed->ctrl  = pressed; break;
                case VK_MENU   : is_pressed->alt   = pressed; break;
                case VK_SHIFT  : is_pressed->shift = pressed; break;
                case VK_SPACE  : is_pressed->space = pressed; break;
                case VK_TAB    : is_pressed->tab   = pressed; break;
                default: break;
            }
            app->OnKeyChanged(key, pressed);

            break;

        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_LBUTTONDBLCLK:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);

            switch (message) {
                case WM_MBUTTONUP:
                case WM_MBUTTONDOWN:
                case WM_MBUTTONDBLCLK: mouse_button = &app->controls.mouse.middle_button; break;
                case WM_RBUTTONUP:
                case WM_RBUTTONDOWN:
                case WM_RBUTTONDBLCLK: mouse_button = &app->controls.mouse.right_button; break;
                default: mouse_button = &app->controls.mouse.left_button;
            }

            switch (message) {
                case WM_MBUTTONDBLCLK:
                case WM_RBUTTONDBLCLK:
                case WM_LBUTTONDBLCLK: mouse_button->doubleClick(x, y); app->controls.mouse.double_clicked = true; app->OnMouseButtonDoubleClicked(mouse_button); break;
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                case WM_LBUTTONUP:     mouse_button->up(x, y);   app->OnMouseButtonUp(mouse_button); break;
                default:               mouse_button->down(x, y); app->OnMouseButtonDown(mouse_button); break;
            }

            break;

        case WM_MOUSEWHEEL:
            scroll_amount = (f32)(GET_WHEEL_DELTA_WPARAM(wParam)) / (f32)(WHEEL_DELTA);
            app->controls.mouse.scroll(scroll_amount); app->OnMouseWheelScrolled(scroll_amount);
            break;

        case WM_MOUSEMOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            app->controls.mouse.move(x, y);        app->OnMouseMovementSet(x, y);
            app->controls.mouse.setPosition(x, y); app->OnMousePositionSet(x, y);
            break;

        case WM_INPUT:
            if ((hasRawMouseInput(lParam)) && (
                    raw_inputs.data.mouse.lLastX != 0 ||
                    raw_inputs.data.mouse.lLastY != 0)) {
                x = raw_inputs.data.mouse.lLastX;
                y = raw_inputs.data.mouse.lLastY;
                app->controls.mouse.moveRaw(x, y); app->OnMouseRawMovementSet(x, y);
            }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
    void* window_content_memory = GlobalAlloc(GPTR, RENDER_SIZE);
    if (!window_content_memory)
        return -1;

    LARGE_INTEGER performance_frequency;
    QueryPerformanceFrequency(&performance_frequency);
    os::ticks_per_second = (u64)performance_frequency.QuadPart;

    app = createApp();
    app->window_content.pixels = (Pixel*)window_content_memory;
    app->controls.key_map.ctrl = VK_CONTROL;
    app->controls.key_map.alt = VK_MENU;
    app->controls.key_map.shift = VK_SHIFT;
    app->controls.key_map.space = VK_SPACE;
    app->controls.key_map.tab = VK_TAB;
    if (!app->OnReady()) return -1;

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
    win_rect.right  = app->window_width;
    win_rect.bottom = app->window_height;
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    window = CreateWindowA(
            window_class.lpszClassName,
            app->window_title,
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
        app->OnWindowRedraw();
        InvalidateRgn(window, null, false);
    }

    return 0;
}