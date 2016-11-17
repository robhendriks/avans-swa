#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../drawable/abstract_drawable_game_object.h"
#include "../game_level/game_level.h"

namespace domain {
    namespace gameworld {
        class game_world : public domain::drawable::abstract_drawable_game_object{
        public:
            game_world();

            game_world(std::vector<std::shared_ptr<game_level::game_level>>& game_levels);
            void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            void unload(engine::graphics::texture_manager &texture_manager);
            std::shared_ptr<game_level::game_level> get_current_level();
            std::shared_ptr<game_level::game_level> next_level();
            std::shared_ptr<game_level::game_level> reset_level();
            ~game_world();

        private:
            int _current_lvl;
            std::vector<std::shared_ptr<game_level::game_level>> m_levels;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
