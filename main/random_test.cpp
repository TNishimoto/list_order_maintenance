#include <iostream>
#include <string>
#include <memory>
#include "../include/online_suffix_sort.hpp"
#include "stool/include/print.hpp"
#include "stool/include/cmdline.h"
#include "stool/include/io.hpp"
#include "stool/include/debug.hpp"

using namespace std;

template <typename T>
void suffix_array_test(vector<T> &text){
    //stool::Printer::print("text",text);
   vector<uint64_t> sa = stool::construct_naive_SA<T, uint64_t>(text);
   std::vector<uint64_t> sa2 = stool::lom::construct_suffix_array(text);

    //stool::Printer::print("collect",sa);
    //stool::Printer::print("test   ",sa2);    
    stool::equal_check(sa, sa2);
}

int main(int argc, char *argv[]){
    
    cmdline::parser p;
    p.add<uint64_t>("size", 'l', "text length", true);
    p.parse_check(argc, argv);
    uint64_t size = p.get<uint64_t>("size");
    uint64_t loop = 10000;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<char> text = stool::create_deterministic_integers<char>(size, 10, -10, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<uint8_t> text = stool::create_deterministic_integers<uint8_t>(size, 255, 0, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<int32_t> text = stool::create_deterministic_integers<int32_t>(size, 255, -255, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<uint32_t> text = stool::create_deterministic_integers<uint32_t>(size, 510, 0, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<int64_t> text = stool::create_deterministic_integers<int64_t>(size, 1024, -1024, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;

    for(size_t i=0;i<loop;i++){
        if(i %100 == 0) std::cout << "+" << std::flush;
        std::vector<uint64_t> text = stool::create_deterministic_integers<uint64_t>(size, 2048, 0, i);
        suffix_array_test(text);
    }
    std::cout << std::endl;


    /*
   stool::lom::OnlineBackwardSuffixSort<uint64_t> ss;
   std::string s = "misissippi";
   for(int64_t i=s.size()-1;i > 0;i--){
       ss.push((uint64_t)s[i]);
   }

   std::vector<uint64_t> sa = ss.to_suffix_array();
   stool::Printer::print(sa);
    */
   std::cout << "END" << std::endl;

}