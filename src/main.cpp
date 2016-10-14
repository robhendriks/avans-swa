#include "game/engine.h"

int main(int argc, char *argv[]) {
    game::engine engine;
    engine.init();
    engine.destroy();

    return 0;
}
