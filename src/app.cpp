#include "app.hpp"

using namespace pixanv;


App& App::getInstance() {
    static App theInstance;
    return theInstance;
}