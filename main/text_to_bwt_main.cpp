#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <random>
#include <chrono>
//#include "divsufsort64.h"
#include "stool/src/cmdline.h"
#include "../src/online_suffix_sort.hpp"
#include "stool/src/print.hpp"

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
void constructOccCharVec(const std::vector<uint8_t> &text, std::vector<bool> &output)
{
    output.resize(256, false);
    for (uint64_t i = 0; i < text.size(); i++)
    {
        output[text[i]] = true;
    }
}
void replace(std::vector<uint8_t> &text, uint8_t oldChar, uint8_t newChar)
{
    for (uint64_t i = 0; i < text.size(); i++)
    {
        if (text[i] == oldChar)
        {
            text[i] = newChar;
        }
    }
}
void sanityze(std::vector<uint8_t> &text)
{
    std::vector<bool> occVec;
    constructOccCharVec(text, occVec);
    if (occVec[0])
    {
        std::cout << "This text contains character 0" << std::endl;
        uint8_t replaceChar = 0;
        for (uint64_t i = 1; i < occVec.size(); i++)
        {
            if (i != 8 && !occVec[i])
            {
                replaceChar = i;
                break;
            }
        }
        if (replaceChar != 0)
        {
            std::cout << "We replace the character 0 with " << (int)replaceChar << "." << std::endl;
            replace(text, 0, replaceChar);
        }
        else
        {
            std::cout << "We cannot replace the character 0." << std::endl;
            throw -1;
        }
    }

    if (occVec[8])
    {
        std::cout << "This text contains character 8" << std::endl;
        uint8_t replaceChar = 8;
        for (uint64_t i = 9; i < occVec.size(); i++)
        {
            if (!occVec[i])
            {
                replaceChar = i;
                break;
            }
        }
        if (replaceChar != 8)
        {
            std::cout << "We replace the character 8 with " << (int)replaceChar << "." << std::endl;
            replace(text, 8, replaceChar);
        }
        else
        {
            std::cout << "We cannot replace the character 8." << std::endl;
            throw -1;
        }
    }
}
template <typename T>
void load_text_build_bwt_write_bwt(string &input, string &output)
{
    std::vector<T> text;
    load<T>(input, text);
    std::vector<uint64_t> sa = stool::LO::construct_suffix_array(text);
    std::vector<T> bwt;
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
    write<T>(output, bwt);
}

int main(int argc, char *argv[])
{
    cmdline::parser p;
    p.add<string>("input_file", 'i', "input file path", true);
    p.add<string>("output_file", 'o', "output bwt file path", false, "");
    //p.add<int64_t>("special_character", 's', "special character", false, 0);
    p.add<string>("char_type", 'c', "char_type", false, "u8");

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
    else
    {
        throw -1;
    }

    /*
    uint8_t sc = 0;
    if(specialCharacter.size() > 0){
        sc = specialCharacter[0];
    }
    std::cout << "Special character: " << sc << "(" << (uint)sc << ")" << std::endl;
    if (outputFile.size() == 0)
    {
            outputFile = inputFile + ".bwt";
    }
    std::vector<uint8_t> text;
    load(inputFile, text);
    sanityze(text);

    text.push_back(sc);
    std::vector<uint8_t> bwt = construct_bwt(text);

    if(bwt.size() < 100){
        std::cout << "Input Text: ";
        for(auto c : text){
            std::cout << c;
        }
        std::cout << std::endl;

        std::cout << "Output BWT: ";
        for(auto c : bwt){
            std::cout << c;
        }
        std::cout << std::endl;
        
    }

    write(outputFile, bwt);
    */
}
