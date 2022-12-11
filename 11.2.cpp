#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Monkey {
public:
  queue<int64_t> items;
  string operation;
  int64_t changeFactor;
  int64_t condition;
  int64_t trueIndex;
  int64_t falseIndex;
  int64_t inspectionCount;

  void print64_t() {
    cout << "i'm holding ";
    for (size_t i = 0; i < items.size(); i++) {
      cout << items.front() << " ";
      items.push(items.front());
      items.pop();
    }
    cout << endl;
    cout << "inspections " << inspectionCount << endl;
    cout << "operation " << operation << changeFactor << endl;
    cout << "test " << condition << endl;
    cout << "true >> " << trueIndex << endl;
    cout << "false >> " << falseIndex << endl;
    cout << "----------------" << endl;
  }
};

void runRound(vector<Monkey*> monkeys, int64_t divider) {
  for(auto m: monkeys) {
    while(!m->items.empty()) {
      int64_t old = m->items.front();
      int64_t res = old;
      m->items.pop();
      int64_t factor;
      if (m->changeFactor == 0) {
        factor = old;
      } else {
        factor = m->changeFactor;
      }

      if (m->operation == "*") {
        res = old * factor;
      } else {
        res = old + factor;
      }

      res = res % divider;

      if (res % m->condition == 0) {
        monkeys[m->trueIndex]->items.push(res);
      } else {
        monkeys[m->falseIndex]->items.push(res);
      }

      m->inspectionCount += 1;
    }
  }
}

int main() {
  ifstream file("data/11");
  string str;
  regex numReg("-?\\d+");
  regex operationReg("[\\*\\+]");
  vector<Monkey *> monkeys;

  int64_t parsedLine;
  while (getline(file, str)) {
    int64_t i = parsedLine % 7;

    switch (parsedLine % 7) {
    case 0:
      monkeys.push_back(new Monkey);
      break;
    case 1: {
      smatch matches;
      while (regex_search(str, matches, numReg)) {
        monkeys.back()->items.push(stoi(matches.str()));
        str = matches.suffix();
      }
      break;
    }
    case 2: {
      smatch opMatch;
      regex_search(str, opMatch, operationReg);
      monkeys.back()->operation = opMatch.str();
      smatch numMatch;
      regex_search(str, numMatch, numReg);
      if (numMatch.length() > 0) {
        monkeys.back()->changeFactor = stoi(numMatch.str());
      }
      break;
    }
    case 3: {
      smatch match;
      regex_search(str, match, numReg);
      monkeys.back()->condition = stoi(match.str());
      break;
    }
    case 4: {
      smatch match;
      regex_search(str, match, numReg);
      monkeys.back()->trueIndex = stoi(match.str());
      break;
    }
    case 5: {
      smatch match;
      regex_search(str, match, numReg);
      monkeys.back()->falseIndex = stoi(match.str());
      break;
    }
    };

    parsedLine += 1;
  }

  int64_t divider = 1;
  for (auto m: monkeys) {
    divider *= m->condition;
  }

  for (int64_t i = 0; i < 10000; i += 1) {
    runRound(monkeys, divider);
  }

  vector<int64_t> inspections;

  for (auto m : monkeys) {
    inspections.push_back(m->inspectionCount);
    m->print64_t();
  }
  sort(inspections.begin(), inspections.end(), greater<int64_t>());
  cout << inspections.at(1) * inspections.at(0) <<endl;
}
