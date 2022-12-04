#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file("data/4");
  std::string str;
  int score = 0;
  while (std::getline(file, str)) {
    std::string left = str.substr(0, str.find(","));
    std::string right = str.substr(str.find(",") + 1, str.length());
    int x1 = std::stoi(left.substr(0, left.find("-")));
    int x2 = std::stoi(right.substr(0, right.find("-")));
    int y1 = std::stoi(left.substr(left.find("-") + 1, left.length()));
    int y2 = std::stoi(right.substr(right.find("-") + 1, right.length()));

    if (x2 <= x1 && y2 >= y1) {
      score += 1;
      continue;
    }

    if (x1 <= x2 && y1 >= y2) {
      score += 1;
    }
  }

  std::cout << score;
}
