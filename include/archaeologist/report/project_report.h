#pragma once

#include <filesystem>
#include <vector>

namespace archaeologist {

class ProjectReport {
public:
  void generate(const std::vector<std::filesystem::path> &files);
};

} // namespace archaeologist