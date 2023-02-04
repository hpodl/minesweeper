cmake_minimum_required(VERSION 3.15.0)
project(Minesweeper VERSION 0.4)

FIND_PACKAGE(FLTK REQUIRED)


SET (CMAKE_CXX_STANDARD 20)
ADD_COMPILE_OPTIONS(-Wall -Wextra -pedantic -Werror )
INCLUDE_DIRECTORIES(./src/include)


ENABLE_TESTING()

ADD_SUBDIRECTORY(./src/include)
ADD_SUBDIRECTORY(./tests)

ADD_EXECUTABLE(Minesweeper ./src/main.cpp)

TARGET_LINK_LIBRARIES(Minesweeper MinefieldUI MainWindow)
TARGET_LINK_LIBRARIES(Minesweeper ${FLTK_LIBRARIES})

