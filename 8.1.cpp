#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct TreePos {
  int height;
  int pos;
};

int main() {
  ifstream file("data/8");
  string str;
  vector<vector<int>> grid;
  set<string> visible;
  vector<int> topMaximums(100, -1);
  vector<stack<TreePos>> botMaximums;
  int y = 0;
  int maxX = 0;

  while (getline(file, str)) {
    int x = 0;
    int leftMaximum = -1;
    maxX = str.length();
    stack<TreePos> rightVisibles;

    while (x < str.length()) {
      //left
      int height = str[x] - '0';
      if (height > leftMaximum) {
        visible.insert(to_string(x) + "-" + to_string(y));
        leftMaximum = height;
      }

      //right
      while (!rightVisibles.empty()) {
        if (height < rightVisibles.top().height) {
          rightVisibles.push(TreePos{.height = height, .pos = x});
          break;
        } else {
          rightVisibles.pop();
        }
      }
      if (rightVisibles.empty()) {
        rightVisibles.push(TreePos{.height = height, .pos = x}); 
      }

      // top
      if (height > topMaximums[x]) {
        visible.insert(to_string(x) + "-" + to_string(y));
        topMaximums[x] = height;
      }

      // bot
      botMaximums.reserve(str.length());
      while (!botMaximums[x].empty()) {
        if (height < botMaximums[x].top().height) {
          botMaximums[x].push(TreePos{.height = height, .pos = y});
          break;
        } else {
          botMaximums[x].pop();
        }
      }
      if (botMaximums[x].empty()) {
        botMaximums[x].push(TreePos{.height = height, .pos = y});
      } 

      x += 1;
    }

    while (!rightVisibles.empty()) {
      TreePos tp = rightVisibles.top();
      int height = tp.height; 
      int x = tp.pos;
      visible.insert(to_string(x) + "-" + to_string(y));
      rightVisibles.pop();
    }

    y += 1;
  }

  for (int x = 0; x < maxX; x += 1) {
    auto st = botMaximums[x];
    while(!st.empty()) {
      TreePos tp = st.top();
      int height = tp.height; 
      int y = tp.pos;
      visible.insert(to_string(x) + "-" + to_string(y));
      st.pop();
    }
  }

  cout << visible.size() << "\n";
}
