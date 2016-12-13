//
// Created by Rob Hendriks on 08/12/2016.
//

#include "field_deserializer.h"
#include "json_level_loader.h"

namespace services {
    namespace level_loader {

        field_ptr field_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            int id, x, y, object_id;
            bool immutable;

            id = json.value("id", -1);
            x = json.value("x", -1);
            y = json.value("y", -1);
            object_id = json.value("object", -1);
            immutable = json.value("immutable", false);

            if (id < 0 || x < 0 || y < 0) {
                SDL_Log("Field has missing or invalid data\n");
                return nullptr;
            }

            int img_row, img_col;
            img_row = id / 17;
            img_col = id % 17;

            auto img_pos = vec2_t{
                static_cast<float>(img_col * json_level_loader::TILE_WIDTH),
                static_cast<float>(img_row * json_level_loader::TILE_HEIGHT)};

            auto result = std::make_shared<field>(vec2_t{static_cast<float>(x), static_cast<float>(y)});
            result->set_draw_settings("images/tileset.png", img_pos);

            if (object_id > -1) {
                result->set_object_id(object_id);
            }

            return result;
        }

    }
}
