#include <fstream>
#include <iostream>
#include <string>
#include <set>

int main() {
  std::ifstream file("data/6");
  std::string str;
  while (std::getline(file, str)) {
    int i = 3;
    while (i < str.length()) {
      std::set<char> chars;
      chars.insert(str[i]);
      chars.insert(str[i-1]);
      chars.insert(str[i-2]);
      chars.insert(str[i-3]);
      if (chars.size() == 4) {
        std::cout << i + 1;
        break;
      }
      i += 1;
    }
  }
}
