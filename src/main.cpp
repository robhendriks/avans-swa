#include "game/engine.h"
#include "gui/menu_gui.h"

int main(int argc, char *argv[]) {
    game::engine *engine = &game::engine::get();
    engine->run();
    //gui::menu_gui *menu = new gui::menu_gui();
    //engine->setActiveGUI(menu);

    return 0;
}