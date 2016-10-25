#include "game/engine.h"
#include "gui/menu_gui.h"

int main(int argc, char *argv[]) {
    game::engine *engine = &game::engine::get();
    engine->run();
    gui::menu_gui *menu = new gui::menu_gui();
    engine->setActiveGUI(menu);

    return 0;
}

/*
void engine::setActiveGUI(gui::base_gui* gui) {
    m_gui = gui;
}

if(this->m_gui != nullptr)
this->m_gui->render(m_display->get_renderer());
 */