cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++14")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(third_party)
add_subdirectory(tests)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

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
    src/gui/views/main_menu.h
    src/engine/graphics/texture_manager.cpp
    src/engine/graphics/texture_manager.h
    src/engine/eventbus/eventbus.h
    src/engine/eventbus/subscriber.h
    src/engine/events/key_down.h
    src/engine/input/keycodes.h
    src/gui/controllers/menu_controller.cpp
    src/gui/controllers/menu_controller.h
    src/engine/events/mouse_button_down.h
    src/engine/events/window_cleared.cpp
    src/engine/events/window_cleared.h
    src/engine/input/mouse_buttons.h
    src/engine/events/mouse_button_up.h
    src/engine/engine_config.h
    src/config/config.h
    src/utils/string_utils.h
    src/engine/graphics/color_manager.cpp
    src/engine/graphics/color_manager.h
    src/gui/views/main_map.cpp
    src/gui/views/main_map.h
    src/gui/controllers/main_map_controller.cpp
    src/gui/controllers/main_map_controller.h
    src/gui/models/main_map_model.h
    src/gui/views/base_view.h
    src/gui/controllers/base_controller.cpp
    src/gui/controllers/base_controller.h
    src/services/registry/registry.h
    src/game.cpp
    src/game.h
    src/engine/audio/sound_manager.cpp
    src/engine/audio/sound_manager.h
    src/engine/audio/music_manager.cpp
    src/engine/audio/music_manager.h
    src/events/object_placed_on_field.cpp
    src/events/object_placed_on_field.h
    src/events/object_cannot_be_placed_on_field.cpp
    src/events/object_cannot_be_placed_on_field.h
    src/listeners/play_sound_when_object_is_placed_on_field.cpp
    src/listeners/play_sound_when_object_is_placed_on_field.h
    src/listeners/play_sound_when_object_cannot_be_placed_on_field.cpp
    src/listeners/play_sound_when_object_cannot_be_placed_on_field.h
    src/engine/audio/state.h
    src/engine/audio/sound_callback_wrapper.cpp
    src/engine/audio/sound_callback_wrapper.h
    src/domain/drawable/drawable_game_object.cpp
    src/domain/drawable/drawable_game_object.h
    src/domain/drawable/abstract_drawable_game_object.h
    src/services/map_loader/base_map_loader.h
    src/services/map_loader/json_map_loader.cpp
    src/services/map_loader/json_map_loader.h
    src/gui/controllers/credits_controller.cpp
    src/gui/controllers/credits_controller.h
    src/gui/views/credits.cpp
    src/gui/views/credits.h
    src/engine/graphics/font_manager.cpp
    src/engine/graphics/font_manager.h
    src/engine/graphics/moveable_box.cpp
    src/engine/graphics/moveable_box.h
    src/domain/buildings/road.cpp
    src/domain/buildings/road.h
    src/engine/draganddrop/drag_and_drop.h
    src/engine/draganddrop/dragable.h
    src/engine/draganddrop/dropable.h
    src/engine/events/mouse_motion.cpp
    src/engine/events/mouse_motion.h
    src/engine/draganddrop/drag_and_drop.cpp
    src/domain/game_level/game_level.cpp
    src/domain/game_level/game_level.h src/domain/game_level/game_stats.cpp src/domain/game_level/game_stats.h src/gui/views/win_game_over.cpp src/gui/views/win_game_over.h src/gui/models/transition_level_model.h)


include_directories(third_party/json/src
        third_party/di-cpp14/include
        third_party/type
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIR})

add_executable(city_defence ${SOURCES})
add_library(city_defence_sources STATIC ${SOURCES})

target_link_libraries(city_defence
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARY})

add_custom_command(TARGET city_defence PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:city_defence>/)
