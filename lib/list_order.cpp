#include "../include/list_order.hpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


namespace stool {

namespace lom
{
	/*
	ListOrderMaintenance::ListOrderMaintenance() : _list() {
		this->clear();
	}
	*/
	/*
	void ListOrderMaintenance::clear() {
		this->_list.clear();
		this->labelMaxValue = std::numeric_limits<LOInt>::max() / 4;
		this->_list.push_back(0);
		this->_B = this->_list.begin();
		this->_list.push_back(this->labelMaxValue/2);
	}
	*/
	/*
	LOInt ListOrderMaintenance::getBasicLabel(const std::list<LOInt>::iterator& item) {
		if (item == this->_B) {
			return 0;
		}
		else {
			return this->getDistance(this->_B, item);
		}
	}
	*/
/*
	LOInt ListOrderMaintenance::getStarLabel(const std::list<LOInt>::iterator& item) {
		auto succ = ++std::list<LOInt>::iterator(item);
		if (succ == this->_list.end()) {
			
			return this->labelMaxValue;
		}
		else {
			return this->getBasicLabel(succ);
		}
	}
	*/
/*
	bool ListOrderMaintenance::remove(std::list<LOInt>::iterator& x) {
		this->_list.erase(x);
		return true;
	}
	*/
	/*
	void ListOrderMaintenance::relabeling(const std::list<LOInt>::iterator& x) {
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
	*/
	/*
	const std::list<LOInt>::iterator ListOrderMaintenance::insertAfter(const std::list<LOInt>::iterator& x) {
		if (x == --this->_list.end()) throw "error";
		this->relabeling(x);
		auto succ = ++std::list<LOInt>::iterator(x);

		LOInt y = this->getHalfPosition(x, succ);

		auto ptr = this->_list.insert(succ, y);
		this->errorCheck(ptr);
		this->errorCheck(x);
		return ptr;
	}
	*/
	/*
	bool ListOrderMaintenance::errorCheck() {
		for (auto it = this->_list.begin(); it != this->_list.end(); it++) {
			this->errorCheck(it);
		}
		return true;
	}
	*/
/*
	bool ListOrderMaintenance::errorCheck(const std::list<LOInt>::iterator& x) {
		if (!(this->getBasicLabel(x) < this->getStarLabel(x))) {
			this->print(x);
			throw "error";
		}
		return true;
	}
	*/
	/*
	bool ListOrderMaintenance::errorCheck(const std::list<LOInt>::iterator& start, const std::list<LOInt>::iterator& end) {
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
	*/
	/*
	const std::list<LOInt>::iterator ListOrderMaintenance::insertAfter() {
		return this->insertAfter(this->_B);
	}
	*/
#ifdef _INT128
	/*
	string to_string(__int128_t n)
	{
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
	*/
#endif // !_INT128

/*
string to_string(uint64_t n)
{
	return std::to_string(n);
}
*/
/*
LOInt ListOrderMaintenance::getDistance(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &y) {
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
*/
/*
LOInt ListOrderMaintenance::getHalfPosition(const std::list<LOInt>::iterator &x, const std::list<LOInt>::iterator &succ) {

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
*/
	/*
	const std::list<LOInt>::iterator ListOrderMaintenance::getMinimumIterator() {
		return this->_B;
	}
	const std::list<LOInt>::iterator ListOrderMaintenance::getMaximumIterator() {
		return --this->_list.end();
	}
	*/
}
}