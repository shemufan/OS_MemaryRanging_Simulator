// PageTableEntry.h
#pragma once

class PageTableEntry {
 public:
  int pageNo;         // 页号
  int blockNo;        // 所在物理块号，-1 表示不在内存
  bool inMemory;      // 是否在内存中
  int lastVisitTime;  // 最近访问时间，LRU使用

  PageTableEntry(int pageNo = 0)
      : pageNo(pageNo), blockNo(-1), inMemory(false), lastVisitTime(0) {}
};