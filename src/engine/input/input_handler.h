//
// Created by robbie on 22-10-2016.
//

#ifndef CITY_DEFENCE_INPUT_HANDLER_H
#define CITY_DEFENCE_INPUT_HANDLER_H

#include <vector>
#include <set>
#include <functional>
#include "SDL.h"
#include "../observer/observee.h"
#include "../math/vec2.hpp"
#include "keycodes.h"

namespace engine {
    namespace input {
        class input_handler : public observer::observee<input_handler> {
        public:
            static input_handler *get_instance();

            void clean();

            void update(const SDL_Event &event);

            void reset();

            bool is_right_mouse_button_pressed() const;

            bool is_middle_mouse_button_pressed() const;

            bool is_left_mouse_button_pressed() const;

            math::vec2_t *get_mouse_position() const;

            bool is_key_down(SDL_Scancode key) const;

            input_handler(input_handler const &) = delete;

            void operator=(input_handler const &) = delete;

        private:
            input_handler();

            static input_handler *m_instance;

            bool update_states(const SDL_Event &event);

            bool m_right_mouse_button_pressed;
            bool m_middle_mouse_button_pressed;
            bool m_left_mouse_button_pressed;
            math::vec2_t *m_mouse_position;
            const Uint8 *m_key_states;
        };
    }
}

#endif //CITY_DEFENCE_INPUT_HANDLER_H
