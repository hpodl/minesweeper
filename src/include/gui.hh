#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

#include <memory>
#include <vector>
#include <iostream>

#include "GameBoard.hh"

class FieldButton : public Fl_Button {
    public:
        Point pos;
        FieldButton(int x, int y, int w, int h, Point pos, const char * L);

        
    void onRevealStyle(const char* representation);

    void onMarkStyle();

    void defaultStyle();
};


class MinefieldUI : public Fl_Group {
    std::vector<std::unique_ptr<FieldButton>> _fields;
    GameBoard _board;

    std::unique_ptr<FieldButton>& _getButton(Point point);
    void _handle_mouse_click();
    int _buttonSize;
public:
    int handle(int event) override;

    void reset(dimension_t newWidth, dimension_t newHeight, area_t mineCount);

    MinefieldUI(int x, int y, int w, int h);
    
    /**
     * @brief Renders an width by height board of fields
     * 
     * @param width horizontal fields
     * @param height vertical fields
     */
    void create_minefield(dimension_t width, dimension_t height, area_t mineCount);



    void reveal(Point point);

    void mark(Point point);
};