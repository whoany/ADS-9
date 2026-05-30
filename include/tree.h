// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v) : value(v) {}
  };

  explicit PMTree(const std::vector<char>& in) {
    root = new Node('\0');
    std::vector<char> elems = in;
    std::sort(elems.begin(), elems.end());
    build(root, elems);
  }

  ~PMTree() { clear(root); }

  Node* getRoot() const { return root; }

 private:
  Node* root;

  void build(Node* node, const std::vector<char>& elems) {
    for (std::size_t i = 0; i < elems.size(); ++i) {
      Node* child = new Node(elems[i]);
      node->children.push_back(child);
      std::vector<char> rest;
      for (std::size_t j = 0; j < elems.size(); ++j)
        if (j != i)
          rest.push_back(elems[j]);
      build(child, rest);
    }
  }

  void clear(Node* node) {
    if (node == nullptr)
      return;
    for (Node* child : node->children)
      clear(child);
    delete node;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
