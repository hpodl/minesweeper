ADD_LIBRARY(Field Field.hh Field.cpp)
ADD_LIBRARY(GameBoard GameBoard.hh GameBoard.cpp)
ADD_LIBRARY(MinefieldUI MinefieldUI.hh MinefieldUI.cpp)
ADD_LIBRARY(MainWindow MainWindow.hh MainWindow.cpp)

target_link_libraries(GameBoard Field)
target_link_libraries(MainWindow MinefieldUI GameBoard)
