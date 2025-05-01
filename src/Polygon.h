#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"

class Polygon : public Shape {
    float x;
    float y;
    int sides;
    float length;
    float r;
    float g;
    float b;

public:
    Polygon();
    Polygon(float x, float y, int sides, float length, float r, float g, float b);

    void draw();
    void IncreaseSize();
    void DecreaseSize();
    bool CollidePoint(float,float);
    void setColor(float r, float g, float b);
    void setPosition(float x, float y);
};

#endif