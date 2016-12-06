//
// Created by robbie on 5-12-2016.
//

#ifndef CITY_DEFENCE_ENGINE_STATE_CHANGED_H
#define CITY_DEFENCE_ENGINE_STATE_CHANGED_H

#include "../engine.h"

namespace engine {
    namespace events {
        class engine_state_changed {
        public:
            engine_state_changed(state new_state, state old_state);
            state get_new_state() const;
            state get_old_state() const;
        private:
            state m_new_state;
            state m_old_state;
        };
    }
}


#endif //CITY_DEFENCE_ENGINE_STATE_CHANGED_H
