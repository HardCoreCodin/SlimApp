#include "../SlimApp.h"

struct FilesApp : public SlimApp {
    bool OnReady() override {
        void* f = os::openFileForReading(__FILE__);
        os::readFromFile(file_str, file_buffer_size, f);
        os::closeFile(f);
        return true;
    }

    void OnWindowRedraw() override {
        window_content.fill(Color(Black));
        window_content.drawText(Color(Green), file_str, 5, 5);
    }

private:
    static constexpr u32 file_buffer_size = 4096;
    static char file_str[file_buffer_size];
};

char FilesApp::file_str[FilesApp::file_buffer_size];

SlimApp* createApp() { return new FilesApp(); }