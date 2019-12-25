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
DOUBLE_NUMPY repeat(DOUBLE_NUMPY arr, unsigned time);
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

DOUBLE_NUMPY repeat(DOUBLE_NUMPY arr,unsigned time){
    // INFO: It's recommand to convert pyarray to xarray, to get stable result.
    xt::xarray<double> xarr = arr;

    xt::svector<size_t> shape = xarr.shape();
    shape.insert(shape.begin(), 0);
    xt::xarray<double> stack_arr(shape);

    xt::xarray<double> new_arr = xt::view(xarr, xt::newaxis(), xt::all(), xt::all(), xt::all());

    for (unsigned i = 0; i < time; i++){
        stack_arr = xt::concatenate(xtuple(stack_arr, new_arr), 0);
    }

    return stack_arr;
}

DOUBLE_NUMPY RandomCrop(DOUBLE_NUMPY arr, tuple<int,int> shape){
    xt::xarray<double> xarr = arr;

    int h = xarr.shape(0);
    int w = xarr.shape(1);

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

    return xt::view(xarr, xt::range(top,top + new_h), xt::range(left,left + new_w));
}

