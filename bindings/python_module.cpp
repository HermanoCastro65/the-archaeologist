#include <iostream>

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include "archaeologist/runner/self_runner.h"

namespace py = pybind11;

PYBIND11_MODULE(archaeologist_py, m) {

  py::class_<archaeologist::SelfRunner>(m, "SelfRunner")
      .def(py::init<>())

      .def("run", [](archaeologist::SelfRunner &runner, const std::string &path) {
        py::scoped_ostream_redirect stream(std::cout, py::module_::import("sys").attr("stdout"));

        runner.run(path);
      });
}