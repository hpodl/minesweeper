cmake_minimum_required(VERSION 3.0.0)
project(Minesweeper VERSION 0.1)



set (CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories(./src/include)

enable_testing()

add_subdirectory(./src/include)
add_subdirectory(./tests)

add_executable(Minesweeper ./src/main.cpp)
target_link_libraries(Minesweeper Field GameBoard)
