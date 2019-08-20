#include <iostream>
#include <string>
#include <memory>
#include "../src/online_suffix_sort.hpp"
#include "stool/src/print.hpp"

using namespace std;

template<typename T>
void print(std::vector<T> &text, std::vector<uint64_t> &sa){
    stool::Printer::print("text", text);
    stool::Printer::print("SA  ", sa);

    for(uint64_t i=0;i<sa.size();i++){
        uint64_t p = sa[i];
        std::cout << p << ": ";
        for(uint64_t x=sa[i];x<text.size();x++){
            std::cout << text[x];
            if(x < text.size() - 1){
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    
    std::cout << "char vector" << std::endl;
    std::vector<char> vec1{'m', 'i', 's', 'i', 's', 's', 'i', 'p', 'p', 'i'};
    std::vector<uint64_t> sa1 = stool::LO::construct_suffix_array(vec1);
    print<char>(vec1, sa1);

    std::cout << "uint8_t vector" << std::endl;
    std::vector<uint8_t> vec2{'m', 'i', 's', 'i', 's', 's', 'i', 'p', 'p', 'i'};
    std::vector<uint64_t> sa2 = stool::LO::construct_suffix_array(vec2);
    print<uint8_t>(vec2, sa2);


    std::cout << "int32_t vector" << std::endl;
    std::vector<int32_t> vec3{0, 123, -12, 12, -2, 2, 3, 5, 12, 12, -13};
    std::vector<uint64_t> sa3 = stool::LO::construct_suffix_array(vec3);
    print<int32_t>(vec3, sa3);

    std::cout << "uint32_t vector" << std::endl;
    std::vector<uint32_t> vec4{12, 123, 12, 12, 2, 2, 3, 5, 12, 12, 13};
    std::vector<uint64_t> sa4 = stool::LO::construct_suffix_array(vec4);
    print<uint32_t>(vec4, sa4);

    std::cout << "int64_t vector" << std::endl;
    std::vector<int64_t> vec5{-12, 123, -12, -12, -2, -2, -3, -5, -12, -12, 13};
    std::vector<uint64_t> sa5 = stool::LO::construct_suffix_array(vec5);
    print<int64_t>(vec5, sa5);

    std::cout << "uint64_t vector" << std::endl;
    std::vector<uint64_t> vec6{12, 123, 12, 2, 2, 2, 12, 2, 2, 3, 5, 12, 12, 13};
    std::vector<uint64_t> sa6 = stool::LO::construct_suffix_array(vec6);
    print<uint64_t>(vec6, sa6);


}