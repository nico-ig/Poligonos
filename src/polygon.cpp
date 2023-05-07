#include <iostream>
#include <cmath>
#include "polygon.h"

Polygon read_polygon() {
  int v;
  std::cin >> v; 

  std::vector<Point> vertices;
  while ( v-- ) { vertices.push_back(read_point()); }

  return Polygon(vertices);
}

void print_polygon(int i, Polygon p) {
  std::cout << i;
  if ( !p.is_simple() ) { std::cout << " nao simples\n"; return; }
  std::cout << " simples e ";
  if ( p.is_convex() ) { std::cout << "convexo\n"; }
  else { std::cout << "nao convexo\n"; }
}

void print_polygon_set(int i, Point p, std::vector<Polygon> S) {
  std::cout << i << ":";
  bool is_first = true;
  for ( size_t j = 0; j < S.size(); j++ )
    if ( S[j].is_simple() && S[j].contains(p) ) { 
      if ( !is_first ) { std::cout << " "; }
      std::cout << j+1; 
      is_first = false;
    }   
  std::cout << "\n";
}

void Polygon::mount_edges() {
  this->last_x = std::max(vertices[0].x, vertices[vertices.size() - 1].x);

  for ( size_t i = 0; i < vertices.size() - 1; i++ ) {
    edges.push_back(Edge(vertices[i], vertices[i+1]));
    this->last_x = std::max(this->last_x, vertices[i].x);
  }

  edges.push_back(Edge(vertices[vertices.size() - 1], vertices[0]));
}  

void Polygon::check_simple() {
  if ( this->edges.size() < 3 ) { this->simple = false; return; }
    
  this->simple = true;
  for ( size_t i = 0; i < edges.size() && this->simple; i++ ) {
    Edge e = edges[i];
    if ( e.length() == 0 ) { this->simple = false; break; }
    for ( size_t j = i + 1; j < edges.size() && this->simple; j++ ) {
      Edge e1 = edges[j];
      if ( e1.length() == 0 || e.intersect(e1) ) { 
        this->simple = false; }
    } 
  }
}

void Polygon::check_convex() {
  if ( this->edges.size() < 3 ) { this->convex = false; return; }

  int ori;
  this->edges[0].scalar_product(this->edges[1]) > 0 ? ori = 1 : ori = -1;
  this->convex = true;

  for ( size_t i = 1; i < this->edges.size() - 1 && this->convex; i++ ) {
    Edge e = this->edges[i];
    Edge e1 = this->edges[i+1];
    if ( ori * e.scalar_product(e1) <= 0 ) { this->convex = false; }
  }

  if ( this->convex ) {
    Edge e = this->edges[this->edges.size() - 1];
    Edge e1 = this->edges[0];
    this->convex = ori * e.scalar_product(e1) > 0;
  }
}

bool Polygon::contains(Point p) {
  if ( p.x > this->last_x + ERR ) { return false; }
  Edge h(p, Point(last_x + 10, p.y));
  int cnt = 0;
  bool vertex_counted = false;
  for ( Edge e : this->edges ) {
    if ( (e.is_vertex(p) && !vertex_counted) || (h.intersect(e) && !(h.contains(e.A) && h.contains(e.B))) ) { 
      cnt++; 
      vertex_counted = true;
    }
  }

  return cnt % 2;
}

Polygon::Polygon(std::vector<Point> v) : vertices(v) { 
  this->mount_edges();
  this->check_simple();  
  if ( this->simple ) { this->check_convex(); } 
}

std::vector<Point>::iterator Polygon::begin() { return vertices.begin(); }
std::vector<Point>::iterator Polygon::end() { return vertices.end(); }
size_t Polygon::size() { return vertices.size(); }
bool Polygon::is_convex() { return this->convex; }
bool Polygon::is_simple() { return simple; }

