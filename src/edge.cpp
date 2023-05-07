#include <cmath>
#include <iostream>
#include "edge.h"

void Edge::check_vertical() {
  if ( abs(A.x - B.x) <= ERR ) { is_vertical = true; }
  else 
  { 
    m = (B.y - A.y) / (B.x - A.x);
    b = A.y - m * A.x; 
    is_vertical = false; 
  }
}

void Edge::calc_length() {
  double dx = pow(A.x - B.x, 2);
  double dy = pow(A.y - B.y, 2);
  this->len = sqrt(dx + dy); 
}

double Edge::length() { return this->len; }

Edge::Edge(Point A, Point B) : A(A), B(B) {
  this->calc_length();
  this->check_vertical();
}

bool Edge::is_vertex(Point p) {
  return p == A || p == B;
}

bool Edge::contains(Point p) {
  double xMin = std::min(A.x, B.x);
  double xMax = std::max(A.x, B.x);
  double yMin = std::min(A.y, B.y);
  double yMax = std::max(A.y, B.y);

  if ((p.x >= (xMin-ERR) && p.x <= (xMax+ERR)) 
      && (p.y >= (yMin-ERR) && p.y <= (yMax+ERR))) { return true; }
  return false;
}

bool Edge::is_collinear(Edge h) {
  return (this->is_vertical && h.is_vertical) || 
         ((!this->is_vertical && !h.is_vertical) 
          && std::abs(this->m - h.m) <= ERR);
}

bool Edge::intersect_collinear(Edge h) {
  if ( this->contains(h.A) && !this->is_vertex(h.A) ) { return true; }
  if ( this->contains(h.B) && !this->is_vertex(h.B) ) { return true; }
  return false;
}

bool Edge::intersect(Edge h) {
  if ( this->is_collinear(h) ) {
    return this->intersect_collinear(h);
  }

  if ( this->is_vertical || h.is_vertical ) { 
    double vx, y, hxMin, hxMax, vyMin, vyMax;  

    if ( h.is_vertical ) { 
      vx = h.A.x;
      y = this->m * vx + this->b;
      hxMin = std::min(this->A.x, this->B.x);
      hxMax = std::max(this->A.x, this->B.x);
      vyMin = std::min(h.A.y, h.B.y);
      vyMax = std::max(h.A.y, h.B.y);
    }

    else {
      vx = this->A.x;
      y = h.m * vx + h.b;
      hxMin = std::min(h.A.x, h.B.x);
      hxMax = std::max(h.A.x, h.B.x);
      vyMin = std::min(this->A.y, this->B.y);
      vyMax = std::max(this->A.y, this->B.y);
    }

    if ( hxMin - vx > ERR || vx - hxMax > ERR ) { return false; }
    if ( y > (vyMax - ERR) || y < (vyMin + ERR) ) { return false; } 
    if ( this->is_vertex({vx, y}) && h.is_vertex({vx, y}) ) { return false; }
    return true;
  } 

  double x = (this->b - h.b) / (h.m - this->m);
  double y = this->m * x + this->b;

  Point p(x, y);
  if ( this->contains(p) && !this->is_vertex(p) ) 
    if ( h.contains(p) && !h.is_vertex(p) ) { return true; } 

  return false;
}

double Edge::scalar_product(Edge e) {
  double x1 = this->B.x - this->A.x;
  double y1 = this->B.y - this->A.y;
  double x2 = e.B.x - e.A.x;
  double y2 = e.B.y - e.A.y;
  return x1*y2 - y1*x2;
}
