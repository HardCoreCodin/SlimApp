#include "../SlimApp.h"

void showTheAnswer() {
    // Clear the window content to black:
    PixelGrid &canvas = app->window_content;
    canvas.fill(Color(Black));

    // Draw a multi-colored line of text:
    canvas.drawText(Color(Green),
               (char*)"The answer is... :    (!)",
               100, 50);
    canvas.drawNumber(Color(Red  ),
                      42, 270, 50);
}

void App::init(Defaults *defaults) {
    // Tell the app how to draw the window content:
    on.windowRedraw = showTheAnswer;
}


