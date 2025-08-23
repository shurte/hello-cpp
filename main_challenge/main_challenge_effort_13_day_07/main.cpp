#include <iostream>

class Hello {
    public:
        Hello() {
            std::cout << "Hello" << '\n';
        }

        ~Hello() {
            std::cout << "Bye" << '\n';
        }
};

#define SDL_MAIN_HANDLED
#include <SDL.h>

int main() {
    Hello hello;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        SDL_WINDOW_SHOWN
    );

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

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}