//
// Created by Rob Hendriks on 10/01/2017.
//

#include "command_manager.h"

namespace utils {
    void command_manager::execute(const std::vector<std::string> &args) {
        if (args.size() == 0) {
            throw std::runtime_error("Unknown command.");
        }

        if (m_commands.find(args[0]) == m_commands.end()) {
            std::stringstream ss;
            ss << "Unknown command \"" << args[0] << "\".";
            throw std::runtime_error(ss.str());
        }

        auto &command = m_commands[args[0]];
        auto usage = std::get<0>(command);
        auto cb = std::get<1>(command);

        if (!cb(args)) {
            throw std::runtime_error(std::string("Usage: " + usage));
        }
    }

    void command_manager::add(const std::string &name, const std::string &usage, const callback &cb) {
        m_commands.emplace(name, std::make_tuple(usage, cb));
    }
}
