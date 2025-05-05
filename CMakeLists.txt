cmake_minimum_required(VERSION 3.10)
project(gsl C)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories(
    include
)

add_executable(gsl src/main.c src/glad.c src/window.c src/shader.c)
target_link_libraries(gsl ${GLFW_LIBRARIES} GL m dl)
