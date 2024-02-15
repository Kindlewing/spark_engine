cmake_minimum_required(VERSION 3.28)
project(spark)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SRC
	src/main.cpp
)

add_subdirectory(./vendor/glfw)
find_package(OpenGL REQUIRED)
add_executable(spark ${SRC})

target_link_libraries(spark OpenGL::GL)
target_link_libraries(spark glfw)
