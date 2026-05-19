// MemoryManager.h
#pragma once
#include <iostream>
#include <vector>

#include "Config.h"
#include "MemoryBlock.h"

class MemoryManager {
 private:
  std::vector<MemoryBlock> blocks;

 public:
  MemoryManager();

  int findFreeBlock() const;
  void loadPageToBlock(int pageNo, int blockNo);
  int getPageInBlock(int blockNo) const;
  int findBlockByPage(int pageNo) const;
  void removePageFromBlock(int blockNo);

  void printMemoryState(std::ostream& os = std::cout) const;
};