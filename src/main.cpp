#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "gui/views/main_menu.h"
#include "router.h"
#include "engine/eventbus/eventbus.h"

int main(int argc, char *argv[]) {

    // Get the engine
    engine::engine *engine1 = new engine::engine();
    engine1->warmup();

    // Create the ioc container
    auto injector = boost::di::make_injector(
        boost::di::bind<>.to(engine1->get_texture_manager())
    );

    // Create the router
    router &router1 = router::get_instance();
    engine::eventbus::eventbus<engine::events::window_cleared>::get_instance().subscribe(&router1);

    // Register actions
    auto menu_controller = injector.create<gui::controllers::menu_controller>();
    router1.register_action("main_menu", std::bind(&gui::controllers::menu_controller::show, menu_controller , injector.create<gui::views::main_menu&>()));
    router1.register_action("quit", std::bind(&gui::controllers::menu_controller::quit, menu_controller, engine1));

    // Start with the main menu
    router1.use("main_menu");

    // Run the game
    engine1->run();

    // Clean
    delete engine1;

    return 0;
}
