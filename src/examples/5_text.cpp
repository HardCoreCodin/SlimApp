#include "../SlimApp.h"

struct TextApp : public SlimApp {
    void OnWindowRedraw() override {
        // Clear the window content to black:
        window_content.fill(Color(Black));

        // Draw a multi-colored line of text:
        window_content.drawText(Color(Green),
                        (char*)"The answer is... :    (!)",
                        100, 50);
        window_content.drawNumber(Color(Red  ),
                          42, 270, 50);
    }
};

SlimApp* createApp() { return new TextApp(); }