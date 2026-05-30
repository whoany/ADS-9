// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <ctime>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);
  std::vector<std::vector<char>> perms = getAllPerms(tree);
  std::cout << "Vse perestanovki:" << std::endl;
  for (int i = 0; i < perms.size(); i++) {
    for (int j = 0; j < perms[i].size(); j++)
      std::cout << perms[i][j];
    std::cout << std::endl;
  }
  std::vector<char> p1 = getPerm1(tree, 2);
  std::vector<char> p2 = getPerm2(tree, 2);
  std::cout << "getPerm1(2): ";
  for (int i = 0; i < p1.size(); i++)
    std::cout << p1[i];
  std::cout << std::endl;
  std::cout << "getPerm2(2): ";
  for (int i = 0; i < p2.size(); i++)
    std::cout << p2[i];
  std::cout << std::endl;
  std::cout << "\nn  getAllPerms  getPerm1  getPerm2" << std::endl;
  for (int n = 1; n <= 8; n++) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; i++)
      alphabet.push_back('1' + i);
    PMTree t(alphabet);
    clock_t start = clock();
    getAllPerms(t);
    double timeAll = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    start = clock();
    getPerm1(t, 1);
    double time1 = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    start = clock();
    getPerm2(t, 1);
    double time2 = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << n << "  " << timeAll << "  " << time1 << "  " << time2
              << std::endl;
  }
  return 0;
}
