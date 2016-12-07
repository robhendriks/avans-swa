//
// Created by Mark on 21-11-2016.
//

#ifndef CITY_DEFENCE_WAVEGENERATOR_H
#define CITY_DEFENCE_WAVEGENERATOR_H

#include "../../domain/nations/enemy.h"
#include "../../domain/nations/nation.h"
#include <memory>
#include <utility>

namespace domain{
    namespace map{
        namespace ai{
            class ai;
        }
    }
}

namespace services {
    namespace wave{
        class wavegenerator {

        public:
            wavegenerator(std::shared_ptr<domain::map::ai::ai> ai);

            //INPUT PARAMS FOR PROPER GENERATION
            //(REQUIRED) 1. The time in seconds over which the enemies should be generated on the map
            //(REQUIRED) 2. The total amount of enemies oppertunity you want
            //(REQUIRED) 3. The nation of which you want the enemies to be created

            //(optional) 4. The way the enemies spread over time, false means all equally spread, true more at the same thime. Default value is 25
            //(optional) 5. Force enemies startiner at the given oppertunity costs not to spawn, 0 is off. Default is 0.
            //(optional) 6. Force bosses not to spawn. Default is false.
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> generateEnemies(int _time, int _oppertunity, domain::nations::nation _nation, bool _spread = false ,int capoppertunity = 0,bool _noboss = false);
            //RETURNS
            //Pair values
            //First is time mililseconds the enemy should be spawned relative to last one
            //Second is a pointer to the enemy domain object
            std::shared_ptr<domain::map::ai::ai> get_ai();
            ~wavegenerator();
        private:
            std::shared_ptr<domain::map::ai::ai> m_ai;
        };
    }
}

#endif //CITY_DEFENCE_WAVEGENERATOR_H
