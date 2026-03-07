import sys
import os

# adiciona build/python ao path
current_dir = os.path.dirname(__file__)
project_root = os.path.abspath(os.path.join(current_dir, ".."))
build_python = os.path.join(project_root, "build", "python")

sys.path.insert(0, build_python)

import archaeologist_py

runner = archaeologist_py.SelfRunner()
runner.run()