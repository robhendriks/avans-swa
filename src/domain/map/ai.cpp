//
// Created by Bert on 7-12-2016.
//

#include "ai.h"
#include "objects/road.h"
#include "objects/building.h"

namespace domain {
    namespace map {
        domain::map::ai::ai() {

        }

        std::shared_ptr<field> ai::get_next_field(std::shared_ptr<field> current_field) {
            if(current_field == nullptr)
                return nullptr;
            else{
                auto neighbours = current_field->get_neighbors();
                for(auto &neighbour : neighbours)
                {
                    auto object = neighbour->get_object();
                    //first check if building exist near road
                    auto b = dynamic_cast<domain::map::objects::building*>(object);
                    if(b != nullptr)
                    {
                        //TODO attack function, don't move further
                        //return current_field;
                    }
                    //check of it's type is a road
                    auto r = dynamic_cast<domain::map::objects::road*>(object);
                    if(r != nullptr)
                    {
                        //if weight is less or equal, return first neighbour
                        if(current_field->get_weight() <= neighbour->get_weight() )
                        {
                            //TODO: check which neighbour, now its the first
                            return neighbour;
                        }
                    }
                }
                return current_field;
            }
        }

        std::shared_ptr<field> ai::get_spawn_point(std::shared_ptr<map> current_map) {
            if(current_map != nullptr)
            {
                auto spawn_point = std::shared_ptr<field>();

                auto fields = current_map->get_fields_with_objects();
                for(auto &field : fields)
                {
                    //if I can dynamic cast it to road, it's a road and a valid spawn point
                    auto road = dynamic_cast<domain::map::objects::road*>(field.get()->get_object());
                    if(road != nullptr)
                    {
                        spawn_point = field;
                        break;
                    }
                }
                return spawn_point;
            }
            else
            {
                return nullptr;
            }
        }

        std::shared_ptr<field> ai::move(std::shared_ptr<map> current_map, int times) {
            auto next_field = get_next_field(get_spawn_point(current_map));
            //hardcoded for moving over path
            for(int i = 25; i >= 0; i--)
            {
                next_field = get_next_field(next_field);
            }
            return next_field;
        }


    }
}
