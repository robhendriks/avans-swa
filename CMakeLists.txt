cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(city_defence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OPENGL REQUIRED)

include_directories(
    external/glfw/include/GLFW
    external/glew/include
    external/glm
)

add_subdirectory(external)

set(ALL_LIBRARIES ${OPENGL_LIBRARY} glfw libglew_static)

set(SOURCE_FILES src/main.cpp)
add_executable(city_defence ${SOURCE_FILES})
target_link_libraries(city_defence ${ALL_LIBRARIES})
