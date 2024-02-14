cmake_minimum_required(VERSION 3.10)
project(spark)
set(src 
	src/main.c
) 
add_executable(spark ${src})
