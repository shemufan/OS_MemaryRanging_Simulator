// JsonExporter.cpp
#include "JsonExporter.h"

#include <fstream>

#include "Config.h"

static void writeJsonArray(std::ofstream& out,
                           const std::vector<int>& values) {
  out << "[";
  for (size_t i = 0; i < values.size(); i++) {
    if (i > 0) out << ", ";
    out << values[i];
  }
  out << "]";
}

void JsonExporter::exportToFile(const std::string& filePath,
                                const std::string& algorithm,
                                const std::vector<SimulationStep>& steps) {
  std::ofstream file(filePath);
  if (!file.is_open()) return;

  file << "{\n";
  file << "  \"algorithm\": \"" << algorithm << "\",\n";
  file << "  \"totalInstructions\": " << INSTRUCTION_COUNT << ",\n";
  file << "  \"pageSize\": " << PAGE_SIZE << ",\n";
  file << "  \"pageCount\": " << PAGE_COUNT << ",\n";
  file << "  \"memoryBlockCount\": " << MEMORY_BLOCK_COUNT << ",\n";
  file << "  \"steps\": [\n";

  for (size_t i = 0; i < steps.size(); i++) {
    const auto& s = steps[i];
    file << "    {\n";
    file << "      \"stepNo\": " << s.stepNo << ",\n";
    file << "      \"instructionNo\": " << s.instructionNo << ",\n";
    file << "      \"pageNo\": " << s.pageNo << ",\n";
    file << "      \"offset\": " << s.offset << ",\n";
    file << "      \"pageFault\": " << (s.pageFault ? "true" : "false")
         << ",\n";
    file << "      \"blockNo\": " << s.blockNo << ",\n";
    file << "      \"physicalAddress\": " << s.physicalAddress << ",\n";
    file << "      \"loadedPage\": " << s.loadedPage << ",\n";
    file << "      \"victimPage\": " << s.victimPage << ",\n";
    file << "      \"memoryState\": ";
    writeJsonArray(file, s.memoryState);
    file << ",\n";
    file << "      \"pageFaultCount\": " << s.pageFaultCount << ",\n";
    file << "      \"pageFaultRate\": " << s.pageFaultRate << "\n";
    file << "    }";
    if (i < steps.size() - 1) file << ",";
    file << "\n";
  }

  file << "  ]\n";
  file << "}\n";

  file.close();
}

void JsonExporter::exportToJsFile(const std::string& filePath,
                                  const std::string& algorithm,
                                  const std::vector<SimulationStep>& steps) {
  std::ofstream file(filePath);
  if (!file.is_open()) return;

  file << "var SIMULATION_DATA = {\n";
  file << "  \"algorithm\": \"" << algorithm << "\",\n";
  file << "  \"totalInstructions\": " << INSTRUCTION_COUNT << ",\n";
  file << "  \"pageSize\": " << PAGE_SIZE << ",\n";
  file << "  \"pageCount\": " << PAGE_COUNT << ",\n";
  file << "  \"memoryBlockCount\": " << MEMORY_BLOCK_COUNT << ",\n";
  file << "  \"steps\": [\n";

  for (size_t i = 0; i < steps.size(); i++) {
    const auto& s = steps[i];
    file << "    {\n";
    file << "      \"stepNo\": " << s.stepNo << ",\n";
    file << "      \"instructionNo\": " << s.instructionNo << ",\n";
    file << "      \"pageNo\": " << s.pageNo << ",\n";
    file << "      \"offset\": " << s.offset << ",\n";
    file << "      \"pageFault\": " << (s.pageFault ? "true" : "false")
         << ",\n";
    file << "      \"blockNo\": " << s.blockNo << ",\n";
    file << "      \"physicalAddress\": " << s.physicalAddress << ",\n";
    file << "      \"loadedPage\": " << s.loadedPage << ",\n";
    file << "      \"victimPage\": " << s.victimPage << ",\n";
    file << "      \"memoryState\": ";
    writeJsonArray(file, s.memoryState);
    file << ",\n";
    file << "      \"pageFaultCount\": " << s.pageFaultCount << ",\n";
    file << "      \"pageFaultRate\": " << s.pageFaultRate << "\n";
    file << "    }";
    if (i < steps.size() - 1) file << ",";
    file << "\n";
  }

  file << "  ]\n";
  file << "};\n";

  file.close();
}
