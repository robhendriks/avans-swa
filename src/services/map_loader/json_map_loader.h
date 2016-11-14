//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_JSON_MAP_LOADER_H
#define CITY_DEFENCE_JSON_MAP_LOADER_H

#include "base_map_loader.h"
#include "../../config/json_config.h"
namespace services {
    namespace level_loader {
        class json_map_loader : public base_map_loader {
        public:
            json_map_loader();
            domain::gameworld::game_world load(std::string file_location);
            virtual ~json_map_loader();
        private:
            void load_tiles(json &root);
            void load_objects(json &root);
            std::tuple<int, int> get_length_and_width(json &root);
        };
    }
}


#endif //CITY_DEFENCE_JSON_MAP_LOADER_H
