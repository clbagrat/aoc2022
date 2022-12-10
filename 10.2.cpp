#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

int width = 40;

void update_cycle(int &cycles, int x, string &res) {
  int pixel = cycles % width;

  if (pixel == x - 1 || pixel == x || pixel == x + 1) {
    res += "#";
  } else {
    res += ".";
  }
  cycles += 1;
}

int main() {
  ifstream file("data/10");
  string str;
  regex numReg("-?\\d+$");
  int cycles;
  int X = 1;
  int sum;
  string res;

  while (getline(file, str)) {
    string operation = str.substr(0, str.find(" "));
    if (operation == "noop") {
      update_cycle(cycles, X, res);
    } else {
      smatch matches;
      regex_search(str, matches, numReg);
      if (matches.size() > 0) {
        int num = stoi(matches[0]);
        update_cycle(cycles, X, res);
        update_cycle(cycles, X, res);
        X += num;
      }
    }
  }

  for (int h = 0; h < 6; h += 1) {
    cout << res.substr(h * 40, 40) << endl;
  }
}
