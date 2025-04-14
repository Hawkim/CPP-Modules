#include "Point.hpp"

static Fixed sign(Point p1, Point p2, Point p3) {
    return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - 
           (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed d1 = sign(point, a, b);
    Fixed d2 = sign(point, b, c);
    Fixed d3 = sign(point, c, a);

    // Check if all signs are positive or all are negative
    bool all_positive = (d1 > 0) && (d2 > 0) && (d3 > 0);
    bool all_negative = (d1 < 0) && (d2 < 0) && (d3 < 0);
    //exactly on edge
    bool on_edge = (d1 == 0) || (d2 == 0) || (d3 == 0);

    return (all_positive || all_negative) && !on_edge;
}