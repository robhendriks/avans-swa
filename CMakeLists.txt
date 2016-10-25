cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++0x")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(third_party)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCES src/main.cpp
    src/math/vec2.hpp
    src/math/box2.hpp
    src/graphics/color4.hpp
    src/game/engine.cpp
    src/game/engine.h
    src/game/window.cpp
    src/game/window.h
    src/game/window_config.h
    src/config/json_config.cpp
    src/config/json_config.h
    src/game/settings.cpp
    src/game/settings.h)

include_directories(third_party/json/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIRS})

add_executable(city_defence ${SOURCES})
target_link_libraries(city_defence
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARIES})

add_custom_command(TARGET city_defence PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:city_defence>/)
