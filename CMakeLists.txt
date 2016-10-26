cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(third_party)
add_subdirectory(tests)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCES src/main.cpp
    src/config/config.h
    src/config/config.cpp
    src/config/ini_config.h
    src/config/ini_config.cpp
    src/data/repository.h
    src/data/json/json_repository.h
    src/math/vec2.hpp
    src/math/box2.hpp
    src/observer/observee.h
    src/observer/observer.h
    src/game/tile.h
    src/game/tile.cpp
    src/game/world.h
    src/game/world.cpp
    src/game/graphics/texture.cpp
    src/game/graphics/texture.h
    src/game/graphics/sprite.cpp
    src/game/graphics/sprite.h
    src/game/engine.cpp
    src/game/engine.h
    src/game/graphics/display.cpp
    src/game/graphics/display.h
    src/game/input/input_handler.cpp
    src/game/input/input_handler.h)

include_directories(third_party/simpleini
    third_party/json/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIRS})

add_executable(city_defence ${SOURCES})

target_link_libraries(city_defence
    simpleini
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARIES})

add_custom_command(TARGET city_defence PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:city_defence>)

add_custom_command(TARGET city_defence PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:city_defence>/assets)

add_custom_command(TARGET city_defence PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:city_defence>/data)
