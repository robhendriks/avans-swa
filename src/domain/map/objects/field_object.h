//
// Created by robbie on 22-11-2016.
//

#ifndef CITY_DEFENCE_FIELD_OBJECT_H
#define CITY_DEFENCE_FIELD_OBJECT_H

#include "../../drawable/drawable_game_object.h"
#include "../field.h"
#include "../../game_level/game_stats.h"
#include <memory>

namespace domain {
    namespace map {
        class field;
    }
}

namespace domain {
    namespace map {
        namespace objects {
            class field_object : public virtual drawable::drawable_game_object {
            public:
                field_object();

                field_object(const field_object &obj);

                void set_rotation(int rotation);

                int get_rotation() const;

                void set_field(std::shared_ptr<field> field1);

                std::shared_ptr<field> get_field() const;

                virtual void update_game_stats(domain::game_level::game_stats &game_stats1, std::string action) = 0;

                virtual ~field_object() = default;

            protected:
                int m_rotation;
                std::shared_ptr<field> m_field;
            };
        }
    }
}

#endif //CITY_DEFENCE_FIELD_OBJECT_H
