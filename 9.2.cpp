#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Vector2 {
public:
  double x;
  double y;

  Vector2(double X, double Y) {
    x = X;
    y = Y;
  };

  void operator += (Vector2 const &other) {
    x += other.x;
    y += other.y;
  }

  Vector2 operator - (Vector2 const &other) {
    Vector2 res(x - other.x, y - other.y);

    return res; 
  };
  
  Vector2 operator + (Vector2 const &other) {
    Vector2 res(other.x + x, other.y + y);

    return res; 
  };

  void operator >> (Vector2 const &other) {
    if (other.x > 0) {
      x += (int)ceil(other.x);
    } else {
      x += (int)floor(other.x);
    }

    if (other.y > 0) {
      y += (int)ceil(other.y);
    } else {
      y += (int)floor(other.y);
    }
  };

  double magnitude() { return sqrt(x * x + y * y); };

  Vector2 normalized() {
    double m = magnitude();
    Vector2 res(x/m, y/m);

    return res;
  }

  string toString() {
    return to_string((int)x) + "-" + to_string((int)y);
  }
};


int main() {
  ifstream file("data/9");
  string str;

  map<string, Vector2*> directions {
    { "R", new Vector2(1, 0) },
    { "L", new Vector2(-1, 0) },
    { "U", new Vector2(0, 1) },
    { "D", new Vector2(0, -1) },
  };

  set<string> visited {"0-0"};
  int bodyLength = 9;

  Vector2 head(0, 0);
  vector<Vector2*> body(9);
  while(bodyLength--) {
    body[bodyLength] = new Vector2(0, 0);
  }
  auto tail = body[8];

  while (getline(file, str)) {
    string d = str.substr(0, str.find(" "));
    int steps = stoi(str.substr(str.find(" ") + 1, str.length()));

    while (steps--) {
      head >> *directions[d];
      auto prev = &head;
      for (int i = 0; i < body.size(); i += 1) {
        auto bodyPart = body[i];
        double magnitude = (*prev - *bodyPart).magnitude();
        if (magnitude >= 1.5) {
          Vector2 normalized = (*prev - *bodyPart).normalized();
          *bodyPart >> normalized;
          if (bodyPart == tail) {
            visited.insert(tail->toString());
          }
        }
        prev = bodyPart;
      }
    }
  }

  cout << visited.size();
}
