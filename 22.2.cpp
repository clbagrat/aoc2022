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

class Grid {
  int px = 50;
  int py = 0;
  int dx = 0;
  int dy = -1;

public:
  vector<char> points;
  int width;
  int height;
  string to_str() {
    return to_string(px) + "-" + to_string(py) +
           " char: " + points[px * width + py];
  }
  void move(Instruction instruction) {
    if (instruction.rotate == "R") {
      int b = -dy;
      dy = dx;
      dx = b;
    } else {
      int b = dy;
      dy = -dx;
      dx = b;
    }
    int stepsLeft = instruction.steps;
    while (stepsLeft--) {
      int cdy = dy;
      int cdx = dx;
      int ny = py + dy;
      int nx = px + dx;
      if (ny < 0 && 50 <= nx && nx < 100 && dy == -1) {
        dy = 0;
        dx = 1;
        ny = nx + 100;
        nx = 0;
      } else if (nx < 0 && 150 <= ny && ny <= 200 && dx == -1) {
        dy = 1;
        dx = 0;
        nx = ny - 100;
        ny = 0;
      } else if (ny < 0 && 100 <= nx && nx < 150 && dy == -1) {
        nx = nx - 100;
        ny = 199;
      } else if (ny >= 200 && 0 <= nx && nx < 50 && dy == 1) {
        ny = 0;
        nx = nx + 100;
      } else if (nx >= 150 && 0 <= ny && ny < 50 && dx == 1) {
        dx = -1;
        ny = 149 - ny;
        nx = 99;
      } else if (nx == 100 && 100 <= ny && ny < 150 && dx == 1) {
        dx = -1;
        ny = 149 - ny;
        nx = 149;
      } else if (ny == 50 && 100 <= nx && nx < 150 && dy == 1) {
        dy = 0;
        dx = -1;
        ny = nx - 50;
        nx = 99;
      } else if (nx == 100 && 50 <= ny && ny < 100 && dx == 1) {
        dy = -1;
        dx = 0;
        nx = ny + 50;
        ny = 49;
      } else if (ny == 150 && 50 <= nx && nx < 100 && dy == 1) {
        dy = 0;
        dx = -1;
        ny = nx + 100;
        nx = 49;
      } else if (nx == 50 && 150 <= ny && ny <= 200 && dx == 1) {
        dy = -1;
        dx = 0;
        nx = ny - 100;
        ny = 149;
      } else if (ny == 99 && 0 <= nx && nx < 50 && dy == -1) {
        dy = 0;
        dx = 1;
        ny = nx + 50;
        nx = 50;
      } else if (nx == 49 && 50 <= ny && ny < 100 && dx == -1) {
        dy = 1;
        dx = 0;
        nx = ny - 50;
        ny = 100;
      } else if (nx == 49 && 0 <= ny && ny < 50 && dx == -1) {
        dx = 1;
        ny = 149 - ny;
        nx = 0;
      } else if (nx < 0 && 100 <= ny && ny < 150 && dx == -1) {
        dx = 1;
        ny = 149 - ny;
        nx = 50;
      }
      if (points[ny * width + nx] == '#') {
        dy = cdy;
        dx = cdx;
        break;
      }
      px = nx;
      py = ny;
    };
  };
  int get_result() {
    int d = 0;
    if (dy == 0) {
      if (dx == 1) {
        d = 0;
      } else {
        d = 2;
      }
    } else {
      if (dy == 1) {
        d = 1;
      } else {
        d = 3;
      }
    }
    return 1000 * (px + 1) + 4 * (py + 1) + d;
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
    if (str == "")
      break;
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
      while (left--) {
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
