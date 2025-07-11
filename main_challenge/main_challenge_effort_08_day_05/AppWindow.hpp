#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL_ttf.h>

class AppWindow {
    public:
        AppWindow();
        void loop();
        ~AppWindow();

    private:
        SDL_Window* _window = nullptr;
};
