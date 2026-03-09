from utils.paths import setup_cpp_module

setup_cpp_module()

import archaeologist_py


class ArchaeologistRunner:

    def run(self, path):

        runner = archaeologist_py.SelfRunner()
        runner.run(path)