project(city_defency_test)

add_subdirectory(../third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../third_party/json/src
    ../third_party/di-cpp14/include
    ../third_party/type
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIR})

add_executable(runCityDefenceTests
    data/person.cpp
    data/person.h
    data/json/person_json_repository.h
    data/json/person_json_repository.cpp
    data/json/json_repository_tests.cpp
    engine/math/vec2_tests.cpp
    engine/audio/music_manager_tests.cpp engine/audio/sound_manager_tests.cpp)

target_link_libraries(runCityDefenceTests gtest gtest_main)
target_link_libraries(runCityDefenceTests city_defence_sources)
target_link_libraries(runCityDefenceTests
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARY})

add_custom_command(TARGET runCityDefenceTests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/tests/data/json/persons.json $<TARGET_FILE_DIR:runCityDefenceTests>/data/json/persons.json)

add_custom_command(TARGET runCityDefenceTests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/tests/engine/audio/sounds/pop.wav $<TARGET_FILE_DIR:runCityDefenceTests>/data/sounds/pop.wav)
