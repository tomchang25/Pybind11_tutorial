// pybind11_exp.cpp
#include "STL.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(STL, m) {   // module import name, module object
    // redirct stdout to py::stdout
    m.attr("redirect_output") = py::capsule(new py::scoped_output_redirect(...),
    [](void *sor) { delete static_cast<py::scoped_output_redirect *>(sor); });

    m.doc() = "STL tutorial";      // module doc string 
    m.def("randomint1D", &randomint1D);
    m.def("zeros2D", &zeros2D);
    m.def("test", &test);
}

