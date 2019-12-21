// Copyright 2019 <mmeshcher>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using std::string;
using std::size_t;
using boost::filesystem::path;
#define AccountsMap std::map<string, std::map<string, Account>> 
#define AccountsMapIter std::map<string, std::map<string, Account>>::iterator

struct Account
{
    std::string date;
    size_t count = 0;

    Account() {}

    Account(std::string d)
    {
        date = d;
        count = 1;
    }
};

class BrokerImpl
{
public:
	BrokerImpl() {}

	BrokerImpl(const path& path) {
		m_path = path;
		m_map = resolve(path);
	}

	AccountsMap get_result() {
		return m_map;
	}

	bool is_right_file(path a);
	
	AccountsMap resolve(const path& path);

	void add_balance(const string& path, const string& dt, const string& id);

	void find_paths(const path& p, const std::string& dir_path);

private:

	path m_path;

	AccountsMap m_map;
};

#endif // INCLUDE_HEADER_HPP_
