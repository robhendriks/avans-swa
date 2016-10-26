#include "game/engine.h"
#include "gui/menu_gui.h"

int main(int argc, char *argv[]) {
    game::engine *engine = &game::engine::get();
    gui::menu_gui *menu = new gui::menu_gui();

    engine->set_active_gui(menu);
    engine->run();

    return 0;
}
