#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int const ORE = 0;
int const CLAY = 1;
int const OBS = 2;
int const GEO = 3;

using price = pair<int, int>;

int get_time_needed(int need, int have, int speed) {
  return have >= need ? 1 : 1 + (need - have + speed - 1) / speed;
}

int simulate(vector<price> prices, vector<int> stash, vector<int> robots,
             int t) {

  int res = stash[GEO] + t * robots[GEO];

  if (robots[ORE] < prices[ORE].first || robots[ORE] < prices[CLAY].first ||
      robots[ORE] < prices[OBS].first || robots[ORE] < prices[GEO].first) {
    int tn = get_time_needed(prices[ORE].first, stash[ORE], robots[ORE]);
    if (t > tn) {
      auto n_stash = stash;
      auto n_robots = robots;
      int type = 4;
      while (type--) {
        n_stash[type] += tn * robots[type];
      }
      n_stash[ORE] -= prices[ORE].first;
      n_robots[ORE] += 1;
      res = max(res, simulate(prices, n_stash, n_robots, t - tn));
    }
  }

  if (robots[CLAY] < prices[OBS].second) {
    // how much time do i need to produce enough ORE for 1 CLAY
    int tn = get_time_needed(prices[CLAY].first, stash[ORE], robots[ORE]);
    if (t > tn) {
      auto n_stash = stash;
      auto n_robots = robots;
      int type = 4;
      while (type--) {
        n_stash[type] += tn * robots[type];
      }
      n_stash[ORE] -= prices[CLAY].first;
      n_robots[CLAY] += 1;
      res = max(res, simulate(prices, n_stash, n_robots, t - tn));
    }
  }

  if (robots[CLAY] && robots[OBS] < prices[GEO].second) {
    int tn =
        max(get_time_needed(prices[OBS].first, stash[ORE], robots[ORE]),
            get_time_needed(prices[OBS].second, stash[CLAY], robots[CLAY]));
    if (t > tn) {
      auto n_stash = stash;
      auto n_robots = robots;
      int type = 4;
      while (type--) {
        n_stash[type] += tn * robots[type];
      }
      n_stash[ORE] -= prices[OBS].first;
      n_stash[CLAY] -= prices[OBS].second;
      n_robots[OBS] += 1;

      res = max(res, simulate(prices, n_stash, n_robots, t - tn));
    }
  }

  if (robots[OBS]) {
    int tn = max(get_time_needed(prices[GEO].first, stash[ORE], robots[ORE]),
                 get_time_needed(prices[GEO].second, stash[OBS], robots[OBS]));

    if (t > tn) {
      auto n_stash = stash;
      auto n_robots = robots;
      int type = 4;
      while (type--) {
        n_stash[type] += tn * robots[type];
      }
      n_stash[ORE] -= prices[GEO].first;
      n_stash[OBS] -= prices[GEO].second;
      n_robots[GEO] += 1;

      res = max(res, simulate(prices, n_stash, n_robots, t - tn));
    }
  }

  return res;
}

int main() {
  ifstream file("data/19");
  string str;
  regex numReg("\\d+");
  int total = 1;

  int x = 0;
  while (getline(file, str)) {
    if (x == 3)
      break;
    x += 1;
    smatch match;
    vector<price> prices(4, {0, 0});
    int i = 0;
    vector<int> parced;
    while (regex_search(str, match, numReg)) {
      int val = stoi(match.str());
      parced.push_back(val);
      str = match.suffix();
      i += 1;
    }
    prices[ORE] = {parced[1], 0};
    prices[CLAY] = {parced[2], 0};
    prices[OBS] = {parced[3], parced[4]};
    prices[GEO] = {parced[5], parced[6]};

    total *= simulate(prices, {0, 0, 0, 0}, {1, 0, 0, 0}, 32);
  }
  cout << total << endl;
}
