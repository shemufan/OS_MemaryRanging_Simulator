// InstructionGenerator.cpp
#include "InstructionGenerator.h"

#include <cstdlib>

std::vector<int> InstructionGenerator::generate() {
  std::vector<int> instructions;

  while (instructions.size() < INSTRUCTION_COUNT) {
    int m = rand() % INSTRUCTION_COUNT;
    instructions.push_back(m);

    if (instructions.size() >= INSTRUCTION_COUNT) break;
    if (m + 1 < INSTRUCTION_COUNT) {
      instructions.push_back(m + 1);
    }

    if (instructions.size() >= INSTRUCTION_COUNT) break;
    if (m > 0) {
      int m1 = rand() % m;
      instructions.push_back(m1);

      if (instructions.size() >= INSTRUCTION_COUNT) break;
      if (m1 + 1 < INSTRUCTION_COUNT) {
        instructions.push_back(m1 + 1);
      }

      if (instructions.size() >= INSTRUCTION_COUNT) break;
      if (m1 + 2 < INSTRUCTION_COUNT) {
        int m2 = m1 + 2 + rand() % (INSTRUCTION_COUNT - m1 - 2);
        instructions.push_back(m2);

        if (instructions.size() >= INSTRUCTION_COUNT) break;
        if (m2 + 1 < INSTRUCTION_COUNT) {
          instructions.push_back(m2 + 1);
        }
      }
    }
  }

  return instructions;
}