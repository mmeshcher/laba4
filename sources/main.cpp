// Copyright 2019 <mmeshcher>

#include <header.hpp>
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

// std::map<string, std::map<string, Account>> bal;

// void add_balance(const string& path, const string& dt, const string& id)
// {
//     if (bal.find(path) == bal.end()){
//         bal[path][id] = { Account { dt } };
//         return;
//     }

//     if (bal[path].find(id) == bal[path].end()) {
//         bal[path][id] = { Account { dt } };
//         return;
//     }
//     bal[path][id].count++;
//     if (bal[path][id].date < dt)
//         bal[path][id].date = dt;
// }

// void find_paths(const path& p, const std::string& dir_path) {
//     if(boost::filesystem::is_directory(p))
//     {
//         for(auto& entry : directory_iterator{ p })
//         {
//             if (boost::filesystem::is_directory(entry))
//             {
//                 find_paths(entry, (dir_path.length() > 0 ? dir_path + "/" : dir_path)
//                                    + entry.path().filename().string());
//                 continue;
//             }
//             if (is_right_file(entry.path()))
//             {
//                 auto balance = entry.path().filename().string();
//                 cout << dir_path << " " << balance << std::endl;
//                 add_balance(dir_path, balance.substr(17, 8), balance.substr(8, 8));
//             }
//         }
//     }
// }




int main(
    int argc,
    char *argv[]
) {
    path path_to_ftp;
    if (argc == 1) path_to_ftp = (path(argv[0])).parent_path();
    else path_to_ftp = path(argv[1]);
    // std::string dir_path= "";
    // find_paths(path_to_ftp, dir_path);

    auto bal = (BrokerImpl { path_to_ftp }).get_result();

    cout << "\nFinish searching.\n\n\nBegin naming best results\n";
    for (auto b : bal) {
        for (auto item : b.second) {
            cout << b.first << "  Account:" << item.first << " files:"
                << item.second.count << " lastdate:" << item.second.date << "\n";
        }
    }
}
