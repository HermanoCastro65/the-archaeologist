#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>
#include <map>
#include <memory>

namespace archaeologist {

DirectoryScanner::DirectoryScanner() { ignore.load("config/scanner_ignore.json"); }

std::vector<std::filesystem::path> DirectoryScanner::scan(const std::filesystem::path &root) {

  std::vector<std::filesystem::path> files;

  for (auto it = std::filesystem::recursive_directory_iterator(root);
       it != std::filesystem::recursive_directory_iterator(); ++it) {

    const auto &entry = *it;
    auto path = entry.path();

    if (entry.is_directory()) {

      std::string name = path.filename().string();

      if (ignore.directories.count(name)) {
        it.disable_recursion_pending();
        continue;
      }
    }

    if (entry.is_regular_file()) {

      std::string ext = path.extension().string();

      if (ignore.extensions.count(ext))
        continue;

      files.push_back(path);
    }
  }

  return files;
}

void DirectoryScanner::list(const std::vector<std::filesystem::path> &files) {
  for (const auto &file : files) {
    std::cout << file.string() << "\n";
  }
}

struct TreeNode {
  std::map<std::string, std::unique_ptr<TreeNode>> children;
};

static void print_tree(const TreeNode &node, const std::string &prefix) {

  for (auto it = node.children.begin(); it != node.children.end(); ++it) {

    bool last = std::next(it) == node.children.end();

    std::cout << prefix;
    std::cout << (last ? "`-- " : "|-- ");
    std::cout << it->first << "\n";

    std::string new_prefix = prefix + (last ? "    " : "|   ");

    print_tree(*it->second, new_prefix);
  }
}

void DirectoryScanner::tree(const std::vector<std::filesystem::path> &files,
                            const std::filesystem::path &root) {

  TreeNode rootNode;

  for (const auto &path : files) {

    auto relative = std::filesystem::relative(path, root);

    TreeNode *node = &rootNode;

    for (const auto &part : relative) {

      std::string name = part.string();

      if (!node->children.count(name)) {
        node->children[name] = std::make_unique<TreeNode>();
      }

      node = node->children[name].get();
    }
  }

  std::cout << root.filename().string() << "\n";

  print_tree(rootNode, "");
}

} // namespace archaeologist