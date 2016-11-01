cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++14")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(third_party)
add_subdirectory(tests)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCES src/main.cpp
    src/engine/math/vec2.hpp
    src/engine/math/box2.hpp
    src/engine/graphics/color4.hpp
    src/engine/engine.cpp
    src/engine/engine.h
    src/engine/window.cpp
    src/engine/window.h
    src/engine/window_config.h
    src/config/json_config.cpp
    src/config/json_config.h
    src/data/repository.h
    src/data/json/json_repository.h
    src/engine/observer/observee.h
    src/engine/observer/observer.h
    src/engine/input/input_handler.cpp
    src/engine/input/input_handler.h
    src/domain/map/base_field.h
    src/domain/map/base_field.cpp
    src/domain/map/base_map.h
    src/domain/map/base_map.cpp
    src/domain/buildings/building.h
    src/domain/buildings/building.cpp
    src/domain/gameworld/game_world.h
    src/domain/gameworld/game_world.cpp
    src/domain/map/map.h
    src/domain/map/map.cpp
    src/domain/map/passable_field.h
    src/domain/map/passable_field.cpp
    src/domain/resources/resource.h
    src/domain/resources/resource.cpp
    src/domain/buildings/base_placeable_object.cpp
    src/domain/buildings/base_placeable_object.h
    src/gui/views/main_menu.cpp
    src/gui/views/main_menu.h src/engine/texture/texture_manager.cpp src/engine/texture/texture_manager.h src/engine/eventbus/eventbus.h src/engine/eventbus/subscriber.h src/engine/events/key_down.h src/engine/input/keycodes.h src/gui/controllers/menu_controller.cpp src/gui/controllers/menu_controller.h src/engine/events/mouse_button_down.h src/engine/events/window_cleared.cpp src/engine/events/window_cleared.h src/gui/router.cpp src/gui/router.h src/engine/input/mouse_buttons.h src/engine/events/mouse_button_up.h src/engine/engine_config.h src/config/config.h src/utils/string_utils.h src/gui/views/main_map.cpp src/gui/views/main_map.h src/gui/controllers/main_map_controller.cpp src/gui/controllers/main_map_controller.h)

include_directories(third_party/json/src
        third_party/di-cpp14/include
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
