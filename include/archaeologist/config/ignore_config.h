#pragma once

#include <set>
#include <string>

namespace archaeologist {

class IgnoreConfig {
public:
  std::set<std::string> directories;
  std::set<std::string> extensions;

  void load(const std::string &path);
};

} // namespace archaeologist