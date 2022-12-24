#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;
using coord = pair<int, int>;

vector<coord> allAround = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                           {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
vector<pair<vector<coord>, coord>> moveMap = {
    {{{-1, -1}, {0, -1}, {1, -1}}, {0, -1}},
    {{{-1, 1}, {0, 1}, {1, 1}}, {0, 1}},
    {{{-1, -1}, {-1, 0}, {-1, 1}}, {-1, 0}},
    {{{1, -1}, {1, 0}, {1, 1}}, {1, 0}}};

bool isFree(coord cur, vector<coord> directions, set<coord> occupied) {
  for (coord n : directions) {
    coord p = {cur.first + n.first, cur.second + n.second};
    if (occupied.find(p) != occupied.end()) {
      return false;
    }
  }
  return true;
}

coord getNextStep(coord cur, set<coord> occupied) {
  if (isFree(cur, allAround, occupied)) {
    return cur;
  }
  for (auto move : moveMap) {
    if (isFree(cur, move.first, occupied)) {
      return {cur.first + move.second.first, cur.second + move.second.second};
    }
  }
  return cur;
};

void debug(set<coord> elves) {
  for (int y = -20; y < 20; y += 1) {
    for (int x = -20; x < 20; x += 1) {
      if (elves.find({x, y}) != elves.end()) {
        cout << '#';
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}

int main() {
  ifstream file("data/23");
  string str;
  set<coord> elves;
  int y = 0;
  while (getline(file, str)) {
    int x = 0;
    for (char a : str) {
      if (a == '#') {
        elves.insert({x, y});
      }
      x += 1;
    }
    y += 1;
  }
  int round = 10;
  while (round--) {
    set<coord> potential = {};
    set<coord> overlap = {};
    cout << round << endl;
    for (coord elf : elves) {
      coord nextStep = getNextStep(elf, elves);
      if (overlap.find(nextStep) != overlap.end()) {
        continue;
      }
      if (potential.find(nextStep) != potential.end()) {
        overlap.insert(nextStep);
      } else {
        potential.insert(nextStep);
      }
    }

    set<coord> newElves;
    for (coord elf : elves) {
      coord coordToInsert = getNextStep(elf, elves);
      if (overlap.find(coordToInsert) != overlap.end()) {
        coordToInsert = elf;
      }
      newElves.insert(coordToInsert);
      if (round == 0) {
      }
    }
    elves = newElves;
    rotate(moveMap.begin(), moveMap.begin() + 1, moveMap.end());
  }
  int mx = INFINITY;
  int my = INFINITY;
  int Mx = -INFINITY;
  int My = -INFINITY;
  for (coord elf : elves) {
    mx = min(mx, elf.first);
    my = min(my, elf.second);
    Mx = max(Mx, elf.first);
    My = max(My, elf.second);
  }

  int allGround = (Mx - mx + 1) * (My - my + 1);
  cout << allGround - elves.size() << endl;
}
