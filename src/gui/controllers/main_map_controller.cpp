//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/map/passable_field.h"
#include "../../domain/buildings/building.h"

namespace gui {
    namespace controllers {
        void main_map_controller::show(int call, views::main_map &view) {
            if (call > 0) {
                // Last call, unsubscribe
                view.after_last_draw();
            } else {
                if (call < 0) {
                    // First call, subscribe on eventbus
                    view.before_first_draw();
                }
                models::main_map_model d = models::main_map_model();
                // Draw the view
                view.draw(d);
            }
        }

        bool main_map_controller::click_tile(domain::map::base_field& f){
            try{
                domain::map::passable_field& p = (domain::map::passable_field&) f;
                p.set_placed_object(domain::buildings::building());
                SDL_Log("BUILDING PLACED!");
            }
            catch(std::exception e){
                SDL_Log(e.what());
                return false;
            }
            return true;
        }
    }
}