// Copyright 2019 <mmeshcher>

#include "header.hpp"
#include <map>
#include <iostream>
#include <algorithm>

using std::cout;
using boost::filesystem::path;
using boost::filesystem::directory_entry;
using boost::filesystem::directory_iterator;
using std::map;
using std::string;
using std::make_pair;

int main(
    int argc,
    char *argv[]
) {
    path path_to_ftp;
    if (argc == 1) path_to_ftp = (path(argv[0])).parent_path();
    else path_to_ftp = path(argv[1]);

    auto bal = (BrokerImpl { path_to_ftp }).get_result();

    cout << "\nFinish searching.\n\n\nBegin naming best results\n";
    for (auto b : bal) {
        for (auto item : b.second) {
            cout << b.first << "  Account:" << item.first << " files:"
                << item.second.count << " lastdate:" << item.second.date << "\n";
        }
    }
}
