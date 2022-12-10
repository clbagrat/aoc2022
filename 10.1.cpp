#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

void update_cycle(int &cycles, int &sum, int x) {
  cycles += 1;
  if (cycles == 20 || (cycles - 20) % 40 == 0) {
    sum += cycles * x;
  } 
}

int main() {
  ifstream file("data/10");
  string str;
  regex numReg("-?\\d+$");
  int cycles;
  int X = 1;
  int sum;

  while (getline(file, str)) {
    string operation = str.substr(0, str.find(" "));
    if (operation == "noop") {
      update_cycle(cycles, sum, X);
    } else {
      smatch matches;
      regex_search(str, matches, numReg);
      if (matches.size() > 0) {
        int num = stoi(matches[0]);
        update_cycle(cycles, sum, X);
        update_cycle(cycles, sum, X);
        X += num;
      }
    }
  }
  cout << sum;
}
