# ruff: noqa: E402

import os
import sys

current_dir = os.path.dirname(__file__)

project_root = os.path.abspath(os.path.join(current_dir, "../../"))

python_module_dir = os.path.join(project_root, "build", "python")

sys.path.insert(0, python_module_dir)

import archaeologist_py  # type: ignore


class ArchaeologistRunner:
    def run(self, path):

        runner = archaeologist_py.SelfRunner()

        runner.run(path)
