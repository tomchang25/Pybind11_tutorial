// pybind11_exp.cpp
#include "STL.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(STL, m) {   // module import name, module object
    // redirct stdout to py::stdout
    py::add_ostream_redirect(m);

    m.def("randomint1D", &randomint1D);
    m.def("zeros2D", &zeros2D);
    m.def("test", &test, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());
    m.def("test_pure", &test);
}


