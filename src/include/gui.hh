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
    int handle(int event) override;

    public:
        Point pos;
        FieldButton(int x, int y, int w, int h, Point pos, const char * L);
};


class MinefieldUI : public Fl_Group {
    std::vector<std::unique_ptr<FieldButton>> fields_;
    GameBoard board;

    std::unique_ptr<FieldButton>& getField(Point point);
    
    void real_callback(FieldButton* w);

public:
    static void static_callback(FieldButton* w, void* data);

    MinefieldUI(int x, int y, int w, int h);
    
    /**
     * @brief Renders an width by height board of fields
     * 
     * @param width horizontal fields
     * @param height vertical fields
     */
    void create_minefield(dimension_t width, dimension_t height, area_t mineCount);


    void reveal(Point point);
};