// Copyright 2022 NNTU-CS
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

namespace {

void printPerm(const std::vector<char>& perm) {
  if (perm.empty()) {
    std::cout << "(none)";
    return;
  }
  for (char c : perm)
    std::cout << c;
}

}
 
int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);
  
  std::vector<std::vector<char>> perms = getAllPerms(tree);
  std::cout << "All permutations of 1 2 3:" << std::endl;
  for (const std::vector<char>& p : perms) {
    printPerm(p);
    std::cout << ' ';
  }
  std::cout << std::endl;
  
  std::cout << "getPerm1(tree, 1) = ";
  printPerm(getPerm1(tree, 1));
  std::cout << std::endl;
  std::cout << "getPerm2(tree, 2) = ";
  printPerm(getPerm2(tree, 2));
  std::cout << std::endl;
  
  using Clock = std::chrono::high_resolution_clock;
  std::mt19937 gen(12345);
  
  std::ofstream csv("result/experiment.csv");
  csv << "n,getAllPerms,getPerm1,getPerm2" << std::endl;
  
  std::cout << "\n n |  getAllPerms |     getPerm1 |     getPerm2  (seconds)\n";
  
  for (int n = 1; n <= 10; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i)
      alphabet.push_back(static_cast<char>('1' + i));
    
    PMTree t(alphabet);
    
    int64_t total = 1;
    for (int i = 2; i <= n; ++i)
      total *= i;
    std::uniform_int_distribution<int64_t> dist(1, total);
    
    auto t0 = Clock::now();
    std::vector<std::vector<char>> all = getAllPerms(t);
    auto t1 = Clock::now();
    
    int num = static_cast<int>(dist(gen));
    auto t2 = Clock::now();
    volatile std::vector<char> r1 = getPerm1(t, num);
    auto t3 = Clock::now();
    
    num = static_cast<int>(dist(gen));
    auto t4 = Clock::now();
    volatile std::vector<char> r2 = getPerm2(t, num);
    auto t5 = Clock::now();
    
    auto sec = [](Clock::time_point a, Clock::time_point b) {
      return std::chrono::duration<double>(b - a).count();
    };
    double tAll = sec(t0, t1);
    double tP1 = sec(t2, t3);
    double tP2 = sec(t4, t5);
    std::printf("%2d | %12.8f | %12.8f | %12.8f\n", n, tAll, tP1, tP2);
    csv << n << ',' << tAll << ',' << tP1 << ',' << tP2 << std::endl;
  }
  return 0;
}
