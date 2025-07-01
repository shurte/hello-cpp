#include <iostream>
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class MainGame {

public:
    int init() {
        int initResult = SDL_Init(SDL_INIT_VIDEO);

        if (initResult < 0) {
            std::cout << "could not initialize sdl2: " << SDL_GetError() << '\n';
            return 1;
        }

        window = SDL_CreateWindow(
                "hello_sdl2",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
            );

        if (window == NULL) {
            std::cout << "could not create window: " << SDL_GetError() << '\n';
            return 1;
        }

        SDL_Surface* screenSurface = NULL;
        screenSurface = SDL_GetWindowSurface(window);
        
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(window);

        return 0;
    }

    void run_loop() {
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

    void close() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window* window = NULL;
};

int main(int argc, char* args[]) {

    MainGame game;

    if (game.init() == 0) {
        game.run_loop();
        game.close();
    }

    return 0;
}