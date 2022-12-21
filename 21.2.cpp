#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct SuperInt {
  long value = 0;
  bool isVar = false;
  string variable = "";
  SuperInt() {}
  SuperInt(long number) {
    isVar = false;
    value = number;
  };
  SuperInt(string x) {
    isVar = true;
    variable = x.length() == 1 ? x : "(" + x + ")";
  }
  string to_str() { return isVar ? variable : to_string(value); }
  SuperInt operator+(SuperInt const &other) {
    if (!isVar && !other.isVar) {
      return SuperInt(value + other.value);
    }

    if (isVar) {
      return SuperInt(variable + "+" + to_string(other.value));
    } else {
      return SuperInt(to_string(value) + "+" + other.variable);
    }
  };
  SuperInt operator-(SuperInt const &other) {
    if (!isVar && !other.isVar) {
      return SuperInt(value - other.value);
    }

    if (isVar) {
      return SuperInt(variable + "-" + to_string(other.value));
    } else {
      return SuperInt(to_string(value) + "-" + other.variable);
    }
  };
  SuperInt operator*(SuperInt const &other) {
    if (!isVar && !other.isVar) {
      return SuperInt(value * other.value);
    }

    if (isVar) {
      return SuperInt(variable + "*" + to_string(other.value));
    } else {
      return SuperInt(to_string(value) + "*" + other.variable);
    }
  };
  SuperInt operator/(SuperInt const &other) {
    if (!isVar && !other.isVar) {
      return SuperInt(value / other.value);
    }

    if (isVar) {
      return SuperInt(variable + "/" + to_string(other.value));
    } else {
      return SuperInt(to_string(value) + "/" + other.variable);
    }
  };
};

struct Monkey {
  string name;
  bool isSolved;
  string left;
  string right;
  string operation;
  SuperInt value;
  string to_str() {
    return name + ": " + left + operation + right + " (" + value.to_str() +
           ") " + (isSolved ? "solved" : "");
  }
};

int main() {
  ifstream file("data/21");
  string str;
  regex opReg("(\\+|\\-|\\*|\\/)");
  regex numReg("\\d+");
  regex strReg("[a-z]+");
  map<string, SuperInt> solvedValues;
  vector<Monkey> monkeys;

  while (getline(file, str)) {
    Monkey newMonkey = {};

    smatch operMatch;
    if (regex_search(str, operMatch, opReg)) {
      newMonkey.operation = operMatch.str();
    }

    smatch valueMatch;
    if (regex_search(str, valueMatch, numReg)) {
      newMonkey.value = SuperInt(stoi(valueMatch.str()));
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
    if (newMonkey.name == "humn") {
      newMonkey.value = SuperInt("x");
    }
    if (newMonkey.name == "root") {
      newMonkey.operation = "=";
    }

    if (newMonkey.value.value || newMonkey.value.isVar) {
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
        cout << leftSolve->second.to_str() << " " << monkey.operation << " "
             << rightSolve->second.to_str() << endl;
        cout << "copy paste to wolfram alfa :D " << endl;
        return 0;
      }
    }
  }
}
