#include "game/engine.h"

int main(int argc, char *argv[]) {
    game::engine *engine = &game::engine::get();
    engine->run();

    return 0;
}
