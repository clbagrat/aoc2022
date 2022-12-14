#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>

using namespace std;

int main() {
  ifstream file("data/14");
  string str;
  regex numPairs("\\d+,\\d+");
  set<pair<int, int>> cave;
  int pit;

  while (getline(file, str)) {
    smatch match;
    pair<int, int> prev;
    while (regex_search(str, match, numPairs)) {
      string m = match.str();
      pair<int, int> cur;
      cur.first = stoi(m.substr(0, m.find(',')));
      cur.second = stoi(m.substr(m.find(',') + 1));
      auto og = cur;
      pit = max(pit, cur.second);

      if (prev.first != 0) {
        cave.insert(prev);
        cave.insert(cur);
        while (cur != prev) {
          pair<int, int> n = cur;
          if (cur.first != prev.first) {
            n.first = min(cur.first, prev.first) + 1;
          }
          if (cur.second != prev.second) {
            n.second = min(cur.second, prev.second) + 1;
          }
          cave.insert(n);
          if (cur < prev) {
            cur = n;
          } else {
            prev = n;
          }
        }
      }
      prev = og;
      str = match.suffix();
    }
  }

  int res;

  while (true) {
    pair<int, int> s{500, 0};

    while (true) {
      if (s.second > pit) {
        cout << res;
        return res;
      }
      if (cave.find({s.first, s.second + 1}) == cave.end()) {
        s.second += 1;
        continue;
      } else if (cave.find({s.first - 1, s.second + 1}) == cave.end()) {
        s.second += 1;
        s.first -= 1;
        continue;
      } else if (cave.find({s.first + 1, s.second + 1}) == cave.end()) {
        s.second += 1;
        s.first += 1;
        continue;
      } else {
        cave.insert(s);
        break;
      }
    }
    res += 1;
  }
}
