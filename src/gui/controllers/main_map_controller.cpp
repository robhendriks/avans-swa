//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
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

                // Draw the view
                view.draw();
            }
        }
    }
}