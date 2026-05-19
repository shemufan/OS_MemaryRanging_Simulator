// ReplacementAlgorithm.h
#pragma once
#include <string>

#include "MemoryManager.h"
#include "PageTable.h"

class ReplacementAlgorithm {
 public:
  // 选择一个淘汰的页面
  virtual int selectVictimPage(PageTable& pageTable,
                               MemoryManager& memoryManager) = 0;

  virtual void onPageLoaded(int pageNo) {};

  virtual void onPageVisited(int pageNo) {};

  virtual std::string getAlgorithmName() const = 0;

  virtual ~ReplacementAlgorithm() {};
};
