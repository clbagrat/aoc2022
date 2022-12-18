#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct V3 {
  int x;
  int y;
  int z;

  string to_str() {
    return to_string(x) + "," + to_string(y) + "," + to_string(z);
  }

  double distance(V3 other) {
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2) +
                pow(other.z - z, 2));
  };
};

class Shape {
public:
  int surface;
  vector<V3> pixels;

  void add_pixel(V3 pixel) {
    int connections = get_connecting_count(pixel);
    pixels.push_back(pixel);
    surface -= connections;
    surface += (6 - connections);
  }

  int get_connecting_count(V3 other) {
    int res = 0;
    for (V3 pixel : pixels) {
      if (pixel.distance(other) == 1) {
        res += 1;
      }
    }
    return res;
  }
};

int main() {
  ifstream file("data/18");
  string str;
  Shape mainShape;

  while (getline(file, str)) {
    int x;
    int y;
    int z;
    sscanf(str.c_str(), "%d,%d,%d", &x, &y, &z);
    V3 vec {.x = x, .y = y, .z = z};
    mainShape.add_pixel(vec);
  }
    cout <<  mainShape.surface << endl;
}
