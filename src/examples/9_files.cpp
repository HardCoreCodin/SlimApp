#include "../SlimApp.h"

static char file_str[4096];

void drawFile() {
    PixelGrid &canvas = app->window_content;
    canvas.fill(Color(Black));
    canvas.drawText(Color(Green),
             file_str, 5, 5);
}

void App::init(Defaults *defaults) {
    on.windowRedraw = drawFile;
    void* f = os::openFileForReading(__FILE__);
    os::readFromFile(file_str, 4096, f);
    os::closeFile(f);
}

