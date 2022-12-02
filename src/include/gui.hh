#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

#include <memory>
#include <vector>
#include <iostream>

struct FieldPos {
    int x_, y_;
};

class Field : public Fl_Button {
    int handle(int event) override;

    public:
        FieldPos pos;
        Field(int x, int y, int w, int h, FieldPos pos, const char * L);
};


class MinefieldUI : public Fl_Group {
    std::vector<std::unique_ptr<Field>> fields_;

    std::unique_ptr<Field>& getField(int x, int y);
    
    void real_callback(Fl_Widget* w);

public:
    static void static_callback(Fl_Widget* w, void* data);

    MinefieldUI(int x, int y, int w, int h);
    
    /**
     * @brief Renders an width by height board of fields
     * 
     * @param width horizontal fields
     * @param height vertical fields
     */
    void render_minefield(int width, int height);

};