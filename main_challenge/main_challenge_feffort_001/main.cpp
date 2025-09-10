#include <hello.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <GL/glew.h>

int main() {
    Hello hello;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        SDL_WINDOW_OPENGL
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewInit();
    SDL_GL_MakeCurrent(window, context);

    GLuint VBO[1];
    GLuint VAO[1];

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    GLfloat rectangle[] = {
        -1.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        -1.0f, 0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

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

        glClearColor(0.0f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_POLYGON, 0, 4);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}