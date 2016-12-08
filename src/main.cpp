#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "config/json_config.h"
#include "utils/string_utils.h"
#include "services/level_loader/json_level_loader.h"
#include "services/level_loader/nation_deserializer.h"
#include "services/level_loader/nations_deserializer.h"
#include "services/level_loader/building_deserializer.h"
#include "services/level_loader/buildings_deserializer.h"
#include "services/level_loader/resources_deserializer.h"

using namespace services::level_loader;
using namespace utils::json_utils;

int main(int argc, char *argv[]) {
    // Register type deserializers
    json_factory::get()
        .register_deserializer<nation_ptr>(std::make_shared<nation_deserializer>())
        .register_deserializer<nation_ptr_vector>(std::make_shared<nations_deserializer>())
        .register_deserializer<building_ptr>(std::make_shared<building_deserializer>())
        .register_deserializer<building_ptr_vector>(std::make_shared<buildings_deserializer>())
        .register_deserializer<resource_ptr_vector>(std::make_shared<resources_deserializer>());

    /**
     * CONFIG
     */
    auto *json_config = new config::json_config("config.json");
    json_config->load();

    engine::window_config w_config = {
        json_config->get_string("engine.title"),
        engine::graphics::color4_t(utils::string_utils::hex_to_long(json_config->get_string("window.background_color")))
    };

    w_config.w = json_config->get_int("window.width", w_config.w);
    w_config.h = json_config->get_int("window.height", w_config.h);
    w_config.debug = json_config->get_bool("window.debug", w_config.debug);

    engine::engine_config e_config = {w_config};

    // Create a font_manager with fonts
    auto *font_manager = new engine::graphics::font_manager();
    font_manager->add("fonts/Roboto-Regular.ttf", "roboto");

    /**
     * END OF CONFIG
     */

    // Get the engine
    engine::engine *engine1 = new engine::engine(e_config);
    engine1->warmup();

    // Create the ioc container
    auto *game1 = new game(*engine1->get_window());

    std::ifstream file("scenarios.json");
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Unable to open file: ") + "scenarios.json");
    }

    json root;
    try {
        root << file;
    } catch (std::exception &e) {
        // TODO: proper error handling
        throw;
    }

    services::level_loader::json_level_loader *level_loader = new services::level_loader::json_level_loader(root);

    auto di_config = [&]() {
        return boost::di::make_injector(
            boost::di::bind<>.to(*game1),
            boost::di::bind<>.to(*engine1),
            boost::di::bind<>.to(*engine1->get_texture_manager()),
            boost::di::bind<>.to(*engine1->get_color_manager()),
            boost::di::bind<>.to(*engine1->get_sound_manager()),
            boost::di::bind<>.to(*engine1->get_music_manager()),
            boost::di::bind<>.to(*engine1->get_window()),
            boost::di::bind<>.to(*font_manager),
            boost::di::bind<services::level_loader::base_level_loader>.to(*level_loader)
        );
    };

    /**
     *  ADD SUBSCRIBERS
     */
    auto &eventbus = engine::eventbus::eventbus::get_instance();

    // Subscribe the game to the window cleared event and display changed events
    eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::window_cleared> *>(game1));
    eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::display_changed> *>(game1));

    /**
     * END OF SUBSCRIBERS REGISTRY
     */

    // Start with show
    gui::controllers::menu_controller *menu_controller = boost::di::make_injector(
        di_config()).create<gui::controllers::menu_controller *>();
    menu_controller->show();

    // Run the game
    engine1->run();

    // Stop/cooldown the engine
    delete font_manager;
    engine1->cooldown();

    // More cleaning
    delete game1;
    delete menu_controller;
    delete json_config;
    delete engine1;
    delete level_loader;

    return 0;
}
