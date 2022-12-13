#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct coord {
  int x;
  int y;

  string to_str() { return to_string(x) + "-" + to_string(y); }
};

int bfs(vector<vector<char>> grid, coord start) {
  int steps = 0;
  queue<pair<coord, int>> q;
  q.push({start, 0});
  vector<string> visited;
  while (!q.empty()) {
    auto c = q.front().first;
    auto v = q.front().second;
    q.pop();
    char myChar = grid[c.y][c.x];

    vector<coord> candidates{
        {.x = c.x + 1, .y = c.y},
        {.x = c.x - 1, .y = c.y},
        {.x = c.x, .y = c.y + 1},
        {.x = c.x, .y = c.y - 1},
    };
    for (auto cand : candidates) {
      if (cand.x < 0 || cand.y < 0 || cand.x >= grid[0].size() ||
          cand.y >= grid.size()) {
        continue;
      }
      char targetChar = grid[cand.y][cand.x];
      if (grid[cand.y][cand.x] == '{') {
        return v + 1;
      }
      if (targetChar - myChar > 1) {
        continue;
      }
      if (find(visited.begin(), visited.end(), cand.to_str()) !=
          visited.end()) {
        continue;
      }
      visited.push_back(cand.to_str());
      q.push({cand, v + 1});
    }
  }
  return 10;
}

int main() {
  ifstream file("data/12");
  string str;
  vector<vector<char>> grid;
  coord startCoord;

  int y = 0;
  while (getline(file, str)) {
    grid.push_back({});

    int x = 0;
    for (char ch : str) {
      if (ch == 'E') {
        grid.back().push_back('{');
      } else if (ch == 'S') {
        startCoord.x = x;
        startCoord.y = y;
        grid.back().push_back('`');
      } else {
        grid.back().push_back(ch);
      }
      x += 1;
    }
    y += 1;
  }

  for (auto yy : grid) {
    for (auto xx : yy) {
      cout << xx;
    }
    cout << endl;
  }

  cout << bfs(grid, startCoord);
}
