#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl/filesystem.h>

#include "archaeologist/report/git_repository_report.h"
#include "archaeologist/runner/self_runner.h"
#include "archaeologist/scanner/directory_scanner.h"
#include "archaeologist/search/file_finder.h"


namespace py = pybind11;

PYBIND11_MODULE(archaeologist_py, m) {

  py::class_<archaeologist::SelfRunner>(m, "SelfRunner")
      .def(py::init<>())
      .def("run", [](archaeologist::SelfRunner &runner, const std::string &path) {
        py::scoped_ostream_redirect stream(std::cout, py::module_::import("sys").attr("stdout"));

        runner.run(path);
      });

  py::class_<archaeologist::DirectoryScanner>(m, "DirectoryScanner")
      .def(py::init<>())
      .def("scan", [](archaeologist::DirectoryScanner &scanner, const std::string &path) {
        return scanner.scan(std::filesystem::path(path));
      });

  py::class_<archaeologist::FileFinder>(m, "FileFinder")
      .def(py::init<>())
      .def("find", &archaeologist::FileFinder::find)
      .def("print_file_content", [](archaeologist::FileFinder &finder,
                                    const std::filesystem::path &path,
                                    const std::filesystem::path &root) {
        py::scoped_ostream_redirect stream(std::cout, py::module_::import("sys").attr("stdout"));

        finder.print_file_content(path, root);
      });

  py::class_<archaeologist::GitRepositorySummary>(m, "GitRepositorySummary")
      .def_readonly("repository", &archaeologist::GitRepositorySummary::repository)
      .def_readonly("language", &archaeologist::GitRepositorySummary::language)
      .def_readonly("files", &archaeologist::GitRepositorySummary::files)
      .def_readonly("directories", &archaeologist::GitRepositorySummary::directories);

  py::class_<archaeologist::GitRepositoryReport>(m, "GitRepositoryReport")
      .def(py::init<>())
      .def("analyze", &archaeologist::GitRepositoryReport::analyze)
      .def("print", [](archaeologist::GitRepositoryReport &report,
                       const archaeologist::GitRepositorySummary &summary) {
        py::scoped_ostream_redirect stream(std::cout, py::module_::import("sys").attr("stdout"));

        report.print(summary);
      });
}