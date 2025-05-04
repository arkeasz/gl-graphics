cmake_minimum_required(VERSION 3.10)
project(gsl C)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories(
    include  # para glad.h y KHR
)

add_executable(gsl src/main.c src/glad.c)
target_link_libraries(gsl ${GLFW_LIBRARIES} GL m dl)


# cmake_minimum_required(VERSION 3.10)
# project(gsl C)

# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLW REQUIRED glfw3)
# include_directories(${GLFW_INCLUDE_DIRS})
# link_directories(${GLFW_LIBRARY_DIRS})

# include_directories(
#     include
#     /usr/include
# )

# add_executable(gsl src/main.c src/glad.c)
# target_link_libraries(gsl glfw GL m)
