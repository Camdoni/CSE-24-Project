#include "Toolbar.h"
#include <FL/Enumerations.H>
using namespace bobcat;

void Toolbar::deselectAllTools() {
    pencilButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
}

void Toolbar::visualizeSelectedTool() {
    if (tool == PENCIL) {
        pencilButton->color(FL_WHITE);
    }
    else if (tool == ERASER) {
        eraserButton->color(FL_WHITE);
    }
    else if (tool == CIRCLE) {
        circleButton->color(FL_WHITE);
    }
    else if (tool == TRIANGLE) {
        triangleButton->color(FL_WHITE);
    }
    else if (tool == RECTANGLE) {
        rectangleButton->color(FL_WHITE);
    }
}

void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();

    action = NONE;

    if (sender == pencilButton) {
        tool = PENCIL;
    }
    else if (sender == eraserButton) {
        tool = ERASER;
    }
    else if (sender == circleButton) {
        tool = CIRCLE;
    }
    else if (sender == triangleButton) {
        tool = TRIANGLE;
    }
    else if (sender == rectangleButton) {
        tool = RECTANGLE;
    }

    else if (sender == clearButton) {
        action = CLEAR;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

TOOL Toolbar::getTool() const {
    return tool;
}

ACTION Toolbar::getAction() const {
    return action;
}

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    pencilButton = new Image(x, y, 40, 40, "./assets/pencil.png");
    eraserButton = new Image(x, y + 40, 40, 40, "./assets/eraser.png");
    circleButton = new Image(x, y + 80, 40, 40, "./assets/circle.png");
    triangleButton = new Image(x, y + 120,40, 40, "./assets/triangle.png");
    polygonButton = new Image(x,y+160,40,40,"./assets/polygon.png");
    rectangleButton = new Image(x, y + 200, 40, 40, "./assets/rectangle.png");
    clearButton = new Image(x, y + 240, 40, 40, "./assets/clear.png");
    plusButton = new Image(x,y+280,20,40,"./assets/plus.png");
    minusButton = new Image(x+20,y+280,20,40,"./assets/minus.png");
    sendToBackButton = new Image(x,y+320,20,40,"./assets/send-to-back.png");
    bringToFrontButton = new Image(x+20,y+320,20,40,"./assets/bring-to-front.png");
    mouseButton = new Image(x,y+360,40,40,"./assets/mouse.png");

    tool = PENCIL;
    action = NONE;

    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);
    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    clearButton->box(FL_BORDER_BOX);
    plusButton->box(FL_BORDER_BOX); 
    minusButton->box(FL_BORDER_BOX); 
    polygonButton->box(FL_BORDER_BOX);
    mouseButton->box(FL_BORDER_BOX);
    sendToBackButton->box(FL_BORDER_BOX);
    bringToFrontButton->box(FL_BORDER_BOX);

    visualizeSelectedTool();

    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(plusButton,Toolbar::onClick); 
    ON_CLICK(minusButton,Toolbar::onClick); 
    ON_CLICK(polygonButton,Toolbar::onClick);
    ON_CLICK(mouseButton,Toolbar::onClick);
}