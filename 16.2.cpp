#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

using namespace std;

struct Valve {
  string name;
  int flow;
  vector<string> connecitons;
  bool activated(set<string> active) {
    return active.find(name) != active.end();
  }
  string get_key(set<string> active, int sec, bool isElephant) {
    string a = "";
    for (auto ac : active) {
      a += ac + "_";
    }
    return name + ":" + to_string(sec) + ":" + a + ":" + to_string(isElephant);
  }
  string to_str() {
    string con = " => ";
    for (auto s : connecitons) {
      con += s + " ";
    }
    return name + " (" + to_string(flow) + ") " + con;
  }
};

map<string, Valve> allValves;
map<string, int> cache;

int simulate(Valve valve, int sec, set<string> active, bool isElephant) {
  string cacheKey = valve.get_key(active, sec, isElephant);
  auto c = cache.find(cacheKey);
  if (c != cache.end()) {
    return c->second;
  }
  if (sec == 0) {
    if (isElephant) {
      return simulate(allValves.find("AA")->second, 26, active, false);
    } else {
      return 0;
    }
  }
  bool isActivated = valve.activated(active);
  int m = 0;
  for (auto connection : valve.connecitons) {
    m = max(m, simulate(allValves.find(connection)->second, sec - 1, active,
                        isElephant));
  }

  if (valve.flow > 0 && !isActivated) {
    active.insert(valve.name);
    m = max(m, valve.flow * (sec - 1) +
                   simulate(valve, sec - 1, active, isElephant));
  }

  cache.insert({cacheKey, m});
  return m;
}

int main() {
  ifstream file("data/16");
  string str;
  regex numReg("\\d+");
  regex valveReg("[A-Z][A-Z]");

  while (getline(file, str)) {
    smatch nmatch;
    int flow;
    Valve valve;
    if (regex_search(str, nmatch, numReg)) {
      valve.flow = stoi(nmatch.str());
    }

    smatch vmatch;
    while (regex_search(str, vmatch, valveReg)) {
      if (valve.name == "") {
        valve.name = vmatch.str();
      } else {
        valve.connecitons.push_back(vmatch.str());
      }
      str = vmatch.suffix();
    }
    allValves.insert({valve.name, valve});
  }
  cout << simulate(allValves.find("AA")->second, 26, {}, true);
}
