#include "app.hpp"
#include <string>
#include <stdexcept>
#include <glad/gl.h>
#include "opengl.hpp"

using namespace pixanv;
using namespace std::string_literals;

void App::initWindow(const std::string& title, int width, int height, int scale) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: "s + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title.c_str(),
        width * scale,
        height * scale,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        throw std::runtime_error("Window could not be created! SDL_Error: "s + std::string(SDL_GetError()));
    }
    SDL_SetWindowMinimumSize(window, width, height);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    context = SDL_GL_CreateContext(window);
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    SDL_Log("Using OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
}

App& App::getInstance() {
    static App theInstance;
    return theInstance;
}

void App::init(const std::string& title, int width, int height, int scale, bool useIntegerScaling) {
    if (isInitComplete) return;
    integerScaling = useIntegerScaling;
    initWindow(title, width, height, scale);
    keyboardState = SDL_GetKeyboardState(nullptr);
    initOpenGL(width, height);
    resizeOpenGL(width * scale, height * scale, integerScaling);
    windowWidth = frameWidth = width;
    windowHeight = frameHeight = height;
    canvas.resize(width, height);

    if (currentScene == nullptr) {
        dummyScene = new Scene();
        currentScene = dummyScene;
    }

    isInitComplete = true;
}

void App::run() {
    if (!isInitComplete) return;
    SDL_Event event;
    isRunning = true;
    if (!currentScene->isLoaded) currentScene->onLoad();

    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                isRunning = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                windowWidth = event.window.data1;
                windowHeight = event.window.data2;
                resizeOpenGL(windowWidth, windowHeight, integerScaling);
                break;
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat) {
                    currentScene->onKeyDown(event.key.scancode);
                }
                break;
            case SDL_EVENT_KEY_UP:
                currentScene->onKeyUp(event.key.scancode);
                break;
            case SDL_EVENT_MOUSE_MOTION:
            {
                int x, y;
                screenToFrame(event.motion.x, event.motion.y, x, y);
                currentScene->onMouseMove(
                    x,
                    y,
                    event.motion.xrel,
                    event.motion.yrel
                );
            }
            break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                int x, y;
                screenToFrame(event.motion.x, event.motion.y, x, y);
                currentScene->onMouseDown(
                    event.button.button,
                    event.button.clicks,
                    x,
                    y
                );
            }
            break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                int x, y;
                screenToFrame(event.motion.x, event.motion.y, x, y);
                currentScene->onMouseUp(
                    event.button.button,
                    event.button.clicks,
                    x,
                    y
                );
            }
            break;
            case SDL_EVENT_MOUSE_WHEEL:
            {
                int x = event.wheel.integer_x;
                int y = event.wheel.integer_y;
                if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                    x *= -1;
                    y *= -1;
                }
                currentScene->onMouseWheel(x, y);
            }
            break;
            }
        }

        currentScene->onUpdate();

        glClear(GL_COLOR_BUFFER_BIT);
        currentScene->onDraw();
        presentOpenGL(canvas.m_data.data());

        SDL_GL_SwapWindow(window);
        SDL_Delay(5);
    }
}

App::~App() {
    if (dummyScene) delete dummyScene;

    freeOpenGL();

    if (context) SDL_GL_DestroyContext(context);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::setScene(Scene* scene) {
    currentScene = scene;
    if (isInitComplete) {
        currentScene->onLoad();
    }
}

void App::requestExit() {
    isRunning = false;
}

int App::registerKey(const std::string keyname) {
    return SDL_GetScancodeFromName(keyname.c_str());
}

int App::registerKey(const char* keyname) {
    return SDL_GetScancodeFromName(keyname);
}

bool App::isKeyPressed(int key) {
    return keyboardState[key];
}

void App::setIntegerScaling(bool useIntegerScaling) {
    integerScaling = useIntegerScaling;
    if (isInitComplete) resizeOpenGL(windowWidth, windowHeight, integerScaling);
}

void App::setScale(int scale) {
    windowWidth = frameWidth * scale;
    windowHeight = frameHeight * scale;
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED) {
        SDL_RestoreWindow(window);
    }
    SDL_SetWindowSize(window, windowWidth, windowHeight);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}