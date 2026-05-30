// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <vector>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

namespace {

void collect(PMTree::Node* node, std::vector<char>* path,
             std::vector<std::vector<char>>* out) {
  if (node->children.empty()) {
    out->push_back(*path);
    return;
  }
  for (PMTree::Node* child : node->children) {
    path->push_back(child->value);
    collect(child, path, out);
    path->pop_back();
  }
}

int64_t factorial(int n) {
  int64_t result = 1;
  for (int i = 2; i <= n; ++i)
    result *= i;
  return result;
}
} //namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collect(tree.getRoot(), &path, &result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size()))
    return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  PMTree::Node* node = tree.getRoot();
  int n = static_cast<int>(node->children.size());
  if (num < 1 || num > factorial(n))
    return {};
  std::vector<char> result;
  int64_t index = num - 1;
  while (!node->children.empty()) {
    int count = static_cast<int>(node->children.size());
    int64_t block = factorial(count - 1);
    int64_t which = index / block;
    index %= block;
    node = node->children[which];
    result.push_back(node->value);
  }
  return result;
}
