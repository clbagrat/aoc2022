#include <fstream>
#include <string>
#include <iostream>

int main() 
{ 
    std::ifstream file("data/1");
    std::string str; 
    int max = 0;
    int cur_elf = 0;
    while (std::getline(file, str))
    {
      if (str == "") {
        cur_elf = 0;
      } else {
        int callories = std::stoi(str);
        cur_elf += callories;
        max = std::max(max, cur_elf);
      }
    }

    std::cout << max;
}

