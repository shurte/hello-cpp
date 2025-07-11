#include "AppWindow.hpp"

AppWindow::AppWindow() {
    _window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500,
        500,
        0
    );
}

void AppWindow::loop() {
    SDL_Event event;
    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }
    }
}

AppWindow::~AppWindow() {
    SDL_DestroyWindow(_window);
}
