#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main() 
{ 
    std::ifstream file("data/1");
    std::string str; 
    std::vector<int> callories;
    int cur_elf = 0;
    int max = 0;
    while (std::getline(file, str))
    {
      if (str == "") {
        callories.push_back(cur_elf);
        cur_elf = 0;
      } else {
        int callories = std::stoi(str);
        cur_elf += callories;
      }
    }

    std::make_heap(callories.begin(), callories.end());

    std::pop_heap(callories.begin(), callories.end());
    max += callories.back();
    callories.pop_back();

    std::pop_heap(callories.begin(), callories.end());
    max += callories.back();
    callories.pop_back();

    std::pop_heap(callories.begin(), callories.end());
    max += callories.back();

    std::cout << max;
}

