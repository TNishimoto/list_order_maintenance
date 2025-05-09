#include <iostream>
#include <string>
#include <memory>
#include "../include/constructor.hpp"


//#include "stool/src/cmdline.h"
//#include "stool/src/io.hpp"
//#include "repair.hpp"

using namespace std;

void suffix_array_test(vector<uint8_t> &text){

   vector<uint64_t> sa = stool::construct_naive_SA<uint8_t, uint64_t>(text);
   std::vector<uint64_t> sa2 = stool::lom::construct_suffix_array(text);


    stool::Printer::print("collect",sa);
    stool::Printer::print("test   ",sa2);

    
    stool::equal_check(sa, sa2);
}

int main(int argc, char *argv[]){
    
    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file name", true);
    p.add<string>("type", 'c', "char type", true);
    p.parse_check(argc, argv);
    std::string inputFile = p.get<std::string>("input_file");
    std::string type = p.get<std::string>("type");

    if(type == "8"){
        std::vector<char> T;
        stool::load_vector(inputFile, T, false);    
    }else if(type == "uchar"){
        std::vector<uint8_t> T;
        stool::load_vector(inputFile, T, false);
        suffix_array_test(T);
    }else if(type == "32"){
        std::vector<int32_t> T;
        stool::load_vector(inputFile, T, false);
    }else if(type == "u32"){
        std::vector<uint32_t> T;
        stool::load_vector(inputFile, T, false);
    }else if(type == "64"){
        std::vector<int64_t> T;
        stool::load_vector(inputFile, T, false);
    }else if(type == "u64"){
        std::vector<uint64_t> T;
        stool::load_vector(inputFile, T, false);
    }else{
        throw std::runtime_error("error!");
    }
 
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