#include <pybind11/pybind11.h>

#include "archaeologist/runner/self_runner.h"

namespace py = pybind11;

PYBIND11_MODULE(archaeologist_py, m) {
  m.doc() = "The Archaeologist Python bindings";

  py::class_<archaeologist::SelfRunner>(m, "SelfRunner")
      .def(py::init<>())
      .def("run", &archaeologist::SelfRunner::run);
}