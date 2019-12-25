#include <iostream>
using namespace std;

#ifdef USE_PYTHON
    #include <pybind11/pybind11.h>
    namespace py = pybind11;
#endif

int add(int i, int j);
void echo(string str);
void test();
