//
// Created by Rob Hendriks on 08/12/2016.
//

#include "map_deserializer.h"
#include "json_level_loader.h"

namespace services {
    namespace level_loader {

        map_ptr map_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            std::string id, title, description;
            int width, height, duration;

            id = json.value("id", "");
            title = json.value("title", "");
            description = json.value("description", "");
            width = json.value("width", -1);
            height = json.value("height", -1);
            duration = json.value("duration", -1);

            if (id.empty() || title.empty() || width < 8 || width > 64 || height < 8 || height > 64 ||
                duration < 60000) {
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

            // Load objects
            object_ptr_vector objects;
            if (json.find("objects") != json.end())
                objects = json_deserialize<object_ptr_vector>(json["objects"]);

            for (auto &field : fields) {
                result->add_field(field);
                field->set_map(result);

                if (field->get_object_id() == -1)
                    continue;

                for (auto &object : objects) {
                    if (object->get_id() == field->get_object_id()) {
//                        field->place_object(object.get());
                        break;
                    }
                }
            }


            // Load goals
            std::map<std::string, int> goals;
            if (json.find("goals") != json.end()) {
                nlohmann::json obj = json["goals"];
                nlohmann::json::iterator it = obj.begin();

                for (; it != obj.end(); ++it)
                    goals[it.key()] = obj.value(it.key(), -1);
            }

            // Create metadata object
            auto meta = std::make_shared<map_metadata>();
            meta->id = id;
            meta->title = title;
            meta->description = description;
            meta->duration = duration;
            meta->goals = goals;
            result->set_meta(meta);

            return result;
        }

    }
}
