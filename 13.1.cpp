#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

using namespace std;

struct Signal {
  bool plain;
  int number;
  vector<Signal> child;
  string to_str() {
    if (plain) {
      return to_string(number);
    } else {
      string res = "[";
      for (auto s : child) {
        res += s.to_str();
        res += " ";
      }
      res += "]";
      return res;
    }
  }
};

Signal CreateSignal(string raw) {
  stack<Signal *> st;
  Signal root = {.plain = false};
  st.push(&root);
  string curNumber;
  for (char ch : raw) {
    switch (ch) {
    case '[': {
      Signal n = {.plain = false};
      st.top()->child.push_back(n);
      st.push(&st.top()->child.back());
      break;
    }
    case ']': {
      if (curNumber != "") {
        st.top()->child.push_back({.plain = true, .number = stoi(curNumber)});
        curNumber = "";
      }
      st.pop();
      break;
    }
    case ',': {
      if (curNumber != "") {
        st.top()->child.push_back({.plain = true, .number = stoi(curNumber)});
        curNumber = "";
      }
      break;
    }
    default: {
      curNumber += ch;
    }
    }
  }
  return root;
};

int is_signals_valid(Signal left, Signal right) {
  if (left.plain && right.plain) {
    if (left.number < right.number) {
      return 1;
    } else if (left.number > right.number) {
      return -1;
    } else {
      return 0;
    }
  }
  if (!left.plain && !right.plain) {
    int i = 0;
    while (i < left.child.size()) {
      if (i >= right.child.size()) {
        return -1;
      }
      int res = is_signals_valid(left.child[i], right.child[i]);
      if (res != 0) {
        return res;
      }
      i += 1;
    }
    if (left.child.size() < right.child.size()) {
      return 1;
    }
    return 0;
  }
  if (!left.plain && right.plain) {
    Signal n = {.plain = false, .child = {right}};
    return is_signals_valid(left, n);
  }
  if (left.plain && !right.plain) {
    Signal n = {.plain = false, .child = {left}};
    return is_signals_valid(n, right);
  }
  cout << "HOW?" << endl;
  return -1;
}

int main() {
  ifstream file("data/13");
  string str;
  int x = 1;
  vector<Signal> signals;
  vector<int> validSignals;

  while (getline(file, str)) {
    if (str != "") {
      Signal n = CreateSignal(str);
      signals.push_back(n);
    }
    if (signals.size() == 2) {
      int validity = is_signals_valid(signals[0], signals[1]);
      if (validity >= 0) {
        validSignals.push_back(x);
      }
      signals = {};
      x++;
    }
  }
  int res = 0;
  for (auto index : validSignals) {
    res += index;
  }
  cout << "---" << res << "---" << endl;
}
