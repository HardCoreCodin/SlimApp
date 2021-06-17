#include "../app.h"
#include "../shapes.h"
// Or using the single-header file:
// #include "../SlimApp.h"

void drawShapesToCanvas(PixelGrid *canvas) {
    // Draw and fill a rectangle with different colors:
    Rect rect;
    rect.min.x = rect.min.y = 100;
    rect.max.x = rect.max.y = 300;
    fillRect(canvas, Color(Blue), &rect);
    drawRect(canvas, Color(Red ), &rect);

    // Prepare vertex positions of a triangle then draw a filled yellow one:
    static float X[3] = {150, 250, 200};
    static float Y[3] = {150, 150, 250};
    fillTriangle(canvas, Color(Yellow), X, Y);

    // Draw an un-filled green triangles elsewhere, this time with arbitrary line drawing:
    drawLine2D(canvas, Color(Green), 150, 175, 250, 175);
    drawLine2D(canvas, Color(Green), 250, 175, 200, 275);
    drawLine2D(canvas, Color(Green), 200, 275, 150, 175);

    // Draw a multi-colored rectangle by drawing horizontal and vertical lines with different colors:
    drawHLine2D(canvas, Color(Magenta), 90, 310, 310);
    drawHLine2D(canvas, Color(Magenta), 90, 310, 90);
    drawVLine2D(canvas, Color(Cyan   ), 90, 310, 310);
    drawVLine2D(canvas, Color(Cyan   ), 90, 310, 90);

    // Draw a filled and un-filled circles with different colors:
    fillCircle(canvas, Color(Cyan), 200, 175, 18);
    drawCircle(canvas, Color(Red ), 200, 200, 20);
}

void draw() {
    // Get the window content from the app and clear it all to black:
    PixelGrid *canvas = &app->window_content;
    fillPixelGrid(canvas, Color(Black));

    drawShapesToCanvas(canvas);
}

void initApp(Defaults *defaults) {
    // Tell the app what to do whenever it needs to redraw the window:
    app->on.windowRedraw = draw;
}

