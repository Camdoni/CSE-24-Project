#include "ColorSelector.h"
#include <bobcat_ui/textbox.h>
using namespace bobcat;

void ColorSelector::deselectAllColors() {
    redButton->label("");
    greenButton->label("");
    blueButton->label("");
    customButton->label("custom");
}

void ColorSelector::visualizeSelectedColor() {
    if (color == RED) {
        redButton->label("@+5square");
    }
    //else if (color == ORANGE) {
        //orangeButton->label("@+5square");
    //}
    //else if (color == YELLOW) {
        //yellowButton->label("@+5square");
    //}

    else if (color == GREEN) {
         greenButton->label("@+5square");
    }
    else if (color == BLUE) {
        blueButton->label("@+5square");
    }
    // else if (color == INDIGO) {
    //     indigoButton->label("@+5square");
    // }
    // else if (color == CUSTOM) {
    //     customButton->label("custom");
    // }
}

void ColorSelector::onClick(bobcat::Widget* sender) {
    deselectAllColors();

    if (sender == redButton) {
        color = RED;
    }
    else if (sender == greenButton) {
        color = GREEN;
    }
    else if (sender == blueButton) {
        color = BLUE;
    }
    
    else if (sender == customButton) {
        color = CUSTOM;
    }
    
    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedColor();
    redraw();
}

Color ColorSelector::getColor() const {
    if (color == RED) {
        return Color(255/255.0, 0/255.0, 0/255.0);
    }
    else if (color == GREEN) {
        return Color(0/255.0, 255/255.0, 0/255.0);
    }
    else if (color == BLUE) {
        return Color(0/255.0, 0/255.0, 255/255.0);
    }

    else if (color == CUSTOM) {
        if (redInput && greenInput && blueInput && !redInput->empty() && !greenInput->empty() && !blueInput->empty()) {
            int redVal = redInput->value();
            int greenVal = greenInput->value();
            int blueVal = blueInput->value();

            customButton->color(fl_rgb_color(redVal, greenVal, blueVal));
            customButton->labelcolor(FL_WHITE);

            return Color(redVal/255.0, greenVal/255.0, blueVal/255.0);
        } 
        else {
            return Color();
        }
    }
    else {
        return Color();
    }
}

ColorSelector::ColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    redButton = new Button(x, y, 50, 50, "");
    greenButton = new Button(x + 50, y, 50, 50, "");
    blueButton = new Button(x + 100, y, 50, 50, "");
    redInput = new IntInput(x + 150, y+20, 50, 30, "Red");
    blueInput = new IntInput(x + 200, y+20, 50, 30, "Green");
    greenInput = new IntInput(x + 250, y+20, 50, 30, "Blue");
    customButton = new Button(x + 300, y, 50, 50, "custom");
    color = RED;

    redButton->color(fl_rgb_color(255, 0, 0));
    redButton->labelcolor(FL_WHITE);
    //orangeButton->color(fl_rgb_color(255, 127, 0));
    //orangeButton->labelcolor(FL_WHITE);
    //yellowButton->color(fl_rgb_color(255, 255, 0));
    //yellowButton->labelcolor(FL_WHITE);

     greenButton->color(fl_rgb_color(0, 255, 0));
     greenButton->labelcolor(FL_WHITE);
     blueButton->color(fl_rgb_color(0, 0, 255));
     blueButton->labelcolor(FL_WHITE);
    // indigoButton->color(fl_rgb_color(75, 0, 130));
    // indigoButton->labelcolor(FL_WHITE);


    visualizeSelectedColor();

    ON_CLICK(redButton, ColorSelector::onClick);
    //ON_CLICK(orangeButton, ColorSelector::onClick);
    //ON_CLICK(yellowButton, ColorSelector::onClick);
    ON_CLICK(greenButton, ColorSelector::onClick);
    ON_CLICK(blueButton, ColorSelector::onClick);
    // ON_CLICK(indigoButton, ColorSelector::onClick);

    //CUSTOM COLOR
    ON_CLICK(customButton, ColorSelector::onClick);
}