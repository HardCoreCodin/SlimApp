# SlimApp

A minimalist platform-agnostic app layer for writing graphical applications.<br>
A bare-bone application executable on Windows measures at around 13 KB(!)<br>
Can be complied in either C or C++ (only uses the subset of C that C++ also supports).<br>
Available as either a single header file, or a directory of headers (a "unity build" setup).

Architecture: <br>
-
The platform layer only uses operating-system header(s).<br>
The application layer itself has no dependencies (not even on the platform layer or any standard library).<br>
It is just a library that the platform layer uses (has no knowledge of the platform).<br>

More details on this architecture [here](https://youtu.be/Ev_TeQmus68).

Features:
-
Well documented example applications cover the features:<br>

* Bare-bone application (one-liner): Well-behaved window (can be resized minimized/maximized and closed)<br>
  <p float="left">
    <img src="src/examples/1_app.gif" alt="1_app" height="300">
    <img src="src/examples/1_app_c.png" alt="1_app_code" width="400">
  </p>
* Overridable window defaults: Initial dimensions and title.<br>
  <p float="left">
    <img src="src/examples/2_defaults.gif" alt="2_defaults" height="300">
    <img src="src/examples/2_defaults_c.png" alt="2_defaults_code" width="400">
  </p>
* Timers and window-title control:<br>
  <p float="left">
    <img src="src/examples/3_time.gif" alt="3_time" height="300">
    <img src="src/examples/3_time_c.png" alt="3_time_code" width="400">
  </p>
* Drawable window content: Basic shape drawing (Lines, rectangles, triangles and circles)<br>
  <p float="left">
    <img src="src/examples/4_shapes.gif" alt="4_shapes" height="300">
    <img src="src/examples/4_shapes_c.png" alt="4_shapes_code" width="400">
  </p>
* Text: String and number drawing:<br>
  <p float="left">
    <img src="src/examples/5_text.gif" alt="5_text" height="300">
    <img src="src/examples/5_text_c.png" alt="5_text_code" width="400">
  </p>
* Mouse: Buttons (+wheel), cursor position/movement and 'raw' mouse input (captured outside the window).<br>
  <p float="left">
    <img src="src/examples/6_mouse.gif" alt="6_mouse" height="300">
    <img src="src/examples/6_mouse_c.png" alt="6_mouse_code" width="400">
  </p>
* Keyboard: General key tracking + built-in tracking of control keys status (Ctrl, Alt, Shift, Space)<br>
  <p float="left">
    <img src="src/examples/7_keyboard.gif" alt="7_keyboard" height="300">
    <img src="src/examples/7_keyboard_c.png" alt="7_keyboard_code" width="400">
  </p>
* Memory: Arena allocator can be used for heap memory, then bound to the global app instance.<br>
  <p float="left">
    <img src="src/examples/8_memory.gif" alt="8_memory" height="300">
    <img src="src/examples/8_memory_c.png" alt="8_memory_code" width="400">
  </p>
* File: Opening/closing and reading/writing files in a platform-agnostic way (using os-specific API).<br>
  <p float="left">
    <img src="src/examples/9_files_io.gif" alt="9_files" height="300">
    <img src="src/examples/9_files_c.png" alt="9_files_code" width="400">
  </p>

<i>*All input capturing for mouse and keyboard is extendable through callbacks</i><br>