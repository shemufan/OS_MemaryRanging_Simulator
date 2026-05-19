// LRURelpacement.cpp
#include "LRUReplacement.h"

#include <limits.h>

int LRUReplacement::selectVictimPage(PageTable& pageTable,
                                     MemoryManager& memoryManager) {
  int victimPage = -1;
  int minTime = INT_MAX;

  for (int pageNo = 0; pageNo < PAGE_COUNT; pageNo++) {
    PageTableEntry entry = pageTable.getEntry(pageNo);

    if (entry.inMemory && entry.lastVisitTime < minTime) {
      minTime = entry.lastVisitTime;
      victimPage = entry.pageNo;
    }
  }

  return victimPage;
}

std::string LRUReplacement::getAlgorithmName() const { return "LRU"; }
