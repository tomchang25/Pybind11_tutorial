#include "File.h"

int main(){
    test();
    auto bin = read_bin("./data/1.bin");

    for (auto t : bin){
        auto [key, val] = t;
        cout << key << ": " << val << endl;
    }

    cout << endl;
    auto arr = read_csv("./data/2.csv");

    for (auto t : arr){
        auto [key, year, month, day, name, salary] = t;
        cout << key << ": " << year << "/" << month << "/" << day << "  " << name << "  " << salary << endl;
    }

    return 0;
}