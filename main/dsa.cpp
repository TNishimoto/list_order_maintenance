#include <iostream>
#include <string>
#include <memory>
#include "../src/online_suffix_sort.hpp"
#include "stool/src/print.hpp"
#include "stool/src/cmdline.h"
#include "stool/src/io.hpp"
#include "stool/src/debug.hpp"

using namespace std;

int main(int argc, char *argv[]){
    
    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file name", true);
    p.add<string>("output_file", 'o', "output file name", false, "");
    
    p.parse_check(argc, argv);
    std::string inputFile = p.get<std::string>("input_file");
    std::string outputFile = p.get<std::string>("output_file");
    if(outputFile.size() == 0){
        outputFile = inputFile + ".sa64";
    }

    auto start = std::chrono::system_clock::now();
    std::vector<uint8_t> text;
    stool::load_vector(inputFile, text, false);
    std::vector<int64_t> dsa = stool::LO::construct_differential_suffix_array(text);
    
    stool::write_vector(outputFile, dsa, false);

    
    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    std::cout << "\033[36m";
    std::cout << "=============RESULT===============" << std::endl;
    std::cout << "File : " << inputFile << std::endl;
    std::cout << "Output file : " << outputFile << std::endl;
    std::cout << "The length of the input text : " << text.size() << std::endl;
    double charperms = (double)text.size() / elapsed;
    //std::cout << "The number of RLBWT : " << rlbwt.size() << std::endl;
    std::cout << "Excecution time : " << ((uint64_t)elapsed) << "ms";
    std::cout << "[" << charperms << "chars/ms]" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "\033[39m" << std::endl;

}