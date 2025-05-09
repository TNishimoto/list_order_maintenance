#include <iostream>
#include <string>
#include <memory>
#include "../include/constructor.hpp"

using namespace std;

template <typename T>
bool load(string &filename, std::vector<T> &output)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);

    if (!file)
    {
        std::cerr << "error reading file " << endl;
        return false;
    }
    file.seekg(0, ios::end);
    auto n = (unsigned long)file.tellg();
    file.seekg(0, ios::beg);

    output.resize(n / sizeof(T));

    file.read((char *)&(output)[0], n);
    file.close();
    file.clear();

    return true;
}

template <typename T>
void mainfunc(std::string input)
{
    auto start = std::chrono::system_clock::now();

    std::vector<T> text;
    std::cout << "Loading Text..." << std::endl;
    load<T>(input, text);


    std::vector<uint64_t> sa = stool::lom::construct_suffix_array(text);
    std::vector<uint64_t> lcp_array = stool::construct_LCP_array(text, sa);

    std::cout << "Computing delta..." << std::flush;
    std::vector<uint64_t> distinct_substring_counter_array = stool::SubstringComplexityFunctions::construct_distinct_substring_counter_array(lcp_array);
    uint64_t delta = stool::SubstringComplexityFunctions::compute_delta(distinct_substring_counter_array);
    std::cout << "[END]" << std::endl;
    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\033[32m";
    std::cout << "______________________INFO______________________" << std::endl;
    std::cout << "File name \t : " << input << std::endl;

    std::cout << "Text length \t : " << text.size() << std::endl;
    std::cout << "Delta \t \t : " << delta << std::endl;
    double charperms = (double)text.size() / elapsed;
    //std::cout << "The number of RLBWT : " << rlbwt.size() << std::endl;
    std::cout << "Excecution time : " << ((uint64_t)elapsed) << "ms";
    std::cout << "[" << charperms << "chars/ms]" << std::endl;

    std::cout << "_______________________________________________________" << std::endl;
    std::cout << "\033[39m" << std::endl;


}

int main(int argc, char *argv[])
{

    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file path", true);
    //p.add<string>("output_file", 'o', "output bwt file path", false, "");
    // p.add<int64_t>("special_character", 's', "special character", false, 0);
    p.add<string>("char_type", 'c', "char_type", true, "u8");

    p.parse_check(argc, argv);
    string inputFile = p.get<string>("input_file");
    //string outputFile = p.get<string>("output_file");
    // int64_t specialCharacter = p.get<int64_t>("special_character");
    string char_type = p.get<string>("char_type");

    /*
    if (outputFile.size() == 0)
    {
        outputFile = inputFile + ".dsa";
    }
    */

    if (char_type == "u8")
    {
        mainfunc<uint8_t>(inputFile);
    }
    else if (char_type == "u16")
    {
        mainfunc<uint16_t>(inputFile);
    }
    else if (char_type == "u32")
    {
        mainfunc<uint32_t>(inputFile);
    }
    else if (char_type == "u64")
    {
        mainfunc<uint64_t>(inputFile);
    }
    else if (char_type == "i8")
    {
        mainfunc<int8_t>(inputFile);
    }
    else if (char_type == "i16")
    {
        mainfunc<int16_t>(inputFile);
    }
    else if (char_type == "i32")
    {
        mainfunc<int32_t>(inputFile);
    }
    else if (char_type == "i64")
    {
        mainfunc<int64_t>(inputFile);
    }
    else
    {
        throw -1;
    }
}