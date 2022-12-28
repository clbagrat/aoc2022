#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using coord = pair<int, int>;

struct hashFunction {
  size_t operator()(const pair<int, int> &x) const {
    return x.first ^ x.second;
  }
};

typedef unordered_set<coord, hashFunction> CoordHash;

vector<coord> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
vector<coord> counterWinds = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool inWind(vector<CoordHash> *winds, coord pos, int time, int width,
            int height) {
  if (pos.second < 0 || pos.first < 0 || pos.second >= height ||
      pos.first >= width)
    return false;

  for (int i = 0; i < counterWinds.size(); i += 1) {

    coord check = {
        ((pos.first - counterWinds[i].first * time) % width + width) % width,
        ((pos.second - counterWinds[i].second * time) % height + height) %
            height};

    if (winds->at(i).find(check) != winds->at(i).end()) {
      return true;
    }
  }
  return false;
}

int solve(vector<CoordHash> winds, coord start, coord target, int width,
          int height, int startTime) {
  queue<pair<coord, int>> q = {};
  unordered_set<string> seen = {};
  q.push({start, startTime});

  while (!q.empty()) {
    coord oldCoord = q.front().first;
    int time = q.front().second + 1;
    q.pop();

    for (coord move : moves) {
      coord newCoord = {oldCoord.first + move.first,
                        oldCoord.second + move.second};
      if (newCoord == target) {
        return time;
      }
      if (newCoord != start &&
          (newCoord.first < 0 || newCoord.second < 0 ||
           newCoord.first >= width || newCoord.second >= height)) {
        continue;
      }
      if (inWind(&winds, newCoord, time, width, height)) {
        continue;
      }
      string key = to_string(newCoord.first) + "-" +
                   to_string(newCoord.second) + "-" + to_string(time);

      if (seen.find(key) == seen.end()) {
        q.push({newCoord, time});
        seen.insert(key);
      }
    }
  }

  return -1;
}

int main() {
  ifstream file("data/24");
  string str;
  CoordHash lw = {};
  CoordHash rw = {};
  CoordHash uw = {};
  CoordHash dw = {};
  int y = 0;
  int x = 0;
  while (getline(file, str)) {
    x = 0;
    for (char ch : str) {
      if (ch == '<') {
        lw.insert({x, y});
      }
      if (ch == '>') {
        rw.insert({x, y});
      }
      if (ch == '^') {
        uw.insert({x, y});
      }
      if (ch == 'v') {
        dw.insert({x, y});
      }
      x += 1;
    }
    y += 1;
  }
  coord start = {0, -1};
  coord target = {x - 1, y};
  vector<CoordHash> winds = {lw, rw, uw, dw};
  int firstRun = solve(winds, start, target, x, y, 0);
  int secondRun = solve(winds, target, start, x, y, firstRun);
  int thirdRun = solve(winds, start, target, x, y, secondRun);
  cout << firstRun << " " << secondRun << " " << thirdRun << endl;
}
