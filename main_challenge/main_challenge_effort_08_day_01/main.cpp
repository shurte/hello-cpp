// #define SDL_MAIN_HANDLED
// #include <SDL2\SDL.h>
// int main(int argc, char** argv) {
//     SDL_Init(SDL_INIT_VIDEO);

//     SDL_Window* window = SDL_CreateWindow(
//         "Hello",
//         SDL_WINDOWPOS_CENTERED,
//         SDL_WINDOWPOS_CENTERED,
//         500,
//         500,
//         0
//     );

//     SDL_Event event;
//     bool isRunning = true;

//     while (isRunning) {
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     isRunning = false;
//                     break;
//             }
//         }
//     }

//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

class MainWindow {
    public:
        void init() {
            SDL_Init(SDL_INIT_VIDEO);
            _windowPtr = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
            SDL_Surface* surface = NULL;
            surface = SDL_GetWindowSurface(_windowPtr);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(_windowPtr);
        }

        void runLoop() {
            SDL_Event event;
            bool isRunning = true;
            while (isRunning) {
                while(SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            isRunning = false;
                            break;
                    }
                }
            }
        }

        void close() {
            SDL_DestroyWindow(_windowPtr);
            SDL_Quit();
        }

    private:
        SDL_Window* _windowPtr = nullptr;
};

int main(int argc, char** argv) {
    MainWindow window;
    window.init();
    window.runLoop();
    window.close();
    return 0;
}