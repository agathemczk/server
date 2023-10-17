cmake_minimum_required(VERSION 3.26)
project(server C)

set(CMAKE_C_STANDARD 11)

add_executable(server client.c)
target_link_libraries(server Ws2_32)