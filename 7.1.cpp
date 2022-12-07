#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(std::move(item));
  }
  return elems;
}

enum fsType {
  Folder,
  File
};

class Node {
public:
  std::string value;
  Node* parent;
  std::map<std::string, Node*> children;
  int size;
  fsType type;

  Node(std::string val) {
    value = val;
    parent = NULL;
    size = 0;
    type = Folder;
  }
};


int main() {
  std::ifstream file("data/7");
  std::string str;
  auto root = new Node("/");

  Node *currentNode = root;
  while (std::getline(file, str)) {
    std::vector<std::string> parsed = split(str, ' ');
    if (parsed[0] == "$") {
      auto command = parsed[1];
      auto arg = parsed[2];

      if (command == "ls") {
        continue;
      }

      if (command == "cd") {
        if (arg == "/") continue;

        if (arg == "..") {
          currentNode = currentNode->parent;
        } else {
          currentNode = currentNode->children[arg];
        }
      }

    } else if (parsed[0] == "dir") {
      auto dirName = parsed[1];
      auto newNode = new Node(dirName);
      newNode->parent = currentNode;
      currentNode->children.insert({dirName, newNode});
    } else {
      int size = std::stoi(parsed[0]);
      auto fileName = parsed[1];
      auto newNode = new Node(fileName);
      newNode->parent = currentNode;
      newNode->size = size;
      newNode->type = File;

      currentNode->children.insert({fileName, newNode});
    }
  }

  std::stack<Node*> st;
  st.push(root);

  while(!st.empty()) {
    Node* current = st.top();
    st.pop();
    if (current->size > 0) {
      Node* parent = current->parent;
      while (parent) {
        parent->size += current->size;
        parent = parent->parent;
      }
    }
    for (const auto &p : current->children) {
      st.push(p.second);
    }
  }
  
  int res = 0;
  st.push(root);
  root->size = 0;
  while(!st.empty()) {
    Node* current = st.top();
    st.pop();
    for (const auto &p : current->children) {
      st.push(p.second);
    }
    if (current->type == File) continue;
    if (current->size < 100000) {
      res += current->size;
    }
  }

  std::cout << res;
}
