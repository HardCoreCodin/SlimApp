#include "../app.h"
#include "../text.h"
// Or using the single-header file:
// #include "../SlimApp.h"

void showTheAnswer() {
    // Clear the window content to black:
    PixelGrid *canvas = &app->window_content;
    fillPixelGrid(canvas, Color(Black));

    // Draw a multi-colored line of text:
    drawText(  canvas, Color(Green),
               "The answer is... :    (!)",
               100, 50);
    drawNumber(canvas, Color(Red  ),
               42,
               260, 50);
}

void initApp(Defaults *defaults) {
    // Tell the app how to draw the window content:
    app->on.windowRedraw = showTheAnswer;
}


