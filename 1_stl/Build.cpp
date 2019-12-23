// pybind11_exp.cpp
#include "STL.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
namespace py = pybind11;

PYBIND11_MODULE(STL, m) {   // module import name, module object
    // Add a scoped redirect for your noisy code
    m.def("noisy_func", []() {
        py::scoped_ostream_redirect stream(
            std::cout,                               // std::ostream&
            py::module::import("sys").attr("stdout") // Python output
        );
        call_noisy_func();
    });

    m.doc() = "STL tutorial";      // module doc string 
    m.def("randomint1d", &randomint1d);
    m.def("zeros2D", &zeros2D);
}

...

