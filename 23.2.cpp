#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using coord = pair<int, int>;

struct hashFunction {
  size_t operator()(const pair<int, int> &x) const {
    return x.first ^ x.second;
  }
};

typedef unordered_set<coord, hashFunction> Elves;

vector<coord> allAround = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                           {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

vector<pair<vector<coord>, coord>> moveMap = {
    {{{-1, -1}, {0, -1}, {1, -1}}, {0, -1}},
    {{{-1, 1}, {0, 1}, {1, 1}}, {0, 1}},
    {{{-1, -1}, {-1, 0}, {-1, 1}}, {-1, 0}},
    {{{1, -1}, {1, 0}, {1, 1}}, {1, 0}}};


void debug(Elves elves) {
  for (int y = -10; y < 20; y += 1) {
    for (int x = -10; x < 20; x += 1) {
      if (elves.find({x, y}) != elves.end()) {
        cout << '#';
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}

bool isFree(coord cur, vector<coord> directions, Elves* occupied) {
  for (coord n : directions) {
    coord p = {cur.first + n.first, cur.second + n.second};
    if (occupied->find(p) != occupied->end()) {
      return false;
    }
  }
  return true;
}

coord getNextStep(coord cur, Elves* occupied) {
  auto isAllFree = isFree(cur, allAround, occupied);
  if (isAllFree) {
    return cur;
  }
  for (auto move : moveMap) {
    if (isFree(cur, move.first, occupied)) {
      return {cur.first + move.second.first, cur.second + move.second.second};
    }
  }
  return cur;
};

int main() {
  ifstream file("data/23");
  string str;
  Elves elves;
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
  int round = 1;
  while (true) {
    Elves potential = {};
    Elves overlap = {};
    //cout << "Round : " << round << endl;
    for (coord elf : elves) {

      auto t1 = chrono::high_resolution_clock::now();
      coord nextStep = getNextStep(elf, &elves);
      auto t2 = chrono::high_resolution_clock::now();
      auto ms_int = chrono::duration_cast<chrono::microseconds>(t2 - t1);
      if (overlap.find(nextStep) != overlap.end()) {
        continue;
      }
      if (potential.find(nextStep) != potential.end()) {
        overlap.insert(nextStep);
      } else {
        potential.insert(nextStep);
      }
    }

    Elves newElves = {};
    for (coord elf : elves) {
      coord coordToInsert = getNextStep(elf, &elves);
      if (overlap.find(coordToInsert) != overlap.end()) {
        coordToInsert = elf;
      }
      newElves.insert(coordToInsert);
    }

    if (newElves == elves) {
      cout << "result: " << round << endl;
      return 0;
    } else {
      cout << round << endl;
      elves = newElves;
    }
    rotate(moveMap.begin(), moveMap.begin() + 1, moveMap.end());
    round += 1;
  }
}
