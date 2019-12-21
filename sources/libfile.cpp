// Copyright 2019 <mmeshcher>

#include <header.hpp>

using std::string;
using std::size_t;
using std::stoi;
using std::cout;
using boost::filesystem::path;
using boost::filesystem::directory_entry;
using boost::filesystem::directory_iterator;
using std::map;

AccountsMap BrokerImpl::resolve(const path& path) {
	std::string dir_path = "";
    find_paths(path, dir_path);
    return m_map;
}

void BrokerImpl::add_balance(const string& path, const string& dt, const string& id) {
	if (m_map.find(path) == m_map.end()){
        m_map[path][id] = { Account { dt } };
        return;
    }

    if (m_map[path].find(id) == m_map[path].end()) {
        m_map[path][id] = { Account { dt } };
        return;
    }
    m_map[path][id].count++;
    if (m_map[path][id].date < dt)
        m_map[path][id].date = dt;
}

void BrokerImpl::find_paths(const path& p, const std::string& dir_path) {
	if(boost::filesystem::is_directory(p))
    {
        for (auto& entry : directory_iterator{ p })
        {
            if (boost::filesystem::is_directory(entry))
            {
                find_paths(entry, (dir_path.length() > 0 ? dir_path + "/" : dir_path)
                                   + entry.path().filename().string());
                continue;
            }
            if (is_right_file(entry.path()))
            {
                auto balance = entry.path().filename().string();
                cout << dir_path << " " << balance << std::endl;
                add_balance(dir_path, balance.substr(17, 8), balance.substr(8, 8));
            }
        }
    }
}

bool BrokerImpl::is_right_file(path a) {
	if (a.extension().string() != ".txt") return false;
	a = a.stem();
	if (a.extension().string() == ".old") return false;
	string name = a.string();
	if (name.length() != 25) return false;
	size_t pos = name.find("balance");
	if (pos != 0) return false;
	name.erase(name.begin(), name.begin() + 7);
	for (size_t i : {0, 9}) {
		if (name[i] != '_') return false;
		string nums = name.substr(i+1, i+8);
		for (size_t p = 0; p < nums.length(); ++p) {
			if (nums[p]<'0' || nums[p]>'9') return false;
		}
	}
	return true;
}
