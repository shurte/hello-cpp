#define SDL_MAIN_HANDLED
#include <SDL2/SDL_ttf.h>
class AppWindow {
    public:
        AppWindow() {
            _window = SDL_CreateWindow(
                "Hello",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                500,
                500,
                0
            );

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

        ~AppWindow() {
            if (_window) {
                SDL_DestroyWindow(_window);
            }
        }

    private:
        SDL_Window* _window = nullptr;
};
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    AppWindow window;
    window.loop();
    SDL_Quit();
    return 0;
}