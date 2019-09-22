cmake_minimum_required(VERSION 3.5)


project(tictactoe)

set(tictactoe_VERSION_MAJOR 1)
set(tictactoe_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS_DEBUG " -O0 -fopenmp -g ")
set (CMAKE_CXX_FLAGS_RELEASE "-march=native -fopenmp -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wno-unused-parameter -Wshadow -Wnon-virtual-dtor ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 ")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build  ${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/TGUI-0.8.5-build  ${CMAKE_PREFIX_PATH}")

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1-build/lib/cmake/SFML") 
set(TGUI_DIR "${PROJECT_SOURCE_DIR}/TGUI-0.8.5-build/lib/cmake/TGUI") 
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/lib/inc/config.h"
  )


MESSAGE(${CMAKE_PREFIX_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
#find_package(TGUI 0.8  REQUIRED)

set(EXECUTABLE_NAME "tictactoe")

include_directories( . )
#include_directories( TGUI-0.8.5-build/include )
include_directories( lib/inc )
add_subdirectory(utilities)
#add_subdirectory(TGUI-examples)

file( GLOB LIBRARY_SOURCE_FILES lib/src/*.cpp )

add_executable(${EXECUTABLE_NAME} driver/main.cpp ${LIBRARY_SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} utilities sfml-graphics  sfml-window  sfml-audio  )

#add_executable(screens driver/screens.cpp lib/src/screen_1.cpp  lib/src/MenuScreen.cpp lib/src/TwoPlayerScreen.cpp)
add_executable(screens driver/screens.cpp ${LIBRARY_SOURCE_FILES} )
target_link_libraries(screens utilities sfml-graphics sfml-window  sfml-audio  )
