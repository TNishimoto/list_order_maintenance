#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <random>
#include <chrono>
//#include "divsufsort64.h"
#include "../module/stool/include/cmdline.h"
#include "../include/online_suffix_sort.hpp"
#include "../module/stool/include/print.hpp"

using namespace std;

std::vector<uint8_t> construct_bwt(const std::vector<uint8_t> &text)
{
    std::vector<uint8_t> bwt;
    std::vector<uint64_t> sa;

    uint64_t n = text.size();
    sa.resize(n);

    //divsufsort64((const unsigned char *)&text[0], (int64_t *)&sa[0], n);

    bwt.resize(n);
    for (uint64_t i = 0; i < bwt.size(); i++)
    {
        if (sa[i] == 0)
        {
            bwt[i] = text[n - 1];
        }
        else
        {
            bwt[i] = text[sa[i] - 1];
        }
    }

    return bwt;
}

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
bool write(string filename, std::vector<T> &text)
{
    std::cout << "writing: " << filename << std::endl;
    auto start = std::chrono::system_clock::now();

    ofstream os(filename, ios::out | ios::binary);
    if (!os)
        return 1;
    os.write((const char *)(&text[0]), sizeof(T) * text.size());
    os.close();

    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "wrote: " << filename << ", time = " << elapsed << std::endl;

    return true;
}
template <typename T>
bool write_plain(string filename, std::vector<T> &text)
{
    std::cout << "writing: " << filename << std::endl;
    auto start = std::chrono::system_clock::now();

    std::string outputStr;
    for(uint64_t i=0;i<text.size();i++){
        std::string s = std::to_string(text[i]);
        for(auto c : s){
            outputStr.push_back(c);
        }
        if(i < text.size() -1){
            outputStr.push_back(',');
        }

    }

    ofstream os(filename, ios::out | ios::binary);
    if (!os)
        return 1;
    os.write((const char *)(&outputStr[0]), sizeof(char) * outputStr.size());
    os.close();
    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "wrote: " << filename << ", time = " << elapsed << std::endl;

    return true;
}


template <typename T>
void load_text_build_bwt_write_bwt(string &input, string &output)
{
    std::vector<T> text;
    std::cout << "Loading Text..." << std::endl;
    load<T>(input, text);
    std::cout << "Constructing Suffix Array..." << std::endl;
    std::vector<uint64_t> sa = stool::lom::construct_suffix_array(text);
    std::vector<T> bwt;
    std::cout << "Constructing BWT..." << std::endl;

    bwt.resize(text.size());
    for (uint64_t i = 0; i < text.size(); i++)
    {
        if (sa[i] == 0)
        {
            bwt[i] = text[text.size() - 1];
        }
        else
        {
            bwt[i] = text[sa[i] - 1];
        }
    }
    write_plain(output + ".plain.txt", bwt);
    write<T>(output, bwt);
}
int main(int argc, char *argv[])
{
    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file path", true);
    p.add<string>("output_file", 'o', "output bwt file path", false, "");
    //p.add<int64_t>("special_character", 's', "special character", false, 0);
    p.add<string>("char_type", 'c', "char_type", true, "u8");

    p.parse_check(argc, argv);
    string inputFile = p.get<string>("input_file");
    string outputFile = p.get<string>("output_file");
    //int64_t specialCharacter = p.get<int64_t>("special_character");
    string char_type = p.get<string>("char_type");

    if (outputFile.size() == 0)
    {
        outputFile = inputFile + ".bwt";
    }

    if (char_type == "u8")
    {
        load_text_build_bwt_write_bwt<uint8_t>(inputFile, outputFile);
    }
    else if (char_type == "u16")
    {
        load_text_build_bwt_write_bwt<uint16_t>(inputFile, outputFile);
    }
    else if (char_type == "u32")
    {
        load_text_build_bwt_write_bwt<uint32_t>(inputFile, outputFile);
    }
    else if (char_type == "u64")
    {
        load_text_build_bwt_write_bwt<uint64_t>(inputFile, outputFile);
    }
    else if (char_type == "i8")
    {
        load_text_build_bwt_write_bwt<int8_t>(inputFile, outputFile);
    }
    else if (char_type == "i16")
    {
        load_text_build_bwt_write_bwt<int16_t>(inputFile, outputFile);
    }
    else if (char_type == "i32")
    {
        load_text_build_bwt_write_bwt<int32_t>(inputFile, outputFile);
    }
    else if (char_type == "i64")
    {
        load_text_build_bwt_write_bwt<int64_t>(inputFile, outputFile);
    }
    else
    {
        throw -1;
    }

}
