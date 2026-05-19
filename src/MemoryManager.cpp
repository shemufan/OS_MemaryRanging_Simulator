// MemoryManager.cpp
#include "MemoryManager.h"

#include <iostream>

MemoryManager::MemoryManager() {
  for (int i = 0; i < MEMORT_BLOCK_COUNT; i++) {
    MemoryBlock m(i);
    blocks.push_back(m);
  }
}

int MemoryManager::findFreeBlock() const {
  for (MemoryBlock v : blocks) {
    if (v.isFree()) {
      return v.blockNo;
    }
  }
  return -1;
}

void MemoryManager::loadPageToBlock(int pageNo, int blockNo) {
  blocks[blockNo].pageNo = pageNo;
}

int MemoryManager::getPageInBlock(int blockNo) const {
  return blocks[blockNo].pageNo;
}

int MemoryManager::findBlockByPage(int pageNo) const {
  for (MemoryBlock v : blocks) {
    if (v.pageNo == pageNo) return v.blockNo;
  }
  return -1;
}

void MemoryManager::removePageFromBlock(int blockNo) {
  blocks[blockNo].pageNo = -1;
}

void MemoryManager::printMemoryState() const {
  for (MemoryBlock v : blocks) {
    std::cout << "blockNo: " << v.blockNo << " pageNo: " << v.pageNo << " "
              << std::endl;
  }
}