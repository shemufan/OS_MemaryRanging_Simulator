// SimulationStep.h
#pragma once
#include <vector>

struct SimulationStep {
  int stepNo;
  int instructionNo;
  int pageNo;
  int offset;
  bool pageFault;
  int blockNo;
  int physicalAddress;
  int loadedPage;
  int victimPage;
  std::vector<int> memoryState;
  int pageFaultCount;
  double pageFaultRate;
};
