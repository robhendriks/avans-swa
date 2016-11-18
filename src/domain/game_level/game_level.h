//
// Created by te on 17-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_LEVEL_H
#define CITY_DEFENCE_GAME_LEVEL_H
#include "string"
#include "../map/base_map.h"
#include <memory>

namespace domain{
    namespace  game_level{
        class game_level : public drawable::abstract_drawable_game_object{
        public:
            game_level(std::string &name, map::base_map *map);
            game_level(std::string &name, std::shared_ptr<map::base_map> map);
            std::string get_name();
            std::shared_ptr<domain::map::base_map> get_map();
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            virtual void unload(engine::graphics::texture_manager &texture_manager);
        private:
            std::string& m_name;
            std::shared_ptr<domain::map::base_map> m_map;
        };
    }
}

#endif //CITY_DEFENCE_GAME_LEVEL_H
