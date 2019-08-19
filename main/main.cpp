#include <iostream>
#include <string>
#include <memory>
#include "../src/suffix_sort.hpp"
#include "stool/src/print.hpp"
#include "stool/src/sa_bwt_lcp.hpp"
#include "stool/src/cmdline.h"
#include "stool/src/io.hpp"

//#include "stool/src/cmdline.h"
//#include "stool/src/io.hpp"
//#include "repair.hpp"

using namespace std;

void suffix_array_test(vector<uint8_t> &text){
   stool::LO::OnlineBackwardSuffixSort<uint64_t> ss;
   for(int64_t i=text.size()-1;i > 0;i--){
       ss.push((uint64_t)text[i]);
   }

   text.push_back(0);
   vector<uint64_t> sa = stool::constructSA<>(text);
   text.pop_back();



   std::vector<uint64_t> sa2 = ss.to_suffix_array();

}

int main(int argc, char *argv[]){
    
    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file name", true);
    p.parse_check(argc, argv);
    std::string inputFile = p.get<std::string>("input_file");
 
    std::vector<uint8_t> T = stool::load_text_from_file(inputFile); // input text
    std::cout << T.size() << std::endl;
    
    /*
   stool::LO::OnlineBackwardSuffixSort<uint64_t> ss;
   std::string s = "misissippi";
   for(int64_t i=s.size()-1;i > 0;i--){
       ss.push((uint64_t)s[i]);
   }

   std::vector<uint64_t> sa = ss.to_suffix_array();
   stool::Printer::print(sa);
    */
   std::cout << "END" << std::endl;

}