//
// Created by Rob Hendriks on 08/12/2016.
//

#include "map_deserializer.h"

namespace services {
    namespace level_loader {

        map_ptr map_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            std::string id, title, description;
            int width, height;

            id = json.value("id", "");
            title = json.value("title", "");
            description = json.value("description", "");
            width = json.value("width", -1);
            height = json.value("height", -1);

            if (id.empty() || title.empty() ||
                width < 8 || width > 64 || height < 8 || height > 64) {
                SDL_Log("Map has missing or invalid data\n");
                return nullptr;
            }

            SDL_Log("Loading map %s...\n", title.c_str());

            auto result = std::make_shared<map>(
                vec2_t{static_cast<float>(width),
                       static_cast<float>(height)},
                vec2_t{static_cast<float>(64),
                       static_cast<float>(64)});

            // Load fields
            field_ptr_vector fields;
            if (json.find("tiles") != json.end())
                fields = json_deserialize<field_ptr_vector>(json["tiles"]);

            for (auto &field : fields) {
                result->add_field(field);
                field->set_map(result);
            }

            // Load objects
            object_ptr_vector objects;
            if (json.find("objects") != json.end())
                objects = json_deserialize<object_ptr_vector>(json["objects"]);

            /*fields.front()->place_object(objects.front());*/
            // TODO: SMart Pointers!!!!

            // TODO: stuff with objects

            return result;
        }

    }
}
