//
// Created by te on 10-Nov-16.
//

#ifndef CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H
#define CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H


#include "../../engine/math/box2.hpp"
#include "../../engine/graphics/texture_manager.h"
#include "abstract_drawable_game_object.h"
#include <memory>

namespace domain {
    namespace drawable {
        class drawable_game_object : public abstract_drawable_game_object {
        public:
            drawable_game_object();

            drawable_game_object(const drawable_game_object &obj);

            virtual void set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position = {0, 0});

            // can be overwritten in case you don't want to load the textures of the current object because there is a chance
            // you won't draw them but only of a child object. (if overwritten no call will be made to draw_object)
            virtual void draw(draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

            // override in case something else gets drawn instead of only itself
            virtual void unload(draw_managers_wrapper &draw_managers);

            virtual engine::math::box2_t get_box() const = 0;

            float get_max_row() const;

            void set_max_row(float row);

            float get_max_column() const;

            void set_max_column(float max_column);

            float get_transition() const;

            void set_transition(long transition_time);

            void set_current_column(float column);

            void set_current_row(float row);

        protected:
            SDL_Texture *m_texture;

            std::string m_file_loc;
            std::unique_ptr<engine::math::vec2_t> m_image_start_position;

            // load texture of current object in case its not loaded in yet. (this will fill texture field or give a exception
            void load_texture_if_not_loaded_yet(engine::graphics::texture_manager &texture_manager);

        private:
            // basic implementation is to draw the current object (needs to be overwritten for also drawing children)
            virtual void draw_object(engine::graphics::texture_manager &texture_manager);

            // count based
            float m_max_column = 1;
            float m_max_row = 1;

            long m_transition = 1000;
            unsigned int m_last_transition_time = 0;

            // index based
            float m_current_column = 0;
            float m_current_row = 0;

            virtual void animation(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed);


        };
    }
}

#endif //CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H
