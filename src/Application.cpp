#include "Application.h"
#include "Enums.h"
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;
using namespace std;

#define SELECT_LAST_PLACED

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    lastMX = mx;
    lastMY = my;
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();


    if (tool == PENCIL) {
        canvas->startScribble();
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->eraseShape(mx, my);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) { 
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE) {
        canvas->addTriangle(mx, my, 0.2, 0.2, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addPolygon(mx, my,color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == SELECT) {
        shapeSelected = nullptr;
        if (canvas->shapes.size()) {
            for (signed long long i = canvas->shapes.size()-1; i >=0;i--) {
                Shape* shape = canvas->shapes[i];
                if (shape->CollidePoint(mx, my)) {
                    std::cout << "Shape: " << i <<std::endl;
                    shapeSelected = shape;
                    shapeSelectedIndex = i;
                    break;
                }   
            }
        }
    }
#ifdef SELECT_LAST_PLACED
    if (tool == RECTANGLE || tool == TRIANGLE || tool == CIRCLE || tool == POLYGON) {
        shapeSelectedIndex = canvas->shapes.size()-1;
        shapeSelected = canvas->shapes[shapeSelectedIndex];
    }
#endif

}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
#ifdef SELECT_LAST_PLACED
    if (canvas->endScribble()) {
        shapeSelectedIndex = canvas->shapes.size()-1;
        shapeSelected = canvas->shapes[shapeSelectedIndex];
    }
#else
    canvas->endScribble();
#endif

}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    float dx = mx - lastMX;
    float dy = my - lastMY;
    lastMX = mx;
    lastMY = my;
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
    canvas->eraseShape(mx, my);
    canvas->redraw();
}
    else if (tool == SELECT) {
        if (shapeSelected != nullptr) {
            
            shapeSelected->move(dx, dy);
            canvas->redraw();

        }
    }
}


void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();
    if (action == CLEAR) {
        canvas->clear();
        shapeSelected = nullptr;
    }
    else if (action == SEND_TO_BACK) {
        std::cout << "SEND TO BACK" <<std::endl;
        if (canvas->shapes.size() && shapeSelected != nullptr) {
            if (canvas->shapes[shapeSelectedIndex] == shapeSelected) {
                Shape* first = canvas->shapes[0];
                canvas->shapes[0] = shapeSelected;
                canvas->shapes[shapeSelectedIndex] = first;
                shapeSelectedIndex = 0;
            }
        } 

    }
    else if (action == SEND_TO_FRONT) {
        std::cout << "SEND TO FRONT" <<std::endl;
        if (canvas->shapes.size() && shapeSelected != nullptr) {
            if (canvas->shapes[shapeSelectedIndex] == shapeSelected) {
                Shape* last = canvas->shapes[canvas->shapes.size()-1];
                canvas->shapes[canvas->shapes.size()-1] = shapeSelected;
                canvas->shapes[shapeSelectedIndex] = last;
                shapeSelectedIndex = canvas->shapes.size()-1;
            }
        } 
    }
    else if (action == SIZE_INCREASE) { 
        std::cout << "SIZE INCREASE" <<std::endl;

        if (canvas->shapes.size() && shapeSelected != nullptr) {
            if (canvas->shapes[shapeSelectedIndex] == shapeSelected) {
                shapeSelected->IncreaseSize();
            }
        }
    }
    else if (action == SIZE_DECREASE) {
        std::cout << "SIZE DECREASE" <<std::endl;
        if (canvas->shapes.size() && shapeSelected != nullptr) {
            if (canvas->shapes[shapeSelectedIndex] == shapeSelected) {
                shapeSelected->DecreaseSize();
            }
        }
    }
    canvas->redraw();

}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();

    if (shapeSelected) {
        std::cout << "Updating selected shape's color" << std::endl;
        shapeSelected->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw(); 
    }
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Pain Application");

    toolbar = new Toolbar(0, 0, 50, 400);
    canvas = new Canvas(40, 0, 350, 350);
    colorSelector = new ColorSelector(50, 350, 350, 50);
    shapeSelected = nullptr;
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);
    window->show();
}