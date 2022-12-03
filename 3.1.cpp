#include <fstream>
#include <string>
#include <iostream>
#include <set>

int main() 
{
  std::ifstream file("data/3");
  std::string str;
  int score = 0;

  while (std::getline(file, str))
  {
    int left = 0;
    int right = str.length() - 1;
    std::set<char> left_set;
    std::set<char> right_set;
    char common;
    while (left != right ) {
      left_set.insert(str[left]);
      right_set.insert(str[right]);
      if (right_set.find(str[left]) != right_set.end()) {
        common = str[left];
        break;
      }
      if (left_set.find(str[right]) != left_set.end()) {
        common = str[right];
        break;
      }
      left += 1;
      right -= 1;
    }

    int char_score = (int)common;
    std::cout << common;
    if (char_score > 96) {
      score += char_score - 96;
      std::cout << char_score - 96;
    } else {
      score += char_score - 38;
      std::cout << char_score - 38;
    }
    

    std::cout << "\n";
  }
  std::cout << score;
}
