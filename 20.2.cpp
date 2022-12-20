#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  long val;
  Node *Left;
  Node *Right;
  Node(long v) { val = v; }
  string to_str() {
    Node *cur = Right;
    string res = " > " + to_string(val) + " > ";
    while (cur != this) {
      res += to_string(cur->val) + " > ";
      cur = cur->Right;
    };
    return res;
  }
  string prlong(int val) {
    Node *cur = this;
    string res = "";
    while (val--) {
      res += to_string(cur->val);
      cur = cur->Right;
    }
    return res;
  }
};

int main() {
  ifstream file("data/20");
  string str;
  vector<Node *> nodes;
  Node *zero;
  long factor = 811589153;
  while (getline(file, str)) {
    Node *newNode = new Node(stoi(str) * factor);
    if (str == "0") {
      zero = newNode;
    }
    if (nodes.size()) {
      Node *last = nodes.back();
      last->Right = newNode;
      newNode->Left = last;
    }
    nodes.push_back(newNode);
  }
  nodes.back()->Right = nodes.front();
  nodes.front()->Left = nodes.back();

  long m = nodes.size() - 1;
  long mixCount = 10;
  while (mixCount--) {
    for (Node *node : nodes) {

      long val = node->val % m;
      if (val == 0)
        continue;
      if (node->val > 0) {
        Node *cur = node;
        while (val--) {
          cur = cur->Right;
        }
        if (cur == node)
          continue;
        node->Left->Right = node->Right;
        node->Right->Left = node->Left;
        cur->Right->Left = node;
        node->Right = cur->Right;
        cur->Right = node;
        node->Left = cur;
        continue;
      }
      if (val < 0) {
        Node *cur = node;
        while (val++) {
          cur = cur->Left;
        }
        if (cur == node)
          continue;
        node->Left->Right = node->Right;
        node->Right->Left = node->Left;
        cur->Left->Right = node;
        node->Left = cur->Left;
        cur->Left = node;
        node->Right = cur;
        continue;
      }
    }
  }

  long x = 3000;
  long sum = 0;
  Node *cur = zero;
  while (x--) {
    cur = cur->Right;
    if (x % 1000 == 0) {
      cout << x << " " << cur->val << endl;
      sum += cur->val;
    }
  }
  cout << sum << endl;
}
