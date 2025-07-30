#include <print>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/gl.h>
#include "opengl.hpp"
#include "color.hpp"

const int FRAME_WIDTH = 480;
const int FRAME_HEIGHT = 360;


int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("HellForge", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    SDL_Log("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    try {
        initOpenGL(FRAME_WIDTH, FRAME_HEIGHT);
    }
    catch (const std::runtime_error& e) {
        SDL_Log("[OpenGL] %s", e.what());
    }

    std::print("Size of Color: {}", sizeof(Color));

    std::vector<Color> frame(FRAME_WIDTH * FRAME_HEIGHT);

    for (int y = 0;y < FRAME_HEIGHT;y++) {
        for (int x = 0;x < FRAME_WIDTH;x++) {
            frame[x + y * FRAME_WIDTH] = Color(y * 31 / FRAME_HEIGHT, x * 63 / FRAME_WIDTH, 16);
        }
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        presentOpenGL(frame.data());

        SDL_GL_SwapWindow(window);
        SDL_Delay(1);
    }

    freeOpenGL();

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}