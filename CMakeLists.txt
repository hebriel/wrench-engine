cmake_minimum_required(VERSION 3.10)
project(wrench CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

function(add_opengl_to_libs)
    if (APPLE)
        set(LIBS ${LIBS} "-framework OpenGL" PARENT_SCOPE)
    elseif(UNIX AND NOT APPLE)
        set(LIBS ${LIBS} X11 GL PARENT_SCOPE)
    elseif(WIN32)
        list(APPEND LIBS opengl32 PARENT_SCOPE)
    endif()
endfunction()

function(add_glew_to_libs)
    if (UNIX)
        set(LIBS ${LIBS} GLEW PARENT_SCOPE)
    endif()
    #todo : Support win32
endfunction()

function(add_sdl2_to_libs)
    set(LIBS ${LIBS} SDL2 PARENT_SCOPE)
endfunction()

add_library(wrench core/core.h window/window.cc window/window.h core/types.h core/core.cc renderer/gl/gl_settings.h renderer/gl/gl.h renderer/common/context.cc renderer/common/context.h renderer/gl/gl_context.cc renderer/gl/gl_context.h)
add_library(wrench-shared SHARED core/core.h window/window.cc window/window.h core/types.h core/core.cc renderer/gl/gl_settings.h renderer/gl/gl.h renderer/common/context.cc renderer/common/context.h renderer/gl/gl_context.cc renderer/gl/gl_context.h)
add_executable(example main.cpp)

add_opengl_to_libs()
add_sdl2_to_libs()
add_glew_to_libs()

target_link_libraries(wrench ${LIBS})
target_link_libraries(wrench-shared ${LIBS})
target_link_libraries(example ${LIBS} wrench)
