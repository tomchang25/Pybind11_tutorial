// pybind11_exp.cpp
#include "SimpleNumpy.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
namespace py = pybind11;


PYBIND11_MODULE(SimpleNumpy, m) {
    xt::import_numpy();
    // redirct stdout to py::stdout
    py::add_ostream_redirect(m);

    m.def("test", &test, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());
    m.def("sub_val", &sub_val);
    m.def("plus_arr", &plus_arr);
    m.def("repeat", &repeat);
    //m.def("RandomCrop", &RandomCrop);
}


