// pybind11_exp.cpp
#include "HelloWorld.h"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(HelloWorld, m) {   // module import name, module object
    m.doc() = "pybind11 example plugin";      // module doc string

    m.def("add",                              // function name
        &add,                               // function pointer
        "A function which adds two numbers" //function doc string
    );

    m.def("echo", &echo, "A function which repeat input");
    m.def("test", &test, "A function which repeat input");
}
