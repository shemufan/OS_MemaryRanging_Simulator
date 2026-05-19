// main.cpp
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

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

  std::unique_ptr<ReplacementAlgorithm> algorithm;

  if (choice == 1) {
    algorithm = std::make_unique<FIFOReplacement>();
  } else {
    algorithm = std::make_unique<LRUReplacement>();
  }

  InstructionGenerator generator;
  std::vector<int> instructions = generator.generate();

  Simulator simulator(algorithm.get());
  simulator.run(instructions);

  return 0;
}