#include "../app.h"
#include "../text.h"
// Or using the single-header file:
// #include "../SlimApp.h"

static char file_str[4096];

void drawFile() {
    PixelGrid *canvas = &app->window_content;
    fillPixelGrid(canvas, Color(Black));
    drawText(canvas, Color(Green),
             file_str, 5, 5);
}

void initApp(Defaults *defaults) {
    app->on.windowRedraw = drawFile;
    Platform *os = &app->platform;
    void* f = os->openFileForReading(__FILE__);
    os->readFromFile(file_str, 4096, f);
    os->closeFile(f);
}

