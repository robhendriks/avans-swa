//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_JSON_MAP_LOADER_H
#define CITY_DEFENCE_JSON_MAP_LOADER_H

#include <iostream>
#include <fstream>
#include <json.hpp>
#include "base_level_loader.h"
#include "../../utils/json_utils.hpp"
#include "../../config/json_config.h"
#include "../../domain/map/map.h"
#include "../../engine/math/vec2.hpp"
#include "../../domain/map/objects/building.h"
#include "../../domain/map/objects/road.h"
#include "../../domain/map/objects/defensive_building.h"
#include "../../domain/map/objects/economic_building.h"
#include "nation_deserializer.h"
#include "nations_deserializer.h"

using json = nlohmann::json;
using namespace engine::math;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        typedef std::shared_ptr<domain::map::map> map_ptr;
        typedef std::shared_ptr<domain::map::objects::building> building_ptr;

        class json_level_loader : public base_level_loader {
        public:
            static const int TILE_WIDTH;
            static const int TILE_HEIGHT;

            json_level_loader(json root);

            std::unique_ptr<domain::game_level::game_level> load();

        private:
            template<typename T>
            bool load(const std::string &filename, T &obj);

            map_ptr load_all_levels(std::string filename);

            void load_fields(json &root, domain::map::map &map1);

            void load_objects(json &root, domain::map::map &map1);

            json m_root;
            std::vector<building_ptr> m_buildings;
            std::vector<nation_ptr> m_nations;
            std::vector<map_ptr> m_maps;
            bool m_nations_loaded;
            bool m_buildings_loaded;
        };

    };
};


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
