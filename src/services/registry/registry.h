//
// Created by robbie on 4-11-2016.
//

#ifndef CITY_DEFENCE_REGISTRY_H
#define CITY_DEFENCE_REGISTRY_H

#include <string>
#include <functional>
#include <map>

namespace services {
    namespace registry {
        template<typename T>
        class registry {
        public:
            void add(std::string name, std::function<T *()> f) {
                m_registry[name] = f;
            }

            T *resolve(std::string name) {
                if (m_registry.find(name) != m_registry.end()) {
                    return m_registry[name]();
                }

                return nullptr;
            }

        private:
            std::map<std::string, std::function<T *()>> m_registry;
        };
    }
}

#endif //CITY_DEFENCE_REGISTRY_H
