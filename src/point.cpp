#include <iostream>
#include "point.h"

Point read_point() {
  double x, y;
  std::cin >> x >> y;

  return Point(x, y);
}

Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator==(Point p) { 
  return abs(p.x - x) <= ERR && abs(p.y - y) <= ERR; 
}
