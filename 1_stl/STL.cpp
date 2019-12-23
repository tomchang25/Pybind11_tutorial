#include "STL.h"

vector<int> randomint1D(int low, int high, int size){
    // First create an instance of an engine.
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {low, high};

    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    vector<int> vec(size);
    generate(begin(vec), end(vec), gen);

    return vec;
}

vector<vector<int>> zeros2D(tuple<int,int> shape){
    auto [m,n] = shape;

    return vector<vector<int>>(
    m,
    vector<int>(n,0));
}


int main(){
    for ( const auto &row : randomint1D(-5,88,7) )
    {
        cout << row << " ";
    }
    cout << endl;

    for ( const auto &row : zeros2D({3,4}) )
    {
        for ( const auto &s : row ) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 1;
}