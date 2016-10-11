cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(city_defence VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCES src/main.cpp)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIRS}
)

add_executable(city_defence ${SOURCES})
target_link_libraries(
    city_defence
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
)
