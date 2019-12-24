#include <iostream>
#include <vector>
#include <tuple>

#include "xtensor/xarray.hpp"
#include "xtensor/xrandom.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xadapt.hpp"
#include "xtensor/xio.hpp"
using namespace std;

#ifdef USE_PYTHON

// bind numpy to xtensor
#define FORCE_IMPORT_ARRAY                // numpy C api loading
#include "xtensor-python/pyarray.hpp"     // Numpy bindings
using namespace std;

typedef xt::pyarray<double> DOUBLE_NUMPY;

#else

typedef xt::xarray<double> DOUBLE_NUMPY;

#endif

void test();
DOUBLE_NUMPY sub_val(DOUBLE_NUMPY arr, int num);
DOUBLE_NUMPY plus_arr(DOUBLE_NUMPY arr1, DOUBLE_NUMPY arr2);
DOUBLE_NUMPY repeat(DOUBLE_NUMPY arr, vector<size_t> shape, unsigned time);
DOUBLE_NUMPY RandomCrop(DOUBLE_NUMPY arr, tuple<int,int> shape);


void test(){
    cout << "hello "
         << "world!" << endl;
}


DOUBLE_NUMPY sub_val(DOUBLE_NUMPY arr, int num){
    return arr - num;   
}

DOUBLE_NUMPY plus_arr(DOUBLE_NUMPY arr1, DOUBLE_NUMPY arr2){
    return arr1 + arr2;   
}
DOUBLE_NUMPY repeat(DOUBLE_NUMPY arr,vector<size_t> shape,unsigned time){
    DOUBLE_NUMPY stack_arr(shape);

    auto new_arr = xt::view(arr, xt::newaxis(), xt::all(), xt::all(), xt::all());

    for (unsigned i = 0; i < time; i++){
        stack_arr = xt::concatenate(xtuple(stack_arr, new_arr), 0);
    }

    return stack_arr;
}
/*
DOUBLE_NUMPY RandomCrop(DOUBLE_NUMPY arr, tuple<int,int> shape){
    //TODO: BUG, crop array is not in origin array

    int h = arr.shape(0);
    int w = arr.shape(1);

    int new_h = get<0>(shape) ;
    int new_w = get<1>(shape);

    int top;
    if (h == new_h){
        top = 0;
    }
    else{
        top = rand()%(h - new_h);
    }

    int left;
    if (w == new_w){
        left = 0;
    }
    else{
        left = rand()%(w - new_w);
    }

    cout << top << " " << left << " " << new_h << " " << new_w << " " << endl;
    return xt::view(arr, xt::range(top,top + new_h), xt::range(left,left + new_w));
}
*/
