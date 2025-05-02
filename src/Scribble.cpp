#include "Scribble.h"
#include <GL/gl.h>
#include <iostream>
#include <cmath>

void Scribble::addPoint(float x, float y, float r, float g, float b, int size){
    points.push_back(new Point(x, y, r, g, b, size));
}


void Scribble::draw(){
    // We do a little bit of optimizations
    if (!points.size()) return;
    Point* p = points[0];

    glColor3f(p->getR(),p->getG(),p->getB());

    glLineWidth(p->getSize());
    glBegin(GL_LINE_STRIP);
        for (Point* p : points) {
            glVertex2f(p->getX(), p->getY());
        }
    glEnd();
    glPointSize(p->getSize());
    glBegin(GL_POINTS);
        for (Point* p : points) {
            glVertex2f(p->getX(), p->getY());
        }
    glEnd();
    
}

Scribble::~Scribble(){
    for (unsigned int i = 0; i < points.size(); i++){
        delete points[i];
    }
    points.clear();
}

void Scribble::IncreaseSize() {
    for (Point* p : points) {
        p->IncreaseSize();
    }
}

void Scribble::DecreaseSize() {
    for (Point* p : points) {
        p->DecreaseSize();
    }
}

bool Scribble::CollidePoint(float x,float y) {
    float min_x,min_y,max_x,max_y;
    min_x = MAXFLOAT;
    min_y = MAXFLOAT;
    max_x = -MAXFLOAT;
    max_y = -MAXFLOAT;
 
    
    for (Point* p : points) {
        float x = p->getX();
        float y = p->getY();
        if (x < min_x) min_x = x;
        if (y < min_y) min_y = y;
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
    }
    // std::cout << "MIN " <<min_x << min_y <<std::endl;
    // std::cout << "MAX " <<max_x << max_y <<std::endl;
    return (min_x <= x && x <= max_x) && (min_y <= y && y <= max_y);
}

void Scribble::setColor(float r, float g, float b) {
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->setColor(r, g, b);
    }
}    


void Scribble::move(float dx, float dy) {
    for (Point* p : points) {
        p->move(dx,dy);
    }
}