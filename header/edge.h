#ifndef __EDGE__
#define __EDGE__

#include "point.h"

class Edge {
private:
  double len;
  bool is_vertical;
  void check_vertical();
  bool is_collinear(Edge h);
  bool intersect_collinear(Edge h); 
  void calc_length();

public:
  Edge(Point A, Point B);

  double length();
  bool is_vertex(Point p);
  bool is_edge(Point p);
  bool contains(Point p);
  bool intersect(Edge h);
  double scalar_product(Edge e);

  double b, m;
  Point A, B;
};

#endif
