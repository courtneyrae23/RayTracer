#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__


class Color {
  public:
    float r, g, b;
    Color(float x = 0.0, float y = 0.0, float z = 0.0) {
        r = x;
        g = y;
        b = z;
    }
    Color operator+(const Color&);
    Color operator*(const Color&);
    Color operator*(const float);
    void print();
};

#endif