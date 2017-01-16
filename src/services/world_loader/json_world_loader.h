//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_JSON_MAP_LOADER_H
#define CITY_DEFENCE_JSON_MAP_LOADER_H


#include <fstream>
#include <json.hpp>
#include "base_world_loader.h"
#include "../../config/json_config.h"
#include "../../domain/map/map.h"
#include "../../engine/math/vec2.hpp"
#include "../../domain/map/objects/building.h"


using json = nlohmann::json;
using namespace engine::math;

namespace services {
    namespace world_loader {
        class json_world_loader : public base_world_loader {
        public:

            domain::gameworld::game_world* load(std::string file);

            ~json_world_loader();

        private:
            domain::game_level::game_level* load_level(std::string url);

            void load_fields(json &root, domain::map::map &map1);

            void load_objects(json &root, domain::map::map &map1);

            std::vector<domain::nations::nation*> load_nations(std::string nation_url);

            json m_root;
            std::vector<domain::map::objects::building*> vec_building;
            std::vector<domain::nations::nation*> vec_nations;
            std::vector<domain::game_level::game_level*> vec_levels;

            domain::map::objects::building* load_buildings(std::string url);
        };
    };
};


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
