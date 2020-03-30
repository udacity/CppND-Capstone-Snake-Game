cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(ShooterGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(ShooterGame
    src/main.cpp
    src/game.cpp
    src/game.h
    src/controller.cpp
    src/controller.h
    src/renderer.cpp
    src/renderer.h
    src/shooter.cpp
    src/shooter.h
    src/missile.cpp
    src/missile.h
    src/EnemyShip.cpp
    src/EnemyShip.h
    src/EnemyShipManager.cpp
    src/EnemyShipManager.h
    src/Direction.h
)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(ShooterGame ${SDL2_LIBRARIES})
