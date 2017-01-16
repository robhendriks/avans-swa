#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"
#include "../field.h"
#include "../../resources/resource.h"
#include "../../game_level/game_level.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public dragable_field_object, public domain::combat::defender,
                             public engine::eventbus::subscriber<engine::events::mouse_motion> {
            public:
                building(const engine::math::box2_t &box, const std::string &id, int hitpoints, double health_ragen,
                         const std::string &name,
                         const std::vector<resources::resource*> &required_resources);

                building(field &field1, const std::string &id, int hitpoints, double health_ragen,
                         const std::string &name,
                         const std::vector<resources::resource*> &required_resources);

                // Copy constructor
                building(const building &obj);

                ~building();

                dragable_field_object *clone() const;

                bool can_place_on(field &field1) const;

                std::vector<domain::resources::resource*> get_required_resources();

                virtual void update_game_stats(domain::game_level::game_stats &game_stats1, std::string action);

                virtual void update(domain::game_level::game_level &game_level);

                virtual int lower_hitpoints(int points);

                virtual void draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

                virtual void set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position = {0, 0});

                virtual void set_box(engine::math::box2_t box);

                virtual engine::math::box2_t get_box() const;

                void on_event(engine::events::mouse_motion &event);

                std::string get_id() const;

            protected:
                std::string id;
                double health_ragen;
                std::string name;
                std::vector<domain::resources::resource*> required_resources;
                bool show_hover_info;
            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
