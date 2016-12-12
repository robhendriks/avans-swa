//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_JSON_MAP_LOADER_H
#define CITY_DEFENCE_JSON_MAP_LOADER_H


#include <fstream>
#include <json.hpp>
#include "base_level_loader.h"
#include "../../config/json_config.h"
#include "../../domain/map/map.h"
#include "../../engine/math/vec2.hpp"
#include "../../domain/map/objects/building.h"


using json = nlohmann::json;
using namespace engine::math;

namespace services {
    namespace level_loader {
        class json_level_loader : public base_level_loader {
        public:
            json_level_loader(json root);
            int get_level_count();
            std::unique_ptr<domain::game_level::game_level> load(int id);

        private:
            std::shared_ptr<domain::map::map> load_all_levels(std::string url);

            void load_fields(json &root, domain::map::map &map1);

            void load_objects(json &root, domain::map::map &map1);

            std::vector<std::shared_ptr<domain::nations::nation>> load_nations(std::string nation_url);

            json m_root;
            std::vector<std::shared_ptr<domain::map::objects::building>> vec_building;
            std::vector<std::shared_ptr<domain::nations::nation>> vec_nations;
            std::vector<std::shared_ptr<domain::map::map>> vec_levels;

            std::shared_ptr<domain::map::objects::building> load_buildings(std::string url);


        };
    };
};


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
