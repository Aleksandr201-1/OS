cmake_minimum_required(VERSION 3.0.2)

project(lab5 VERSION 1.0 LANGUAGES C)

set(STATIC_EXE mainStat)
set(SHARED_EXE mainDyn)
set(SOURCE_STAT_EXE mainStat.c)
set(SOURCE_SHAR_EXE mainDyn.c)

add_library(1S STATIC lib1.h lib1.c)
add_library(1D SHARED lib1.h lib1.c)
add_library(2S STATIC lib2.h lib2.c)
add_library(2D SHARED lib2.h lib2.c)
target_link_libraries(1D PRIVATE m)
target_link_libraries(2D PRIVATE m)
target_link_libraries(1S PRIVATE m)
target_link_libraries(2S PRIVATE m)

add_executable(${STATIC_EXE} ${SOURCE_STAT_EXE} lib2.h lib2.c)
add_executable(${SHARED_EXE} ${SOURCE_SHAR_EXE})

target_link_libraries(${STATIC_EXE} ${LIB2D} m)
target_link_libraries(${SHARED_EXE} PRIVATE m dl)

add_definitions(-std=c99 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -lm -ldl)
