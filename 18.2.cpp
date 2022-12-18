#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
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

  vector<V3> get_neighbors() {
    vector<V3> res;
    res.push_back((V3){.x = x + 1, .y = y, .z = z});
    res.push_back((V3){.x = x - 1, .y = y, .z = z});
    res.push_back((V3){.x = x, .y = y + 1, .z = z});
    res.push_back((V3){.x = x, .y = y - 1, .z = z});
    res.push_back((V3){.x = x, .y = y, .z = z + 1});
    res.push_back((V3){.x = x, .y = y, .z = z - 1});
    return res;
  }
};
V3 create_v3(string str) {
  int x;
  int y;
  int z;
  sscanf(str.c_str(), "%d,%d,%d", &x, &y, &z);
  return {.x = x, .y = y, .z = z};
}

class Shape {
public:
  set<string> pixels;
  int mx = 1000000;
  int my = 1000000;
  int mz = 1000000;
  int Mx = -10000;
  int My = -10000;
  int Mz = -10000;

  void add_pixel(V3 pixel) {
    pixels.insert(pixel.to_str());
    mx = min(mx, pixel.x);
    my = min(my, pixel.y);
    mz = min(mz, pixel.z);
    Mx = max(Mx, pixel.x);
    My = max(My, pixel.y);
    Mz = max(Mz, pixel.z);
  }

  int get_surface() {
    queue<V3> q;
    int bx = mx - 1;
    int by = my - 1;
    int bz = mz - 1;
    int Bx = Mx + 1;
    int By = My + 1;
    int Bz = Mz + 1;

    q.push({.x = bx, .y = by, .z = bz});
    set<string> seen;
    int res = 0;

    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      for (V3 n : cur.get_neighbors()) {
        if (n.z > Bz || n.x > Bx || n.y > By || n.x < bz || n.y < by ||
            n.z < bz) {
          continue;
        }
        if (pixels.find(n.to_str()) != pixels.end()) {
          res += 1;
          continue;
        }
        if (seen.find(n.to_str()) == seen.end()) {
          seen.insert(n.to_str());
          q.push(n);
        }
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
    mainShape.add_pixel(create_v3(str));
  }
  cout << mainShape.get_surface() << endl;
}
