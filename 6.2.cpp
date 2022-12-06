#include <fstream>
#include <iostream>
#include <string>
#include <set>

int main() {
  std::ifstream file("data/6");
  std::string str;
  int og_count = 14;
  while (std::getline(file, str)) {
    int i = og_count - 1;
    while (i < str.length()) {
      std::set<char> chars;
      int count = og_count;
      while (count--) {
        chars.insert(str[i-count]);
      }
      if (chars.size() == og_count) {
        std::cout << i + 1 << "\n";
        break;
      }
      i += 1;
    }
  }
}
