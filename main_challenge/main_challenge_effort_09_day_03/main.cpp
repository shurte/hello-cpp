#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <GL/glew.h>

#include <iostream>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    std::cout << "Init result: " << error << '\n';

    SDL_Window* window = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500,
        500,
        SDL_WINDOW_OPENGL
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);

    const unsigned char* version = glGetString(GL_VERSION);
    std::cout << "Version: " << version << '\n';

    SDL_GL_MakeCurrent(window, context);

    glViewport(0, 0, 500, 500);
    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);

    // GLuint shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    // GLfloat firstTriangle[] = {
    //     -0.9f, -0.5f, 0.0f,  // Left 
    //     -0.0f, -0.5f, 0.0f,  // Right
    //     -0.45f, 0.5f, 0.0f,  // Top 
    // };
    // GLfloat secondTriangle[] = {
    //     0.0f, -0.5f, 0.0f,  // Left
    //     0.9f, -0.5f, 0.0f,  // Right
    //     0.45f, 0.5f, 0.0f   // Top 
    // };
    // GLuint VBOs[2], VAOs[2];
    // glGenVertexArrays(2, VAOs); // We can also generate multiple VAOs or buffers at the same time
    // glGenBuffers(2, VBOs);

    // glBindVertexArray(VAOs[0]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
    // glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

    // glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
    // glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
    // glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
    // glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

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

        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAOs[0]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // glBindVertexArray(VAOs[1]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    // glDeleteVertexArrays(2, VAOs);
    // glDeleteBuffers(2, VBOs);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}