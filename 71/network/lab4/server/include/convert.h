#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <bitset>
#include <sstream>

std::vector<int> split(const std::string& s, const std::string& delim)
{
	std::vector<int> res;
	size_t current_idx = 0;
	while (current_idx != std::string::npos)
	{
		size_t from = s.find_first_not_of(delim, current_idx);
		size_t to = s.find_first_of(delim, from);
		size_t len = std::string::npos;
		if (to != std::string::npos)
		{
			len = to - from;
		}
		int oct = std::stoi(s.substr(from, len));
		res.push_back(oct);
		current_idx = to;
	}
	return res;
}

std::string ip2Bin(std::vector<int> ip)
{
	std::stringstream binAddress;
	for (std::vector<int>::const_iterator i = ip.begin(), end = ip.end(); i != end; i++)
	{
		//std::cout << *i << std::endl;
		if (i == end - 1)
		{
			binAddress << std::bitset<8>(*i);
		}
		else
		{
			binAddress << std::bitset<8>(*i) << ".";
		}
	}
	std::string result(binAddress.str());
	return result;
}

std::string ip2Hex(std::vector<int> ip)
{
	std::stringstream hexAddress;
	for (std::vector<int>::const_iterator i = ip.begin(), end = ip.end(); i != end; i++)
	{
		//std::cout << *i << std::endl;
		if (i == end - 1)
		{
			hexAddress << std::hex << *i;
		}
		else
		{
			hexAddress << std::hex << *i << ".";
		}
	}
	std::string result(hexAddress.str());
	return result;
}

