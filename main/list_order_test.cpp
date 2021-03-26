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

void print_vec(stool::LO::ListOrderMaintenance &list,std::vector<std::list<stool::LO::LOInt>::iterator> &vec){
    
        std::cout << "[";
		for(uint64_t i=0;i<vec.size();i++){
            std::cout << list.getBasicLabel(vec[i]);
            if(i + 1 != vec.size()){
                std::cout << ", ";
            }
		}
        std::cout << "]";
        std::cout << std::endl;
}

void test()
{
		stool::LO::ListOrderMaintenance list;
        std::vector<std::list<stool::LO::LOInt>::iterator> vec;

        auto ptr1 = list.insertAfter();
        vec.push_back(ptr1);
        auto ptr5 = list.insertAfter(ptr1);
        vec.push_back(ptr5);

        auto ptr3 = list.insertAfter(ptr1);
        vec.insert(vec.begin() + 1,ptr3);

        auto ptr2 = list.insertAfter(ptr1);
        vec.insert(vec.begin() + 1,ptr2);

        auto ptr4 = list.insertAfter(ptr3);
        vec.insert(vec.begin() + 3,ptr4);


        print_vec(list, vec);

        std::cout << "The label of ptr1 pointer = " << list.getBasicLabel(ptr1) << std::endl;
        std::cout << "The label of ptr2 pointer = " << list.getBasicLabel(ptr2) << std::endl;
        std::cout << "ptr1 < ptr2 ? = " << list.order(ptr1, ptr2) << std::endl;
        std::cout << "ptr2 > ptr1 ? = " << list.order(ptr2, ptr1) << std::endl;

        list.remove(ptr3);
        vec.erase(vec.begin() + 2 );
        print_vec(list, vec);

        list.clear();
        vec.clear();



}

int main()
{
	test();

	return 0;
}