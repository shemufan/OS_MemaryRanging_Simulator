// FIFOReplacement.h
#pragma once
#include <queue>

#include "ReplacementAlgorithm.h"

class FIFOReplacement : public ReplacementAlgorithm {
 private:
  std::queue<int> pageQueue;

 public:
  int selectVictimPage(PageTable& PageTable,
                       MemoryManager& memoryManager) override;

  void onPageLoaded(int pageNo) override;

  std::string getAlgorithmName() const override;
};