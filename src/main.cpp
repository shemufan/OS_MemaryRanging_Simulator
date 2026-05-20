// main.cpp
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>

#include "FIFOReplacement.h"
#include "InstructionGenerator.h"
#include "JsonExporter.h"
#include "LRUReplacement.h"
#include "Simulator.h"

class TeeBuf : public std::streambuf {
  std::streambuf* a;
  std::streambuf* b;

 public:
  TeeBuf(std::streambuf* a, std::streambuf* b) : a(a), b(b) {}

 protected:
  int overflow(int c) override {
    if (c == EOF) return EOF;
    a->sputc(c);
    return b->sputc(c);
  }
};

int main() {
  srand((unsigned int)time(nullptr));

  std::ofstream resultFile("result.txt");
  TeeBuf teeBuf(std::cout.rdbuf(), resultFile.rdbuf());
  std::ostream tee(&teeBuf);

  tee << "请求分页存储管理模拟系统" << std::endl;
  tee << "1. FIFO 页面置换算法" << std::endl;
  tee << "2. LRU 页面置换算法" << std::endl;
  tee << "请选择算法: ";

  int choice;
  std::cin >> choice;

  std::unique_ptr<ReplacementAlgorithm> algorithm;

  if (choice == 1) {
    algorithm = std::make_unique<FIFOReplacement>();
  } else if (choice == 2) {
    algorithm = std::make_unique<LRUReplacement>();
  } else {
    tee << "输入错误，默认使用 LRU 页面置换算法。" << std::endl;
    algorithm = std::make_unique<LRUReplacement>();
  }

  InstructionGenerator generator;
  std::vector<int> instructions = generator.generate();

  Simulator simulator(algorithm.get(), tee);
  simulator.run(instructions);

  JsonExporter exporter;
  exporter.exportToFile("output/simulation_result.json",
                        algorithm->getAlgorithmName(),
                        simulator.getSteps());
  exporter.exportToJsFile("output/simulation_data.js",
                          algorithm->getAlgorithmName(),
                          simulator.getSteps());

  return 0;
}