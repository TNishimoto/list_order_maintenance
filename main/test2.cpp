#include <iostream>
#include <string>
#include <memory>
#include <bitset>
#include <cassert>
#include <chrono>
#include "../include/constructor.hpp"


#include <filesystem>

void time_print(std::string msg, double time, uint64_t text_size){
    double comp_charperms = (double)text_size / time;
    std::cout << msg << time << "ms ";
    std::cout << "[" << comp_charperms << "chars/ms]" << std::endl;
}

uint64_t get_alphabet(std::vector<uint8_t> &text){
    std::vector<bool> checker;
    checker.resize(UINT8_MAX, 0);
    for(auto c : text){
        checker[c] = true;
    }

    uint64_t counter = 0;
    for(uint64_t i = 0;i < checker.size();i++){
        if(checker[i]){
            counter++;
        }
    }
    return counter;
}

int main(int argc, char *argv[])
{
#ifdef DEBUG
    std::cout << "\033[41m";
    std::cout << "DEBUG MODE!" << std::endl;
    std::cout << "\e[m" << std::endl;
    // std::cout << "\033[30m" << std::endl;
#endif
#ifdef SLOWDEBUG
    std::cout << "\033[41m";
    std::cout << "SLOWDEBUG MODE!" << std::endl;
    std::cout << "\e[m" << std::endl;
    // std::cout << "\033[30m" << std::endl;
#endif

    cmdline::parser p;

    p.add<std::string>("input_file", 'i', "input file name", true);
    p.parse_check(argc, argv);
    std::string filename = p.get<std::string>("input_file");

    /*
    bool dirCheck = std::__fs::filesystem::is_directory(std::__fs::filesystem::status(filename));
    if (dirCheck)
    {
        throw std::runtime_error("This is a directory");
    }
    */

    std::ifstream tmpInputStream;
    tmpInputStream.open(filename, std::ios::binary);
    std::vector<uint8_t> text;

    stool::IO::load(tmpInputStream, text);


    std::cout << "Build: SA, ISA, LCP Array" << std::endl;
    std::vector<uint64_t> sa;
    std::vector<uint64_t> isa;
    std::vector<uint64_t> lcpArray;
    double sa_elapsed = 0;
    {
        std::chrono::system_clock::time_point start, end;
        start = std::chrono::system_clock::now();
        std::vector<uint64_t> sa1 = stool::lom::construct_suffix_array(text);
        std::vector<uint64_t> isa1 = stool::constructISA(text, sa1);
        std::vector<uint64_t> lcpArray1 = stool::constructLCP(text, sa1);
        end = std::chrono::system_clock::now();
        sa_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        sa.swap(sa1);
        isa.swap(isa1);
        lcpArray.swap(lcpArray1);
    }


    std::cout << "\033[36m";
    std::cout << "=============RESULT===============" << std::endl;
    std::cout << "File : " << filename << std::endl;
    // std::cout << "Output : " << outputFile << std::endl;
    std::cout << "The length of the input text : \t \t" << text.size() << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "\033[39m" << std::endl;
}
