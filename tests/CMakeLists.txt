project(city_defency_test)

add_subdirectory(../third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

include_directories(../third_party/json/src
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR})

add_executable(runCityDefenceTests
    data/person.cpp
    data/person.h
    data/json/person_json_repository.h
    data/json/person_json_repository.cpp
    data/json/json_repository_tests.cpp
    math/vec2_tests.cpp)

target_link_libraries(runCityDefenceTests gtest gtest_main)

add_custom_command(TARGET runCityDefenceTests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/tests/data/json/persons.json $<TARGET_FILE_DIR:runCityDefenceTests>/data/json/persons.json)
