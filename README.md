# SlimApp

A minimalist platform-agnostic app layer for desktop apps written in plain C.<br>
A bare-bone application executable on Windows measures at around 13 KB(!)<br>
Can be complied in either C or C++ (only uses the subset of C that C++ also supports).<br>
Available as either a single header file, or a directory of headers (a "unity build" setup).

Architecture: <br>
-
The platform layer only uses operating-system header(s).<br>
The appication layer has no dependencies - not even on the platform layer or any standard library.<br>
It is just a library that the platform layer uses (has no knowledge of the platform).<br>

More details on this architecture [here](https://youtu.be/Ev_TeQmus68).

Features:
-
Well documented example applications cover the features:<br>

* Bare-bone application (one-liner): Well-behaved window (can be resized minimized/maximized and closed)<br>
  <img src="src/examples/1_app.gif" alt="1_app" height="300"><img src="src/examples/1_app_c.png" alt="1_app_code" height="300">
* Overridable window defaults: Initial dimensions and title.<br>
  <img src="src/examples/2_defaults.gif" alt="2_defaults" height="300"><img src="src/examples/2_defaults_c.png" alt="2_defaults_code" height="300" width="400">
* Timers and window-title control:<br>
  <img src="src/examples/3_time.gif" alt="3_time" height="300"><img src="src/examples/3_time_c.png" alt="3_time_code" height="300">
* Drawable window content: Basic shape drawing (Lines, rectangles, triangles and circles)<br>
  <img src="src/examples/4_shapes.gif" alt="4_shapes" height="300"><img src="src/examples/4_shapes_c.png" alt="4_shapes_code" height="300">
* Text: String and number drawing:<br>
  <img src="src/examples/5_text.gif" alt="5_text" height="300"><img src="src/examples/5_text_c.png" alt="5_text_code" height="300">
* Mouse: Buttons (+wheel), cursor position/movement and 'raw' mouse input (captured outside the window).<br>
  <img src="src/examples/6_mouse.gif" alt="6_mouse" height="300"><img src="src/examples/6_mouse_c.png" alt="6_mouse_code" height="300">
* Keyboard: General key tracking + built-in tracking of control keys status (Ctrl, Alt, Shift, Space)<br>
  <img src="src/examples/7_keyboard.gif" alt="7_keyboard" height="300"><img src="src/examples/7_keyboard_c.png" alt="7_keyboard_code" height="300">
* Game: Built-in linear memory allocator (a.k.a: Arena) can be used for heap memory, and stored on the App.<br>
  <img src="src/examples/8_game.gif" alt="8_game" height="300"><img src="src/examples/8_game_c.png" alt="8_game_code" height="300">

<i>*All input capturing for mouse and keyboard is overridable via callbacks (settable function pointers)</i><br>