// JsonExporter.h
#pragma once
#include <string>
#include <vector>

#include "SimulationStep.h"

class JsonExporter {
 public:
  void exportToFile(const std::string& filePath,
                    const std::string& algorithm,
                    const std::vector<SimulationStep>& steps);

  void exportToJsFile(const std::string& filePath,
                      const std::string& algorithm,
                      const std::vector<SimulationStep>& steps);
};
