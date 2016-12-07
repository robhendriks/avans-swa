//
// Created by Bert on 7-12-2016.
//

#include "ai.h"
#include "objects/road.h"
#include "objects/building.h"
#include "../nations/enemy.h"

namespace domain {
    namespace map {
        domain::map::ai::ai() {
            m_unit = nullptr;
            m_map = nullptr;
        }

        domain::map::ai::ai(std::shared_ptr<map> current_map, std::shared_ptr<domain::nation::enemy> unit) {
            m_map = current_map;
            m_current_field = get_spawn_point();
            m_unit = unit;
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

        std::shared_ptr<field> ai::get_spawn_point() {
            if(m_map != nullptr)
            {
                auto spawn_point = std::shared_ptr<field>();

                auto fields = m_map->get_fields_with_objects();
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

        std::shared_ptr<field> ai::move(unsigned int elapsed_time) {
            if(static_cast<int>(elapsed_time) - static_cast<int>(m_last_movement_time) > m_movement_time) {
                m_next_field = get_next_field(m_next_field);
                m_last_movement_time = elapsed_time;
            }
            return m_next_field;
        }

        bool ai::is_initialised() const {
            return m_map != nullptr && m_unit != nullptr;
        }

        void ai::set_map(std::shared_ptr<map> map) {
            m_map = map;
            m_current_field = get_spawn_point();
        }

        void ai::set_unit(std::shared_ptr<domain::nation::enemy> unit) {
            m_unit = unit;
        }

    }
}
