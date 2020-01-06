cmake_minimum_required(VERSION 3.10)
project(wrench CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#Options
option(BUILD_DOC "Build the documentation" ON)
option(BUILD_EXAMPLE "Build an example executable" ON)

#Find Doxygen
if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/documentation/Doxyfile)

        #File configuration
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        add_custom_target(doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating Doxygen documentation"
                VERBATIM)
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the documentation")
    endif (DOXYGEN_FOUND)
endif()

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
#todo: Add a target to build a shared library
#todo: Make a separated module in ./src for every source file
add_library(wrench src/core/core.h src/window/window.cc src/window/window.h src/core/types.h src/core/core.cc src/renderer/gl/gl_settings.h src/renderer/gl/gl.h src/renderer/common/context.cc src/renderer/common/context.h src/renderer/gl/gl_context.cc src/renderer/gl/gl_context.h src/renderer/common/shader.cc src/renderer/common/shader.h src/renderer/gl/gl_shader.cc src/renderer/gl/gl_shader.h src/renderer/common/vertex_buffer.h src/renderer/common/index_buffer.h src/renderer/gl/gl_vertex_buffer.cc src/renderer/gl/gl_vertex_buffer.h src/renderer/gl/gl_index_buffer.cc src/renderer/gl/gl_index_buffer.h src/renderer/common/vertex_array.cc src/renderer/common/vertex_array.h src/renderer/gl/gl_vertex_array.cc src/renderer/gl/gl_vertex_array.h src/renderer/common/layout.cc src/renderer/common/layout.h src/renderer/gl/all.h src/renderer/common/renderer.cc src/renderer/common/renderer.h)

if(BUILD_EXAMPLE)
    add_executable(example src/example/main.cpp)

    add_custom_command(
            TARGET example POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/example/resources
            ${CMAKE_CURRENT_BINARY_DIR}/resources)
endif()

#Add include directories
include_directories(${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

#Add libraries to LIBS
add_opengl_to_libs()
add_sdl2_to_libs()
add_glew_to_libs()

#Link libraries in LIBS
target_link_libraries(wrench ${LIBS})

if(BUILD_EXAMPLE)
    target_link_libraries(example ${LIBS} wrench)
    target_include_directories(example PUBLIC src)
endif()