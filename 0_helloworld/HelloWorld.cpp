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
}

void test(){
    print("Hello world!");
}
