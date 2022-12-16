#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>

using namespace std;

int distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
  ifstream file("data/15");
  string str;
  regex numPairs("-?\\d+");
  set<pair<int, int>> res;
  set<pair<int, int>> antiRes;

  int target = 2000000;
  while (getline(file, str)) {
    smatch match;
    vector<int> coords;
    while (regex_search(str, match, numPairs)) {
      coords.push_back(stoi(match.str()));
      str = match.suffix();
    }
    int sx = coords[0];
    int sy = coords[1];
    int bx = coords[2];
    int by = coords[3];
    if (sy == target) {
      res.insert({sx, sy});
    }
    if (by == target) {
      antiRes.insert({bx, by});
    }
    int d = distance(sx, sy, bx, by);
    cout << d << endl;
    if (sy > target && sy - d <= target || sy < target && sy + d >= target) {
      int x = sx - d;
      while (x < sx + d) {
        if (distance(sx, sy, x, target) <= d) {
          res.insert({x, target});
        }
        x += 1;
      }
    }
  }
  cout << res.size() - antiRes.size() << endl;
}
