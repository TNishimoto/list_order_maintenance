#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <exception>
#include <memory>
#include <map>
#include <set>
#include <forward_list>
#include "../include/list_order_map.hpp"
#include "stool/include/debug.hpp"

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
		stool::lom::ListOrderMap<uint64_t, ListOrderMaintenanceTest> listOrderMap;
		for (auto it : vec)
		{
			
			if (!listOrderMap.contains(it))
			{
				std::cout << "Add " << it << " into the map" << std::endl;

				listOrderMap.add(it);
			}else{
				std::cout << "The map already contains " << it << std::endl;
			}
		}

		std::vector<uint64_t> vec2;

		for (auto it : listOrderMap.map)
		{
			vec2.push_back(it.first);
		}
		std::cout << std::endl;
		for(uint64_t i=1;i<vec2.size();i++){			
			if(vec2[i] <= vec2[i-1]){
				throw std::logic_error("Error!");
			}
		}

		std::cout << "The sorted integers in the map are " << std::endl;
		for (auto it : listOrderMap.map)
		{
			std::cout << it.first << "," << std::flush;
		}
		std::cout << std::endl;

		std::cout << "OK!" << std::endl;
}

int main()
{
	test(100);

	return 0;
}