cmake_minimum_required(VERSION 3.10)
project(wrench CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#Find SDL2
find_package(SDL2 REQUIRED)

#Find OpenGL
find_package(OpenGL REQUIRED)

#Find GLM
find_package(glm REQUIRED)

#Find GLEW
find_package(GLEW REQUIRED)

#Enable C++17
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /std:c++17")
endif(MSVC)

#Add OpenGL to the LIBS variable
function(add_opengl_to_libs)
    set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} PARENT_SCOPE)
endfunction()

#Add GLEW to the LIBS variable
function(add_glew_to_libs)
    set(LIBS ${LIBS} ${GLEW_LIBRARY} PARENT_SCOPE)
endfunction()

#Add SDL2 to the LIBS variable
function(add_sdl2_to_libs)
    set(LIBS ${LIBS} ${SDL2_LIBRARY} PARENT_SCOPE)
endfunction()

#Add targets and source files
#todo: Make a LIB_SOURCES variable working like the current LIBS one
add_library(wrench core/core.h window/window.cc window/window.h core/types.h core/core.cc renderer/gl/gl_settings.h renderer/gl/gl.h renderer/common/context.cc renderer/common/context.h renderer/gl/gl_context.cc renderer/gl/gl_context.h)
#todo: add_library(wrench-shared SHARED core/core.h window/window.cc window/window.h core/types.h core/core.cc renderer/gl/gl_settings.h renderer/gl/gl.h renderer/common/context.cc renderer/common/context.h renderer/gl/gl_context.cc renderer/gl/gl_context.h core/SDL.h)
add_executable(example main.cpp)

#Add include directories
include_directories(${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

#Add libraries to LIBS
add_opengl_to_libs()
add_sdl2_to_libs()
add_glew_to_libs()

#Link libraries in LIBS
target_link_libraries(wrench ${LIBS})
#target_link_libraries(wrench-shared ${LIBS})
target_link_libraries(example ${LIBS} wrench)
