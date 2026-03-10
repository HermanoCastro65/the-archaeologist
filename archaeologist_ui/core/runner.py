# ruff: noqa: E402

import os
import sys

current_dir = os.path.dirname(__file__)
project_root = os.path.abspath(os.path.join(current_dir, "../../"))
python_module_dir = os.path.join(project_root, "build", "python")

sys.path.insert(0, python_module_dir)

import archaeologist_py  # type: ignore


class ArchaeologistRunner:
    def __init__(self):

        self.runner = archaeologist_py.SelfRunner()
        self.file_finder = archaeologist_py.FileFinder()
        self.files = []

    def run(self, path):

        self.files = self.runner.run(path)

    def search_file(self, filename):

        results = self.file_finder.find(self.files, filename)

        for path in results:
            self.file_finder.print_file_content(path)
