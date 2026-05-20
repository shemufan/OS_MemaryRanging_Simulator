// MemoryManager.cpp
#include "MemoryManager.h"

#include <iostream>

MemoryManager::MemoryManager() {
  for (int i = 0; i < MEMORY_BLOCK_COUNT; i++) {
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

std::vector<int> MemoryManager::getMemoryState() const {
  std::vector<int> state;
  for (const auto& block : blocks) {
    state.push_back(block.pageNo);
  }
  return state;
}

void MemoryManager::printMemoryState(std::ostream& os) const {
  os << "当前内存块状态: [";
  for (int i = 0; i < blocks.size(); i++) {
    if (blocks[i].pageNo == -1) {
      os << "-";
    } else {
      os << blocks[i].pageNo;
    }

    if (i != blocks.size() - 1) {
      os << ", ";
    }
  }
  os << "]" << std::endl;
}