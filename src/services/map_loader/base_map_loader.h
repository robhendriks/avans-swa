//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_BASE_MAP_LOADER_H
#define CITY_DEFENCE_BASE_MAP_LOADER_H

namespace services {
    namespace map_loader {
        class base_map_loader {
        public:
            base_map_loader(std:: location);

        protected:
            std::string location;
        };
    }
}


#endif //CITY_DEFENCE_BASE_MAP_LOADER_H
