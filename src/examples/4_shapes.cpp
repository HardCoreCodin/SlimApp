#include "../SlimApp.h"

struct ShapesApp : public SlimApp {
    void OnWindowRedraw() override {
        // Clear the window content to black:
        window_content.fill(Color(Black));

        // Draw and fill a rectangle with different colors:
        Rect rect;
        rect.min.x = rect.min.y = 100;
        rect.max.x = rect.max.y = 300;
        window_content.fillRect(Color(Blue), rect);
        window_content.drawRect(Color(Red ), rect);

        // Prepare vertex positions of a triangle then draw a filled yellow one:
        static float X[3] = {150, 250, 200};
        static float Y[3] = {150, 150, 250};
        window_content.fillTriangle(Color(Yellow), X, Y);

        // Draw an un-filled green triangles elsewhere, this time with arbitrary line drawing:
        window_content.drawLine2D(Color(Green), 150, 175, 250, 175);
        window_content.drawLine2D(Color(Green), 250, 175, 200, 275);
        window_content.drawLine2D( Color(Green), 200, 275, 150, 175);

        // Draw a multi-colored rectangle by drawing horizontal and vertical lines with different colors:
        window_content.drawHLine2D(Color(Magenta), 90, 310, 310);
        window_content.drawHLine2D(Color(Magenta), 90, 310, 90);
        window_content.drawVLine2D(Color(Cyan   ), 90, 310, 310);
        window_content.drawVLine2D(Color(Cyan   ), 90, 310, 90);

        // Draw a filled and un-filled circles:
        window_content.fillCircle(Color(Cyan), 200, 175, 18);
        window_content.drawCircle(Color(Red ), 200, 200, 20);
    }
};
SlimApp* createApp() { return new ShapesApp(); }