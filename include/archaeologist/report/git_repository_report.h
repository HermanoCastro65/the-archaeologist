#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace archaeologist {

struct GitRepositorySummary {
  std::string repository;
  std::string language;
  size_t files;
  size_t directories;
};

class GitRepositoryReport {
public:
  GitRepositorySummary analyze(const std::vector<std::filesystem::path> &files);

  void print(const GitRepositorySummary &summary);
};

} // namespace archaeologist