#include <string>
#include <map>
#include <fstream>
#include <string>
#include <iostream>

int main() 
{ 
    std::ifstream file("data/2");
    std::string str; 
    std::map<std::string, int> score_map = {{"X", 1}, {"Y", 2}, {"Z", 3}};
    std::map<std::string, int> win = {{"XC", 6}, {"YA", 6}, {"ZB", 6}, {"XA", 3}, {"YB", 3}, {"ZC", 3}};
    int  score = 0;
    while (std::getline(file, str))
    {
      std::string t = std::string(1, str.at(0));
      std::string m = std::string(1, str.at(2));
      int cur_score = score_map[m];

      if (win[m+t]) {
        cur_score += win[m+t];
      }

      std::cout << m;
      std::cout << t;
      std::cout << cur_score;
      std::cout << "\n";
      score += cur_score;
    }

    std::cout << score;

}

