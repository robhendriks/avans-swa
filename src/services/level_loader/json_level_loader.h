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
#include "../../domain/map/map.h"
#include "nations_deserializer.h"
#include "buildings_deserializer.h"
#include "map_deserializer.h"

using json = nlohmann::json;
using namespace engine::math;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using map_ptr_vector = std::vector<map_ptr>;

        class json_level_loader : public base_level_loader {
        public:
            static const int TILE_WIDTH;
            static const int TILE_HEIGHT;

            json_level_loader(json root);

            std::unique_ptr<domain::game_level::game_level> load();

        private:
            template<typename T>
            bool load(const std::string &filename, T &obj);

            json m_root;
            building_ptr_vector m_buildings;
            nation_ptr_vector m_nations;
            map_ptr_vector m_maps;
        };

    };
};


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
