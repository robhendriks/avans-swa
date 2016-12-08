#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"
#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            building::building(engine::math::box2_t box, int hitpoints) : dragable_field_object(box), domain::combat::defender(hitpoints, 0) {}

            building::building(std::shared_ptr<field> field1, int hitpoints) : dragable_field_object(field1), domain::combat::defender(hitpoints, 0) {}

            building::building(const building &obj, int hitpoints) : dragable_field_object(obj), domain::combat::defender(hitpoints, 0) {}

            /**
             * Make sure a building can only be placed next to a road object
             *
             * @param field1
             * @return
             */
            bool building::can_place_on(field &field1) const {
                for (auto &neighbor : field1.get_neighbors()) {
                    if (neighbor->has_object() && dynamic_cast<road*>(neighbor->get_object())) {
                        return true;
                    }
                }

                return false;
            }

            dragable_field_object *building::clone() const {
                return new building(*this);


            }
            std::vector<std::shared_ptr<domain::resources::resource>> building::get_required_resources() {
                return required_resources;
            }

            void building::set_required_resource(std::vector<std::shared_ptr<domain::resources::resource>> resources){
                required_resources = resources;
            }


            void building::update(domain::game_level::game_level game_level){

            }


            void building::update_game_stats(domain::game_level::game_stats &game_stats1) {
                game_stats1.increase("buildings");
            }

            building::building(const engine::math::box2_t &box, const std::string &id, int hitpoints,
                               double health_ragen, const std::string &name,
                               const std::vector<std::shared_ptr<resources::resource>> &required_resources
                               )
                : dragable_field_object(box), domain::combat::defender(hitpoints, 0), id(id), health_ragen(health_ragen), name(name),
                  required_resources(required_resources){}

            int building::lower_hitpoints(int by) {
                SDL_Log("%d", get_hp());
                int result = domain::combat::defender::lower_hitpoints(by);
                if (result == 0) {
                    notify_observers(this, "object-destroyed");
                }
                return result;
            }



            void building::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
                dragable_field_object::draw(draw_managers, time_elapsed);
            }

            void building::set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position) {
                dragable_field_object::set_draw_settings(file_loc, image_start_position);
            }

            void building::set_box(std::shared_ptr<engine::math::box2_t> box) {
                dragable_field_object::set_box(box);
            }

            engine::math::box2_t building::get_box() const {
                return dragable_field_object::get_box();
            }
        }

    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
