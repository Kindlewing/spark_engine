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
	${VENDOR_INCLUDE_DIR}/glad/glad.c
	${VENDOR_INCLUDE_DIR}/stb_image/stb_image.cpp
	src/core/main.cpp
	src/core/graphics/shader.cpp
	src/core/graphics/renderer.cpp
	src/core/logger.cpp
	src/core/rawModel.cpp
	src/core/entities/sprite.cpp
	
)

add_subdirectory(vendor/glfw)
add_executable(spark ${SRC})
target_link_libraries(spark glfw)
