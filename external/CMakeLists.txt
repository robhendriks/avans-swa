#
# GLFW

add_subdirectory(glfw)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        -lGL -lGLU -lXrandr -lXext -lX11 -lrt
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#
# GLEW

add_subdirectory(glew)
