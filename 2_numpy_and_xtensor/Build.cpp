// pybind11_exp.cpp
#include "SimpleNumpy.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

// bind numpy to xtensor
#define FORCE_IMPORT_ARRAY                // numpy C api loading
#include "xtensor-python/pyarray.hpp"     // Numpy bindings

namespace py = pybind11;

PYBIND11_MODULE(SimpleNumpy, m) {
    // redirct stdout to py::stdout
    py::add_ostream_redirect(m);
    xt::import_numpy();

    m.def("test", &test, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());
}


