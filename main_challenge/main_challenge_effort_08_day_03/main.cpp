#define SDL_MAIN_HANDLED
#include <SDL2/SDL_ttf.h>
class MyApp {
    public:
        MyApp() {
            SDL_Init(SDL_INIT_VIDEO);
            TTF_Init();

            SDL_Window* window = SDL_CreateWindow(
                "Hello",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                500,
                500,
                0
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
        }

        ~MyApp() {
            SDL_Quit();
        }
};
int main(int argc, char** argv) {
    MyApp app;
    return 0;
}