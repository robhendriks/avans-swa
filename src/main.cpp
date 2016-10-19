#include <string>
#include "game/engine.h"
#include "json.hpp"

int main(int argc, char *argv[]) {
//    game::engine *engine = new game::engine();
//    engine->init();
//    engine->destroy();

    nlohmann::json j;

    j["foo"] = "bar";

    std::string s = j.dump();

    printf("%s\n", s.c_str());

    return 0;
}
