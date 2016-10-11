#
# simpleini

project(simpleini)

SET(SIMPLEINI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/simpleini)

include_directories(${SIMPLEINI_DIR})

SET(SIMPLEINI_HEADERS
    ${SIMPLEINI_DIR}/ConvertUTF.h
    ${SIMPLEINI_DIR}/SimpleIni.h)

SET(SIMPLEINI_SOURCES
    ${SIMPLEINI_HEADERS}
    ${SIMPLEINI_DIR}/ConvertUTF.c)

add_library(simpleini ${SIMPLEINI_SOURCES})
