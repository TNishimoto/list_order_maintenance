#include <iostream>
#include <string>
#include <memory>
#include "../include/list_order_map.hpp"
#include "stool/include/light_stool.hpp"


using namespace std;

template <typename T>
	std::vector<T> create_deterministic_integers(uint64_t len, int64_t max, int64_t min, int64_t seed)
	{
		std::mt19937 mt(seed);
		std::uniform_int_distribution<> rand100(0, (max - min) - 1);

		std::vector<T> r;

		for (size_t i = 0; i < len; i++)
		{
			int64_t value = min + rand100(mt);
			r.push_back(value);
		}
		return r;
	}
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

		std::vector<uint64_t> vec = create_deterministic_integers<uint64_t>(num, num * 100, 0, 1);
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