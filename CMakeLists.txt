cmake_minimum_required(VERSION 3.5)


project(tictactoe CXX)

set(TICTACTOE_VERSION_MAJOR 1)
set(TICTACTOE_VERSION_MINOR 3)

OPTION ( TICTACTOE_ENABLE_FUNCTION_UTILITIES "Function timings, call stacks, etc.." OFF)
OPTION ( TICTACTOE_ENABLE_TGUI "FIND TGUI" OFF)
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
    #elseif(MSVC)
    #set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
endif()
if(WIN32)
    set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
    add_definitions(-DTICTACTOE_WIN_32)
endif()

set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build  ${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/TGUI-0.8.5-build  ${CMAKE_PREFIX_PATH}")

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build/lib/cmake/SFML") 

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/lib/inc/config.h"
  )


MESSAGE(${CMAKE_PREFIX_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

if(TICTACTOE_ENABLE_TGUI)
    set(TGUI_DIR "${PROJECT_SOURCE_DIR}/TGUI-0.8.5-build/lib/cmake/TGUI") 
    find_package(TGUI 0.8  REQUIRED)
    include_directories( TGUI-0.8.5-build/include )
endif()

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

add_executable(${EXECUTABLE_NAME} driver/main.cpp ${LIBRARY_SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} tictactoelib  )

if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} sfml-main)
endif()
add_executable(screens driver/screens.cpp ${LIBRARY_SOURCE_FILES} )
target_link_libraries(screens tictactoelib  )

if(TICTACTOE_ENABLE_FUNCTION_UTILITIES)
    target_link_libraries(${EXECUTABLE_NAME} utilities )
    target_link_libraries(screens utilities )
endif()


