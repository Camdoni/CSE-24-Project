#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
class Triangle : public Shape {
    float x;
    float y;
    float base;
    float height;
    float r;
    float g;
    float b;

public:
    Triangle();
    Triangle(float x, float y, float base, float height, float r, float g, float b);

    void draw();
    void IncreaseSize();
    void DecreaseSize();
    bool CollidePoint(float,float);
    void setColor(float r, float g, float b);
    void move(float, float);
};

#endif