//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/buildings/building.h"

namespace gui {
    namespace controllers {

        main_map_controller::main_map_controller(views::main_map &view, models::main_map_model &model, game &game1) :
            base_controller(game1), m_view(view), m_model(model) {

            view.set_controller(*this);

            // This code should be placed somewhere else
            m_model.tile_height = 32;
            m_model.tile_width = 32;
            auto *domain_map = new domain::map::map(10, 10);
            m_model.tiles = domain_map->get_fields();
            engine::math::box2_t *map = new engine::math::box2_t({{0, 0}, {(float) (10 * m_model.tile_width), (float) (10 * m_model.tile_height)}});
            m_model.map = map;
        }

        void main_map_controller::load(const char *filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + filename);
            }

            SDL_Log("Loading level: %s\n", filename);
            json root;

            try {
                root << file;
            } catch (std::exception &e) {
                // TODO: proper error handling
                throw;
            }

            size_t width = root["width"];
            size_t height = root["height"];

            // Create map model
            models::main_map_model map_model;
            map_model.tile_width = 32;
            map_model.tile_height = 32;
            map_model.map = new engine::math::box2_t{0, 0, (float)(width * map_model.tile_width), (float)(height * map_model.tile_height)};

            load_tiles(root, map_model);
            load_objects(root, map_model);

            // TODO:
        }

        void main_map_controller::load_tiles(json &root, models::main_map_model &map_model) {
            if (root.find("tiles") == root.end()) {
                return;
            }

            json tiles = root["tiles"];
            if (!tiles.is_object()) {
                return;
            }

            size_t tileCount = tiles["count"];
            SDL_Log("Loading %d tile(s)...\n", tileCount);

            json data = tiles["data"];
            if (!data.is_array()) {
                return;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int type = elem["type"];

                SDL_Log("%d %d %d", x, y, type);
                // TODO: moeten we tiles niet eerst aanmaken?
//                map_model.tiles.push_back();
            }
        }

        void main_map_controller::load_objects(json &root, models::main_map_model &map_model) {
            if (root.find("objects") == root.end()) {
                return;
            }

            json level_objects = root["objects"];
            if (!level_objects.is_object()) {
                return;
            }

            size_t level_objects_count = level_objects["count"];
            SDL_Log("Loading %d level objects(s)...\n", level_objects_count);

            json data = level_objects["data"];
            if (!data.is_array()) {
                return;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                SDL_Log("%d %d %d", x, y, rotation);
                // TODO: moeten we gebouw objects niet eerst aanmaken?
                // new level_objects
                // map_model.level_objects.push_back();
                
            }
        }

        void main_map_controller::show() {
            // Draw the view
            view(m_view);
        }

        void main_map_controller::tile_click(domain::map::base_field &tile) {
            engine::math::vec2_t* t = new engine::math::vec2_t(0,0);
            domain::buildings::building* building =  new domain::buildings::building("building_1", "images/building.png", t);
            tile.place(building);

            show();
        }
    }
}
