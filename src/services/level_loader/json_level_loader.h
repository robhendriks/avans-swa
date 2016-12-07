//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_JSON_MAP_LOADER_H
#define CITY_DEFENCE_JSON_MAP_LOADER_H

#include <iostream>
#include <fstream>
#include <json.hpp>
#include "base_level_loader.h"
#include "../../config/json_config.h"
#include "../../domain/map/map.h"
#include "../../engine/math/vec2.hpp"
#include "../../domain/map/objects/building.h"
#include "../../domain/map/objects/road.h"
#include "../../domain/map/objects/defensive_building.h"
#include "../../domain/map/objects/economic_building.h"

using json = nlohmann::json;
using namespace engine::math;

namespace services {
    namespace level_loader {

        typedef std::shared_ptr<domain::map::map> map_ptr;
        typedef std::shared_ptr<domain::nations::nation> nation_ptr;
        typedef std::shared_ptr<domain::map::objects::building> building_ptr;

        class json_level_loader : public base_level_loader {
        public:
            static const int TILE_WIDTH;
            static const int TILE_HEIGHT;

            json_level_loader(json root);

            std::unique_ptr<domain::game_level::game_level> load();

        private:
            map_ptr load_all_levels(std::string url);

            void load_fields(json &root, domain::map::map &map1);

            void load_objects(json &root, domain::map::map &map1);

            std::vector<nation_ptr> load_nations(std::string nation_url);

            std::shared_ptr<domain::map::objects::building> load_buildings(std::string url);

            json m_root;
            std::vector<building_ptr> vec_building;
            std::vector<nation_ptr> vec_nations;
            std::vector<map_ptr> vec_levels;
        };

    };
};


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
