#include "engine/engine.h"
#include "gui/controllers/menu_controller.h"
#include "boost/di.hpp"
#include "config/json_config.h"
#include "utils/string_utils.h"
#include "services/level_loader/json_level_loader.h"

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
    w_config.debug = json_config->get_bool("window.debug", w_config.debug);

    engine::engine_config e_config = { w_config };

    // Create a font_manager with fonts
    auto *font_manager = new engine::graphics::font_manager();
    font_manager->add("fonts/Roboto-Regular.ttf", "roboto");

    /**
     * END OF CONFIG
     */

    std::unique_ptr<engine::engine> engine_ptr{new engine::engine{e_config}};
    engine_ptr->warmup();

    std::shared_ptr<game> game_ptr{new game{*engine_ptr->get_window()}};
    engine_ptr->set_game(game_ptr);

    std::ifstream file("level1.json");
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Unable to open file: ") + "level1.json");
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
            boost::di::bind<>.to(*game_ptr),
            boost::di::bind<>.to(*engine_ptr),
            boost::di::bind<>.to(*engine_ptr->get_texture_manager()),
            boost::di::bind<>.to(*engine_ptr->get_color_manager()),
            boost::di::bind<>.to(*engine_ptr->get_sound_manager()),
            boost::di::bind<>.to(*engine_ptr->get_music_manager()),
            boost::di::bind<>.to(*engine_ptr->get_window()),
            boost::di::bind<>.to(*font_manager),
            boost::di::bind<services::level_loader::base_level_loader>.to(*level_loader)
        );
    };

    // Start with show
    std::shared_ptr<gui::controllers::menu_controller> menu_controller_ptr{
         boost::di::make_injector(di_config()).create<gui::controllers::menu_controller*>()};

    menu_controller_ptr->show();

    // Run the game
    engine_ptr->run();

    // Stop/cooldown the engine
    delete font_manager;
    engine_ptr->cooldown();

    // More cleaning
    delete json_config;
    delete level_loader;

    return 0;
}
