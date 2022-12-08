#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int scentic_score(int x, int y, vector<vector<int>> grid) {
  int h = grid[y][x];

  int right = 0;
  int r = x;
  while (r < grid[y].size() - 1) {
    if (r != x && grid[y][r] >= h) {
      break;
    }
    right += 1;
    r += 1;
  }

  int left = 0;
  int l = x;
  while (l > 0) {
    if (l != x && grid[y][l] >= h) {
      break;
    }
    left += 1;
    l -= 1;
  }

  int top = 0;
  int t = y;
  while (t > 0) {
    if (t != y && grid[t][x] >= h) {
      break;
    }
    top += 1;
    t -= 1;
  }

  int bot = 0;
  int b = y;
  while (b < grid.size() - 1) {
    if (b != y && grid[b][x] >= h) {
      break;
    }
    bot += 1;
    b += 1;
  }

  return left * right * top * bot;
}

int main() {
  ifstream file("data/8");
  string str;
  int y = 0;
  vector<vector<int>> grid;
  while (getline(file, str)) {
    vector<int> row(str.length());
    grid.push_back(row);
    for (int x = 0; x < str.length(); x += 1) {
      grid[y][x] = str[x] - '0';
    }
    y += 1;
  }

  int m = 0;

  for (int y = 0; y < grid.size(); y += 1) {
    for (int x = 0; x < grid[y].size(); x += 1) {
       m = max(m, scentic_score(x, y, grid));
    }
  }
  cout << m;
}
