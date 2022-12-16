#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>

using namespace std;

int distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

struct Sensor {
  int x;
  int y;
  int d;
};

int main() {
  ifstream file("data/15");
  string str;
  regex numPairs("-?\\d+");
  vector<Sensor> sensors;
  set<pair<int, int>> beacons;

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
    int d = distance(sx, sy, bx, by);
    sensors.push_back({.x = sx, .y = sy, .d = d});
    beacons.insert({bx, by});
  }

  //  sort(sensors.begin(), sensors.end(),
  //       [](const Sensor &lhs, const Sensor &rhs) {
  //         return lhs.x - lhs.d < rhs.x - rhs.d;
  //       });
  //
  //  for (auto s : sensors) {
  //    cout << s.x << " " << s.y << " " << s.d << endl;
  //  }

  int y = 0;
  int border = 4000000;
  // border = 20;
  while (y < border) {
    vector<pair<int, int>> ranges;
    for (auto s : sensors) {
      int offset = s.d - abs(y - s.y);
      if (offset < 0) {
        continue;
      }
      if (offset == 0) {
      }
      int low = s.x - offset;
      int high = s.x + offset;
      ranges.push_back({low, high});
    }

    sort(ranges.begin(), ranges.end(),
         [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
           return lhs.first < rhs.first;
         });

    vector<pair<int, int>> q;
    for (auto r : ranges) {
      if (q.size() == 0) {
        q.push_back(r);
        continue;
      }
      int qLow = q.back().first;
      int qHigh = q.back().second;
      if (r.first > qHigh + 1) {
        q.push_back(r);
        continue;
      }
      q.back().second = max(qHigh, r.second);
    }

    int res = 0;
    for (auto r : q) {
      if (res < r.first) {
        long asd = ((long)res * (long)4000000) + (long)y;
        cout << res << " " << y << endl;
        cout << asd << endl;

        return 0;
      } else {
        res = r.second + 1;
      }
    }
    y += 1;
  }
}
