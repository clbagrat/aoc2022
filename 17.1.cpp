#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Grid {
  vector<int> content;
  int width;
  int get_fill_height() {
    for (int i = 0; i < content.size(); i += 1) {
      if (content[i] == 1) {
        return get_height() - i / width;
      }
    }
    return 0;
  }
  int get_height() { return content.size() / width; }
  void add_rows(int amount) {
    vector<int> n(amount * width, 0);
    content.insert(content.begin(), n.begin(), n.end());
  }
  string to_str() {
    string res = "";
    int i = 1;
    for (int cell : content) {
      res += cell ? "#" : ".";
      if (i % width == 0) {
        res += "\n";
      }
      i += 1;
    }
    return res;
  }
  bool can_fit(Grid shape, pair<int, int> translate) {
    for (int i = 0; i < shape.content.size(); i += 1) {
      if (!shape.content[i])
        continue;
      int sx = translate.first + i % shape.width;
      if (sx > width - 1 || sx < 0)
        return false;
      int sy = translate.second + i / shape.width;
      if (width * sy + sx >= content.size() || content[width * sy + sx])
        return false;
    }
    return true;
  };
  void add(Grid shape, pair<int, int> translate) {
    for (int i = 0; i < shape.content.size(); i += 1) {
      if (!shape.content[i])
        continue;
      int sx = translate.first + i % shape.width;
      int sy = translate.second + i / shape.width;
      content[width * sy + sx] = 1;
    }
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
  while (getline(file, str)) {
    for (char ch : str) {
      xShift.push_back(ch == '<' ? -1 : 1);
    }
  }

  int count = 2022;
  int shiftCount = -1;
  int rockCount = -1;
  while (count--) {
    rockCount += 1;
    Grid shape = rocks[rockCount % rocks.size()];
    pair<int, int> translate{2, 0};
    int fill = main.get_fill_height();
    int need = fill + 3 + shape.get_height() - main.get_height();
    if (need > 0) {
      main.add_rows(need);
    } else {
      translate.second -= need;
    }

    while (true) {
      shiftCount += 1;
      int shift = xShift[shiftCount % xShift.size()];

      if (main.can_fit(shape, {translate.first + shift, translate.second})) {
        translate.first += shift;
      }
      if (main.can_fit(shape, {translate.first, translate.second + 1})) {
        translate.second += 1;
      } else {
        main.add(shape, translate);
        break;
      }
    }
  }
  cout << main.get_fill_height() << endl;
}
