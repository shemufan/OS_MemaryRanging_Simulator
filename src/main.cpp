// main.cpp
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "FIFOReplacement.h"
#include "InstructionGenerator.h"
#include "LRUReplacement.h"
#include "Simulator.h"

int main() {
  srand((unsigned int)time(nullptr));

  std::cout << "请求分页存储管理模拟系统" << std::endl;
  std::cout << "1. FIFO 页面置换算法" << std::endl;
  std::cout << "2. LRU 页面置换算法" << std::endl;
  std::cout << "请选择算法: ";

  int choice;
  std::cin >> choice;

  ReplacementAlgorithm* algorithm = nullptr;

  if (choice == 1) {
    algorithm = new FIFOReplacement();
  } else {
    algorithm = new LRUReplacement();
  }

  InstructionGenerator generator;
  std::vector<int> instructions = generator.generate();

  Simulator simulator(algorithm);
  simulator.run(instructions);

  delete algorithm;

  return 0;
}