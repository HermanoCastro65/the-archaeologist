import sys
import os

def setup_cpp_module():

    current_dir = os.path.dirname(__file__)
    project_root = os.path.abspath(os.path.join(current_dir, "../.."))
    build_python = os.path.join(project_root, "build", "python")

    sys.path.insert(0, build_python)