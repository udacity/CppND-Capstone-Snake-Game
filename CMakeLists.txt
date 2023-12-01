cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

# Check if the system is macOS and if SDL2 is installed via Homebrew
if(APPLE AND EXISTS /opt/homebrew/include/SDL2)
    # Set the path to the installed SDL2 include and library directories for Homebrew
    set(SDL2_INCLUDE_DIR "/opt/homebrew/include/SDL2")
    set(SDL2_LIB_DIR "/opt/homebrew/lib")

    # Include and Link directories for SDL2
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})

    # Linking against SDL2 library directly
    set(SDL2_LIBRARIES "SDL2")
else()
    # General version for other systems or different installation paths
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} src)
endif()

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES})