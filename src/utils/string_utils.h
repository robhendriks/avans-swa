//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_STRING_UTILS_H
#define CITY_DEFENCE_STRING_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <set>
#include <assert.h>

namespace utils {
    namespace string_utils {

        inline std::string ms_to_hms(unsigned int ms) {
            int s_left = ms / 1000;
            std::string s_string = std::to_string(s_left % 60);
            if (s_string.size() == 1) s_string = "0" + s_string;
            s_left /= 60;
            std::string m_string = std::to_string(s_left % 60);
            if (m_string.size() == 1) m_string = "0" + m_string;
            s_left /= 60;
            std::string h_string = std::to_string(s_left % 24);
            if (h_string.size() == 1) h_string = "0" + h_string;

            return h_string + ":" + m_string + ":" + s_string;
        }

        inline unsigned long hex_to_long(std::string hex) {
            unsigned long value;
            std::istringstream iss(hex);
            iss >> std::hex >> value;

            return value;
        }

        /**
         * Clean the string by removing all the linebreaks e.g. \n
         * @param str
         */
        inline void clean(std::string &str) {
            str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        }

        /**
         * Create a vector of strings by splitting the given string with the given delimiter
         *
         * @param str
         * @param delimiter
         * @return
         */
        inline std::vector<std::string> tokenize(std::string str, std::string delimiter) {
            std::vector<std::string> result;
            if (str.empty()) {
                return result;
            }

            clean(str);
            std::string token;

            size_t last = 0;
            size_t next = 0;
            while ((next = str.find(delimiter, last)) != std::string::npos) {
                token = str.substr(last, next - last);
                if (!token.empty()) {
                    result.push_back(token);
                }
                last = next + 1;
            }

            token = str.substr(last);
            if (!token.empty()) {
                result.push_back(token);
            }

            return result;
        }

        template<class T>
        inline std::string join(std::vector<T> vec, std::function<std::string(const T)> lambda) {
            std::stringstream ss;
            for (size_t i = 0; i < vec.size(); i++) {
                if (i != 0) {
                    ss << ", ";
                }
                ss << lambda(vec[i]);
            }
            return ss.str();
        }

        /**
         * Create a string by joining the strings from a vector with a glue in between
         *
         * @param strs
         * @param glue
         * @return
         */
        inline std::string join(std::vector<std::string> strs, std::string glue = " ") {
            std::stringstream ss;
            for (size_t i = 0; i < strs.size(); i++) {
                if (i != 0) {
                    ss << glue;
                }
                ss << strs[i];
            }
            return ss.str();
        }

        /**
         * Checks if the string ends with the given suffix
         *
         * @param str
         * @param suffix
         * @return bool
         */
        inline bool endswith(const std::string &str, const std::string &suffix) {
            return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
        }

        /**
         * WATCH OUT TRIM FUNCTIONS INCOMING!!!
         */

        // trim by reference
        inline void ltrim(std::string &s, std::set<char> characters_to_trim) {
            if (s.length() > 0) {
                // Check if the first char of the string is in the characters list
                if (characters_to_trim.find(s[0]) != characters_to_trim.end()) {
                    // Erase the first char
                    s.erase(0, 1);
                    ltrim(s, characters_to_trim);
                }
            }
        }

        // trim by copy
        inline std::string ltrimmed(std::string s, std::set<char> characters_to_trim) {
            ltrim(s, characters_to_trim);
            return s;
        }

        // trim by reference
        inline void ltrimws(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); }));
        }

        // trim by copy
        inline std::string ltrimmedws(std::string s) {
            ltrimws(s);
            return s;
        }

        // trim by reference
        inline void rtrim(std::string &s, std::set<char> characters_to_trim) {
            if (s.length() > 0) {
                // Check if the last char of the string is in the characters list
                if (characters_to_trim.find(s[s.length() - 1]) != characters_to_trim.end()) {
                    // Erase the last char
                    s.erase(s.length() - 1, 1);
                    rtrim(s, characters_to_trim);
                }
            }
        }

        // trim by copy
        inline std::string rtrimmed(std::string s, std::set<char> characters_to_trim) {
            rtrim(s, characters_to_trim);
            return s;
        }

        // trim by reference
        inline void rtrimws(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); }).base(),
                    s.end());
        }

        // trim by copy
        inline std::string rtrimmedws(std::string s) {
            rtrimws(s);
            return s;
        }

        // trim by reference
        inline void trim(std::string &s, std::set<char> characters_to_trim) {
            ltrim(s, characters_to_trim);
            rtrim(s, characters_to_trim);
        }

        // trim by copy
        inline std::string trimmed(std::string s, std::set<char> characters_to_trim) {
            trim(s, characters_to_trim);
            return s;
        }

        // trim by reference
        inline void trimws(std::string &s) {
            ltrimws(s);
            rtrimws(s);
        }

        // trim by copy
        inline std::string trimmedws(std::string s) {
            trimws(s);
            return s;
        }

        inline std::string wrap(std::string str, size_t width = 80) {
            std::istringstream words(str);
            std::ostringstream wrapped;
            std::string word;

            if (words >> word) {
                wrapped << word;
                size_t space_left = width - word.length();
                while (words >> word) {
                    if (space_left < word.length() + 1) {
                        wrapped << '\n' << word;
                        space_left = width - word.length();
                    } else {
                        wrapped << ' ' << word;
                        space_left -= word.length() + 1;
                    }
                }
            }

            return wrapped.str();
        }

        inline std::string truncate(std::string str, size_t offset, size_t width) {
            assert(width >= 4);

            size_t len = str.length();

            if (len == 0 || len <= width) {
                return str;
            }
            if (offset > len) {
                offset = len;
            }
            if (len - offset < width - 3) {
                offset = len - (width - 3);
            }
            if (offset <= 4) {
                return str.substr(0, width - 3) + "...";
            }

            assert(width >= 7);

            if (offset + width - 3 < len) {
                return "..." + truncate(str.substr(offset), 0, width - 3);
            }

            return "..." + str.substr(str.length() - (width - 3));
        }

        inline std::string truncate(std::string str, size_t width) {
            return truncate(str, 0, width);
        }
    }
}

#endif //CITY_DEFENCE_STRING_UTILS_H
