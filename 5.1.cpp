#include <fstream>
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
 

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(std::move(item));
  }
  return elems;
}


int main () {
  std::ifstream file("data/5");
  std::string str;
  int stackCount = 9;
  std::vector<std::deque<char>> stacks = {};

  bool instructionsStarted = false;
  while (std::getline(file, str)) {
    if (str == "") {
      instructionsStarted = true;
      continue;
    }

    if (instructionsStarted) {
      std::vector<std::string> command = split(str, ' ');
      int count = std::stoi(command[1]);
      int from = std::stoi(command[3]) - 1;
      int to = std::stoi(command[5]) - 1;
      while (count--) {
        auto top = stacks[from].front();
        stacks[from].pop_front();
        stacks[to].push_front(top);
      }
    } else {
      int curStack = 0;
      while (curStack < stackCount) {
        if (stacks.size() < curStack + 1) {
          stacks.push_back({});
        }
        char ch = str[curStack * 4 + 1];
        if (ch != ' ') {
          stacks.at(curStack).push_back(ch);
        }

        curStack += 1;
      }
    }
  }

  int curStack = 0;
  while(curStack < stackCount) {
    std::cout << stacks[curStack].front();
    curStack += 1;
  }
}
