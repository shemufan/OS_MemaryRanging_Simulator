// MemoryBlock.h
#pragma once

class MemoryBlock {
 public:
  int blockNo;  // 物理块号
  int pageNo;   // 当前装入的页号;-1表示空闲

  MemoryBlock(int blockNo = 0) : blockNo(blockNo), pageNo(-1) {}

  bool isFree() const { return pageNo == -1; }
};