#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct Instruction {
  string rotate;
  int steps;
  string to_str() { return rotate + to_string(steps); }
};

vector<pair<int, int>> directions{
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

class Grid {
  pair<int, int> pos = {-1, 0};
  int dir = 3;
  bool goInDirection(pair<int, int> dir) {
    pair<int, int> p = pos;

    while (true) {
      int nextX = p.first + dir.first;
      int nextY = p.second + dir.second;

      if (nextX < 0) {
        nextX = width - 1;
      } else {
        nextX = nextX % width;
      }
      if (nextY < 0) {
        nextY = height - 1;
      } else {
        nextY = nextY % height;
      }
      char point = points[nextY * width + nextX];
      cout << point << " " << nextX << " " << nextY << endl;
      if (point == ' ') {
        p = {nextX, nextY};
        continue;
      }
      if (point == '.') {
        pos = {nextX, nextY};
        return true;
      }
      if (point == '#') {
        return false;
      }
    }
  };

public:
  vector<char> points;
  int width;
  int height;
  string to_str() {
    return to_string(pos.first) + "-" + to_string(pos.second) +
           " char: " + points[pos.second * width + pos.first];
  }
  void move(Instruction instruction) {
    if (instruction.rotate == "R") {
      dir = (dir + 1) % directions.size();
    } else {
      dir = (dir - 1) < 0 ? directions.size() - 1 : dir - 1;
    }
    int stepsLeft = instruction.steps;
    while (stepsLeft--) {
      bool wasAbleTo = goInDirection(directions[dir]);
      if (!wasAbleTo) {
        return;
      }
    }
  };
  int get_result() {
    return 1000 * (pos.second + 1) + 4 * (pos.first + 1) + dir;
  }
};

int main() {
  ifstream file("data/22");
  string str;
  regex numReg("^\\d+");
  regex charReg("^(L|R)");
  Grid *grid = new Grid();
  vector<Instruction> instructions;
  bool metDivider;

  while (getline(file, str)) {
    if (str == "") break;
    grid->width = max((int)str.length(), grid->width);
    grid->height += 1;
  }
  file.close();
  file.open("data/22");
  while (getline(file, str)) {
    if (str == "") {
      metDivider = true;
      continue;
    }
    if (!metDivider) {
      for (char ch : str) {
        grid->points.push_back(ch);
      }
      int left = grid->width - str.length();
      while (left--){
        grid->points.push_back(' ');
      }
    } else {
      while (str.length()) {
        Instruction cur = {.rotate = "R"};
        smatch rMatch;
        if (regex_search(str, rMatch, charReg)) {
          cur.rotate = rMatch.str();
          str = rMatch.suffix();
        }

        smatch nMatch;
        if (regex_search(str, nMatch, numReg)) {
          cur.steps = stoi(nMatch.str());
          str = nMatch.suffix();
        }
        instructions.push_back(cur);
      }
    }
  }

  for (auto d : instructions) {
    grid->move(d);
  }

  cout << grid->to_str() << endl;
  cout << grid->get_result() << endl;
}
