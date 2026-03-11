# ruff: noqa: E402

import os
import shutil
import stat
import subprocess
import sys
import tempfile
from urllib.parse import urlparse

current_dir = os.path.dirname(__file__)
project_root = os.path.abspath(os.path.join(current_dir, "../../"))
python_module_dir = os.path.join(project_root, "build", "python")

sys.path.insert(0, python_module_dir)

import archaeologist_py  # type: ignore


def _handle_remove_readonly(func, path, exc):
    os.chmod(path, stat.S_IWRITE)
    func(path)


class ArchaeologistRunner:
    def __init__(self):

        self.runner = archaeologist_py.SelfRunner()
        self.scanner = archaeologist_py.DirectoryScanner()
        self.file_finder = archaeologist_py.FileFinder()
        self.repo_report = archaeologist_py.GitRepositoryReport()

        self.files = []
        self.root = None
        self.repo_dir = None

    def _extract_repo_name(self, url):

        path = urlparse(url).path
        name = os.path.basename(path)

        if name.endswith(".git"):
            name = name[:-4]

        return name

    def run(self, path):

        target_display = path

        if path.startswith("http://") or path.startswith("https://"):
            repo_name = self._extract_repo_name(path)

            tmp_root = tempfile.gettempdir()
            clone_dir = os.path.join(tmp_root, repo_name)

            if os.path.exists(clone_dir):
                shutil.rmtree(clone_dir, onexc=_handle_remove_readonly)

            subprocess.run(["git", "clone", "--depth", "1", path, clone_dir], check=True)

            self.repo_dir = clone_dir
            self.root = clone_dir

        else:
            self.root = path
            self.repo_dir = None

        self.files = self.scanner.scan(self.root)

        summary = self.repo_report.analyze(self.files)

        repo_name = os.path.basename(self.root)

        print("Running The Archaeologist")
        print(f"Target: {target_display}\n")

        print("Repository Report")
        print("=================\n")
        print(f"Repository: {repo_name}")
        print(f"Language: {summary.language}")
        print(f"Files: {summary.files}")
        print(f"Directories: {summary.directories}\n")

        self.runner.run(self.root)

    def search_file(self, filename):

        if not self.files:
            print("No files indexed. Run a scan first.")
            return

        results = self.file_finder.find(self.files, filename)

        if not results:
            print("File not found.")
            return

        for path in results:
            self.file_finder.print_file_content(path, self.root)

    def cleanup(self):

        if self.repo_dir and os.path.exists(self.repo_dir):
            shutil.rmtree(self.repo_dir, onexc=_handle_remove_readonly)
            self.repo_dir = None
