//
// Created by Rob Hendriks on 08/12/2016.
//

#include "object_deserializer.h"
#include "json_level_loader.h"

namespace services {
    namespace level_loader {

        object_ptr object_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            int id, x, y, width, height;
            id = json.value("id", -1);
            x = json.value("x", -1);
            y = json.value("y", -1);
            width = json.value("width", -1);
            height = json.value("height", -1);

            if (id < 0 || x < 0 || y < 0 || width < 1 || height < 1) {
                SDL_Log("Object has missing or invalid data\n");
                return nullptr;
            }

            x *= json_level_loader::TILE_WIDTH;
            y *= json_level_loader::TILE_HEIGHT;
            width *= json_level_loader::TILE_WIDTH;
            height *= json_level_loader::TILE_HEIGHT;

            auto result = std::make_shared<road>(box2_t{
                static_cast<float>(x), static_cast<float>(y),
                static_cast<float>(x + width), static_cast<float>(x + height)});

            result->set_id(id);
            result->set_max_column(1);
            result->set_max_row(1);

            result->set_draw_settings("mages/road-straight.png");

            return result;
        }

    }
}
