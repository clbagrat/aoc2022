#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
  std::ifstream file("data/3");
  std::string str;
  int score = 0;
  int index = 0;
  std::map<char, int> char_map = {};

  while (std::getline(file, str)) {
    int bit_pos = index % 3;

    for (int p = 0; p < str.length(); p += 1) {
      char_map[str[p]] |= (1u << bit_pos);
    }

    if (bit_pos == 2) {
      for (auto const &x : char_map) {
        if (x.second == 7) {
          int char_score = (int)x.first;
          if (char_score > 96) {
            score += char_score - 96;
          } else {
            score += char_score - 38;
          }
          break;
        }
      }

      char_map = {};
    }

    index += 1;
  }

  std::cout << score;
}
