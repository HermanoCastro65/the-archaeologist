#include "archaeologist/config/ignore_config.h"
#include "third_party/nlohmann/json.hpp"

#include <fstream>

namespace archaeologist {

using json = nlohmann::json;

void IgnoreConfig::load(const std::string &path) {

  std::ifstream file(path);

  if (!file)
    return;

  json data;
  file >> data;

  if (data.contains("directories")) {
    for (const auto &dir : data["directories"]) {
      directories.insert(dir.get<std::string>());
    }
  }

  if (data.contains("extensions")) {
    for (const auto &ext : data["extensions"]) {
      extensions.insert(ext.get<std::string>());
    }
  }
}

} // namespace archaeologist