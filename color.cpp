#include "color.h"
#include <iostream>
using namespace std;

Color Color::operator+(const Color& color) {
    Color* c = new Color();
    c->r = r + color.r;
    c->g = g + color.g;
    c->b = b + color.b;
    return *c;
}

Color Color::operator*(const Color& color) {
    Color* c = new Color();
    c->r = r * color.r;
    c->g = g * color.g;
    c->b = b * color.b;
    return *c;
}

Color Color::operator*(const float f) {
    Color* c = new Color();
    c->r = r * f;
    c->g = g * f;
    c->b = b * f;
    return *c;
}

void Color::print() {
    cout << "Color: " << "(" << r << "," << g << "," << b << ")" << endl;
}