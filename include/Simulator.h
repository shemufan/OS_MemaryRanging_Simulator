// Simulator.h
#pragma once
#include <vector>

#include "MemoryManager.h"
#include "PageTable.h"
#include "ReplacementAlgorithm.h"

class Simulator {
 private:
  PageTable pageTable;
  MemoryManager memoryManager;
  ReplacementAlgorithm* algorithm;

  int pageFaultCount;
  int currentTime;

 public:
  Simulator(ReplacementAlgorithm* Algorithm);

  void run(const std::vector<int>& instructions);
  void accessInstruction(int instructionNo);
  void printStatistics(int totalInstructions) const;
};