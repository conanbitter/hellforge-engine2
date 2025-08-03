#include "rendertarget.hpp"
#include <string>

namespace pixanv {
    class App;

    class Scene {
        void onLoad(App& app) { isLoaded = true; }
        void onUnload(App& app) { isLoaded = false; }

        void onUpdate(App& app) {}
        void onDraw(App& app, RenderTarget& gfx) {}

        void onKeyDown(App& app, int key) {}
        void onKeyUp(App& app, int key) {}

        void onMouseMove(App& app, int x, int y, int dx, int dy) {}
        void onMouseDown(App& app, int button) {}
        void onMouseUp(App& app, int button) {}

    protected:
        bool isLoaded = false;

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