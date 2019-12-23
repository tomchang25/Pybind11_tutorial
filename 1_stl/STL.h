#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <tuple>
using namespace std;

#ifdef USE_PYTHON
    #include <pybind11/pybind11.h>
    namespace py = pybind11;
#endif

void test();
void print(string str);
void write(string str);
vector<int> randomint1D(int low, int high, int size);
vector<vector<int>> zeros2D(tuple<int, int> shape);
