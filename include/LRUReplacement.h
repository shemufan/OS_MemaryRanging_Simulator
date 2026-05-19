// LRUReplacement.h
#pragma once
#include "ReplacementAlgorithm.h"
class LRUReplacement : public ReplacementAlgorithm {
 public:
  int selectVictimPage(PageTable& pageTable,
                       MemoryManager& memoryManager) override;

  std::string getAlgorithmName() const override;
};