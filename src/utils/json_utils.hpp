//
// Created by Rob Hendriks on 07/12/2016.
//

#ifndef CITY_DEFENCE_JSON_UTILS_HPP
#define CITY_DEFENCE_JSON_UTILS_HPP

#include <fstream>
#include <string>
#include <map>
#include <json.hpp>
#include <any.hpp>

namespace utils {
    namespace json_utils {

        template<typename T>
        class json_deserializer {
        public:
            virtual ~json_deserializer() {
                printf("[dtor] json_deserializer<%s>\n", typeid(T).name());
            }

            virtual T deserialize(const nlohmann::json &json) const = 0;
        };

        template<typename T>
        using json_deserializer_ptr = std::shared_ptr<json_deserializer<T>>;

        using deserializer_map = std::map<std::string, type::any>;

        class json_factory {
        public:
            static json_factory &get() {
                static json_factory instance;
                return instance;
            }

            template<typename T>
            json_factory &register_deserializer(const json_deserializer_ptr<T> &deserializer) {
                m_map.emplace(typeid(T).name(), deserializer);
                return *this;
            }

            template<typename T>
            T deserialize(const nlohmann::json &json) const {
                auto type_name = typeid(T).name();

                deserializer_map::const_iterator it;
                if ((it = m_map.find(type_name)) == m_map.cend()) {
                    throw std::runtime_error(std::string("No deserializers found for type ") + type_name);
                }

                auto &ptr = it->second.as<json_deserializer_ptr<T>>();
                return ptr->deserialize(json);
            }

        private:
            json_factory() = default;

            ~json_factory() = default;

            json_factory(const json_factory &) = delete;

            json_factory &operator=(const json_factory &) = delete;

            deserializer_map m_map;
        };

        template<typename T>
        static inline T json_deserialize(const nlohmann::json &json) {
            return json_factory::get().deserialize<T>(json);
        }

        template<typename T>
        static inline T json_deserialize_file(const std::string &filename) {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit);

            try {
                file.open(filename);
                nlohmann::json json;
                file >> json;

                return json_deserialize<T>(json);
            } catch (const std::exception &e) {
                // TODO: maybe set a custom message?
                throw;
            }
        }
    }
}

#endif //CITY_DEFENCE_JSON_UTILS_HPP
