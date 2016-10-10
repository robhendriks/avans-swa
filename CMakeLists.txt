cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES CXX)

add_subdirectory(external)

include_directories(external/SDL2/include)

set(SOURCES src/main.cpp)

add_executable(city_defence ${SOURCES})
target_link_libraries(city_defence SDL2 SDL2main)
