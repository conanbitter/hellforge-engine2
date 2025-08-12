#include "app.hpp"
#include <string>
#include "texture.hpp"
#include "resources.hpp"
#include "rect.hpp"
using namespace std::string_literals;

const int FRAME_WIDTH = 480;
const int FRAME_HEIGHT = 270;

class TestScene :public pixanv::Scene
{
public:
    TestScene() {};

    int keyAction;
    int mx = 0;
    int my = 0;
    int px = 0;
    int py = 0;

    int keyUp;
    int keyDown;
    int keyLeft;
    int keyRight;

    const pixanv::Color bgColor = pixanv::Color(5, 10, 5);
    pixanv::Texture tex;
    pixanv::Font font;

    void onLoad() override {
        /*for (int y = 0;y < FRAME_HEIGHT;y++) {
            for (int x = 0;x < FRAME_WIDTH;x++) {
                gfx.pixel(x, y, x == y ? pixanv::Color(31, 0, 0) : pixanv::Color(0, 0, 0));
            }
        }*/
        gfx.fill(bgColor);
        keyAction = app.registerKey("D");
        keyLeft = app.registerKey("Left");
        keyRight = app.registerKey("Right");
        keyUp = app.registerKey("Up");
        keyDown = app.registerKey("Down");
        tex = pixanv::Resources::loadTexture("../../assets/testex2.tex");
        font = pixanv::Resources::loadFont("../../assets/main.fon");
        //app.setCursorVisible(false);
    }

    void onKeyDown(int key) override {
        if (key == keyAction) {
            app.setIntegerScaling(!app.getIntegerScaling());
            //app.setScale(3);
        } else if (key == keyLeft) {
            px--;
        } else if (key == keyRight) {
            px++;
        } else if (key == keyUp) {
            py--;
        } else if (key == keyDown) {
            py++;
        }
    }

    void onDraw()override {
        pixanv::Rect test(5, 5, 64, 64);
        pixanv::Rect test2(px, py, 32, 32);
        test2.right = 31;
        test2.bottom = 31;
        gfx.fill(bgColor);
        gfx.blit(tex, 0, 0, pixanv::Color(31, 50, 20));
        gfx.pixel(mx, my, pixanv::Color::RED);
        gfx.print(font, 10, 100, "Hello ");
        gfx.print(font, "World", pixanv::Color::YELLOW);
        gfx.print(font, "!");
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