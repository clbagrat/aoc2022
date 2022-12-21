#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Monkey {
  string name;
  bool isSolved;
  string left;
  string right;
  string operation;
  long value;
  string to_str() {
    return name + ": " + left + operation + right + " (" + to_string(value) +
           ") " + (isSolved ? "solved" : "");
  }
};

int main() {
  ifstream file("data/21");
  string str;
  regex opReg("(\\+|\\-|\\*|\\/)");
  regex numReg("\\d+");
  regex strReg("[a-z]+");
  map<string, long> solvedValues;
  vector<Monkey> monkeys;

  while (getline(file, str)) {
    Monkey newMonkey = {};

    smatch operMatch;
    if (regex_search(str, operMatch, opReg)) {
      newMonkey.operation = operMatch.str();
    }

    smatch valueMatch;
    if (regex_search(str, valueMatch, numReg)) {
      newMonkey.value = stoi(valueMatch.str());
    }

    smatch nameMatch;
    while (regex_search(str, nameMatch, strReg)) {
      if (newMonkey.name == "") {
        newMonkey.name = nameMatch.str();
      } else if (newMonkey.left == "") {
        newMonkey.left = nameMatch.str();
      } else {
        newMonkey.right = nameMatch.str();
      }
      str = nameMatch.suffix();
    }

    if (newMonkey.value) {
      newMonkey.isSolved = true;
      solvedValues.insert({newMonkey.name, newMonkey.value});
    }
    monkeys.push_back(newMonkey);
  }

  while (true) {
    for (Monkey monkey : monkeys) {
      if (monkey.isSolved)
        continue;
      auto leftSolve = solvedValues.find(monkey.left);
      if (leftSolve == solvedValues.end())
        continue;
      auto rightSolve = solvedValues.find(monkey.right);
      if (rightSolve == solvedValues.end())
        continue;

      if (monkey.operation == "+") {
        monkey.value = leftSolve->second + rightSolve->second;
      }
      if (monkey.operation == "-") {
        monkey.value = leftSolve->second - rightSolve->second;
      }
      if (monkey.operation == "/") {
        monkey.value = leftSolve->second / rightSolve->second;
      }
      if (monkey.operation == "*") {
        monkey.value = leftSolve->second * rightSolve->second;
      }
      monkey.isSolved = true;
      solvedValues.insert({monkey.name, monkey.value});
      if (monkey.name == "root") {
        cout << monkey.to_str() << endl;
        return 0;
      }
    }
  }
}
