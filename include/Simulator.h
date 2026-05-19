// Simulator.h
#pragma once
#include <iostream>
#include <vector>

#include "MemoryManager.h"
#include "PageTable.h"
#include "ReplacementAlgorithm.h"

class Simulator {
 private:
  PageTable pageTable;
  MemoryManager memoryManager;
  ReplacementAlgorithm* algorithm;
  std::ostream& out;

  int pageFaultCount;
  int currentTime;

 public:
  Simulator(ReplacementAlgorithm* Algorithm,
            std::ostream& os = std::cout);

  void run(const std::vector<int>& instructions);
  void accessInstruction(int instructionNo);
  void printStatistics(int totalInstructions) const;
};