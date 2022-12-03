Include(FetchContent)
FetchContent_Declare(
Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG origin/devel)
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
FetchContent_Populate(Catch2)
ADD_SUBDIRECTORY("${catch2_SOURCE_DIR}" "${catch2_BINARY_DIR}")
endif()


ADD_EXECUTABLE(GameBoardTests GameBoardTests.cpp)
TARGET_LINK_LIBRARIES(GameBoardTests GameBoard Catch2::Catch2WithMain)
ADD_TEST(NAME GameBoardTests COMMAND GameBoardTests)
