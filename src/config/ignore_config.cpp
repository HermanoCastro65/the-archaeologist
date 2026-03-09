#include "archaeologist/config/ignore_config.h"

#include <fstream>

namespace archaeologist {

void IgnoreConfig::load(const std::string &path) {

  std::ifstream file(path);

  if (!file)
    return;

  std::string line;

  while (std::getline(file, line)) {

    if (line.find(".git") != std::string::npos)
      directories.insert(".git");

    if (line.find("build") != std::string::npos)
      directories.insert("build");

    if (line.find(".ruff_cache") != std::string::npos)
      directories.insert(".ruff_cache");

    if (line.find(".pyc") != std::string::npos)
      extensions.insert(".pyc");
  }
}

} // namespace archaeologist