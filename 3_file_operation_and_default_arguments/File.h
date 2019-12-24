#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

void test();
void test();

vector<tuple<uint64_t, int>> read_bin(string file_name);
vector<tuple<string, unsigned, unsigned, unsigned, string, uint32_t>> read_csv(string file_name, bool ignore_first = true);
