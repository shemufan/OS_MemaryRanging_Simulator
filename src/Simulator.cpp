// Simulator.cpp
#include "Simulator.h"

#include <iostream>

Simulator::Simulator(ReplacementAlgorithm* Algorithm) {
  algorithm = Algorithm;
  pageFaultCount = 0;
  currentTime = 0;
}

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

  std::cout << "访问指令" << instructionNo << "页号" << pageNo << "页内偏移"
            << offset << std::endl;

  if (pageTable.isInMemory(pageNo)) {
    int blockNo = pageTable.getBlockNo(pageNo);
    int physicalAddress = blockNo * PAGE_SIZE + offset;
    std::cout << "命中！" << "指令在物理块：" << blockNo << "物理地址为："
              << physicalAddress << std::endl;
    pageTable.updateVisitTime(pageNo, currentTime);
    algorithm->onPageVisited(pageNo);
  } else {
    pageFaultCount++;

    std::cout << "发生缺页！" << std::endl;

    int freeBlock = memoryManager.findFreeBlock();

    if (freeBlock != -1) {
      memoryManager.loadPageToBlock(pageNo, freeBlock);
      pageTable.loadPage(pageNo, freeBlock, currentTime);
      algorithm->onPageLoaded(pageNo);

      std::cout << "页面" << pageNo << "调入物理块" << freeBlock << std::endl;

    } else {
      int victimPage = algorithm->selectVictimPage(pageTable, memoryManager);
      int victimBlock = pageTable.getBlockNo(victimPage);

      pageTable.removePage(victimPage);

      memoryManager.loadPageToBlock(pageNo, victimBlock);
      pageTable.loadPage(pageNo, victimBlock, currentTime);
      algorithm->onPageLoaded(pageNo);

      std::cout << "淘汰页面：" << victimPage << ",调入页面：" << pageNo
                << ",物理块：" << victimBlock << std ::endl;
    }

    int blockNo = pageTable.getBlockNo(pageNo);
    int physicalAddress = blockNo * PAGE_SIZE + offset;

    std::cout << "调页后物理地址：" << physicalAddress << std::endl;
  }

  memoryManager.printMemoryState();
  std::cout << "------------------------" << std::endl;
}

void Simulator::printStatistics(int totalInstructions) const {
  double pageFaultRate =
      static_cast<double>(pageFaultCount) / totalInstructions;

  std::cout << "========== 内存统计信息 ==========" << std::endl;
  std::cout << "总指令数: " << totalInstructions << std::endl;
  std::cout << "缺页次数 " << pageFaultCount << std::endl;
  std::cout << "缺页率: " << pageFaultRate * 100 << "%" << std::endl;
  std::cout << "使用算法: " << algorithm->getAlgorithmName() << std::endl;
  std::cout << "==================================" << std::endl;
}