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
    std::map<std::string, std::string> loser_map = {{"A", "Z"}, {"B", "X"}, {"C", "Y"}};
    std::map<std::string, std::string> winner_map = {{"A", "Y"}, {"B", "Z"}, {"C", "X"}};
    std::map<std::string, std::string> draw_map = {{"A", "X"}, {"B", "Y"}, {"C", "Z"}};
    int  score = 0;
    while (std::getline(file, str))
    {
      std::string t = std::string(1, str.at(0));
      std::string m = std::string(1, str.at(2));
      int cur_score = 0;
      if (m == "Y") {
        cur_score += score_map[draw_map[t]] + 3;
      }

      if (m == "X") {
        cur_score += score_map[loser_map[t]];
      }

      if (m == "Z") {
        cur_score += score_map[winner_map[t]] + 6;
      }


      std::cout << m;
      std::cout << t;
      std::cout << cur_score;
      std::cout << "\n";
      score += cur_score;
    }

    std::cout << score;
}

