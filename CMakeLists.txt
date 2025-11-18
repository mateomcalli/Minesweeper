cmake_minimum_required(VERSION 3.16)
project(Project_Minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Project_Minesweeper main.cpp)

target_link_libraries(Project_Minesweeper PRIVATE sfml-graphics sfml-window sfml-system)

