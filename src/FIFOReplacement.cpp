// FIFOReplacement.cpp
#include "FIFOReplacement.h"

void FIFOReplacement::onPageLoaded(int pageNo) { pageQueue.push(pageNo); }

int FIFOReplacement::selectVictimPage(PageTable& pageTable,
                                      MemoryManager& memoryManager) {
  int victim = pageQueue.front();
  pageQueue.pop();
  return victim;
}

std::string FIFOReplacement::getAlgorithmName() const { return "FIFO"; }