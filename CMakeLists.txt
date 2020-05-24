cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "--libs sdl2" "-Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} "C:/Program Files/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2" "C:/Program Files/SDL2-2.0.12/x86_64-w64-mingw32/lib" src)

add_executable(DodgerGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/actor.cpp)
#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(DodgerGame ${SDL2_LIBRARIES})
