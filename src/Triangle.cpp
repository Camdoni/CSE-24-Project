#include "Triangle.h"
#include <GL/freeglut.h>
#include <math.h>

Triangle::Triangle() {
    x = 0.0;
    y = 0.0;
    base = 0.2;
    height = 0.2;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Triangle::Triangle(float x, float y, float base, float height, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->base = base;
    this->height = height;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
        glVertex2f(x - base/2, y - height/2);
        glVertex2f(x, y + height/2);
        glVertex2f(x + base/2, y - height/2);
    glEnd();
}

void Triangle::IncreaseSize() {
    base += 0.1;       
}
void Triangle::DecreaseSize() {
    base -= 0.1;
    if (base < 0.1) {
        base = 0.1;
    }
}
bool Triangle::CollidePoint(float x,float y) {
    bool inAABB = (abs(x - this->x) <= base / 2) && (abs(y- this->y) <= height / 2);
    if (!inAABB) return false;

    float top = this->y + height / 2;
    float bottom = this->y - height / 2;
    float left = this->x - base/2;
    float right = this->x + base/2;


    float distA = (left-x)*(left-x) + (top-y)*(top-y);
    float distB = (right-x)*(right-x) + (top-y)*(top-y);
    float distC = (this->x-x)*(this->x-x) + (bottom-y)*(bottom-y);

    float minDistAB = fmin(distA,distB);
    return distC <= minDistAB;

}