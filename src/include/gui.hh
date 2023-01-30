#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <memory>
#include <vector>

#include "types.hh"
#include "GameBoard.hh"

class GameBoard;

/**
 * @brief Fl_Button wrapper with an overrideable style changing methods
 *
 */
class FieldButton : public Fl_Button {
  public:
    FieldButton(int x, int y, int w, int h, const char *L);

    void onRevealStyle(const char *representation);

    void onMarkStyle();

    void defaultStyle();
};

/**
 * @brief GUI interface for the GameBoard
 *
 */
class MinefieldUI : public Fl_Group {
    std::vector<std::unique_ptr<FieldButton>> fields_;
    GameBoard board_;
    int buttonSize_;

    std::unique_ptr<FieldButton> &_getButton(Point point);
    void _handle_mouse_click();

  public:
    int handle(int event) override;

    /**
     * @brief Generates a new gameboard and updates the gui accordingly
     *
     * @param newWidth  - number of vertical fields
     * @param newHeight - number of horizontal fields
     * @param mineCount - number of mines
     */
    void reset(dimension_t newWidth, dimension_t newHeight, area_t mineCount);

    MinefieldUI(int x, int y, int w, int h);

    /**
     * @brief Renders an width by height board of fields
     *
     * @param width horizontal fields
     * @param height vertical fields
     */
    void create_minefield(
        dimension_t width, dimension_t height, area_t mineCount);

    /**
     * @brief Handles the logic behind revealing a field, recurses if neighbours
     * are 0
     *
     * @param point coordinates of the point to be revealed
     */
    void reveal(Point point);

    /**
     * @brief Marks a point as a mine, disabling the ability to reveal it
     * manually and via chording
     *
     * @param point coordinates of the point to be marked
     */

    void mark(Point point);
};