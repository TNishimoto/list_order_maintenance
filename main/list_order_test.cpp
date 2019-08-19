#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <exception>
#include <memory>
#include <map>
#include <set>
#include <forward_list>
#include "../src/MyFunction.cpp"
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
/*
class ListOrderMaintenanceTest
{
public:
	static bool Debug(int seed)
	{
		int num = 100000;
		std::mt19937 mt(seed);
		std::uniform_int_distribution<> rand100(0, (num * 100) - 1);
		ListOrderMap<int, ListOrderMaintenanceTest> mapper;
		int p1 = 0;
		int p2 = 0;
		//auto map = new std::map<int, std::list<LOInt>::iterator>();
		//auto data = new ListOrderMaintenance();
		for (int i = 0; i < num; i++)
		{
			if (i % 1000 == 0)
				std::cout << "+";
			auto x = rand100(mt);
			if (mapper.contains(x))
			{
				mapper.erase(x);
				p1++;
			}
			else
			{
				mapper.add(x);
				p2++;
			}
		}

		int a = -1;
		//LOInt b = 0;
		LOInt p = 0;
		for (auto it : mapper.map)
		{
			if (p >= mapper.getLabel(it.second))
				throw "error";
			if (a > it.first)
				throw "error";
			a = it.first;
			p = mapper.getLabel(it.second);
		}

		std::cout << "end" << std::endl;
		std::cout << p1 << "/" << p2 << std::endl;
		return true;
	}

	static bool Test2(uint64_t num)
	{

		ListOrderMap<int, ListOrderMaintenanceTest> listOrderMap;
		for (uint64_t i = 0; i < num; i++)
		{
			listOrderMap.add(i);
		}

		LOInt p = 0;
		for (auto it : listOrderMap.map)
		{
			if (p >= listOrderMap.getLabel(it.second))
				throw "error";
			p = listOrderMap.getLabel(it.second);
			//std::cout << "(" << it.first << ", " << listOrderMap.getLabel(it.second) << ")" << " ";
		}
		std::cout << "end" << std::endl;
		return true;
	}
};
*/


void test(int num)
{

		std::vector<uint64_t> vec = stool::create_deterministic_integers(num, num * 100, 1);
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
	/*
	for(uint64_t i=0;i<100;i++){

		std::cout << i << std::endl;
	}
	*/
	//const __int128 m = 3329589384618324948;
	//__int128 n = m * m;
	//std::cout << my::to_string(n) << std::endl;
	//my::ListOrderMaintenanceTest::Test3(10000);
	//my::ListOrderMaintenanceTest::Test2(10000);
	//my::ListOrderMaintenanceTest::Debug(10000000);
	//std::cout << "finish" << std::endl;

	return 0;
}