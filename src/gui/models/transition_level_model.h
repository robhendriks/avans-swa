//
// Created by te on 19-Nov-16.
//

#ifndef CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
#define CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
namespace gui {
    namespace models {
        struct transition_level_model {
            transition_level_model() {};
            bool result;
            bool next_lvl_exists;
            unsigned int duration;
        };
    }
}
#endif //CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
