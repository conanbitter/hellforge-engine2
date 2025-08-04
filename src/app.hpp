#include "rendertarget.hpp"
#include <string>

namespace pixanv {
    class App;

    class Scene {
        Scene() :app{ App::getInstance() }, gfx{ app.getCanvas() } {}

        void onLoad() { isLoaded = true; }
        void onUnload() { isLoaded = false; }

        void onUpdate() {}
        void onDraw() {}

        void onKeyDown(int key) {}
        void onKeyUp(int key) {}

        void onMouseMove(int x, int y, int dx, int dy) {}
        void onMouseDown(int button) {}
        void onMouseUp(int button) {}

    protected:
        bool isLoaded = false;
        App& app;
        RenderTarget& gfx;

        friend class App;
    };

    class App {
    public:
        static App& getInstance();
        App() : isInitComplete{ false }, isRunning{ false }, frameWidth{ 0 }, frameHeight{ 0 }, dummyScene(), currentScene{ &dummyScene } {};
        ~App();

        void setScene(Scene* scene);
        void requestExit();

        int registerKey(const std::string keyname);
        bool isKeyPressed(int);

        RenderTarget& getCanvas() { return canvas; };

        App(const App&) = delete;
        App& operator=(const App&) = delete;

    private:
        bool isRunning;
        bool isInitComplete;
        int frameWidth;
        int frameHeight;
        Scene dummyScene;
        Scene* currentScene;
        RenderTarget canvas;
    };


}