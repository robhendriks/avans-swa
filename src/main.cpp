#include "game/engine.h"
#include "gui/menu_gui.h"

int main(int argc, char *argv[]) {
    game::engine *engine = new game::engine();
    gui::menu_gui *menu = new gui::menu_gui();
    engine->setActiveGUI(menu);
    engine->init();
    engine->destroy();

    delete menu;
    return 0;
}
