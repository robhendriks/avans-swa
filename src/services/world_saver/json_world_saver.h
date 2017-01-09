//
// Created by robbie on 8-1-2017.
//

#ifndef CITY_DEFENCE_JSON_WORLD_SAVER_H
#define CITY_DEFENCE_JSON_WORLD_SAVER_H

#include <json.hpp>
#include "base_world_saver.h"
#include "../../data/json/save_games_json_repository.h"

namespace services {
    namespace world_saver {
        class json_world_saver : public base_world_saver {
        public:
            json_world_saver(data::json::save_games_json_repository &save_games_json_repository);

            void save(domain::gameworld::game_world &world);

            nlohmann::json level_to_json(domain::game_level::game_level &level, bool played);

        private:
            data::json::save_games_json_repository &m_save_games_json_repository;
        };
    }
}


#endif //CITY_DEFENCE_JSON_WORLD_SAVER_H
