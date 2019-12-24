#include "File.h"

void test(){
    cout << "hello "
         << "world!" << endl;
}

vector<tuple<uint64_t, int>> read_bin(string file_name){
    vector<tuple<uint64_t, int>> data;
    ifstream rf(file_name, ios::binary);
    if (!rf){
        cerr << "File can't open. " << endl;
        return data;
    }

    int16_t buffer;
    uint64_t key = 0;
    while(rf){
        rf.read((char *)&buffer, 2);
        data.push_back({key, buffer});
        key += 1;
    }

    return data;
}

vector<tuple<string,unsigned,unsigned,unsigned,string, uint32_t>> read_csv(string file_name,bool ignore_first){
    vector<tuple<string,unsigned,unsigned,unsigned,string, uint32_t>> data;
    ifstream rf(file_name);
    if (!rf){
        cerr << "File can't open. " << endl;
        return data;
    }

    if (ignore_first){
        char _[256];
        rf.getline(_,256);
    }

    int16_t buffer;
    uint64_t key = 0;
    while(1){
        if (rf.fail() || rf.eof())
            break;

        string key, name;
        unsigned year, month, day;
        uint32_t salary;

        string temp;

        getline(rf, key, ',');

        getline(rf, temp, ',');
        year = stoul(temp);

        getline(rf, temp, ',');
        month = stoul(temp);

        getline(rf, temp, ',');
        day = stoul(temp);

        getline(rf, name, ',');

        getline(rf, temp);
        salary = stoul(temp);

        data.push_back({key, year, month, day, name, salary});
     
        key += 1;
    }

    return data;

}
