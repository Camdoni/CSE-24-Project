#include "Polygon.h"
#include <GL/freeglut.h>
#include <cmath>
#include <math.h>
#include <iostream>

Polygon::Polygon() {
    x = 0.0;
    y = 0.0;
    sides = 5;
    length = 0.1;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Polygon::Polygon(float x, float y, int sides, float length, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->sides = sides;
    this->length = length;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
        float k = 2* M_PI / sides;
        for (int i = 0; i < sides; i++) {
            float theta = i * k;
            glVertex2f(x + length * cos(theta), y + length * sin(theta));
        }
    glEnd();
}

void Polygon::IncreaseSize() {
    length += 0.1;
}
void Polygon::DecreaseSize() {
    length -= 0.1;
    if (length < 0.1) {
        length = 0.1;
    }
}
float truemod(float x,float y) {
    float a = fmod(x,y);
    if (a < 0) {
        a += y;
    }
    return a;
}


bool Polygon::CollidePoint(float x,float y) {
    float dy = y-this->y;
    float dx = x-this->x;
    float sqrDst = dx*dx+dy*dy;
    if (sqrDst>length*length) return false;
    double theta = atan2(dy,dx);
    const float t_0_2 = M_PI / this->sides;
    const float numerator = cos(t_0_2);
    const float denominator = cos(truemod(theta, 2*t_0_2)-t_0_2);
    float dist_inside = length * numerator / denominator;
    std::cout << "Theta:  " << theta << std::endl;
    std::cout << "T_0_2:  " << t_0_2 << std::endl;
    std::cout << "Radius: " << dist_inside << std::endl;
    return sqrDst < dist_inside*dist_inside;
}