#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "config/json_config.h"
#include "utils/string_utils.h"
#include "listeners/play_sound_when_object_is_placed_on_field.h"
#include "listeners/play_sound_when_object_cannot_be_placed_on_field.h"
#include "services/map_loader/json_map_loader.h"

int main(int argc, char *argv[]) {
    /**
     * CONFIG
     */
    auto *json_config = new config::json_config("config.json");
    json_config->load();

    engine::window_config w_config = {
        json_config->get_string("engine.title"),
        engine::graphics::color4_t(utils::string_utils::hex_to_long(json_config->get_string("window.background_color")))
    };

    w_config.w = json_config->get_int("window.width", 1024);
    w_config.h = json_config->get_int("window.height", 768);

    engine::engine_config e_config = { w_config };
    /**
     * END OF CONFIG
     */

    // Get the engine
    engine::engine *engine1 = new engine::engine(e_config);
    engine1->warmup();

    // Create the ioc container
    auto *game1 = new game();

    services::level_loader::json_map_loader *load_map_service = new services::level_loader::json_map_loader();

    auto di_config = [&]() {
        return boost::di::make_injector(
            boost::di::bind<>.to(*game1),
            boost::di::bind<>.to(*engine1),
            boost::di::bind<>.to(*engine1->get_texture_manager()),
            boost::di::bind<>.to(*engine1->get_color_manager()),
            boost::di::bind<>.to(*engine1->get_sound_manager()),
            boost::di::bind<>.to(*engine1->get_music_manager()),
            boost::di::bind<>.to(*engine1->get_window()),
            boost::di::bind<services::level_loader::base_map_loader>.to(*load_map_service)
        );
    };

    /**
     *  ADD SUBSCRIBERS
     */
    auto &eventbus = engine::eventbus::eventbus::get_instance();

    // Subscribe the game to the window cleared event
    eventbus.subscribe(game1);

    // Subscribe sound to object placed event
    auto placed_injector = boost::di::make_injector(boost::di::bind<std::string>.to("sounds/pop.wav"), di_config());
    auto *placed_subscriber = placed_injector.create<listeners::play_sound_when_object_is_placed_on_field*>();
    eventbus.subscribe(placed_subscriber);

    // Subscribe sound to object cannot be placed event
    auto cannot_placed_injector = boost::di::make_injector(boost::di::bind<std::string>.to("sounds/error.wav"), di_config());
    auto *cannot_placed_subscriber = cannot_placed_injector.create<listeners::play_sound_when_object_cannot_be_placed_on_field*>();
    eventbus.subscribe(cannot_placed_subscriber);
    /**
     * END OF SUBSCRIBERS REGISTRY
     */

    // Start with show
    gui::controllers::menu_controller* menu_controller = boost::di::make_injector(di_config()).create<gui::controllers::menu_controller*>();
    menu_controller->show();

    // Run the game
    engine1->run();

    // Clean
    delete placed_subscriber;
    delete cannot_placed_subscriber;

    // Stop/cooldown the engine
    engine1->cooldown();

    // More cleaning
    delete game1;
    delete menu_controller;
    delete json_config;
    delete engine1;
    delete load_map_service;

    return 0;
}
