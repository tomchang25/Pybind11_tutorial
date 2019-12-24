// pybind11_exp.cpp
#include "File.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(File, m) {   // module import name, module object
    // redirct stdout to py::stdout
    py::add_ostream_redirect(m);
    m.def("test", &test, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());

    // if you want to use keyword arguments in python, set py::arg
    m.def("read_bin", &read_bin,py::arg("file_name"));

    // Default arguments
    m.def("read_csv", &read_csv,py::arg("file_name"),py::arg("ignore_first") = true);
}
