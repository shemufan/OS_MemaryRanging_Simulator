// PageTable.cpp
#include "PageTable.h"

#include <algorithm>

PageTable::PageTable() {
  for (int i = 0; i < PAGE_COUNT; i++) {
    PageTableEntry v(i);
    entries.push_back(i);
  }
}

bool PageTable::isInMemory(int pageNo) const {
  return entries[pageNo].inMemory;
}

int PageTable::getBlockNo(int pageNo) const { return entries[pageNo].blockNo; }

void PageTable::loadPage(int pageNo, int blockNo, int currentTime) {
  entries[pageNo].blockNo = blockNo;
  entries[pageNo].inMemory = true;
  entries[pageNo].lastVisitTime = currentTime;
}

void PageTable::removePage(int pageNo) {
  entries[pageNo].blockNo = -1;
  entries[pageNo].inMemory = false;
}

void PageTable::updateVisitTime(int pageNo, int currentTime) {
  entries[pageNo].lastVisitTime = currentTime;
}

PageTableEntry PageTable::getEntry(int pageNo) const { return entries[pageNo]; }