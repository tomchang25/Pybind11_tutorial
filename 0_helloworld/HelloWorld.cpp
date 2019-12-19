// pybind11_exp.cpp
#include "HelloWorld.h"

void print(string str) {
    #ifndef USE_PYTHON
        cout << str << endl;
    #endif

    #ifdef USE_PYTHON
        py::print(str);
    #endif
}

int add(int i, int j) {
    return i + j;
}

void echo(string str) {
    print(str);

    return;
}

// Test function is work or not
int main(){
    cout << add(1, 3) << endl;
    echo("Hello world");
    return 0;
}