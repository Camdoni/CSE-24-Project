#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <bobcat_ui/bobcat_ui.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    Canvas* canvas;
    ColorSelector* colorSelector;
    Shape* shapeSelected;
    size_t shapeSelectedIndex;
    float lastMX,lastMY;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onColorSelectorChange(bobcat::Widget* sender);

public:
    Application();

    friend struct::AppTest;
};


#endif