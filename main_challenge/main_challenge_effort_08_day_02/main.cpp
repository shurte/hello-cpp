#define SDL_MAIN_HANDLED
#include <SDL2/SDL_ttf.h>
SDL_Window* createWindow() {
    return SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500,
        500,
        0
    );
}
SDL_Texture* createMessage(SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont("FiraCode-VariableFont_wght.ttf", 25);
    SDL_Color white = {0xFF, 0xFF, 0xFF};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Hello", white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_Rect messageRect;
    messageRect.x = 0;
    messageRect.y = 0;
    messageRect.w = 100;
    messageRect.h = 50;
    SDL_RenderCopy(renderer, message, nullptr, &messageRect);
    return message;
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
class AppWindow {
    public:
        AppWindow() {
            _window = createWindow();
            _renderer = SDL_CreateRenderer(_window, -1, 0);
            _message = createMessage(_renderer);
        }

        void start() {
            SDL_RenderPresent(_renderer);
            SDL_UpdateWindowSurface(_window);
            loop();
        }

        ~AppWindow() {
            SDL_DestroyTexture(_message);
            SDL_DestroyWindow(_window);
        }

    private:
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        SDL_Texture* _message = nullptr;
};
class App {
    public:
        App() {
            SDL_Init(SDL_INIT_VIDEO);
            TTF_Init();
        }

        void start() {
            AppWindow appWindow;
            appWindow.start();
        }

        ~App() {
            SDL_Quit();
        }
};
int main(int argc, char** argv) {
    App app;
    app.start();
    return 0;
}