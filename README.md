# SlimApp

A minimalist platform-agnostic app layer for desktop apps written in plain C.<br>

Can be complied in either C or C++ (only uses the subset of C that C++ also supports).<br>

Available as either a single header file or a directory of headers (a "unity build" setup).

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
  <img src="src/examples/1_app.gif" alt="1_app">
* Overridable window defaults: Initial dimensions and title.<br>
  <img src="src/examples/2_defaults.gif" alt="2_defaults">
* Timers and window-title control:<br>
  <img src="src/examples/3_time.gif" alt="3_time">
* Drawable window content: Basic shape drawing (Lines, rectangles, triangles and circles)<br>
  <img src="src/examples/4_shapes.gif" alt="4_shapes">
* Text: String and number drawing:<br>
  <img src="src/examples/5_text.gif" alt="5_text">
* Mouse: Buttons (+wheel), cursor position/movement and 'raw' mouse input (captured outside the window).<br>
  <img src="src/examples/6_mouse.gif" alt="6_mouse">
* Keyboard: General key tracking + built-in tracking of control keys status (Ctrl, Alt, Shift, Space)<br>
  <img src="src/examples/7_keyboard.gif" alt="7_keyboard">
* Game: Built-in linear memory allocator (a.k.a: Arena) can be used for heap memory, and stored on the App.<br>
  <img src="src/examples/8_game.gif" alt="8_game">

<i>*All input capturing for mouse and keyboard is overridable via callbacks (settable function pointers)</i><br>