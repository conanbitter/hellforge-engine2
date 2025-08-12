cmake_minimum_required(VERSION 3.16)

project(hellforge VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(hellforge 
    src/main.cpp
    src/shaders.hpp
    src/shaders.cpp
    src/opengl.hpp
    src/opengl.cpp
    src/color.hpp
    src/color.cpp
    src/app.hpp
    src/app.cpp
    src/imagebuffer.hpp
    src/imagebuffer.cpp
    src/rendertarget.hpp
    src/rendertarget.cpp
    src/scaling.hpp
    src/scaling.cpp
    src/texture.hpp
    src/texture.cpp
    src/resources.hpp
    src/resources.cpp
    src/rect.hpp
    src/rect.cpp
    src/font.hpp
    src/font.cpp
    vendored/glad/src/gl.c
)

target_include_directories(hellforge
    PRIVATE
        vendored/glad/include
)

target_link_libraries(hellforge PRIVATE SDL3::SDL3)