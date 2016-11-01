#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "gui/views/main_menu.h"
#include "gui/router.h"
#include "engine/eventbus/eventbus.h"
#include "config/json_config.h"
#include "utils/string_utils.h"
#include "gui/views/main_map.h"
#include "gui/controllers/main_map_controller.h"

int main(int argc, char *argv[]) {

    // Config
    auto *json_config = new config::json_config("config.json");
    json_config->load();

    engine::window_config w_config = {
        json_config->get_string("engine.title"),
        engine::graphics::color4_t(utils::string_utils::hex_to_long(json_config->get_string("window.background_color")))
    };

    w_config.w = json_config->get_int("window.width", w_config.w);
    w_config.h = json_config->get_int("window.height", w_config.h);

    engine::engine_config e_config = { w_config };

    // Get the engine
    engine::engine *engine1 = new engine::engine(e_config);
    engine1->warmup();

    // Create the ioc container
    auto *texture_manager = engine1->get_texture_manager();
    auto *window = engine1->get_window();
    auto injector = boost::di::make_injector(
        boost::di::bind<>.to(*texture_manager),
        boost::di::bind<>.to(*window)
    );

    // Create the router
    gui::router &router1 = gui::router::get_instance();
    engine::eventbus::eventbus<engine::events::window_cleared>::get_instance().subscribe(&router1);

    // Register actions
    auto menu_controller = injector.create<gui::controllers::menu_controller>();
    auto main_map_controller = injector.create<gui::controllers::main_map_controller>();
    router1.register_action("main_menu", std::bind(&gui::controllers::menu_controller::show, menu_controller , std::placeholders::_1, injector.create<gui::views::main_menu&>()));
    router1.register_action("quit", std::bind(&gui::controllers::menu_controller::quit, menu_controller, std::placeholders::_1, engine1));
    router1.register_action("play", std::bind(&gui::controllers::menu_controller::play, menu_controller , std::placeholders::_1));
    router1.register_action("main_map", std::bind(&gui::controllers::main_map_controller::show, main_map_controller , std::placeholders::_1, injector.create<gui::views::main_map&>()));
    // Start with the main menu
    router1.use("main_menu");
    // Run the game
    engine1->run();

    // Clean
    delete json_config;
    delete texture_manager;
    delete window;
    delete engine1;

    return 0;
}
