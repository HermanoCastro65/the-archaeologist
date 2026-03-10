#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace archaeologist {

class SelfRunner {

public:
  void run(const std::string &input);

  void find_file(const std::vector<std::filesystem::path> &files, const std::string &name);
};

} // namespace archaeologist