#include "app.hpp"
#include <string>
using namespace std::string_literals;

const int FRAME_WIDTH = 480;
const int FRAME_HEIGHT = 270;

class TestScene :public pixanv::Scene
{
public:
    TestScene() {};

    void onLoad() override {
        for (int y = 0;y < FRAME_HEIGHT;y++) {
            for (int x = 0;x < FRAME_WIDTH;x++) {
                gfx.pixel(x, y, x == y ? pixanv::Color(31, 0, 0) : pixanv::Color(0, 0, 0));
            }
        }
    }
};



int main(int argc, char* argv[]) {
    pixanv::App& app = pixanv::App::getInstance();
    app.init("Hellforge"s, FRAME_WIDTH, FRAME_HEIGHT, 2);

    TestScene scene;
    app.setScene(&scene);

    app.run();

    return 0;
}