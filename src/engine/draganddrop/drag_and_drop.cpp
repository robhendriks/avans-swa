//
// Created by robbie on 17-11-2016.
//

#include "drag_and_drop.h"

namespace engine {
    namespace draganddrop {
        drag_and_drop::drag_and_drop(bool select_and_drop) : m_dragging(nullptr), m_next_dragging(nullptr),
                                                             m_select_and_drop(select_and_drop),
                                                             m_started(false), m_mouse_position_on_select(nullptr) {

            // Add self as subscriber on the eventbus
            eventbus::eventbus::get_instance().subscribe((eventbus::subscriber<events::mouse_button_down<input::mouse_buttons::LEFT>>*) this);
            eventbus::eventbus::get_instance().subscribe((eventbus::subscriber<events::mouse_button_up<input::mouse_buttons::LEFT>>*) this);
            eventbus::eventbus::get_instance().subscribe((eventbus::subscriber<events::mouse_motion>*) this);
        }

        drag_and_drop::~drag_and_drop() {
            // Unsubscribe self on eventbus
            eventbus::eventbus::get_instance().unsubscribe((eventbus::subscriber<events::mouse_button_down<input::mouse_buttons::LEFT>>*)this);
            eventbus::eventbus::get_instance().unsubscribe((eventbus::subscriber<events::mouse_button_up<input::mouse_buttons::LEFT>>*) this);
            eventbus::eventbus::get_instance().unsubscribe((eventbus::subscriber<events::mouse_motion>*) this);
        }

        void drag_and_drop::add_dragable(dragable &dragable1) {
            dragable1.set_drag_and_drop(this);
            m_dragables.push_back(&dragable1);
        }

        void drag_and_drop::add_dropable(dropable &dropable1) {
            dropable1.set_drag_and_drop(this);
            m_dropables.push_back(&dropable1);
        }

        void drag_and_drop::remove_dragable(dragable *dragable1) {
            m_dragables.erase(std::remove(m_dragables.begin(), m_dragables.end(), dragable1), m_dragables.end());
        }

        void drag_and_drop::remove_dropable(dropable *dropable1) {
            m_dropables.erase(std::remove(m_dropables.begin(), m_dropables.end(), dropable1), m_dropables.end());
        }

        bool drag_and_drop::set_dragging(dragable &dragable1, bool force) {
            if (m_dragging == nullptr || force) {
                if (m_dragging != nullptr) {
                    // Stop current dragging
                    m_dragging->not_dropped();
                }

                // Set the new dragging object
                m_dragging = &dragable1;

                return true;
            }

            return false;
        }

        void drag_and_drop::set_next_dragging(dragable &dragable1) {
            m_next_dragging = &dragable1;
        }

        void drag_and_drop::on_event(events::mouse_button_down<input::mouse_buttons::LEFT> &event) {
            if (m_started) {
                // Check if there is not already something dragging
                if (m_dragging == nullptr) {
                    // Get the mouse position
                    math::vec2_t *position = input::input_handler::get_instance()->get_mouse_position();
                    // Check if the mouse position is on dragables objects
                    for (auto &dragable : m_dragables) {
                        if (dragable->get_box().contains(*position)) {
                            // Set as dragging
                            m_dragging = dragable;
                            m_mouse_position_on_select = new math::vec2_t(*position);
                            return;
                        }
                    }
                }
            }
        }

        void drag_and_drop::on_event(events::mouse_motion &event) {
            if (m_started) {
                if (m_dragging != nullptr) {
                    // Notify the dragging object we are dragging
                    m_dragging->on_drag(event.get_mouse_position());
                }
            }
        }

        void drag_and_drop::on_event(events::mouse_button_up<input::mouse_buttons::LEFT> &event) {
            if (m_started) {
                // Check if there is a dragging object
                if (m_dragging != nullptr) {
                    // Get the mouse position
                    math::vec2_t *position = input::input_handler::get_instance()->get_mouse_position();
                    // Check if the mouse position is on a dropable object
                    for (auto &dropable : m_dropables) {
                        // This is needed because the dropable can be deleted by one of the call functions
                        auto *save_drop = dropable;
                        if (save_drop->get_box().contains(*position)) {
                            // Try to drop the dragging objects
                            if (save_drop->drop(m_dragging)) {
                                // Stop dragging
                                auto *temp = m_dragging;
                                m_dragging = nullptr;

                                delete m_mouse_position_on_select;
                                m_mouse_position_on_select = nullptr;

                                // Let the object know it's dropped
                                temp->on_drop(save_drop);

                                // Call callbacks
                                for (auto callback : m_callbacks) {
                                    callback(*temp);
                                }

                                // Check for next dragging
                                if (m_next_dragging != nullptr) {
                                    m_dragging = m_next_dragging;
                                    m_next_dragging = nullptr;
                                }

                                // Stop loop
                                return;
                            }
                        }
                    }

                    // When this is reached, the dragging object is not dropped on a dropable
                    if (m_select_and_drop && m_mouse_position_on_select && *m_mouse_position_on_select == *position) {
                        // When select and drop is on and the mouse position is still the same
                        // just ignore this mouse button up
                    } else {
                        // Stop dragging
                        m_dragging->not_dropped();
                        m_dragging = nullptr;
                    }
                }
            }
        }

        void drag_and_drop::start() {
            if (!m_started) {
                m_started = true;
            }
        }

        void drag_and_drop::stop() {
            if (m_started) {
                m_started = false;
            }
        }

        void drag_and_drop::add_on_drop_callback(std::function<void(dragable&)> callback) {
            m_callbacks.push_back(callback);
        }

        bool drag_and_drop::is_dragging() const {
            return m_dragging != nullptr;
        }

        bool drag_and_drop::is_dragging(const dragable *dragable1) const {
            return m_dragging == dragable1;
        }
    }
}
