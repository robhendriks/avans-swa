#include "game/engine.h"

int main(int argc, char *argv[]) {
    game::engine *engine = new game::engine();
    engine->init();
    engine->destroy();

    return 0;
}
