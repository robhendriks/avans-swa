//
// Created by robbie on 17-11-2016.
//

#ifndef CITY_DEFENCE_DRAG_AND_DROP_H
#define CITY_DEFENCE_DRAG_AND_DROP_H

#include <vector>
#include "dragable.h"
#include "dropable.h"
#include "../../engine/input/mouse_buttons.h"
#include "../events/mouse_button_down.h"
#include "../eventbus/subscriber.h"
#include "../events/mouse_button_up.h"
#include "../events/mouse_motion.h"
#include "../eventbus/eventbus.h"
#include "../input/input_handler.h"
#include "../events/engine_state_changed.h"

namespace engine {
    namespace draganddrop {
        class dragable;
    }
}

namespace engine {
    namespace draganddrop {
        class dropable;
    }
}

namespace engine {
    namespace draganddrop {
        class drag_and_drop : eventbus::subscriber<events::mouse_button_down<input::mouse_buttons::LEFT>>,
                              eventbus::subscriber<events::mouse_button_up<input::mouse_buttons::LEFT>>,
                              eventbus::subscriber<events::mouse_motion> {
        public:
            drag_and_drop(bool select_and_drop = true);

            ~drag_and_drop();

            void add_dragable(dragable &dragable1);

            void remove_dragable(dragable *dragable1);

            void add_dropable(dropable &dropable1);

            void remove_dropable(dropable *dropable1);

            void on_event(events::mouse_button_down<input::mouse_buttons::LEFT> &event);

            void on_event(events::mouse_motion &event);

            void on_event(events::mouse_button_up<input::mouse_buttons::LEFT> &event);

            bool set_dragging(dragable &dragable1, bool force = false);

            void set_next_dragging(dragable &dragable1);

            void start();

            void stop();

            void add_on_drop_callback(std::function<void(dragable&)> callback);

        private:
            std::vector<dragable*> m_dragables;
            dragable* m_dragging;
            dragable* m_next_dragging;
            std::vector<dropable*> m_dropables;

            bool m_select_and_drop;
            bool m_started;
            math::vec2_t *m_mouse_position_on_select;

            std::vector<std::function<void(dragable&)>> m_callbacks;
        };
    }
}


#endif //CITY_DEFENCE_DRAG_AND_DROP_H
