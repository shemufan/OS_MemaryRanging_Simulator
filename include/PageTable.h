// PageTable.h
#pragma once
#include <vector>

#include "Config.h"
#include "PageTableEntry.h"

class PageTable {
 private:
  std::vector<PageTableEntry> entries;

 public:
  PageTable();

  bool isInMemory(int pageNo) const;
  int getBlockNo(int pageNo) const;

  void loadPage(int pageNo, int blockNo, int currentTime);
  void removePage(int pageNo);
  void updateVisitTime(int pageNo, int currentTime);

  PageTableEntry getEntry(int pageNo) const;
};