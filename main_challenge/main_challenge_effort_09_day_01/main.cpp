#define NO_SDL_GLEXT
#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glewInit();

    SDL_Window* window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500,
        500,
        SDL_WINDOW_OPENGL
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(0.2, 0.7, 0.5);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 1, 0);
        glEnd();
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}