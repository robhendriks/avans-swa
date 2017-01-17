//
// Created by Rob Hendriks on 10/01/2017.
//

#ifndef CITY_DEFENCE_COMMAND_MANAGER_H
#define CITY_DEFENCE_COMMAND_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

namespace utils {
    using params = std::vector<std::string>;
    using callback = std::function<bool(const params &)>;
    using command = std::tuple<std::string, callback>;

    class command_manager {
    public:
        command_manager() = default;

        ~command_manager() = default;

        void execute(const std::vector<std::string> &args);

        void add(const std::string &name, const std::string &usage, const callback &cb);

        std::map<std::string, command> m_commands;
    };
}

#endif //CITY_DEFENCE_COMMAND_MANAGER_H
