cmake_minimum_required(VERSION 3.8)

link_libraries(kernel32.lib gdi32.lib)

project(SlimApp_1_app)
add_executable(SlimApp_1_app WIN32 src/examples/1_app.c)

project(SlimApp_2_defaults)
add_executable(SlimApp_2_defaults WIN32 src/examples/2_defaults.c)

project(SlimApp_3_time)
add_executable(SlimApp_3_time WIN32 src/examples/3_time.c)

project(SlimApp_4_shapes)
add_executable(SlimApp_4_shapes WIN32 src/examples/4_shapes.c)

project(SlimApp_5_text)
add_executable(SlimApp_5_text WIN32 src/examples/5_text.c)

project(SlimApp_6_mouse)
add_executable(SlimApp_6_mouse WIN32 src/examples/6_mouse.c)

project(SlimApp_7_keyboard)
add_executable(SlimApp_7_keyboard WIN32 src/examples/7_keyboard.c)

project(SlimApp_8_game)
add_executable(SlimApp_8_game WIN32 src/examples/8_game.c)