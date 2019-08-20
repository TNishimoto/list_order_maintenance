#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <exception>
#include <memory>
#include <map>
#include <set>
#include <forward_list>
#include "../src/list_order_map.hpp"
#include "stool/src/debug.hpp"

using namespace std;


class ListOrderMaintenanceTest
{
	public:
	bool operator()(const uint64_t &a, const uint64_t &b) const
	{
		return a < b;
	}
};


void test(int num)
{

		std::vector<uint64_t> vec = stool::create_deterministic_integers<uint64_t>(num, num * 100, 0, 1);
		stool::LO::ListOrderMap<uint64_t, ListOrderMaintenanceTest> listOrderMap;
		for (auto it : vec)
		{
			if (!listOrderMap.contains(it))
			{
				listOrderMap.add(it);
			}
		}

		std::vector<uint64_t> vec2;

		for (auto it : listOrderMap.map)
		{
			vec2.push_back(it.first);
		}
		for(uint64_t i=1;i<vec2.size();i++){
			if(vec2[i] <= vec2[i-1]){
				throw std::logic_error("Error!");
			}
		}
		std::cout << "OK!" << std::endl;
}

int main()
{
	test(2300);

	return 0;
}