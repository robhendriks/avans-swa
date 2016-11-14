//
// Created by robbie on 24-10-2016.
//

#ifndef CITY_DEFENCE_JSON_REPOSITORY_H
#define CITY_DEFENCE_JSON_REPOSITORY_H

#include <vector>
#include <map>
#include "json.hpp"
#include <fstream>
#include "../repository.h"

namespace data {
    namespace json {
        template<typename K, typename V>
        class json_repository : public repository<K, V> {
        public:
            void load() {
                // Make sure the map is empty
                m_map.clear();

                // Fill the map
                std::ifstream file(get_file_location());
                std::string json_string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
                try {
                    // Parse the string
                    nlohmann::json j = nlohmann::json::parse(json_string);

                    // Loop through each json object, and add it to the vector
                    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
                        V* obj = create_from_json(it.value().dump());
                        if (obj != nullptr) {
                            m_map[get_key(*obj)] = obj;
                        }
                    }
                } catch (...) {
                    // Just work with an empty map
                }
            }

            /**
             * Add or update a object
             */
            void save(V& obj) {
                m_map[get_key(obj)] = &obj;
            }

            void remove(V& obj) {
                auto it = m_map.find(get_key(obj));
                if (it != m_map.end()) {
                    m_map.erase(it);
                }
            }

            V* get_by_key(K& key) const {
                auto it = m_map.find(key);
                return (it != m_map.end() ? it->second : nullptr);
            }

            std::vector<V*> all() const {
                std::vector<V*> result;
                for (auto pair : m_map) {
                    result.push_back(pair.second);
                }
                return result;
            }

            size_t size() const {
                return m_map.size();
            }

            /**
             * Commit the changes to the json file
             */
            void commit() {
                // Save the map to the json file
                nlohmann::json j = nlohmann::json::array({});
                for (auto it = m_map.begin(); it != m_map.end(); ++it)
                {
                    j.push_back(nlohmann::json::parse(to_json(*it->second)));
                }

                std::ofstream file;
                file.open (get_file_location());

                // Write to the file
                file << j.dump();

                // Close the file
                file.close();
            }

            /**
             * Rollback the changes
             */
            void rollback() {
                // Is just the same as loading again
                load();
            }

            virtual K& get_key(V& obj) const = 0;
            virtual std::string get_file_location() const = 0;
            virtual V* create_from_json(std::string json_string) const = 0;
            virtual std::string to_json(V& obj) const = 0;

            virtual ~json_repository() = default;
        private:
            std::map<K, V*> m_map;
        };
    }
}

#endif //CITY_DEFENCE_JSON_REPOSITORY_H
