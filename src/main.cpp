#include <vector>
#include <set>
#include <iostream>

#include "polygon.h"

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<Polygon> S;
  for ( int i = 0; i < m; i++ ) { 
    S.push_back(read_polygon()); 
    print_polygon(i+1, S[i]);
  }

  for ( int i = 0; i < n; i++ )
    print_polygon_set(i+1, read_point(), S);
}
