cmake_minimum_required(VERSION 3.10)
project(spark)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(./include/glfw)
target_link_libraries(spark glfw)

set(SRC
	src/main.c
)
add_executable(spark ${SRC})
