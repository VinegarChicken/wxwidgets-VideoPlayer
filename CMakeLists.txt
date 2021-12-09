cmake_minimum_required(VERSION 3.20)
project(VideoPlayer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/wxWidgets)
add_executable(VideoPlayer VideoPlayer.cpp VideoPlayer.h main.cpp main.h MainWindow.cpp MainWindow.h)
target_link_libraries(VideoPlayer wx::media wx::net wx::core wx::base)