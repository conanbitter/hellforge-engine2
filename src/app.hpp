#include <string>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include "rendertarget.hpp"

namespace pixanv {
    class Scene;

    class App {
    public:
        static App& getInstance();
        App() : isInitComplete{ false }, isRunning{ false }, frameWidth{ 0 }, frameHeight{ 0 }, currentScene{ nullptr } {};
        ~App();
        void init(const std::string& title, int width, int height, int scale = 1, bool useIntegerScaling = true);
        void run();

        void setScene(Scene* scene);
        void requestExit();

        int registerKey(const std::string keyname);
        int registerKey(const char* keyname);
        bool isKeyPressed(int key);

        RenderTarget& getCanvas() { return canvas; };
        void setIntegerScaling(bool useIntegerScaling);
        bool getIntegerScaling() const { return integerScaling; }
        void setScale(int scale);

        App(const App&) = delete;
        App& operator=(const App&) = delete;

    private:
        bool isRunning;
        bool isInitComplete;
        int frameWidth;
        int frameHeight;
        int windowWidth;
        int windowHeight;
        Scene* dummyScene;
        Scene* currentScene;
        RenderTarget canvas;
        bool integerScaling;

        SDL_Window* window;
        SDL_GLContext context;
        const bool* keyboardState;

        void initWindow(const std::string& title, int width, int height, int scale);
    };

    class Scene {
    public:
        Scene() :app{ App::getInstance() }, gfx{ app.getCanvas() } {}

        virtual void onLoad() { isLoaded = true; }
        virtual void onUnload() { isLoaded = false; }

        virtual void onUpdate() {}
        virtual void onDraw() {}

        virtual void onKeyDown(int key) {}
        virtual void onKeyUp(int key) {}

        virtual void onMouseMove(int x, int y, int dx, int dy) {}
        virtual void onMouseDown(int button, int repeats, int x, int y) {}
        virtual void onMouseUp(int button, int repeats, int x, int y) {}
        virtual void onMouseWheel(int x, int y) {}
    protected:
        bool isLoaded = false;
        App& app;
        RenderTarget& gfx;

        friend class App;
    };
}