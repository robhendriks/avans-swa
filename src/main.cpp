#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "config/json_config.h"
#include "utils/string_utils.h"
#include "gui/views/main_map.h"
#include "gui/controllers/main_map_controller.h"
#include "listeners/play_sound_when_object_is_placed_on_field.h"
#include "listeners/play_sound_when_object_cannot_be_placed_on_field.h"

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

    w_config.w = json_config->get_int("window.width", w_config.w);
    w_config.h = json_config->get_int("window.height", w_config.h);

    engine::engine_config e_config = { w_config };
    /**
     * END OF CONFIG
     */

    // Get the engine
    engine::engine *engine1 = new engine::engine(e_config);
    engine1->warmup();

    // Create the ioc container
    auto *texture_manager = engine1->get_texture_manager();
    auto *color_manager = engine1->get_color_manager();
    auto *sound_manager = engine1->get_sound_manager();
    auto *music_manager = engine1->get_music_manager();
    auto *window = engine1->get_window();
    auto *game1 = new game();

    auto di_config = [&]() {
        return boost::di::make_injector(
            boost::di::bind<>.to(*game1),
            boost::di::bind<>.to(*engine1),
            boost::di::bind<>.to(*texture_manager),
            boost::di::bind<>.to(*sound_manager),
            boost::di::bind<>.to(*window)
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
    eventbus.subscribe(&placed_injector.create<listeners::play_sound_when_object_is_placed_on_field&>());

    // Subscribe sound to object cannot be placed event
    auto cannot_placed_injector = boost::di::make_injector(boost::di::bind<std::string>.to("sounds/error.wav"), di_config());
    eventbus.subscribe(&cannot_placed_injector.create<listeners::play_sound_when_object_cannot_be_placed_on_field&>());
    /**
     * END OF SUBSCRIBERS REGISTRY
     */

    // Start with show
    auto *menu_controller = boost::di::make_injector(di_config()).create<gui::controllers::menu_controller*>();
    menu_controller->show();

    // Run the game
    engine1->run();

    // Clean
    delete sound_manager;
    delete music_manager;
    delete game1;
    delete menu_controller;
    delete json_config;
    delete texture_manager;
    delete color_manager;
    delete window;
    delete engine1;

    return 0;
}
