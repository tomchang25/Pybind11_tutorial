#include "SimpleNumpy.hpp"     // Numpy bindings

using namespace std;
int main(){
    test();
    auto arr1 = xt::xarray<double>({{3, 4}, {5, 6}, {7, 8}});
    auto arr2 = xt::xarray<double>({{-1, -2}, {-3, -4}, {-5, -6}});

    cout << "Array1: " << endl;
    cout << arr1 << endl;
    cout << endl;

    cout << "Array2: " << endl;
    cout << arr2 << endl;
    cout << endl;

    arr1 = sub_val(arr1, 5);
    cout << "Array1 - 5: " << endl;
    cout << arr1 << endl;
    cout << endl;

    auto arr3 = plus_arr(arr1, arr2);
    cout << "Array3 = Array1 + Array2: " << endl;
    cout << arr3 << endl;
    cout << endl;

    cout << "Repeat three time Array3: " << endl;
    cout << repeat(arr3,3) << endl;
    cout << endl;
    
    // WARNING: if you don't specific var type, it will be xt::random array and change
    xt::xarray<double> arr4 = xt::random::randint<int>({10, 10},0,20);
    cout << "Array4: " << endl;
    cout << arr4 << endl;
    cout << endl;

    cout << "Croped array4: " << endl;
    cout << RandomCrop(arr4,{10,4}) << endl;
    cout << endl;
    

    return 0;
}