#ifndef __POINT__
#define __POINT__

#define ERR 0.009

class Point {
private:

public:
  Point(double x, double y);
  bool operator==(Point p);
  double x, y;
};

Point read_point();

#endif
