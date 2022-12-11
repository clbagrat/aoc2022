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
  queue<int> items;
  string operation;
  int changeFactor;
  int condition;
  int trueIndex;
  int falseIndex;
  int inspectionCount;

  void print() {
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

void runRound(vector<Monkey*> monkeys) {
  for(auto m: monkeys) {
    while(!m->items.empty()) {
      int old = m->items.front();
      int res = old;
      m->items.pop();
      int factor;
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

      res = res / 3;

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

  int parsedLine;
  while (getline(file, str)) {
    int i = parsedLine % 7;

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

  for (int i = 0; i < 20; i += 1) {
    runRound(monkeys);
  }

  vector<int> inspections;

  for (auto m : monkeys) {
    inspections.push_back(m->inspectionCount);
    m->print();
  }
  sort(inspections.begin(), inspections.end(), greater<int>());
  cout << inspections.at(1) * inspections.at(0) <<endl;
}
