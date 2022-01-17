#include "../SlimApp.h"

void drawShapesToCanvas(PixelGrid &canvas) {
    // Draw and fill a rectangle with different colors:
    Rect rect;
    rect.min.x = rect.min.y = 100;
    rect.max.x = rect.max.y = 300;
    canvas.fillRect(Color(Blue), rect);
    canvas.drawRect(Color(Red ), rect);

    // Prepare vertex positions of a triangle then draw a filled yellow one:
    static float X[3] = {150, 250, 200};
    static float Y[3] = {150, 150, 250};
    canvas.fillTriangle(Color(Yellow), X, Y);

    // Draw an un-filled green triangles elsewhere, this time with arbitrary line drawing:
    canvas.drawLine2D(Color(Green), 150, 175, 250, 175);
    canvas.drawLine2D(Color(Green), 250, 175, 200, 275);
    canvas.drawLine2D( Color(Green), 200, 275, 150, 175);

    // Draw a multi-colored rectangle by drawing horizontal and vertical lines with different colors:
    canvas.drawHLine2D(Color(Magenta), 90, 310, 310);
    canvas.drawHLine2D(Color(Magenta), 90, 310, 90);
    canvas.drawVLine2D(Color(Cyan   ), 90, 310, 310);
    canvas.drawVLine2D(Color(Cyan   ), 90, 310, 90);

    // Draw a filled and un-filled circles:
    canvas.fillCircle(Color(Cyan), 200, 175, 18);
    canvas.drawCircle(Color(Red ), 200, 200, 20);
}

void draw() {
    // Clear the window content to black:
    PixelGrid &canvas = app->window_content;
    canvas.fill(Color(Black));

    drawShapesToCanvas(canvas);
}

void App::init(Defaults *defaults) {
    // Tell the app how to draw the window content:
    on.windowRedraw = draw;
}

