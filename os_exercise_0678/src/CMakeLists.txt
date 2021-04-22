cmake_minimum_required(VERSION 3.0.2)

project(lab6-8 VERSION 1.0 LANGUAGES C)

set(SERVER server)
set(CLIENT client)
set(SOURCE_SERVER server.c)
set(SOURCE_CLIENT client.c)

add_library(Mess OBJECT Mess.h Mess.c)
add_library(Tree OBJECT Tree.h Tree.c)
target_link_libraries(Tree PRIVATE pthread)

add_executable(${SERVER} ${SOURCE_SERVER} Mess.h Mess.c Tree.h Tree.c)
add_executable(${CLIENT} ${SOURCE_CLIENT} Mess.h Mess.c)

target_link_libraries(${SERVER} ${Mess} ${Tree} zmq pthread)
target_link_libraries(${CLIENT} ${Mess} zmq)

add_definitions(-std=c99 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -lzmq -lpthread -D_POSIX_C_SOURCE)