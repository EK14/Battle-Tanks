cmake_minimum_required(VERSION 3.14)
project(Battle_Tanks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp maze.cpp maze.h game.cpp game.h Player.cpp Player.h Bullet.cpp Bullet.h)
add_executable(Battle_Tanks ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Battle_Tanks sfml-system sfml-window sfml-graphics sfml-audio sfml-network)