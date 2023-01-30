ADD_LIBRARY(Field Field.hh Field.cpp)
ADD_LIBRARY(GameBoard GameBoard.hh GameBoard.cpp)
ADD_LIBRARY(Gui gui.hh gui.cpp)

target_link_libraries(GameBoard Field)
target_link_libraries(Gui GameBoard)
