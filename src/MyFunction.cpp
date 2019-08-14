#include <vector>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <exception>
#include <algorithm>
#include <fstream>
//#include <stdio.h>
//#include <windows.h>
//#include <Psapi.h>      // Psapi.Lib
using namespace std;

//#define DISP_PARAM(n)    (n), ((n) / 1024)
class MyFunction {
public:
	static unique_ptr<string> CreateRandomString(int len, int alphabetSize) {
		vector<char> alphabets;
		alphabets.push_back('a');
		alphabets.push_back('b');
		alphabets.push_back('c');
		alphabets.push_back('d');
		alphabets.push_back('e');


		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, alphabetSize-1);        // [0, 99] 範囲の一様乱数

		auto r = new string();
		for (int i = 0; i < len; i++) {
			r->append(1, alphabets[rand100(mt)]);
		}
		return unique_ptr<string>(r);
	}

	static unique_ptr<string> CreateDeterministicRandomString(int len, int alphabetSize, int seed) {
		vector<char> alphabets;
		alphabets.push_back('a');
		alphabets.push_back('b');
		alphabets.push_back('c');
		alphabets.push_back('d');
		alphabets.push_back('e');


		std::mt19937 mt(seed);     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, alphabetSize - 1);        // [0, 99] 範囲の一様乱数

		auto r = new string();
		for (int i = 0; i < len; i++) {
			r->append(1, alphabets[rand100(mt)]);
		}
		return unique_ptr<string>(r);
	}
	
	static std::pair<int, int> CreateRandomIntegerPair(int seed, int max) {
		std::mt19937 mt(seed);     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, max - 1);        // [0, 99] 範囲の一様乱数

		int a = rand100(mt);
		int b = rand100(mt);
		if (a < b) {
			return std::pair<int, int>(a, b);
		}
		else {
			return std::pair<int, int>(b, a);
		}
	}
	
	static unique_ptr<vector<int>> CreateRandomInteger(int len, int max) {
		
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, max - 1);        // [0, 99] 範囲の一様乱数

		auto p = new vector<int>();

		for (int i = 0; i < len; i++) {
			auto value = rand100(mt);
			p->push_back(value);
		}
		return unique_ptr<vector<int>>(p);
	}
	static int CreateRandomInt(int max, int seed) {

		std::mt19937 mt(seed);     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, max - 1);        // [0, 99] 範囲の一様乱数
		auto value = rand100(mt);
		return value;

	}
	static unique_ptr<vector<int>> CreateDeterministicRandomInteger(int len, int max, int seed) {
		//std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(seed);     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, max - 1);        // [0, max] 範囲の一様乱数

		auto p = new vector<int>();

		for (int i = 0; i < len; i++) {
			auto value = rand100(mt);
			p->push_back(value);
		}
		return unique_ptr<vector<int>>(p);
	}
	static unique_ptr<string> CreateFibonacciWord(int length) {
		string p0 = "a";
		string p1 = "b";
		string p2 = p1 + p0;
		int t = 1;
		while ((int)p2.size() < length)
		{
			p2 = p1 + p0;
			t++;
			p0 = p1;
			p1 = p2;
			std::cout << p2.size() << std::endl;
		}
		return unique_ptr<string>(new string(p2));

	}
	static int LCP(std::string& item1, std::string& item2) {
		auto min = std::min(item1.size(), item2.size());
		int k = 0;
		for (unsigned int i = 0; i < min; i++) {
			if (item1[i] == item2[i]) {
				k++;
			}
			else {
				break;
			}
		}
		return k;
	}
	static unsigned char *getFileContent(char *filename, unsigned long &n, int termin) {
		std::ifstream file(filename);
		if (!file)
		{
			cerr << "error reading file: " << filename << endl;
			exit(EXIT_FAILURE);
		}

		file.seekg(0, ios::end);
		n = (unsigned long)file.tellg();
		if (termin)
			n++;
		file.seekg(0, ios::beg);

		unsigned char *text = new unsigned char[n + 1];

		char c;
		unsigned long i = 0;

		while (file.get(c))
		{
			text[i] = c;//(c=='\n'||c=='\r')?'X':c;
			i++;
		}
		file.close();

		if (termin)
			text[n - 1] = 0;
		text[n] = 0;
		return text;
	}
	static bool CreateSampleFiles() {
		char* file1 = "../../data/dna.50MB";
		auto str = ReadFile(file1);
		auto len = (*str).size();
		Save("../../data/dna.5MB", *str, len / 10);
		Save("../../data/dna.05MB", *str, len / 100);
		Save("../../data/dna.005MB", *str, len / 1000);
		Save("../../data/dna.0005MB", *str, len / 10000);
		return true;
	}
	static bool ReadAndSave(char* filename, int length, char* outputName) {
		auto str = ReadFile(filename);
		return Save(filename, *str, length);

	}
	static bool Save(char* filename, std::string& text) {
		return Save(filename, text, text.size());
	}
	static bool Save(char* filename, std::string& text, int length) {
		std::ofstream ofs(filename);

		for (int i = 0; i < length; i++) {
			ofs << text[i];
		}
		ofs.close();
		return true;
	}
	static bool Save(char* filename, vector<std::string>& text) {
		std::ofstream ofs(filename);

		for (auto it : text) {
			for (unsigned int i = 0; i < it.size(); i++) {
				ofs << it[i];
			}
			ofs << std::endl;
		}
		ofs.close();
		return true;
	}
	static unique_ptr<std::string> ReadFile(char *filename) {
		std::ifstream file(filename);
		if (!file)
		{
			cerr << "error reading file: " << filename << endl;
			exit(EXIT_FAILURE);
		}

		file.seekg(0, ios::end);
		auto n = (unsigned long)file.tellg();
		file.seekg(0, ios::beg);

		char *text = new char[n + 1];

		char c;
		unsigned long i = 0;

		while (file.get(c))
		{
			text[i] = c;//(c=='\n'||c=='\r')?'X':c;
			i++;
		}
		file.close();

		text[n] = 0;
		auto str = new string(text);
		delete[] text;
		return unique_ptr<string>(str);
	}
	static unique_ptr<string> Reverse(string& str) {
		string p = string();
		for (int i = str.size() - 1; i >= 0; i--) {
			p = p + str[i];
		}
		return std::make_unique<string>(p);
	}
	static int LongestCommonSuffix(string& left, string& right) {
		int min_len = std::min(left.size(), right.size());
		int k = 0;
		while (k < min_len) {
			if (left[left.size() - k - 1] == right[right.size() - k - 1]) {
				k++;
			}
			else {
				break;
			}
		}
		return k;
	}
	static int LongestCommonPrefix(string& left, string& right) {
		int min_len = std::min(left.size(), right.size());
		int k = 0;
		while (k < min_len) {
			if (left[k] == right[k]) {
				k++;
			}
			else {
				break;
			}
		}
		return k;
	}
	
	template <class X>
	static void Print(vector<X>& items) {
		std::cout << "[";
		int k = items.size();
		for (unsigned int i = 0; i < items.size(); i++) {
			std::cout << items[i];
			if (i != items.size() - 1) std::cout << ", ";
		}
		std::cout << "]" << std::endl;

	}
	static int Max(vector<int>& items) {
		int k = 0;
		for (auto it : items) {
			if (k < it) k = it;
		}
		return 0;
	}
	
};
class PointerDeletedException : public std::exception
{


};