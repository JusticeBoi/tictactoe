cmake_minimum_required(VERSION 3.5)


project(tictactoe CXX)

set(TICTACTOE_VERSION_MAJOR 1)
set(TICTACTOE_VERSION_MINOR 5)

OPTION ( TICTACTOE_ENABLE_FUNCTION_UTILITIES "Function timings, call stacks, etc.." OFF)
OPTION ( TICTACTOE_ENABLE_CXX_17 "C++17" ON)

if(TICTACTOE_ENABLE_CXX_17)
    set (CMAKE_CXX_STANDARD 17)
else()
    set (CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    MESSAGE("Compiler CLANG")
    set (CMAKE_CXX_FLAGS_DEBUG " -O0 -fopenmp -g -Wall -Wextra -Wshadow -Wno-unused-paramteter -Wnon-virtual-dtor ")
    set (CMAKE_CXX_FLAGS_RELEASE "-march=native -fopenmp -O3 -Wno-unused-parameter")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    MESSAGE("Compiler GCC")
    set (CMAKE_CXX_FLAGS_DEBUG " -O0 -fopenmp -g -Wall -Wextra -Wshadow -Wno-unused-paramteter -Wnon-virtual-dtor ")
    set (CMAKE_CXX_FLAGS_RELEASE "-march=native -fopenmp -O3 -Wno-unused-parameter")
endif()
if(WIN32)
    set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
    add_definitions(-DTICTACTOE_WIN_32)
endif()

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/lib/inc/config.h"
  )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(EXECUTABLE_NAME "tictactoe")

include_directories( . )
include_directories( lib/inc )

if(TICTACTOE_ENABLE_FUNCTION_UTILITIES)
    add_definitions(-DWITH_FUNCTION_UTILITIES)
    add_subdirectory(utilities)
endif()

file( GLOB LIBRARY_SOURCE_FILES lib/src/*.cpp )
file( GLOB LIBRARY_HEADER_FILES lib/inc/*.hpp )

add_library(tictactoelib SHARED ${LIBRARY_SOURCE_FILES} ${LIBRARY_HEADER_FILES} )
target_link_libraries(tictactoelib sfml-graphics  sfml-window  sfml-audio )

add_executable(${EXECUTABLE_NAME} driver/main.cpp )
target_link_libraries(${EXECUTABLE_NAME} tictactoelib  )

if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} sfml-main)
endif()

if(TICTACTOE_ENABLE_FUNCTION_UTILITIES)
    target_link_libraries(${EXECUTABLE_NAME} utilities )
endif()
