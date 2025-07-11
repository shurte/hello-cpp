#pragma once

#include "AppWindow.hpp"

class App {
    public:
        App() {
            SDL_Init(SDL_INIT_VIDEO);
            AppWindow window;
            window.loop();
        }

        ~App() {
            SDL_Quit();
        }
};