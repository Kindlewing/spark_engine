cmake_minimum_required(VERSION 3.28)
project(spark)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(INCLUDE_DIR include)
set(VENDOR_INCLUDE_DIR vendor/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(spark PRIVATE ${INCLUDE_DIR})
include_directories(spark PRIVATE ${VENDOR_INCLUDE_DIR})

set(SRC
	src/glad.c
	src/main.cpp
	src/shader.cpp
	src/renderer.cpp
	src/logger.cpp
	src/rawModel.cpp
	src/loader.cpp
)

add_subdirectory(vendor/glfw)
add_executable(spark ${SRC})
target_link_libraries(spark glfw)
