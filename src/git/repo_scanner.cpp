#include "archaeologist/git/repo_scanner.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

namespace archaeologist {

std::filesystem::path RepoScanner::clone(const std::string &url) {

  auto temp = std::filesystem::temp_directory_path() /
              ("archaeologist_repo_" + std::to_string(std::time(nullptr)));

  std::string command = "git clone --depth 1 --filter=blob:none " + url + " " + temp.string();

  int result = std::system(command.c_str());

  if (result != 0) {
    throw std::runtime_error("Failed to clone repository");
  }

  return temp;
}

void RepoScanner::cleanup(const std::filesystem::path &path) {

  if (!std::filesystem::exists(path))
    return;

  // Windows sometimes locks git pack files briefly
  for (int i = 0; i < 5; i++) {

    try {

      std::filesystem::remove_all(path);

      if (!std::filesystem::exists(path))
        return;

    } catch (...) {
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  std::cerr << "Warning: temporary repository cleanup failed\n";
}

std::string RepoScanner::repository_name(const std::string &url) {

  auto last_slash = url.find_last_of('/');

  if (last_slash == std::string::npos)
    return "repository";

  std::string name = url.substr(last_slash + 1);

  if (name.ends_with(".git")) {
    name = name.substr(0, name.size() - 4);
  }

  return name;
}

bool RepoScanner::looks_like_git_repo(const std::string &url) {

  if (url.find("github.com") == std::string::npos && url.find("gitlab.com") == std::string::npos) {
    return false;
  }

  auto parts = std::count(url.begin(), url.end(), '/');

  if (parts < 4)
    return false;

  if (!url.ends_with(".git"))
    return false;

  return true;
}

bool RepoScanner::repository_exists(const std::string &url) {

#ifdef _WIN32
  std::string command = "git -c credential.helper= "
                        "-c core.askpass= "
                        "-c credential.interactive=false "
                        "ls-remote " +
                        url + " >nul 2>&1";
#else
  std::string command = "git -c credential.helper= "
                        "-c core.askpass= "
                        "-c credential.interactive=false "
                        "ls-remote " +
                        url + " >/dev/null 2>&1";
#endif

  int result = std::system(command.c_str());

  return result == 0;
}

} // namespace archaeologist