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
  <img src="src/examples/1_app.gif" alt="1_app" height="120">
* Overridable window defaults: Initial dimensions and title.<br>
* Timers and window-title control:<br>
* Drawable window content: Basic shape drawing (Lines, rectangles, triangles and circles)<br>
* Text: String and number drawing:
* Mouse: Buttons (+wheel), cursor position/movement and 'raw' mouse input (captured outside the window).<br>
* Keyboard: General key tracking + built-in tracking of control keys status (Ctrl, Alt, Shift, Space)<br>
* Game: User-data can be stored on the App instance for use elsewhere

<i>*All input capturing for mouse and keyboard is overridable via callbacks (settable function pointers)</i><br>