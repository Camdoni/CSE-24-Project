#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include <bobcat_ui/input.h>
#include <bobcat_ui/textbox.h>
#include "Color.h"
#include "Enums.h"

class ColorSelector : public bobcat::Group {
    bobcat::Button* redButton;
    //bobcat::Button* orangeButton;
    //bobcat::Button* yellowButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    // bobcat::Button* indigoButton;
    bobcat::Button* customButton;
    bobcat::IntInput* redInput;
    bobcat::IntInput* blueInput;
    bobcat::IntInput* greenInput;
    bobcat::TextBox* redText;

    COLOR color;
    void deselectAllColors();
    void visualizeSelectedColor();
    void onClick(bobcat::Widget* sender);

public:
    ColorSelector(int x, int y, int w, int h);

    Color getColor() const;
};

#endif