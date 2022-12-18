#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Grid {
  long size;
  vector<int> content;
  long width;
  long get_fill_height() {
    for (long i = 0; i < content.size(); i += 1) {
      if (content[i] == 1) {
        return get_height() - i / width;
      }
    }
    return 0;
  }
  long get_height() { return content.size() / width; }
  void add_rows(long amount) {
    vector<int> n(amount * width, 0);
    content.insert(content.begin(), n.begin(), n.end());
  }
  string to_str() {
    string res = "";
    long i = 1;
    for (long cell : content) {
      res += cell ? "#" : ".";
      if (i % width == 0) {
        res += "\n";
      }
      i += 1;
    }
    return res;
  }
  bool can_fit(Grid shape, pair<int, int> translate) {
    for (long i = 0; i < shape.content.size(); i += 1) {
      if (!shape.content[i])
        continue;
      long sx = translate.first + i % shape.width;
      if (sx > width - 1 || sx < 0)
        return false;
      long sy = translate.second + i / shape.width;
      if (width * sy + sx >= content.size() || content[width * sy + sx])
        return false;
    }
    return true;
  };
  void add(Grid shape, pair<int, int> translate) {
    for (long i = 0; i < shape.content.size(); i += 1) {
      if (!shape.content[i])
        continue;
      long sx = translate.first + i % shape.width;
      long sy = translate.second + i / shape.width;
      content[width * sy + sx] = 1;
    }
  }
  string get_snapshot() {
    long count = 20 * width;
    string res = "";
    while (count--) {
      res += to_string(content[count]);
    }
    return res;
  }
};

vector<Grid> rocks{{.content = {1, 1, 1, 1}, .width = 4},
                   {.content = {0, 1, 0, 1, 1, 1, 0, 1, 0}, .width = 3},
                   {.content = {0, 0, 1, 0, 0, 1, 1, 1, 1}, .width = 3},
                   {.content = {1, 1, 1, 1}, .width = 1},
                   {.content = {1, 1, 1, 1}, .width = 2}};

int main() {
  ifstream file("data/17");
  string str;
  Grid main{.width = 7};
  vector<int> xShift;
  map<string, pair<int, int>> seen;
  while (getline(file, str)) {
    for (char ch : str) {
      xShift.push_back(ch == '<' ? -1 : 1);
    }
  }

  long T = 1000000000000;
  long count = T;
  long shiftCount = -1;
  long rockCount = -1;
  long res = 0;
  while (count --) {
    rockCount += 1;
    long rockIndex = rockCount % rocks.size();
    Grid shape = rocks[rockIndex];
    pair<int, int> translate{2, 0};
    long fill = main.get_fill_height();
    long need = fill + 3 + shape.get_height() - main.get_height();
    if (need > 0) {
      main.add_rows(need);
    } else {
      translate.second -= need;
    }
    while (true) {
      shiftCount += 1;
      long shift = xShift[shiftCount % xShift.size()];

      if (main.can_fit(shape, {translate.first + shift, translate.second})) {
        translate.first += shift;
      }
      bool canDown =
          main.can_fit(shape, {translate.first, translate.second + 1});
      if (canDown) {
        translate.second += 1;
      } else {
        main.add(shape, translate);
        break;
      }
    }
    if (main.get_height() < 21) continue;
    long shiftIndex = shiftCount % xShift.size();
    string key = to_string(rockIndex) + "-" + to_string(shiftIndex) + "-" +
                 main.get_snapshot();
    if (seen.find(key) != seen.end()) {
      auto found = seen.find(key)->second;
      long prevRockCount = found.first;
      long prevFillHeight = found.second;
      long repeatIteration = rockCount - prevRockCount;
      long repeatHeight = main.get_fill_height() - prevFillHeight;
      long leftIterations = (T - rockCount) / repeatIteration;
      res = leftIterations * repeatHeight;
      count -= leftIterations * repeatIteration;
      seen = {};
    } else {
      seen.insert({key, {rockCount, main.get_fill_height()}});
    }
  }
  cout << main.get_fill_height() + res << endl;
}
