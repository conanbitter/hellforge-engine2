#include "app.hpp"
#include <string>
#include "texture.hpp"
#include "resources.hpp"
using namespace std::string_literals;

const int FRAME_WIDTH = 480;
const int FRAME_HEIGHT = 270;

class TestScene :public pixanv::Scene
{
public:
    TestScene() {};

    int actionKey;
    int mx = 0;
    int my = 0;
    const pixanv::Color bgColor = pixanv::Color(5, 10, 5);
    pixanv::Texture tex;

    void onLoad() override {
        /*for (int y = 0;y < FRAME_HEIGHT;y++) {
            for (int x = 0;x < FRAME_WIDTH;x++) {
                gfx.pixel(x, y, x == y ? pixanv::Color(31, 0, 0) : pixanv::Color(0, 0, 0));
            }
        }*/
        gfx.fill(bgColor);
        actionKey = app.registerKey("D");
        tex = pixanv::Resources::loadTexture("../../assets/transp1.tex");
        //app.setCursorVisible(false);
    }

    void onKeyDown(int key) override {
        if (key == actionKey) {
            app.setIntegerScaling(!app.getIntegerScaling());
            //app.setScale(3);
        }
    }

    void onDraw()override {
        gfx.fill(bgColor);
        gfx.blit(tex, 5, 5);
        gfx.pixel(mx, my, pixanv::Color::RED);
    }

    void onMouseMove(int x, int y, int dx, int dy)override {
        //mx += dx;
        //my += dy;
        mx = x;
        my = y;
        //gfx.fill(bgColor);
        //if (app.isMouseButtonPressed(1)) {
        //gfx.pixel(x, y, pixanv::Color::RED);
        //}
        /*gfx.pixel(x + 1, y, pixanv::Color::RED);
    gfx.pixel(x - 1, y, pixanv::Color::RED);
    gfx.pixel(x, y + 1, pixanv::Color::RED);
    gfx.pixel(x, y - 1, pixanv::Color::RED);*/
    }
};



int main(int argc, char* argv[]) {
    try {
        pixanv::App& app = pixanv::App::getInstance();
        app.init("Hellforge"s, FRAME_WIDTH, FRAME_HEIGHT, 2);

        TestScene scene;
        app.setScene(&scene);

        app.run();
    }
    catch (const std::exception& e) {
        pixanv::App::showErrorMessage(e.what());
    }
    catch (...) {
        pixanv::App::showErrorMessage("Unknown error");
    }

    return 0;
}