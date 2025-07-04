#include <SDL2/SDL.h>

class MainWindow {
    public:
        void init() {
            SDL_Init(SDL_INIT_VIDEO);

            _window = SDL_CreateWindow(
                "Hello", 
                SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOWPOS_CENTERED, 
                500, 
                500, 
                SDL_WINDOW_SHOWN
            );

            SDL_Surface* surface = SDL_GetWindowSurface(_window);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(_window); 
        }

        void loop() {
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
            SDL_DestroyWindow(_window);
            SDL_Quit();
        }

    private:
        SDL_Window* _window = nullptr;
};

int main(int argc, char** argv) {
    MainWindow main;
    main.init();
    main.loop();
    main.close();
    return 0;
}