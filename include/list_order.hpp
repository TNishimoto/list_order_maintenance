#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <exception>
#include <memory>
#include <map>
#include <set>
#include <forward_list>
//using namespace std;

namespace stool
{
namespace lom
{


//using LOInt = __int128_t;
using LOInt = uint64_t;
using LOPointer = std::list<LOInt>::iterator;

class ListOrderLessComparer
{
  public:
	bool operator()(const std::list<LOInt>::iterator &left, const std::list<LOInt>::iterator &right) const
	{
		return *left < *right;
	}
};
class ListOrderLessEqualComparer
{
  public:
	bool operator()(const std::list<LOInt>::iterator &left, const std::list<LOInt>::iterator &right) const
	{
		return *left <= *right;
	}
};

class ListOrderMaintenance
{
  private:
	std::list<LOInt> _list;
	std::list<LOInt>::iterator _B;
	LOInt labelMaxValue;
	LOInt getStarLabel(const std::list<LOInt>::iterator &item){
		auto succ = ++std::list<LOInt>::iterator(item);
		if (succ == this->_list.end()) {
			
			return this->labelMaxValue;
		}
		else {
			return this->getBasicLabel(succ);
		}
	}
	bool errorCheck(){
		for (auto it = this->_list.begin(); it != this->_list.end(); it++) {
			this->errorCheck(it);
		}
		return true;
	}
	bool errorCheck(const std::list<LOInt>::iterator& x){
		if (!(this->getBasicLabel(x) < this->getStarLabel(x))) {
			this->print(x);
			throw "error";
		}
		return true;
	}

	bool errorCheck(const std::list<LOInt>::iterator& start, const std::list<LOInt>::iterator& end){
		if (end == this->_list.end()) {
			return this->errorCheck(start, this->_B);
		}
		else {
			auto x = std::list<LOInt>::iterator(start);
			while (true)
			{
				if (x == this->_list.end()) x = this->_B;
				if (this->getBasicLabel(x) >= this->getStarLabel(x)) {
					throw "error";
				}
				if (x == end) break;
				x++;
			}
			return true;
		}
	}
	void print([[maybe_unused]] const std::list<LOInt>::iterator& x){
		/*
		for (auto &v : this->_list) {
			//std::cout << setw(19) << v << " " << std::flush;
			//if (v == *x) { std::cout << "!" << k << std::endl; }
			
		}
		*/
		/*
		std::cout << std::endl;
		std::cout << this->getBasicLabel(x) << "/" << this->getStarLabel(x) << "/" << *x << std::endl;
		std::cout << "max = " << this->labelMaxValue << std::endl;
		*/
	}

	//const std::list<LOInt>::iterator getMinimumIterator();
	//const std::list<LOInt>::iterator getMaximumIterator();
	//LOInt specialMod(LOInt v);

	void relabeling(const std::list<LOInt>::iterator &x){
		auto succ = ++std::list<LOInt>::iterator(x);
		LOInt j = 1;
		LOInt wj = this->getDistance(x, succ);
		while (wj <= j * j)
		{
			succ++;
			j++;
			if (succ == this->_list.end()) succ = this->_B;
			wj = this->getDistance(x, succ);
		}
		LOInt k = 1;
		succ = ++std::list<LOInt>::iterator(x);
		while (k < j) {
			if (succ == this->_list.end()) succ = this->_B;
			LOInt succValue = ((wj / j) * k) + *x;
			*succ = succValue >= this->labelMaxValue ? succValue - this->labelMaxValue : succValue;
			succ++;
			k++;
		}
		
		this->errorCheck(x, succ);
	}
	LOInt getDistance(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &y){
	if (*y > *x) {
		return *y - *x;
	}
	else if (*y < *x) {
		return *y + (this->labelMaxValue - *x + 1);
	}
	else if (y == x) {
		return this->labelMaxValue;
	}
	else {
		throw "error";
	}
}
	LOInt getHalfPosition(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &succ){

	if (*x < *succ) {
		return (*x + *succ) / 2;
	}
	else {
		LOInt half = (this->labelMaxValue - *x + *succ) / 2;
		LOInt total = *x + half;
		if (total >= this->labelMaxValue) {
			return total - this->labelMaxValue;
		}
		else {
			return total;
		}
	}
}

  public:
	LOInt getBasicLabel(const std::list<LOInt>::iterator &item){
		if (item == this->_B) {
			return 0;
		}
		else {
			return this->getDistance(this->_B, item);
		}
	}
	bool remove(std::list<LOInt>::iterator &x){
		this->_list.erase(x);
		return true;
	}
	const std::list<LOInt>::iterator insertAfter(const std::list<LOInt>::iterator &x){
		if (x == --this->_list.end()) throw "error";
		this->relabeling(x);
		auto succ = ++std::list<LOInt>::iterator(x);

		LOInt y = this->getHalfPosition(x, succ);

		auto ptr = this->_list.insert(succ, y);
		this->errorCheck(ptr);
		this->errorCheck(x);
		return ptr;
	}
	const std::list<LOInt>::iterator insertAfter(){
		return this->insertAfter(this->_B);
	}

	bool order(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &y){
		return this->getBasicLabel(x) < this->getBasicLabel(y);
	}

	ListOrderMaintenance() : _list() {
		this->clear();
	}
	virtual ~ListOrderMaintenance()
	{
	}

	void clear(){
		this->_list.clear();
		this->labelMaxValue = std::numeric_limits<LOInt>::max() / 4;
		this->_list.push_back(0);
		this->_B = this->_list.begin();
		this->_list.push_back(this->labelMaxValue/2);
	}
};
#ifdef _INT128
std::string to_string(__int128_t n){
		enum
		{
			base = 10,
			max_width = 39
		};

		char a[max_width + 1] = { '\0' };
		char *p = a + max_width;
		for (; n != 0; n /= base)
			*--p = (char)('0' + n % base);

		return std::string(p);
	}
#endif
std::string to_string(uint64_t n){
	return std::to_string(n);
}

}
}