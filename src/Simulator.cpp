// Simulator.cpp
#include "Simulator.h"

#include <iostream>

Simulator::Simulator(ReplacementAlgorithm* Algorithm, std::ostream& os)
    : algorithm(Algorithm), out(os), pageFaultCount(0), currentTime(0) {}

void Simulator::run(const std::vector<int>& instructions) {
  for (int i = 0; i < INSTRUCTION_COUNT; i++) {
    accessInstruction(instructions[i]);
  }

  printStatistics(INSTRUCTION_COUNT);
}

void Simulator::accessInstruction(int instructionNo) {
  currentTime++;

  int pageNo = instructionNo / PAGE_SIZE;
  int offset = instructionNo % PAGE_SIZE;

  out << "访问指令：" << instructionNo << " 页号：" << pageNo
      << " 页内偏移：" << offset << std::endl;

  if (pageTable.isInMemory(pageNo)) {
    int blockNo = pageTable.getBlockNo(pageNo);
    int physicalAddress = blockNo * PAGE_SIZE + offset;
    out << "命中！" << "物理块：" << blockNo << " 物理地址为：" << physicalAddress
        << std::endl;
    pageTable.updateVisitTime(pageNo, currentTime);
    algorithm->onPageVisited(pageNo);
  } else {
    pageFaultCount++;

    out << "发生缺页！" << std::endl;

    int freeBlock = memoryManager.findFreeBlock();

    if (freeBlock != -1) {
      memoryManager.loadPageToBlock(pageNo, freeBlock);
      pageTable.loadPage(pageNo, freeBlock, currentTime);
      algorithm->onPageLoaded(pageNo);

      out << "页面" << pageNo << "调入物理块" << freeBlock << std::endl;

    } else {
      int victimPage = algorithm->selectVictimPage(pageTable, memoryManager);
      int victimBlock = pageTable.getBlockNo(victimPage);

      pageTable.removePage(victimPage);

      memoryManager.loadPageToBlock(pageNo, victimBlock);
      pageTable.loadPage(pageNo, victimBlock, currentTime);
      algorithm->onPageLoaded(pageNo);

      out << "淘汰页面：" << victimPage << ",调入页面：" << pageNo
          << ",物理块：" << victimBlock << std::endl;
    }

    int blockNo = pageTable.getBlockNo(pageNo);
    int physicalAddress = blockNo * PAGE_SIZE + offset;

    out << "调页后物理地址：" << physicalAddress << std::endl;
  }

  memoryManager.printMemoryState(out);
  out << "------------------------" << std::endl;
}

void Simulator::printStatistics(int totalInstructions) const {
  double pageFaultRate =
      static_cast<double>(pageFaultCount) / totalInstructions;

  out << "========== 内存统计信息 ==========" << std::endl;
  out << "总指令数: " << totalInstructions << std::endl;
  out << "缺页次数 " << pageFaultCount << std::endl;
  out << "缺页率: " << pageFaultRate * 100 << "%" << std::endl;
  out << "使用算法: " << algorithm->getAlgorithmName() << std::endl;
  out << "==================================" << std::endl;
}