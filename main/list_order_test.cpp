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

namespace my
{
class HeapSort
{
public:
	static uint64_t PROCESSBAR;
	template <typename T, typename COMPARER>
	static void sort(vector<T> &vec)
	{
		std::set<T, COMPARER> set;
		uint64_t count = 0;
		for (auto it : vec)
		{
			set.insert(it);
			count++;
		}
		uint64_t t = 0;
		for (auto it : set)
		{
			vec[t++] = it;
		}
	}
};
uint64_t HeapSort::PROCESSBAR = 100000;
} // namespace my
namespace my
{

class ListOrderMaintenanceTest
{
public:
	bool operator()(const int &a, const int &b) const
	{
		return a < b;
	}
	static bool Debug(int seed)
	{
		int num = 100000;
		std::mt19937 mt(seed);										 //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, (num * 100) - 1); // [0, max] 範囲の一様乱数
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

	static bool Test(int num)
	{

		auto p = MyFunction::CreateDeterministicRandomInteger(num, num * 100, 1);
		ListOrderMap<int, ListOrderMaintenanceTest> listOrderMap;
		for (auto it : *p)
		{
			if (!listOrderMap.contains(it))
			{
				listOrderMap.add(it);
			}
		}

		for (auto it : listOrderMap.map)
		{
			std::cout << it.first << " ";
		}
		std::cout << "end" << std::endl;
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
	static bool Test3(int num)
	{

		auto p = MyFunction::CreateDeterministicRandomInteger(num, num * 100, 1);
		//auto pp = new HeapSort<int, ListOrderMaintenanceTest>();
		HeapSort::sort<int, ListOrderMaintenanceTest>(*p);

		for (auto it : *p)
		{
			std::cout << it << " ";
		}
		std::cout << "end" << std::endl;
		return true;
	}
};



} // namespace my

void test(int num)
{
	std::vector<uint64_t> vec1 = stool::create_deterministic_integers(num, 100, 1);

	std::vector<uint64_t> vec2;
	for(auto &it : vec1){
		vec2.push_back(it);
	}
	std::sort(vec2.begin(), vec2.end());
	my::HeapSort::sort<uint64_t, my::ListOrderMaintenanceTest>(vec1);
	stool::equal_check(vec1, vec2);
}

int main()
{
	test(23);
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