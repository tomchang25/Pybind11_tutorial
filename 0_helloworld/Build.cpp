// pybind11_exp.cpp
#include "HelloWorld.h"

PYBIND11_MODULE(HelloWorld, m) {   // module import name, module object
  m.doc() = "pybind11 example plugin";      // module doc string

  m.def("add",                              // function name
        &add,                               // function pointer
        "A function which adds two numbers" //function doc string
  );

  m.def("echo", &echo, "A function which repeat input");
}
