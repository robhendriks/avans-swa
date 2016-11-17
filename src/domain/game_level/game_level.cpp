//
// Created by te on 17-Nov-16.
//

#include "game_level.h"
namespace domain{
    namespace  game_level{

        game_level::game_level(std::string &name, domain::map::base_map* map) : m_name(name){
            this->m_map = std::shared_ptr<domain::map::base_map>(map);
        }

        game_level::game_level(std::string &name, std::shared_ptr<map::base_map> map) : m_name(name){
            this->m_map = map;
        }

        std::string game_level::get_name() {
            return this->m_name;
        }

        std::shared_ptr<domain::map::base_map> game_level::get_map() {
            return this->m_map;
        }

        void game_level::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            this->m_map->draw(texture_manager, dest);
        }

        void game_level::unload(engine::graphics::texture_manager &texture_manager) {
            this->m_map->unload(texture_manager);
        }


    }
}