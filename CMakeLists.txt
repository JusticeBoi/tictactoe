cmake_minimum_required(VERSION 3.5)


project(tictactoe)

set(tictactoe_VERSION_MAJOR 1)
set(tictactoe_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-march=native -fopenmp -Ofast -Wall -Wextra -Wno-unused-parameter -Wshadow -Wnon-virtual-dtor -g  ")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build  ${CMAKE_PREFIX_PATH}")
set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build/lib/cmake/SFML") 
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/lib/inc/config.h"
  )


MESSAGE(${CMAKE_PREFIX_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(EXECUTABLE_NAME "tictactoe")

#include_directories( library/inc )
include_directories( . )
add_subdirectory(utilities)

file( GLOB LIBRARY_SOURCE_FILES lib/src/*.cpp )

add_executable(${EXECUTABLE_NAME} driver/main.cpp ${LIBRARY_SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} utilities  sfml-graphics sfml-system sfml-window  sfml-audio  )

