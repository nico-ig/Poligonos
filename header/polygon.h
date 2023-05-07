#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include <cstddef>
#include "edge.h"
#include "point.h"

class Polygon {
private:
  bool simple;
  bool convex;
  double last_x;
  std::vector<Point> vertices;
  std::vector<Edge> edges;

  void mount_edges();      
  void check_simple();
  void check_convex();

public:
  Polygon(std::vector<Point> v);

  size_t size(); 
  bool is_simple(); 
  bool is_convex(); 
  bool contains(Point p);
  std::vector<Point>::iterator begin(); 
  std::vector<Point>::iterator end();
};

Polygon read_polygon();
void print_polygon(int i, Polygon p);
void print_polygon_set(int i, Point p, std::vector<Polygon> S);

#endif
