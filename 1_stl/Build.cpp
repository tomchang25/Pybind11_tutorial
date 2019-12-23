// pybind11_exp.cpp
#include "STL.h"

PYBIND11_MODULE(STL, m) {   // module import name, module object
  m.doc() = "STL tutorial";      // module doc string

  m.def("randomint1d", &randomint1d);
  m.def("zeros2D", &zeros2D);
}
