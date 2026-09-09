cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
set(glm_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")
find_package(glm REQUIRED)

add_executable(MyApp scr/main.cpp
        scr/include/quads.cpp
        scr/include/quads.h
)
target_link_libraries(MyApp
        PRIVATE
        ${FREETYPE_LIBRARIES}
        glfw
        GLEW::GLEW
        OpenGL::GL
)
include_directories(${FREETYPE_INCLUDE_DIRS})
target_include_directories(MyApp
        PRIVATE
        ${FREETYPE_INCLUDE_DIRS}
        ${glm_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
)
